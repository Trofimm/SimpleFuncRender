#pragma once
#include "Scene.h"
#include "Sampling.h"

//////////////////////////////////////////////////////////////////////////

static std::vector<float3> G_RESULT_POINTS;

struct RenderSettings 
{
  explicit RenderSettings(const USHORT width, const USHORT height, const UINT maxSample, 
                          const SamplingMethod sampMtd) :
    m_maxSamples(maxSample),
    m_sampMeth(sampMtd)  {}  

  SamplingMethod m_sampMeth   = SamplingMethod::UNIFORM;
  UINT           m_maxSamples = 16000;
};



struct RenderEngine
{
  public:

  explicit RenderEngine(RenderSettings& rendSett, Scene& scene);
    
  void Render();
   

private:
  RenderSettings&     m_rendSett;
  Scene&              m_scene;  
};


//////////////////////////////////////////////////////
// GLUT Callbacks
//////////////////////////////////////////////////////

void display();
void key(unsigned char key, int x, int y);
void idle();
void resize(int w, int h);
void mouse_button(const int button, const int state, const int x, const int y);
void mouse_motion(const int x, const int y);
