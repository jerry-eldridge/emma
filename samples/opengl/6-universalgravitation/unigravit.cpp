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
double g_t = 0;

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
	static double t_last = 0;
	double dt_day = 60*60*24;
	double dt = dt_day;

	// animate Earth about Sun
	double xx, yy, semiaxis,eccentricity;
	point x_sun;
	eccentricity = 0.01671123;
	semiaxis = (152098232e3 + 147098290e3)/2.;
	x_sun.x = 0;//semiaxis - 147098290e3;
	x_sun.y = 0;
	xx = g_x.x - x_sun.x;
	yy = g_x.y - x_sun.y;
	double r = sqrt(xx*xx + yy*yy);
	double Fx, Fy, F, G, m_sun, m_earth;
	G = 6.6738480e-11;
	m_sun = 1.988435e30; // kg
	m_earth = 5.9721986e24; //kg
	F = G*m_sun*m_earth/(r*r);
	Fx = -F*g_x.x/r;
	Fy = -F*g_x.y/r;
	g_a.x = Fx/m_earth;
	g_a.y = Fy/m_earth;

	g_v.x = g_v.x + g_a.x*dt;
	g_v.y = g_v.y + g_a.y*dt;
	g_x.x = g_x.x + g_v.x*dt;
	g_x.y = g_x.y + g_v.y*dt;

	point pt,pt2;
	pt.x = gw/2. + gw/2.*g_x.x/(2*semiaxis);
	pt.y = gh-gh/2.*(1.*g_x.y/(2*semiaxis)) - gh/2.;

	if ((fabs(pt.x - gw/2.) < 1) && (pt.y<gh/2.)) {
		cout << 1.*(g_t - t_last)/dt_day << endl;
		t_last = g_t;
	}

	pt2.x = gw/2. + gw/2.*x_sun.x/(2*semiaxis);
	pt2.y = gh-gh/2.*(1.*x_sun.y/(2*semiaxis)) - gh/2.;

	g_img.Clear(230, 230, 255);

	// Draw Ellipse
	//Ellipse(g_img.r,gw,gh, pt.x, pt.y, 10,10,255);
	//Ellipse(g_img.g,gw,gh, pt.x, pt.y, 10,10,0);
	//Ellipse(g_img.b,gw,gh, pt.x, pt.y, 10,10,0);
	char body[4096] = "E";
	PutText(g_img.r,gw,gh,body,pt.x-15,pt.y-15,"font3",30,30,0.35,0);
	PutText(g_img.g,gw,gh,body,pt.x-15,pt.y-15,"font3",30,30,0.35,0);
	PutText(g_img.b,gw,gh,body,pt.x-15,pt.y-15,"font3",30,30,0.35,255);
	memset(body,0,4096);
	strcpy(body,"S");
	pt.x = gw/2;
	pt.y = gh/2;
	PutText(g_img.r,gw,gh,body,pt2.x-15,pt2.y-15,"font3",30,30,0.35,255);
	PutText(g_img.g,gw,gh,body,pt2.x-15,pt2.y-15,"font3",30,30,0.35,0);
	PutText(g_img.b,gw,gh,body,pt2.x-15,pt2.y-15,"font3",30,30,0.35,0);


	g_t += dt;

	char buff[4096] = "";
	sprintf(buff, "t = %.5f days", g_t/dt_day);
	PutText(g_img.r,gw,gh,buff,10,20,"font3",50,50,0.35,255);
	PutText(g_img.g,gw,gh,buff,10,20,"font3",50,50,0.35,100);
	PutText(g_img.b,gw,gh,buff,10,20,"font3",50,50,0.35,80);

	DisplayImage();

}

void Animate()
{
	Sleep(15);
	Walk();
	glutPostRedisplay();
}

void InitParticle()
{
	g_v.x = 29.78e3;
	g_v.y = 0;
	g_x.x = 0;
	g_x.y = 149598261e3;
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

	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);
	DisplayImage();
    glShadeModel(GL_FLAT);

	g_img.Clear(230, 230, 255);
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
