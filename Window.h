#pragma once
#include "Math.h" //float3
#include <vector>

#include "freeglut/include/GL/freeglut.h"

//////////////////////////////////////////////////////////////////////////

extern USHORT WINDOW_W;
extern USHORT WINDOW_H;

extern std::vector<float3> G_RESULT_POINTS;


//////////////////////////////////////////////////////
// GLUT Callbacks
//////////////////////////////////////////////////////

void display();
void key(unsigned char key, int x, int y);
void idle();
void resize(int w, int h);
void mouse_button(const int button, const int state, const int x, const int y);
void mouse_motion(const int x, const int y);
