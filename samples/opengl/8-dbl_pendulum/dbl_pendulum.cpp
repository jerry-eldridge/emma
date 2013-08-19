//
// dbl_pendulum --- see the link
// http://scienceworld.wolfram.com/physics/DoublePendulum.html
// for equation of motion and positions
#include <windows.h>

#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <math.h>

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
// https://github.com/jerry-eldridge/emma
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
void Mouse(int button, int state, int x, int y);

void DisplayImage();
void DrawPendulum();

int gw = 500;
int gh = 500;
ColorImage g_canvas(gw,gh);
int *g_path = 0;
double *g_r = 0;
double *g_r_last = 0;
double *g_a = 0;
double *g_v = 0;
double g_t = 0;
double *g_l = 0;
double *g_m = 0;

int gN1, gN2, gMAXVAL;

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
	glutMouseFunc(Mouse);
	glutIdleFunc(Animate);
	glutMainLoop();
	return 0;
}

void Walk()
{
	double dt = 1;
	double m1 = g_m[0]; // masses
	double m2 = g_m[1];
	double g = 1;
	double l1 = g_l[0]; // lengths
	double l2 = g_l[1];
	double t1 = g_r[0]; // angles
	double t2 = g_r[1];
	double td1 = g_v[0];
	double td2 = g_v[1];

	// see weblink, eqn (13) at
	// http://scienceworld.wolfram.com/physics/DoublePendulum.html
	g_a[0] = (
		-m2*l2*g_a[1]*cos(t1-t2) + 
		-m2*l2*td2*td2*sin(t1-t2) +
		-g*(m1+m2)*sin(t1) ) / ((m1+m2)*l1);
	g_v[0] = g_v[0] + g_a[0]*dt;
	g_r[0] = g_r[0] + g_v[0]*dt;

	g_a[1] = (
		-m2*l1*g_a[0]*cos(t1-t2) +
		+m2*l1*td1*td1*sin(t1-t2) +
		-m2*g*sin(t2) ) / (m2*l2);
	g_v[1] = g_v[1] + g_a[1]*dt;
	g_r[1] = g_r[1] + g_v[1]*dt;

	// slow down pendulum over time
	double alpha1, alpha2;
	alpha1 = alpha2 = 1.0; // set to 1.0 if no friction
	g_v[0] = alpha1*g_v[0];
	g_v[1] = alpha2*g_v[1];

	double minv, maxv;
	minv = -0.3; maxv = 0.3;
	g_v[0] = max(min(g_v[0],maxv),minv);
	g_v[1] = max(min(g_v[1],maxv),minv);

	DrawPendulum();
	DisplayImage();

	g_r_last[0] = g_r[0];
	g_r_last[1] = g_r[1];

}

void Animate()
{
	Sleep(15);
	Walk();
	glutPostRedisplay();
}

