#pragma once
/* Arcball, written by Bradley Smith, March 24, 2006
 * arcball.h is free to use and modify for any purpose, with no
 * restrictions of copyright or license.
 *
 * Using the arcball:
 *   Call arcball_setzoom after setting up the projection matrix.
 *
 *     The arcball, by default, will act as if a sphere with the given
 *     radius, centred on the origin, can be directly manipulated with
 *     the mouse. Clicking on a point should drag that point to rest under
 *     the current mouse position. eye is the position of the eye relative
 *     to the origin. up is unused.
 *
 *     Alternatively, pass the value: (-radius/|eye|)
 *     This puts the arcball in a mode where the distance the mouse moves
 *     is equivalent to rotation along the axes. This acts much like a
 *     trackball. (It is for this mode that the up vector is required,
 *     which must be a unit vector.)
 *
 *     You should call arcball_setzoom after use of gluLookAt.
 *     gluLookAt(eye.x,eye.y,eye.z, ?,?,?, up.x,up.y,up.z);
 *     The arcball derives its transformation information from the
 *     openGL projection and viewport matrices. (modelview is ignored)
 *
 *     If looking at a point different from the origin, the arcball will still
 *     act as if it centred at (0,0,0). (You can use this to translate
 *     the arcball to some other part of the screen.)
 *
 *   Call arcball_start with a mouse position, and the arcball will
 *     be ready to manipulate. (Call on mouse button down.)
 *   Call arcball_move with a mouse position, and the arcball will
 *     find the rotation necessary to move the start mouse position to
 *     the current mouse position on the sphere. (Call on mouse move.)
 *   Call arcball_rotate after resetting the modelview matrix in your
 *     drawing code. It will call glRotate with its current rotation.
 *   Call arcball_reset if you wish to reset the arcball rotation.
 */

#include "freeglut/include/GL/freeglut.h"
#include "Math.h"

//////////////////////////////////////////////////////////////////////////


struct Camera
{   
  Camera() = default;

  explicit Camera(const vec3& eye, const vec3& centre, const vec3& up) : m_eye(eye), m_centre(centre), m_up(up)  
  {
    arcball_reset();
  }

    
  vec3 m_eye    = { 0.0F, 5.0F, 5.0F };  // (50.0F, 0.0F, 0.0F) side, (0.1F, 50.0F, 0.0F) top.
  vec3 m_centre = { 0.0F,  0.0F, 0.0F };
  vec3 m_up     = { 0.0F,  1.0F, 0.0F };

  // Arcball

  void arcball_setzoom(float radius, vec3 eye, vec3 up);
  void arcball_rotate() const;
  void arcball_reset();
  void arcball_start(int mx, int my);
  void arcball_move(int mx, int my);

  const float SPHERE_RADIUS      = 1.0F;
  const int   SPHERE_LAT_SLICES  = 12;
  const int   SPHERE_LONG_SLICES = 24;

  GLfloat ab_quat[16]  = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
  GLfloat ab_last[16]  = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
  GLfloat ab_next[16]  = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };

  // the distance from the origin to the eye
  GLfloat ab_zoom      = 1.0;
  GLfloat ab_zoom2     = 1.0;

  // the radius of the arcball
  GLfloat ab_sphere    = 1.0;
  GLfloat ab_sphere2   = 1.0;

  // the distance from the origin of the plane that intersects
  // the edge of the visible sphere (tangent to a ray from the eye)
  GLfloat ab_edge      = 1.0;

  // whether we are using a sphere or plane
  bool ab_planar       = false;
  GLfloat ab_planedist = 0.5;

  vec3 ab_start        = vec3(0, 0, 1);
  vec3 ab_curr         = vec3(0, 0, 1);
  vec3 ab_eye          = vec3(0, 0, 1);
  vec3 ab_eyedir       = vec3(0, 0, 1);
  vec3 ab_up           = vec3(0, 1, 0);
  vec3 ab_out          = vec3(1, 0, 0);

  GLdouble ab_glp[16]  = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
  GLdouble ab_glm[16]  = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
  int ab_glv[4]        = { 0,0,640,480 };
};


static Camera G_CAMERA;
