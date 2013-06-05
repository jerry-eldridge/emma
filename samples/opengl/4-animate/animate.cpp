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
#include "io/jpg.h"
#pragma comment(lib, "emma.lib")

int cW, cH;
GLubyte *cImage;
GLuint texName;

void Init();
void DeInit();
void Reshape(int w, int h);
void DrawScene();
void Keyboard(unsigned char key, int x, int y);
void Animate();

void DisplayImage();
void InitParticle();

int gw = 500;
int gh = 500;
ColorImage g_img(gw,gh);
point g_x,g_v,g_a;
polygon ship;

int main(int argc, char** argv)
{

	cout << "exit with ESC key..." << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(gw, gh); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("animate");

	Init();

	glutDisplayFunc(DrawScene); 
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Animate);
	glutMainLoop();
	return 0;
}

void Walk()
{
	static bool save = false; // set to true if want to save frames

	static int count = 0;
	float dt = .1;
	g_v.x = g_v.x + g_a.x*dt;
	g_v.y = g_v.y + g_a.y*dt;
	g_x.x = g_x.x + g_v.x*dt;
	g_x.y = g_x.y + g_v.y*dt;

	if (g_x.y < 0) {
		InitParticle();
		save = false;
	}

	point pt;
	pt.x = g_x.x;
	pt.y = gh-g_x.y;

	g_img.Clear(230, 230, 255);

	//// Draw Ellipse
	//Ellipse(g_img.r,gw,gh, pt.x, pt.y, 10,10,255);
	//Ellipse(g_img.g,gw,gh, pt.x, pt.y, 10,10,0);
	//Ellipse(g_img.b,gw,gh, pt.x, pt.y, 10,10,0);

	// Draw Space Ship
	double area;
	ship.centroid = PolygonCentroid(ship.p, ship.np, &area);
	int i;
	int np = ship.np;
	for (i=0; i<np; i++) {
		ship.p[i].x -= ship.centroid.x;
		ship.p[i].y -= ship.centroid.y;
		ship.p[i].x += g_x.x*20./gw;
		ship.p[i].y += g_x.y*20./gh;
	}
	GraphPolygon2(g_img.r,gw,gh,255, &ship, 20, 20, 0, 230, false);
	GraphPolygon2(g_img.g,gw,gh,255, &ship, 20, 20, 0, 230, false);
	GraphPolygon2(g_img.b,gw,gh,255, &ship, 20, 20, 0, 255, false);

	DisplayImage();

	// Save Frames
	char filename[4096]="";
	sprintf(filename,".\\Z-Frames\\frame-%03d.jpg",count);
	if (save) {
		cout << "Saving..." << filename << endl;
		Save_JPG_P6(&g_img,filename);
	}

	int max_saved_imgs = 100;
	if (count >= max_saved_imgs) {
		save = false;
	}

	count++;
}

void Animate()
{
	Sleep(15);
	Walk();
	glutPostRedisplay();
}

void InitParticle()
{
	g_a.x = 0; 
	g_a.y = -10;
	g_v.x = 20;
	g_v.y = 20;
	g_x.x = gw/5;
	g_x.y = gh/2;
}

void Init()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);

	InitParticle();
	int n;

	ship.parts.push(-1);
	ReadPolygon("space_ship2.txt", &ship);
	int i;
	int np = ship.np;
	for (i=0; i<np; i++) {
		ship.p[i].x -= ship.centroid.x;
		ship.p[i].y -= ship.centroid.y;
		ship.p[i].x *= 0.15;
		ship.p[i].y *= 0.15;
	}

	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);
	DisplayImage();
    glShadeModel(GL_FLAT);

}

// How to Properly call this upon exit? So far, proper exit by ESC key.
void DeInit()
{
	Beep(2000, 50);
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
void DisplayImage()
{
	cImage = new GLubyte[gw*gh*3];
	cW = gw; cH = gh;
	int i, j, R,G,B;
	for (j=0; j<cH; j++) {
		for (i=0; i<cW; i++) {
			g_img.GetPixel2(i,j,R,G,B);
			cImage[(i+gw*j)*3 + 0] = R; // red
			cImage[(i+gw*j)*3 + 1] = G; // green
			cImage[(i+gw*j)*3 + 2] = B; // blue
		}
	}
    glTexImage2D(GL_TEXTURE_2D, 0, 3, cW, cH,
		0, GL_RGB, GL_UNSIGNED_BYTE, &cImage[0]);
	delete []cImage;
}
