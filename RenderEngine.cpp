#include <vector>
#include "freeglut/include/GL/freeglut.h"

#include "RenderEngine.h"

//////////////////////////////////////////////////////////////////

extern USHORT WINDOW_W;
extern USHORT WINDOW_H;


RenderEngine::RenderEngine(RenderSettings& rendSett, Scene& scene) :
	m_rendSett(rendSett),
	m_scene(scene)
{
	G_RESULT_POINTS.resize(rendSett.m_maxSamples);
}


void RenderEngine::Render()
{
	Sampling sampling(m_rendSett.m_sampMeth);

	const int maxDim = 3;
	std::vector<float> rndNums(3);

	for (int i = 0; i < m_rendSett.m_maxSamples; ++i)
	{		
		for (size_t dim = 0; dim < maxDim; ++dim)
		{
			rndNums[dim] = sampling.GetOneRndDigit(i, dim);
			rndNums[dim] = sampling.GetOneRndDigit(i, dim);
			rndNums[dim] = sampling.GetOneRndDigit(i, dim);
		}

		G_RESULT_POINTS[i] = m_scene.Eval(rndNums);
	}
}





void DrawPoints(const std::vector<float3>& a_points)
{
	glBegin(GL_POINTS);
	glColor3f(1.0F, 1.0F, 1.0F);
	for (auto& point : a_points)
		glVertex3f(point.x, point.y, point.z);
	glEnd();
}



void DrawWindow()
{
	// stars: to simulate infinite distance,
	//        translate the sphere of stars to the eye
	//        and perform the arcball rotation around the eye
	//        (also disable depth test so they become the background)
	//glPushMatrix();
	//glDisable( GL_DEPTH_TEST );
	//glTranslatef( eye.x, eye.y, eye.z );
	//arcball_rotate();
	//draw_stars();
	//glEnable( GL_DEPTH_TEST );
	//glPopMatrix();

	// now render the regular scene under the arcball rotation about 0,0,0
	// (generally you would want to render everything here)
	//m_scene.m_camera.arcball_rotate();
	G_CAMERA.arcball_rotate();
	DrawPoints(G_RESULT_POINTS);
}




void reset_view(int w, int h)
{
	const float aspectRatio = (float)(w) / (float)(h);

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0f, aspectRatio, 1.0f, 100.0f);
	gluLookAt(
		G_CAMERA.m_eye.x,    G_CAMERA.m_eye.y,    G_CAMERA.m_eye.z,
		G_CAMERA.m_centre.x, G_CAMERA.m_centre.y, G_CAMERA.m_centre.z,
		G_CAMERA.m_up.x,     G_CAMERA.m_up.y,     G_CAMERA.m_up.z);

	// set up the arcball using the current projection matrix
	G_CAMERA.arcball_setzoom(G_CAMERA.SPHERE_RADIUS, G_CAMERA.m_eye, G_CAMERA.m_up);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//////////////////////////////////////////////////////
// GLUT Callbacks
//////////////////////////////////////////////////////


void resize(int w, int h)
{
	reset_view(w, h);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DrawWindow();

	glutSwapBuffers();
}


void idle()
{
	glutPostRedisplay();
}


// Mouse and keyboard

void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(0);
		//break;
	default:
		break;
	}
	glutPostRedisplay();
}




void click_scene(const int x, const int y)
{
	int invert_y = (WINDOW_H - y) - 1; // OpenGL viewport coordinates are Cartesian
	G_CAMERA.arcball_start(x, invert_y);
}


void drag_scene(const int x, const int y)
{
	int invert_y = (WINDOW_H - y) - 1;
	G_CAMERA.arcball_move(x, invert_y);
}


void mouse_button(const int button, const int state, const int x, const int y)
{
	if (state == GLUT_DOWN)
		click_scene(x, y);
}


void mouse_motion(const int x, const int y)
{
	// glutMotionFunc only called when a mouse button is held down
	drag_scene(x, y);
}
