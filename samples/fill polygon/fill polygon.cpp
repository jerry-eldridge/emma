#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include "core/core.h"
#include "io/io.h"

#include <time.h>

int *gimg = 0;
int gmaxval = 255;
int gw = 500, gh = 500;

int main() 
{
	int w = gw, h = gh;
	gimg = new int[w*h];
	SetIntArray(gimg, w, h, 255);

	srand(time(0));

	Read_Em2_File("..\\data\\lines_data.em2", gmaxval, w, h,
		gimg);

	int i;
	int M = 5;
	pointDouble *p = new pointDouble[M];
	for (i=0; i<M; i++) {
		p[i].x = rand()%w;
		p[i].y = rand()%h;
	}

	// Dont use PolygonFillMean
	clock_t start, stop, DeltaTime;
	start = clock();
	PolygonFillMean(gimg, w, h, p, M, 100);
	stop = clock();
	int diff = stop-start;
	cout << "PolygonFillMean (miliseconds) = " << diff << endl;

	start = clock();
	PolygonFill(gimg, w, h, p, M, 20);
	stop = clock();
	diff = stop-start;
	cout << "PolygonFill (miliseconds) = " << diff << endl;

	delete []p;

	char imgfilename[4098] = "paint3.pgm";
	PGM_P2_From_Image(imgfilename, gimg, w, h, gmaxval);
	system(imgfilename);

	delete []gimg;
}
