#include "Scene.h"


/////////////////////////////////////////////////////////



// convert the quaternion into a rotation matrix
static void quaternion(GLfloat* q, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  GLfloat x2 = x * x;
  GLfloat y2 = y * y;
  GLfloat z2 = z * z;
  GLfloat xy = x * y;
  GLfloat xz = x * z;
  GLfloat yz = y * z;
  GLfloat wx = w * x;
  GLfloat wy = w * y;
  GLfloat wz = w * z;

  q[0]  = 1 - 2 * y2 - 2 * z2;
  q[1]  = 2 * xy + 2 * wz;
  q[2]  = 2 * xz - 2 * wy;
        
  q[4]  = 2 * xy - 2 * wz;
  q[5]  = 1 - 2 * x2 - 2 * z2;
  q[6]  = 2 * yz + 2 * wx;
        
  q[8]  = 2 * xz + 2 * wy;
  q[9]  = 2 * yz - 2 * wx;
  q[10] = 1 - 2 * x2 - 2 * y2;
}


// reset the rotation matrix
static void quatidentity(GLfloat* q)
{
  q[0]  = 1;  q[1] = 0;  q[2] = 0;  q[3] = 0;
  q[4]  = 0;  q[5] = 1;  q[6] = 0;  q[7] = 0;
  q[8]  = 0;  q[9] = 0;  q[10] = 1; q[11] = 0;
  q[12] = 0; q[13] = 0; q[14] = 0; q[15] = 1;
}


// copy a rotation matrix
static void quatcopy(GLfloat* dst, GLfloat* src)
{
  dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
  dst[4] = src[4]; dst[5] = src[5]; dst[6] = src[6];
  dst[8] = src[8]; dst[9] = src[9]; dst[10] = src[10];
}


// multiply two rotation matrices
static void quatnext(GLfloat* dest, GLfloat* left, GLfloat* right)
{
  dest[0]  = left[0] * right[0] + left[1] * right[4] + left[2] * right[8];
  dest[1]  = left[0] * right[1] + left[1] * right[5] + left[2] * right[9];
  dest[2]  = left[0] * right[2] + left[1] * right[6] + left[2] * right[10];
  dest[4]  = left[4] * right[0] + left[5] * right[4] + left[6] * right[8];
  dest[5]  = left[4] * right[1] + left[5] * right[5] + left[6] * right[9];
  dest[6]  = left[4] * right[2] + left[5] * right[6] + left[6] * right[10];
  dest[8]  = left[8] * right[0] + left[9] * right[4] + left[10] * right[8];
  dest[9]  = left[8] * right[1] + left[9] * right[5] + left[10] * right[9];
  dest[10] = left[8] * right[2] + left[9] * right[6] + left[10] * right[10];
}


// find the intersection with the plane through the visible edge
static vec3 edge_coords(vec3 m, Camera& a_cam)
{
  // find the intersection of the edge plane and the ray
  float t = (a_cam.ab_edge - a_cam.ab_zoom) / (a_cam.ab_eyedir * m);
  vec3 a = a_cam.ab_eye + (m * t);
  // find the direction of the eye-axis from that point
  // along the edge plane
  vec3 c = (a_cam.ab_eyedir * a_cam.ab_edge) - a;

  // find the intersection of the sphere with the ray going from
  // the plane outside the sphere toward the eye-axis.
  float ac = (a * c);
  float c2 = (c * c);
  float q = (0.0 - ac - sqrt(ac * ac - c2 * ((a * a) - a_cam.ab_sphere2))) / c2;

  return (a + (c * q)).unit();
}


// find the intersection with the sphere
static vec3 sphere_coords(GLdouble mx, GLdouble my, Camera& a_cam)
{
  GLdouble ax, ay, az;

  gluUnProject(mx, my, 0, a_cam.ab_glm, a_cam.ab_glp, a_cam.ab_glv, &ax, &ay, &az);
  vec3 m       = vec3((float)ax, (float)ay, (float)az) - a_cam.ab_eye;

  // mouse position represents ray: eye + t*m
  // intersecting with a sphere centered at the origin
  GLfloat a    = m * m;
  GLfloat b    = (a_cam.ab_eye * m);
  GLfloat root = (b * b) - a * (a_cam.ab_zoom2 - a_cam.ab_sphere2);
  if (root <= 0) return edge_coords(m, a_cam);
  GLfloat t    = (0.0 - b - sqrt(root)) / a;
  return (a_cam.ab_eye + (m * t)).unit();
}


