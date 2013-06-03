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
	int x, y, dx, dy, color;
	x = 100; y = 100; dx = 30; dy = 30; color = 0;
	char symbol;

	int i;
	for (i=33; i<128; i++) {
		symbol = i;
		PutSymbol(gdisplay, w, h, symbol, x, y, 
			"fparker", dx, dy, color);
		x = x + dx*0.6;
		if (x + dx > w - 100) {
			y = y + dy;
			x = 100;
		}
	}

	char imgfile[2048] = "fparker.pgm";
	PGM_P2_From_Image(imgfile, gdisplay, w, h, gmaxval);
	
	system(imgfile);

	delete []gdisplay;

}
