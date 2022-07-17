#pragma once
#include "freeglut/include/GL/freeglut.h"

#include "IView.h"
#include "IRenderEngine.h"

//////////////////////////////////////////////////////////////////////////


struct ViewportSettings
{
  explicit ViewportSettings(const USHORT width, const USHORT height) :
    m_width(width),
    m_height(height) {}

  USHORT m_width;
  USHORT m_height;  
};



class Viewport : public IViewport
{
public:
  Viewport(ViewportSettings& viewSett, IRenderEngine& rendEngine);

  void Draw() override;


private:
  ViewportSettings& m_viewSett;
  IRenderEngine&    m_rendEngine;
};


