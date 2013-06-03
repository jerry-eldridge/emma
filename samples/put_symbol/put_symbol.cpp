#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"

#include <math.h>

int gw = 500, gh = 500;
int gmaxval = 255;
int *gimg = 0;

int main() 
{

	int w = gw, h = gh;
	gimg = new int[w*h];

	SetIntArray(gimg, w, h, gmaxval);

	Ellipse(gimg, w, h, 200,100, 50,100, 100);
	FillEllipse(gimg, w, h, 100,100, 150,50, 100);

	char str[1024] = "Ellipse Regular and Filled";
	PutText(gimg,w,h,str,50,250);

	char ifile[2048] = "ellipse.pgm";
	PutText(gimg,w,h,ifile,10,400,"font3",20,20,0.42);

	PGM_P2_From_Image(ifile, gimg, w, h, gmaxval);
	system(ifile);

	delete []gimg;

}
