#include <iostream>
#include <cstdlib>
#include <cmath>

#include "RenderEngine.h"
#include "Viewport.h"
#include "FreeglutDraw.h"

//////////////////////////////////////////////////////////////////////

extern USHORT WINDOW_W = 800;
extern USHORT WINDOW_H = 600;

int main(int argc, char ** argv)
{  
  Scene scene;
  scene.LoadScene(Scene_sphere);
  
  const uint32_t maxSamples = 100000;

  RenderSettings   rendSett(WINDOW_W, WINDOW_H, maxSamples, SamplingMethod::SOBOL);
  ViewportSettings viewSett(WINDOW_W, WINDOW_H);

  RenderFunction renderFunc(rendSett, scene, G_RESULT_POINTS);
  Viewport viewport(viewSett, renderFunc);
  viewport.Draw();


  glutInit(&argc, argv);
  glutInitWindowSize(WINDOW_W, WINDOW_H);
  glutInitWindowPosition((2048 - WINDOW_W)/2, (1024 - WINDOW_H)/2);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  
  glutCreateWindow("Simple render");
  
  glutReshapeFunc (resize);
  glutDisplayFunc (display);
  glutIdleFunc    (idle);
  glutKeyboardFunc(key);
  glutMouseFunc   (mouse_button);
  glutMotionFunc  (mouse_motion);
  
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  
  glutMainLoop();
  
  return 0; // never reached
}