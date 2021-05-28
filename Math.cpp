#include "Math.h"


//////////////////////////////////////////////////

float Distance(point2 a, point2 b)
{
  const float x = b.x - a.x;
  const float y = b.y - a.y;
  const float result = sqrtf(x * x + y * y);
  return result;
}

void SimpleCompress(float3 &outColor)
{
  outColor.x /= (1.0f + outColor.x);
  outColor.y /= (1.0f + outColor.y);
  outColor.z /= (1.0f + outColor.z);
}

void Clamp(float3 & outColor)
{
  if (outColor.x > 1.0f) outColor.x = 1.0f;
  if (outColor.y > 1.0f) outColor.y = 1.0f;
  if (outColor.z > 1.0f) outColor.z = 1.0f;
}

void ClampMinMax(float & a)
{
  if      (a > 1.0f) a = 1.0f;
  else if (a < 0.0f) a = 0.0f;
}

inline vec3 rotate_x(vec3 v, float sin_ang, float cos_ang)
{
  return vec3(
    v.x,
    (v.y * cos_ang) + (v.z * sin_ang),
    (v.z * cos_ang) - (v.y * sin_ang)
  );
}

inline vec3 rotate_y(vec3 v, float sin_ang, float cos_ang)
{
  return vec3(
    (v.x * cos_ang) + (v.z * sin_ang),
    v.y,
    (v.z * cos_ang) - (v.x * sin_ang)
  );
}

float dot(const vec2 & u, const vec2 & v) { return { u.x*v.x + u.y*v.y }; }
vec2  VectorFromPoint(const point2 & a, const point2 & b) { return { a.x - b.x, a.y - b.y }; }
vec2  NormalToVect(const vec2 & a) { return { a.y * (-1.0f), a.x }; }



