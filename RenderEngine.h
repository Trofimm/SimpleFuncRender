#pragma once
#include "Scene.h"
#include "Sampling.h"
#include "IRenderEngine.h"

//////////////////////////////////////////////////////////////////////////


struct RenderSettings 
{
  explicit RenderSettings(const USHORT width, const USHORT height, const UINT maxSample, 
                          const SamplingMethod sampMtd) :
    m_width(width),
    m_height(height),
    m_maxSamples(maxSample),
    m_sampMtd(sampMtd)  {}  

  USHORT         m_width      = 512;
  USHORT         m_height     = 512;
  UINT           m_maxSamples = 16000;
  SamplingMethod m_sampMtd    = SamplingMethod::UNIFORM;
};



class RenderFunction : public IRenderEngine
{
  public:
  explicit RenderFunction(RenderSettings& rendSett, Scene& scene, std::vector<float3>& points);
    
  void Render() override;
   

private:
  RenderSettings&      m_rendSett;
  Scene&               m_scene;  
  std::vector<float3>& m_points;
};

