#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include "core/core.h"
#include "io/io.h"

int gw = 500, gh = 500;
int gmaxval = 255;
int *gdisplay = 0;

int main() 
{

	int w = gw, h = gh;
	gdisplay = new int[w*h];

	SetIntArray(gdisplay, w, h, gmaxval);
	PGM_P2_From_Image("myplot.pgm", gdisplay, w, h, gmaxval);
	
	system("myplot.pgm");

	delete []gdisplay;

}