void DrawPendulum()
{
	g_canvas.Clear(230, 230, 255);

	point A, B, C, D, E;
	A.x = gw/2.;
	A.y = gh/2.;
	// see weblink
	B.x = A.x - g_l[0]*sin(g_r[0]);
	B.y = A.y - -g_l[0]*cos(g_r[0]);
	C.x = B.x - g_l[1]*sin(g_r[1]);
	C.y = B.y - -g_l[1]*cos(g_r[1]);

	D.x = A.x - g_l[0]*sin(g_r_last[0]);
	D.y = A.y - -g_l[0]*cos(g_r_last[0]);
	E.x = D.x - g_l[1]*sin(g_r_last[1]);
	E.y = D.y - -g_l[1]*cos(g_r_last[1]);

	double ex, ey;
	ex = ey = 1;
	DrawLine2(g_path,gw,gh, D, B, 200, ex,ey);
	DrawLine2(g_path,gw,gh, E, C, 255, ex,ey);
	int i,j;
	for (j=0; j<gh; j++) {
		for (i=0; i<gw; i++) {
			if (g_path[j+gh*i] == 200) {
				g_canvas.SetPixel2(i,j, 200,190,170);
			}
			if (g_path[j+gh*i] == 255) {
				g_canvas.SetPixel2(i,j, 170,190,200);
			}
		}
	}

	color col;
	col.r = 0; col.g = 0; col.b = 255;
	ex = ey = 3;
	DrawLine2(g_canvas.r,g_canvas.N1,g_canvas.N2,A,B,col.r,ex,ey);
	DrawLine2(g_canvas.g,g_canvas.N1,g_canvas.N2,A,B,col.g,ex,ey);
	DrawLine2(g_canvas.b,g_canvas.N1,g_canvas.N2,A,B,col.b,ex,ey);

	DrawLine2(g_canvas.r,g_canvas.N1,g_canvas.N2,B,C,col.r,ex,ey);
	DrawLine2(g_canvas.g,g_canvas.N1,g_canvas.N2,B,C,col.g,ex,ey);
	DrawLine2(g_canvas.b,g_canvas.N1,g_canvas.N2,B,C,col.b,ex,ey);

	double rx, ry;
	rx = ry = 5;
	col.r = 0; col.g = 0; col.b = 0;

	FillEllipse(g_canvas.r,g_canvas.N1,g_canvas.N2,A.x,A.y,rx,ry,col.r);
	FillEllipse(g_canvas.g,g_canvas.N1,g_canvas.N2,A.x,A.y,rx,ry,col.g);
	FillEllipse(g_canvas.b,g_canvas.N1,g_canvas.N2,A.x,A.y,rx,ry,col.b);

	rx = ry = 10;
	col.r = 255; col.g = 0; col.b = 0;
	FillEllipse(g_canvas.r,g_canvas.N1,g_canvas.N2,B.x,B.y,rx,ry,col.r);
	FillEllipse(g_canvas.g,g_canvas.N1,g_canvas.N2,B.x,B.y,rx,ry,col.g);
	FillEllipse(g_canvas.b,g_canvas.N1,g_canvas.N2,B.x,B.y,rx,ry,col.b);

	FillEllipse(g_canvas.r,g_canvas.N1,g_canvas.N2,C.x,C.y,rx,ry,col.r);
	FillEllipse(g_canvas.g,g_canvas.N1,g_canvas.N2,C.x,C.y,rx,ry,col.g);
	FillEllipse(g_canvas.b,g_canvas.N1,g_canvas.N2,C.x,C.y,rx,ry,col.b);

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

	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);
	DisplayImage();
    glShadeModel(GL_FLAT);

	int nlinks = 2;

	g_r = new double[nlinks];
	g_r_last = new double[nlinks];
	g_r[0] = 40*(2*PI/360); // 40 degrees
	g_r[1] = 30*(2*PI/360);

	g_r_last[0] = g_r[0];
	g_r_last[1] = g_r[0];

	g_a = new double[nlinks];
	g_v = new double[nlinks];
	g_l = new double[nlinks];
	g_m = new double[nlinks];

	g_a[0] = 0;
	g_v[0] = 0;
	g_a[1] = 0;
	g_v[1] = 0;

	g_l[0] = 100;
	g_l[1] = 80;

	g_m[0] = 10;
	g_m[1] = 40;

	g_path = new int[gw*gh];
	SetIntArray(g_path,gw,gh, 0);

	DrawPendulum();

}

// How to Properly call this upon exit? So far, proper exit by ESC key.
void DeInit()
{
	Beep(2000, 50);

	delete []g_path;
	delete []g_r;
	delete []g_r_last;
	delete []g_a;
	delete []g_v;
	delete []g_l;
	delete []g_m;
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
		case 'r':
			SetIntArray(g_path,gw,gh, 0);
			break;
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
			g_canvas.GetPixel2(i,j,R,G,B);
			cImage[(i+gw*j)*3 + 0] = R; // red
			cImage[(i+gw*j)*3 + 1] = G; // green
			cImage[(i+gw*j)*3 + 2] = B; // blue
		}
	}
    glTexImage2D(GL_TEXTURE_2D, 0, 3, cW, cH,
		0, GL_RGB, GL_UNSIGNED_BYTE, &cImage[0]);
	delete []cImage;
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
		}
	}
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
		}
	}

	if (button == GLUT_MIDDLE_BUTTON) {
		if (state == GLUT_DOWN) {
		}
	}
}