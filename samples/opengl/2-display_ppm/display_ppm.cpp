//
// emma-colorimage.cpp - displays a PPM image using glew/OpenGL/glut.
//    (It uses Emma graphics library to read in PPM image. Edit
//     PPM image to view contents.) Alternatively, there are
//    image editors that read PPM files, eg Irfanview, Adobe.
//
#include <windows.h>

#include <iostream>
using namespace std;
#include <string>
#include <fstream>

// gl/glu comes with Windows. 
#include <gl/gl.h>
#include <gl/glu.h>
#pragma comment(lib, "OpenGL32.Lib")
#pragma comment(lib, "glU32.Lib")

// Need to install freeglut (or other glut)
// for glut.h and glut32.lib. Binaries exist, but source contains
// (old) redbook examples. The binaries have glut.h file, but you can
// compile glut32.lib with Visual Studio 2008 Express.
#include <gl/glut.h>
#pragma comment(lib, "glut32.lib")

// Use Emma graphics library (c) Jerry Eldridge
#include "core/core.h"
#include "io/io.h"
#pragma comment(lib, "emma.lib")

int cW, cH;
GLubyte *cImage;
GLuint texName;

void ReadTexture(GLubyte *cimg, color *img, int w, int h);
void Init(color *img, int w, int h);
void DeInit();
void Reshape(int w, int h);
void DrawScene();
void Keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	char imgfile[4096] = "mandelbrot.ppm";
	int w, h, maxval;
	color *img = 0;
	Read_PPM_File(imgfile,maxval,w,h,img); // uses Emma

	cout << "exit with ESC key..." << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow(imgfile);

	Init(img,w,h);
	delete []img;

	glutDisplayFunc(DrawScene); 
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}

void Init(color *img, int w, int h)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);
	ReadTexture(cImage, img,w,h);
    glShadeModel(GL_FLAT);
}

// How to Properly call this upon exit? So far, proper exit by ESC key.
void DeInit()
{
	Beep(2000, 500);
}

void Reshape(int w, int h)
{
	glViewport(0,0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void DrawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(0.0, cH);
    glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex2f(cW, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex2f(cW, cH);
    glEnd();
	glFlush();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			DeInit();
			exit(0);
			break;
	}
}

// texture based on the OpenGL Programming Guide, Shreiner, 7th Ed., 2010,
// pp398-399, or freeglut redbook checker.c
// (modified by Jerry Eldridge to use dynamic arrays)
void ReadTexture(GLubyte *cimg, color *img, int w, int h)
{
	cImage = new GLubyte[w*h*3];
	cW = w; cH = h;
	int i, j, R,G,B;
	for (j=0; j<cH; j++) {
		for (i=0; i<cW; i++) {
			R = img[j+h*i].r;
			G = img[j+h*i].g;
			B = img[j+h*i].b;
			cImage[(j+h*i)*3 + 0] = R; // red
			cImage[(j+h*i)*3 + 1] = G; // green
			cImage[(j+h*i)*3 + 2] = B; // blue
		}
	}

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, cW, cH,
		0, GL_RGB, GL_UNSIGNED_BYTE, &cImage[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
	delete []cImage;
}
