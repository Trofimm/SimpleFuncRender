#include "Math.h"
#include "Brdf.h"

float TestGGX(const float alpha, const float theta_o, const float theta, const float phi)
{
  // view vector
  const float3 v(sin(theta_o), 0.0f, cos(theta_o));

  // masking
  const float a       = 1.0f / (alpha * tan(theta_o));
  const float Lambda  = (-1.0f + sqrt(1.0f + 1.0f / a * a)) / 2.0f;
  const float G       = 1.0f / (1.0f + Lambda);

  // reflected vector
  const float3 l(cos(phi)*sin(theta), sin(phi)*sin(theta), cos(theta));
  // half vector
  const float3 h = (v + l) / normalize(v + l);

  // GGX distribution
  float D = 0.0f;

  if (h.z > 0.0f)
  {
    // angle associated with H
    const float theta_h = acos(h.z);
    D = 1.0f / pow(1.0f + pow(tan(theta_h) / alpha, 2), 2);
    D = D / (PI * alpha*alpha * pow(h.z, 4));
  }

    
  // display integral (should be 1)
  const float color = sin(theta) * D * G / abs(4.0f * v.z);

  return color;
}
