#include "Math.h"
#include "Scene.h"

/////////////////////////////////////////////////////////

float3 Scene_plane(std::vector<float>& a_rnd)
{
  float3 deviation;
  const float2 rnd = { a_rnd[0], a_rnd[1] };

  deviation.x      = rnd.x * 2.0F - 1.0F;
  deviation.y      = 0.0F;
  deviation.z      = rnd.y * 2.0F - 1.0F;

  return deviation;
}


float3 Scene_volumeCube(std::vector<float>& a_rnd)
{
  float3 deviation;
  const float3 rnd = { a_rnd[0], a_rnd[1], a_rnd[3] };

  deviation.x      = rnd.x * 2.0F - 1.0F;
  deviation.y      = rnd.y * 2.0F - 1.0F;
  deviation.z      = rnd.z * 2.0F - 1.0F;

  return deviation;
}


float3 Scene_BRDF_Diffuse(std::vector<float>& a_rnd)
{
  float3 deviation;
  const float2 rnd = { a_rnd[0], a_rnd[1] };

  float phi        = TWOPI * rnd.x;
  float theta      = rnd.y;
  float h          = sqrt(1.0F - theta * theta);
  deviation.x      = cos(phi) * h;
  deviation.y      = theta;
  deviation.z      = sin(phi) * h;

  return deviation;
}


float3 Scene_BRDF_DiffuseImportance(std::vector<float>& a_rnd)
{
  float3 deviation;
  const float2 rnd = { a_rnd[0], fmax(a_rnd[1], 1e-6F) };

  const float phi      = TWOPI * rnd.x;
  const float cosTheta = pow(rnd.y, 1.0F / (E + 1.0F));
  const float sinTheta = sqrt(1.0F - cosTheta * cosTheta);  
  deviation.x          = cos(phi) * sinTheta;
  deviation.y          = cosTheta;
  deviation.z          = sin(phi) * sinTheta;

  return deviation;
}


float3 Scene_BRDF_PhongImportance(std::vector<float>& a_rnd)
{
  float3 deviation;
  const float2 rnd     = { a_rnd[0], fmax(a_rnd[1], 1e-6F) };

  const float cosPower = 10.0F;
  
  const float phi      = TWOPI * rnd.x;
  const float sinTheta = sqrt(1.0F - pow(rnd.y, 2.0F / (cosPower + 1.0F)));
  const float cosTheta = pow(rnd.y, 1.0F / (cosPower + 1.0F));
  
  deviation.x          = cos(phi) * sinTheta;
  deviation.y          = cosTheta;
  deviation.z          = sin(phi) * sinTheta;

  return deviation;
}


float3 Scene_BRDF_GGXImportance(std::vector<float>& a_rnd)
{
  const float2 rnd = { a_rnd[0], fmax(a_rnd[1], 1e-6F) };
  float3 deviation;

  const float roughness = 0.5f; // [0-1]

  const float phi       = TWOPI * rnd.x;
  const float cosTheta  = sqrt((1.0F - rnd.y) / (1.0F + roughness * roughness * rnd.y - rnd.y));
  const float sinTheta  = sqrt(1.0F - cosTheta * cosTheta);
  deviation.x           = sinTheta * cos(phi);
  deviation.y           = cosTheta;
  deviation.z           = sinTheta * sin(phi);

  return deviation;
}


float3 Scene_Sin(std::vector<float>& a_rnd)
{
  const float2 rnd = { a_rnd[0], a_rnd[1] };
  float3 deviation;

  deviation.x = rnd.x - 0.5F;
  deviation.y = sin(rnd.x * PI * 3.0F);
  deviation.z = rnd.y;

  return deviation;
}


float3 Scene_SeaShell(std::vector<float>& a_rnd)
{
  const float2 rnd = { a_rnd[0], a_rnd[1] };
  float3 deviation;

  const float u = rnd.x * 8 * PI;
  const float v = rnd.y * TWOPI - PI;

  deviation.x = u * cos(u) * (cos(v) + 1.0F);
  deviation.y = u * sin(v) - powf((u + 3) / 8.0F * PI, 2) + 100.0F;
  deviation.z = u * sin(u) * (cos(v) + 1.0F);

  return deviation * 0.02F;
}



