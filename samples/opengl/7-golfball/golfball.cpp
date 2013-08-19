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
void Mouse(int button, int state, int x, int y);

void DisplayImage();
void CopyHeightMapToCanvas();

int gw = 500;
int gh = 500;
ColorImage g_canvas(gw,gh);
point g_x,g_v,g_a;
double g_t = 0;

int *g_img = 0;
point *g_grad = 0;
int gN1, gN2, gMAXVAL;

int main(int argc, char** argv)
{
	Read_JPG_File("heightmap.jpg", gMAXVAL, gN1, gN2, g_img);

	cout << "exit with ESC key..." << endl;
	cout << "Click Mouse to reposition ball" << endl;
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
	// Display HeightMap as Background Texture
	CopyHeightMapToCanvas();

	// With Particle at position g_x on Heightmap
	double dt = 1;
	point F; // Force

	int ii,jj;
	// Clamp Values plus 1 unit border so particle doesn't ride rim
	ii = min(gN1-1-1,max(0+1,g_x.x));
	jj = min(gN2-1-1,max(0+1,g_x.y));

	// F = -grad(heightmap)
	F.x = -g_grad[jj+gN2*ii].x;
	F.y = -g_grad[jj+gN2*ii].y;

	double m = 10; // mass, heavier means slower

	g_a.x = F.x/m; // acceleration
	g_a.y = F.y/m;
	g_v.x = g_v.x + g_a.x*dt; // velocity
	g_v.y = g_v.y + g_a.y*dt;
	g_x.x = g_x.x + g_v.x*dt; // position
	g_x.y = g_x.y + g_v.y*dt;

	// Particle has momentum p = m*v so fade momentum
	// by reducing velocity's magnitude (speed) over time
	double fade = 0.9;
	g_v.x *= fade;
	g_v.y *= fade;

	// Clamp Values
	g_x.x = min(gN1-1,max(0,g_x.x));
	g_x.y = min(gN2-1,max(0,g_x.y));

	// Note Canvas is bigger than HeightMap. Draw Circle/Ellipse
	// where particle is at (for each red, green, blue plane). 
	// Scale position to Canvas.
	double rx, ry;
	rx = ry = 5;
	color col;
	col.r = 255; col.g = 0; col.b = 0;
	Ellipse(g_canvas.r,g_canvas.N1,g_canvas.N2,g_x.x*gw/gN1,g_x.y*gh/gN2,rx,ry,col.r);
	Ellipse(g_canvas.g,g_canvas.N1,g_canvas.N2,g_x.x*gw/gN1,g_x.y*gh/gN2,rx,ry,col.g);
	Ellipse(g_canvas.b,g_canvas.N1,g_canvas.N2,g_x.x*gw/gN1,g_x.y*gh/gN2,rx,ry,col.b);

	DisplayImage();
}

void Animate()
{
	Sleep(15);
	Walk();
	glutPostRedisplay();
}

void CopyHeightMapToCanvas()
{
	int M1, M2;
	double *dimg1 = new double[gN1*gN2];
	CopyIntToDoubleArray(g_img, dimg1, gN1, gN2);
	double *dimg2 = 0;
	ScaleSizeDoubleArray(dimg1, dimg2, 1.*gw/gN1, 1.*gh/gN2,
		gN1, gN2, M1, M2);
	int i,j;
	for (j=0; j<gh; j++) {
		for (i=0; i<gw; i++) {
			int R, G, B;
			R = G = B = (int) dimg2[j+M2*i];
			g_canvas.SetPixel2(i,j, R, G, B);
		}
	}
	delete []dimg1;
	delete []dimg2;
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

	g_canvas.Clear(230, 230, 255);

	CopyHeightMapToCanvas();

	// Init Particle
	g_x.x = rand()%gN1;
	g_x.y = rand()%gN2;
	g_v.x = 0;
	g_v.y = 0;
	g_a.x = 0;
	g_a.y = 0;

	// Calculate Gradient of Height Map
	g_grad = new point[gN1*gN2];
	int i,j,n;
	for (n=0; n<gN1*gN2; n++) g_grad[n].x = g_grad[n].y = 0.0;
	double dx, dy;
	dx = dy = 1;
	for (j=0; j<gN2-1; j++) {
		for (i=0; i<gN1-1; i++) {
			g_grad[j+gN2*i].x = (g_img[j+gN2*(i+1)] - g_img[j+gN2*i])/dx;
			g_grad[j+gN2*i].y = (g_img[(j+1)+gN2*i] - g_img[j+gN2*i])/dy;
		}
	}

}

// How to Properly call this upon exit? So far, proper exit by ESC key.
void DeInit()
{
	Beep(2000, 50);

	delete []g_img;
	delete []g_grad;
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
			g_x.x = x*1.*gN1/gw;
			g_x.y = y*1.*gN2/gh;
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