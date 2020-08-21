#ifndef _FREEGLUT_h_
#define _FREEGLUT_h_
#include <nds.h>
#include <math.h>

void glVertex2i(int x, int y) { glVertex3f(x, y, 0.0); }
void glVertex2f(float x, float y) { glVertex3f(x, y, 0.0); }  
void glVertex2d(double x, double y) { glVertex3f(x, y, 0.0); }
void glVertex3i(int x, int y, int z) { glVertex3f(x, y, z); }
void glVertex3d(double x, double y, double z) { glVertex3f(x, y, z); } 
void glColor4i(int red, int green, int blue, int alpha){ glColor3f(red, green, blue); }
void glColor4f(float red, float green, float blue, float alpha){ glColor3f(red, green, blue); }
void glColor4d(double red, double green, double blue, double alpha){ glColor3f(red, green, blue); }
void glColor3i(int red, int green, int blue){ glColor3f(red, green, blue); }
void glColor3d(double red, double green, double blue){ glColor3f(red, green, blue); }

void gluOrtho2D(double left, double right, double bottom, double top) { glOrtho(left, right, bottom, top, 0.1, 100); }

#define GLUT_RGBA POLY_ALPHA(31)
#define glClearDepth() glClearDepth(0x7FFF)
#define glPopMatrix() glPopMatrix(1)

#define glutInitDisplayMode(a) glPolyFmt(a)

#define glutPostRedisplay() swiWaitForVBlank()
#define glutSwapBuffers() glFlush(0)

void glutInit(int *argc, char **argv)
{ 
	glInit();
	glEnable(GL_ANTIALIAS);
	glClearColor(255,255,255,31);
	videoSetMode(MODE_0_3D);
	glClearPolyID(63);
	glClearDepth(); 
	glColor3f(1.0,1.0,1.0);
} 
void glutInitWindowSize(int w, int h){ glViewport(0,0,w,h); }

void glutCreateWindow(const char *title)
{ 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0 / 192.0, 0.1, 800);
	gluLookAt(	0.0, 0.0, 0.1,		//camera possition 
				0.0, 0.0, 0.0,		//look at
				0.0, 1.0, 0.0);		//up
	glMatrixMode(GL_MODELVIEW);
}

void (*reshapefunc)(int ,int) = NULL;
void (*displayfunc)(void) = NULL;
void (*joystickfunc)(void) = NULL;

void glutReshapeFunc(void (*callback) (int ,int))
{
	reshapefunc = callback;
}

void glutDisplayFunc(void (*callback) (void))
{		
	displayfunc = callback;
}

void glutJoystickFunc(void (*callback) (void))
{	
	joystickfunc = callback;
}

void glutMainLoop(void)
{
	if(reshapefunc) reshapefunc(256, 192);
	
	while(1) 
	{		
		scanKeys();	
		
		if(displayfunc) displayfunc();
		if(joystickfunc) joystickfunc();
	}
}

void glutSolidCube(double size)
{
	glScalef(size, size, size);
	
	//top
	glBegin(GL_QUADS);                
		glVertex3f( 0.5f, 0.5f,-0.5f);
		glVertex3f(-0.5f, 0.5f,-0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f( 0.5f, 0.5f, 0.5f);
	glEnd();
	// bottom
	glBegin(GL_QUADS);                 
		glVertex3f( 0.5f,-0.5f, 0.5f);
		glVertex3f(-0.5f,-0.5f, 0.5f);
		glVertex3f(-0.5f,-0.5f,-0.5f);
		glVertex3f( 0.5f,-0.5f,-0.5f);
	glEnd();            
	// left
	glBegin(GL_QUADS);
		glVertex3f(-0.5f,-0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f,-0.5f);
		glVertex3f(-0.0f,-0.0f,-0.5f);
	glEnd();
	// right
	glBegin(GL_QUADS);
		glVertex3f( 0.5f, 0.5f, 0.5f);
		glVertex3f( 0.5f,-0.5f, 0.5f);
		glVertex3f( 0.5f,-0.5f,-0.5f);
		glVertex3f( 0.5f, 0.5f,-0.5f);
	glEnd();
	// front
	glBegin(GL_QUADS);
		glVertex3f( 0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f,-0.5f, 0.5f);
		glVertex3f( 0.5f,-0.5f, 0.5f);
		glEnd();
	// back
	glBegin(GL_QUADS);
		glVertex3f(-0.5f, 0.5f,-0.5f);
		glVertex3f( 0.5f, 0.5f,-0.5f);
		glVertex3f( 0.5f,-0.5f,-0.5f);
		glVertex3f(-0.5f,-0.5f,-0.5f);
	glEnd();
}

void glutWireCube(double size)
{
	glScalef(size, size, size);
	glBegin(GL_QUADS);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.05, 1.0);
		glVertex3f(1.0, 1.05, 1.0);
		
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(1.05, -1.0, 1.0);
		glVertex3f(1.05, 1.0, 1.0);
		
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.05, 1.0);
		glVertex3f(1.0, -1.05, 1.0);
		
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.05, -1.0, 1.0);
		glVertex3f(-1.05, 1.0, 1.0);
	glEnd();
	
	glBegin(GL_QUADS);
		glVertex3f(1.0, 1.0, -1.0);
		glVertex3f(-1.0, 1.0, -1.0);
		glVertex3f(-1.0, 1.05, -1.0);
		glVertex3f(1.0, 1.05, -1.0);
		
		glVertex3f(1.0, 1.0, -1.0);
		glVertex3f(1.0, -1.0, -1.0);
		glVertex3f(1.05, -1.0, -1.0);
		glVertex3f(1.05, 1.0, -1.0);
		
		glVertex3f(1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.05, -1.0);
		glVertex3f(1.0, -1.05, -1.0);
		
		glVertex3f(-1.0, 1.0, -1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.05, -1.0, -1.0);
		glVertex3f(-1.05, 1.0, -1.0);
	glEnd();
	
	glBegin(GL_QUADS);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.05, 1.0, 1.0);
		glVertex3f(1.0, 1.0, -1.0);
		glVertex3f(1.05, 1.0, -1.0);
		
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(1.05, -1.0, 1.0);
		glVertex3f(1.0, -1.0, -1.0);
		glVertex3f(1.05, -1.0, -1.0);
	glEnd();
	
	glBegin(GL_QUADS);
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.05, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, -1.0);
		glVertex3f(-1.05, 1.0, -1.0);
		
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.05, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.05, -1.0, -1.0);
	glEnd();
}

#endif
