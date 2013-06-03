#include <iostream>
using namespace std;

#include <complex>
#include <math.h>

typedef complex<double> Complex;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"

int main() 
{
	Complex a, b, c, d;

	int w = 500, h = 500; // width, height
	ColorImage img(w,h);
	img.Clear(180, 180, 255);
	Complex z;
	point p;
	int i, j;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			z = Complex(i,j);
			Complex z2 = Complex(128,0)*log(z);
			int r, g, b;
			FalseColor(norm(z2), 128, r, g, b);
			//img.SetPixel(j + h*i, r, g, b);
			img.SetPixel2(i,j, r, g, b);

		}
	}

	char imagefile[4096] = "log2.ppm";
	img.Save_PGM_P6(imagefile);
	system(imagefile); // 'double click' on imagefile

	system("pause");
	return 0;
}
