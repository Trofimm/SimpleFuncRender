#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "freeglut/include/GL/freeglut.h"
#include "RenderEngine.h"


//////////////////////////////////////////////////////////////////////

  extern USHORT WINDOW_W = 800;
  extern USHORT WINDOW_H = 800;

int main(int argc, char ** argv)
{  
  Scene scene;
  scene.LoadScene(Scene_SeaShell);
  
  const uint32_t maxSamples = 100000;

  RenderSettings rendSett(WINDOW_W, WINDOW_H, maxSamples, SamplingMethod::SOBOL);
  RenderEngine   render(rendSett, scene);  
  render.Render();


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