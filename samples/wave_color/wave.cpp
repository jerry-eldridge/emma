#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"

#include <math.h>

ColorImage gimg(500,500);

#define PI 3.1415926535897932384626433832795

int main()
{
	gimg.Clear(255,255,255);
	int w = gimg.N1, h = gimg.N2;

	int i,j;
	int R, G, B;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			double t = 126*sin(2*PI*i/w*j/h*4.0) + 127;
			FalseColor(t, 127, R, G, B);
			gimg.SetPixel2(i,j, R, G, B);
		}
	}

	char ifile[2048] = "wave_color.ppm";
	gimg.Save_PGM_P6(ifile);
	system(ifile);

	system("pause");
	return 0;
}