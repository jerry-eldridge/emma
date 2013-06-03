#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"

#include <math.h>

int *gimg = 0;
int w = 500, h = 500;
int gmax = 255;
#define PI 3.1415926535897932384626433832795

int main()
{
	gimg = new int[w*h];
	SetIntArray(gimg, w, h, gmax);

	int i, j;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			gimg[i+j*w] = 126*sin(2*PI*(i)/w*(j)/h*4.0*2.0) + 127;
			//gimg[i+j*w] = 126*sin(2*PI*(i-250)/w*(j-250)/h*4.0*2.0) + 127;
		}
	}

	char ifile[2048] = "wave.pgm";
	PGM_P2_From_Image(ifile, gimg, w, h, gmax);
	system(ifile);

	if (!gimg) delete []gimg;

	system("pause");
	return 0;
}