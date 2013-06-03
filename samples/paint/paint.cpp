#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include "core/core.h"
#include "io/io.h"

int *gimg = 0;
int gmaxval = 255;
int gw = 500, gh = 500;

int main() 
{
	int w = gw, h = gh;
	gimg = new int[w*h];
	SetIntArray(gimg, w, h, 255);

	Read_Em2_File("lines_data.em2", gmaxval, w, h,
		gimg);
	int n;
	for (n=0; n<w*h; n++) {
		gimg[n] = gmaxval - gimg[n];
	}
	FillBucket(gimg, w, h, 250, 300, 0, 100);
	for (n=0; n<w*h; n++) {
		gimg[n] = gmaxval - gimg[n];
	}

	char imgfilename[4098] = "paint2.pgm";
	PGM_P2_From_Image(imgfilename, gimg, w, h, gmaxval);
	system(imgfilename);

	delete []gimg;
}
