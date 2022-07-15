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



float3 Scene_sphere(std::vector<float>& a_rnd)
{
  const float2 rnd = { a_rnd[0], a_rnd[1] };
  float3 deviation;

  const float u = rnd.x * TWOPI - PI;
  const float v = rnd.y * PI - HALFPI;

  deviation.x = cos(u) * cos(v);
  deviation.y = sin(u) * cos(v);
  deviation.z = sin(v);

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

  const float u = rnd.x * 8.0F * PI;
  const float v = rnd.y * TWOPI - PI;

  deviation.x = u * cos(u) * (cos(v) + 1.0F);
  deviation.y = u * sin(v) - powf((u + 3) / 8.0F * PI, 2) + 100.0F;
  deviation.z = u * sin(u) * (cos(v) + 1.0F);

  deviation.y -= 20.0F; // offset in center coord

  return deviation * 0.02F;
}


float3 Scene_Shamrock(std::vector<float>& a_rnd)
{
  const float2 rnd = { a_rnd[0], a_rnd[1] };
  float3 deviation;

  const float u = rnd.x * 4.0F * PI - TWOPI;
  const float v = rnd.y * TWOPI - PI;

  deviation.x = cos(u) * cos(v) + 3.0F * cos(u) * (1.5F + sin(1.5F * u) / 2.0F);
  deviation.y = sin(u) * cos(v) + 3.0F * sin(u) * (1.5F + sin(1.5F * u) / 2.0F);
  deviation.z = sin(v) + 2.0F * cos(1.5F * u);

  return deviation * 0.15F;
}


float3 Scene_DiniSurface(std::vector<float>& a_rnd)
{
  const float2 rnd = { a_rnd[0], a_rnd[1] };
  float3 deviation;

  const float u = rnd.x * 4.0F * PI;
  const float v = rnd.y * 2.0F + 0.001F;

  deviation.x = cos(u) * sin(v);
  deviation.y = sin(u) * sin(v);
  deviation.z = cos(v) + log(tan(v / 2.0F)) + 0.2F * u - 4.0F;

  deviation.z += 4.0F; // offset in center coord

  return deviation * 0.5F;
}

float3 Scene_Surface01(std::vector<float>& a_rnd)
{
  const float2 rnd = { a_rnd[0], a_rnd[1] };
  float3 deviation;

  const float u = rnd.x * (2.0F + PI) - PI;
  const float v = rnd.y * TWOPI - PI;

  deviation.x = u * sin(v);
  deviation.y = u * cos(v);
  deviation.z = u * sin(u) * sin(u);
  
  return deviation * 0.3F;
}
