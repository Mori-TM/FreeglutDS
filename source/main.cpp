#include <nds.h>
#include <time.h>
#include <stdio.h>
#include "freeglut.h"

float PMZ = -60.0;
float PMX = 0.0;
float PMY = 0.0;

float CMZ = 0.1;
float CMZ1 = 0.0;
float CMX = 0.0;
float CMY = 0.0;

float CRMZ = 0.0;
float CRMX = 0.0;
float CRMY = 0.0;

void Key()
{
//	touchPosition touch;
//	touchRead(&touch);
	u16 keys = keysHeld();
	
	if((keys & KEY_LEFT)) {CMX -= 0.3;}
	if((keys & KEY_RIGHT)) {CMX += 0.3;}
	if((keys & KEY_UP)) {CMZ -= 0.3; CMZ1 -= 0.3;}
	if((keys & KEY_DOWN)) {CMZ += 0.3; CMZ1 += 0.3;}
}

void Display()
{
	glLoadIdentity();
	glClearColor(227,215,247,31); // BG must be opaque for AA to work
	gluLookAt(	CMX, CMY, CMZ,		//camera possition 
				CMX, CMY, CMZ1,		//look at
				0.0, 1.0, 0.0);		//up	
	
	glPushMatrix();
		glTranslatef(PMX, PMY, PMZ);
			
		for(int i = 0; i < 11; i++)
		for(int yy = 0; yy < 11; yy++)
			for(int j= 0; j < 11; j++) 
			{
				if(yy == 0){ glColor3f(1.0 ,0.0, 0.0); }
				if(yy == 1){ glColor3f(0.0 ,1.0, 0.0); }
				if(yy == 2){ glColor3f(0.0 ,0.0, 1.0); }
				if(yy == 3){ glColor3f(1.0 ,1.0, 0.0); }
				if(yy == 4){ glColor3f(1.0 ,0.0, 1.0); }
				if(yy == 5){ glColor3f(0.0 ,1.0, 1.0); }
				
				if(yy == 6){ glColor3f(1.0 ,0.0, 0.0); }
				if(yy == 7){ glColor3f(0.0 ,1.0, 0.0); }
				if(yy == 8){ glColor3f(0.0 ,0.0, 1.0); }
				if(yy == 9){ glColor3f(1.0 ,1.0, 0.0); }
				if(yy == 10){ glColor3f(1.0 ,0.0, 1.0); }
				if(yy == 11){ glColor3f(0.0 ,1.0, 1.0); }

			     glPushMatrix();
					glTranslatef(i*1.0,yy*1.0,j * 1.0);
   	         		glutSolidCube(1.0);
      		    glPopMatrix();
	        }		
						
	glPopMatrix();
	
	glutSwapBuffers();		
	glutPostRedisplay();
}


void Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 256.0 / 192.0, 0.1, 800);
//	gluOrtho2D(-3.0, 3.0, 2.0, -2.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) 
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | POLY_CULL_NONE);
	glutInitWindowSize(255, 191);
	glutCreateWindow("Hello");
	
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutJoystickFunc(Key);
	glutMainLoop();
		
	return 0;
}
