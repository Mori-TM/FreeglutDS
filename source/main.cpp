#include <nds.h>
#include <time.h>
#include <stdio.h>
#include "freeglut.h"

#include <nds/arm9/image.h>
#include "Test_pcx.h"
#include "TM_pcx.h"

float CMZ = 0.1;
float CMX = 0.0;
float CMY = 0.0;

float CRX = 1.57;
float CRY = 0.0;
float CRZ = 1.0;

float lx, ly, lz;

int texture[2];
int LoadGLTextures()
{
	glGenTextures(2, &texture[0]);
	sImage pcx;
	loadPCX((u8*)TM_pcx, &pcx);
	image8to16(&pcx);
	
	glBindTexture(0, texture[0]);
	glTexImage2D(0, 0, GL_RGBA, TEXTURE_SIZE_128 , TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, pcx.image.data8);
	imageDestroy(&pcx);
	
	loadPCX((u8*)Test_pcx, &pcx);
	image8to16(&pcx);
	glBindTexture(0, texture[1]);
	glTexImage2D(0, 0, GL_RGBA, TEXTURE_SIZE_128 , TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, pcx.image.data8);
	imageDestroy(&pcx);
	
	return TRUE;
}


void Key(int key)
{
//	touchPosition touch;
//	touchRead(&touch);	

	lx = cos(CRX) * -cos(CRY);
	ly = sin(CRY);
	lz = sin(CRX) * -cos(CRY);	

	if((key & KEY_A)) {CRX += 0.2;}
	if((key & KEY_Y)) {CRX -= 0.2;}
	if((key & KEY_X)) {CRY += 0.2;}
	if((key & KEY_B)) {CRY -= 0.2;}
	
	if((key & KEY_LEFT)) {CMX -= 0.3;}
	if((key & KEY_RIGHT)) {CMX += 0.3;}
	if((key & KEY_UP)) {CMZ -= 0.3;}
	if((key & KEY_DOWN)) {CMZ += 0.3;}
}

void Display()
{
	glLoadIdentity();
	glClearColor(0.89,0.84,0.96,1); 
	gluLookAt(	CMX, CMY, CMZ,				//camera possition 
				CMX+lx, CMY+ly, CMZ+lz,		//look at
				0.0, 1.0, 0.0);				//up
					
	glPushMatrix();
		glTranslatef(0.0, 0.0, -1.0);
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0 ,1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 1.0); glVertex2f(-0.5, -0.5);
			glTexCoord2f(1.0, 1.0); glVertex2f(0.5, -0.5);
			glTexCoord2f(1.0, 0.0); glVertex2f(0.5, 0.5);
			glTexCoord2f(0.0, 0.0); glVertex2f(-0.5, 0.5);
		glEnd();
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();	
		glTranslatef(0.0, 0.0, -40.0);
			
		for(int i = 0; i < 6; i++)
		for(int yy = 0; yy < 6; yy++)
			for(int j= 0; j < 6; j++) 
			{

			     glPushMatrix();
					glTranslatef(i*1.0,yy*1.0,j * 1.0);
   	         		glutSolidCube(0.5);
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
	glutCreateWindow("Hello Glut");

	glMaterialf(GL_AMBIENT, RGB15(16,16,16));
	glMaterialf(GL_DIFFUSE, RGB15(16,16,16));
	glMaterialf(GL_SPECULAR, BIT(15) | RGB15(8,8,8));
	glMaterialf(GL_EMISSION, RGB15(16,16,16));
	glMaterialShinyness();
	
	vramSetBankA(VRAM_A_TEXTURE);
	LoadGLTextures();
	
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutJoystickFunc(Key);
	glutMainLoop();
		
	return 0;
}
