#include "Viewport.h"
#include "RenderEngine.h"

//////////////////////////////////////////////////////////////////


Viewport::Viewport(ViewportSettings& viewSett, IRenderEngine& rendEngine):
  m_viewSett(viewSett),
  m_rendEngine(rendEngine) {}



void Viewport::Draw()
{
  m_rendEngine.Render();
}



