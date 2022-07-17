#include <iostream>
#include <cstdlib>
#include <cmath>

#include "RenderEngine.h"
#include "Viewport.h"
#include "Window.h"

//////////////////////////////////////////////////////////////////////


int main(int argc, char ** argv)
{  
  glutInit(&argc, argv);
  const auto screenWidth  = (USHORT)(glutGet(GLUT_SCREEN_WIDTH));
  const auto screenHeight = (USHORT)(glutGet(GLUT_SCREEN_HEIGHT));

  Scene scene;
  scene.LoadScene(Scene_SeaShell);
  
  const uint32_t maxSamples = 100000;
  WINDOW_W = (USHORT)(screenWidth * 0.7F);
  WINDOW_H = (USHORT)(screenHeight * 0.9F);
  RenderSettings   rendSett(WINDOW_W, WINDOW_H, maxSamples, SamplingMethod::SOBOL);
  ViewportSettings viewSett(WINDOW_W, WINDOW_H);

  RenderFunction renderFunc(rendSett, scene, G_RESULT_POINTS);
  Viewport viewport(viewSett, renderFunc);
  viewport.Draw();



  glutInitWindowSize(WINDOW_W, WINDOW_H);
  glutInitWindowPosition((screenWidth - WINDOW_W)/2, (screenHeight - WINDOW_H)/2);
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