#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include <math.h>
#include <fstream>
#include "core/core.h"
#include "io/io.h"

#include <deque>

int *gimg = 0;
int gw = 500, gh = 500;
int gmaxval = 255;

int main()
{
	int w = gw;
	int h = gh;
	gimg = new int[w*h];
	SetIntArray(gimg, w, h, gmaxval);

	Vector3D camera, center;
	camera.x = 0.0;
	camera.y = 100.0;
	camera.z =  300.0;

	center.x = 100.0;
	center.y = 100.0;
	center.z = 0;
	Read_Ema_File("..\\data\\cube.ema",
		gmaxval, w, h, gimg, camera, center);

	char ifile[2048]="cube.pgm";
	PGM_P5_From_Image(ifile, gimg, w, h);
	system(ifile);

	delete []gimg;
}
