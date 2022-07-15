#pragma once
#include <vector>
#include <functional>
#include "Math.h"
#include "Camera.h"

//////////////////////////////////////////////////////////////////


struct Scene
{ 
public:
  Scene() = default;

  void LoadScene(const std::function<float3(std::vector<float>& a_rnd)>& func) { m_func = func; }
  float3 Eval(std::vector<float>& a_rnd) const { return m_func(a_rnd); }

  Camera m_camera;

private:
  std::function<float3(std::vector<float>& a_rnd)> m_func; 
};


float3 Scene_plane                 (std::vector<float>& a_rnd); 
float3 Scene_sphere                (std::vector<float>& a_rnd); 
float3 Scene_volumeCube            (std::vector<float>& a_rnd);
float3 Scene_BRDF_Diffuse          (std::vector<float>& a_rnd);
float3 Scene_BRDF_DiffuseImportance(std::vector<float>& a_rnd);
float3 Scene_BRDF_PhongImportance  (std::vector<float>& a_rnd);
float3 Scene_BRDF_GGXImportance    (std::vector<float>& a_rnd);
float3 Scene_Sin                   (std::vector<float>& a_rnd);
float3 Scene_SeaShell              (std::vector<float>& a_rnd);
float3 Scene_Shamrock              (std::vector<float>& a_rnd);
float3 Scene_DiniSurface           (std::vector<float>& a_rnd);
float3 Scene_Surface01             (std::vector<float>& a_rnd);

