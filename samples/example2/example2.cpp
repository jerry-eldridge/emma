#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include "core/common.h"
#include "core/int_images.h"
#include "io/image_io.h"
#include "io/ppm.h"

int gw = 500, gh = 500;
int gmaxval = 255;
color *gdisplay = 0;

void xSetColorArray(color *display, int w, int h, color col);

int main() 
{

	int w = gw, h = gh;
	gdisplay = new color[w*h];

	color col;
	col.r = 0; col.g = 0; col.b = 255;
	xSetColorArray(gdisplay, w, h, col);

	//SetIntArray(gdisplay, w, h, gmaxval);

	char ifilename[2048] = "eg2.ppm";
	PPM_P6_From_ColorImage(ifilename, gdisplay, w, h);
	system(ifilename);

	delete []gdisplay;

}

void xSetColorArray(color *display, int w, int h, color col)
{
	int i, j;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			display[j*w + i].r = 0;
			display[j*w + i].g = 0;
			display[j*w + i].b = 255;
		}
	}
}
