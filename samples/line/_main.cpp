#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include "core/core.h"
#include "io/io.h"

int *gdisplay = 0;
int gmaxval = 255;
int gw = 500, gh = 500;

void Routine(int *&img);

int main() 
{
	int w = gw, h = gh;
	gdisplay = new int[w*h];

	Routine(gdisplay);
	
	char imgfilename[4098] = "line.pgm";
	PGM_P2_From_Image(imgfilename, gdisplay, w, h, gmaxval);
	system(imgfilename);

	delete []gdisplay;
}

void Routine(int *&img)
{
	int w, h;
	w = gw; h = gh;
	SetIntArray(img, w, h, gmaxval);

	point p1, p2;
	int val = 0;
	p1.x = 40; p1.y = 50;
	p2.x = 100; p2.y = 200;
	DrawLine(img, w, h, p1, p2, val);
	DrawLine(img, w, h, 0, 0, w, 300, 40);
}