// get intersection with plane for "trackball" style rotation
static vec3 planar_coords(GLdouble mx, GLdouble my, Camera& a_cam)
{
  GLdouble ax, ay, az;

  gluUnProject(mx, my, 0, a_cam.ab_glm, a_cam.ab_glp, a_cam.ab_glv, &ax, &ay, &az);
  vec3 m    = vec3((float)ax, (float)ay, (float)az) - a_cam.ab_eye;
  // intersect the point with the trackball plane
  GLfloat t = (a_cam.ab_planedist - a_cam.ab_zoom) / (a_cam.ab_eyedir * m);
  vec3 d    = a_cam.ab_eye + m * t;

  return vec3(d * a_cam.ab_up, d * a_cam.ab_out, 0.0);
}


void Camera::arcball_setzoom(float radius, vec3 eye, vec3 up)
{
  ab_eye         = eye; // store eye vector
  ab_zoom2       = ab_eye * ab_eye;
  ab_zoom        = sqrt(ab_zoom2); // store eye distance
  ab_sphere      = radius; // sphere radius
  ab_sphere2     = ab_sphere * ab_sphere;
  ab_eyedir      = ab_eye * (1.0 / ab_zoom); // distance to eye
  ab_edge        = ab_sphere2 / ab_zoom; // plane of visible edge

  if (ab_sphere <= 0.0) // trackball mode
  {
    ab_planar    = true;
    ab_up        = up;
    ab_out       = (ab_eyedir ^ ab_up);
    ab_planedist = (0.0 - ab_sphere) * ab_zoom;
  }
  else
    ab_planar    = false;

  glGetDoublev(GL_PROJECTION_MATRIX, ab_glp);
  glGetIntegerv(GL_VIEWPORT, ab_glv);
}


// affect the arcball's orientation on openGL
void Camera::arcball_rotate() const { glMultMatrixf(ab_quat); }


// reset the arcball
void Camera::arcball_reset()
{
  quatidentity(ab_quat);
  quatidentity(ab_last);
}


// begin arcball rotation
void Camera::arcball_start(int mx, int my)
{
  // saves a copy of the current rotation for comparison
  quatcopy(ab_last, ab_quat);
  if (ab_planar) ab_start = planar_coords((GLdouble)mx, (GLdouble)my, *this);
  else ab_start           = sphere_coords((GLdouble)mx, (GLdouble)my, *this);
}


// update current arcball rotation
void Camera::arcball_move(int mx, int my)
{
  if (ab_planar)
  {
    ab_curr       = planar_coords((GLdouble)mx, (GLdouble)my, *this);
    if (ab_curr.equals(ab_start)) return;

    // d is motion since the last position
    vec3 d        = ab_curr - ab_start;

    GLfloat angle = d.length() * 0.5;
    GLfloat cosa  = cos(angle);
    GLfloat sina  = sin(angle);
    // p is perpendicular to d
    vec3 p        = ((ab_out * d.x) - (ab_up * d.y)).unit() * sina;

    quaternion(ab_next, p.x, p.y, p.z, cosa);
    quatnext(ab_quat, ab_last, ab_next);
    // planar style only ever relates to the last point
    quatcopy(ab_last, ab_quat);
    ab_start      = ab_curr;

  }
  else {
    ab_curr       = sphere_coords((GLdouble)mx, (GLdouble)my, *this);
    if (ab_curr.equals(ab_start))
    { // avoid potential rare divide by tiny
      quatcopy(ab_quat, ab_last);
      return;
    }

    // use a dot product to get the angle between them
    // use a cross product to get the vector to rotate around
    GLfloat cos2a = ab_start * ab_curr;
    GLfloat sina  = sqrt((1.0 - cos2a) * 0.5);
    GLfloat cosa  = sqrt((1.0 + cos2a) * 0.5);
    vec3 cross    = (ab_start ^ ab_curr).unit() * sina;
    quaternion(ab_next, cross.x, cross.y, cross.z, cosa);

    // update the rotation matrix
    quatnext(ab_quat, ab_last, ab_next);
  }
}

