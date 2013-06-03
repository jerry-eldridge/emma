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
	int w = 500, h = 500; // width, height
	ColorImage img(w,h);
	img.Clear(180, 180, 255);

	Complex z;
	int i, j;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			z = Complex(1.0*i/w-0.5,1.0*j/h-0.5);
			Complex z2 = sqrt(z);
			double Re = real(z2);
			if (Re < 0.0001) {
				img.SetPixel2(i,j,255,255,255);
				//cout << i << " " << j << endl;
			} else {
				int R, G, B;
				FalseColor(norm(z2)*255, 127, R, G, B);
				img.SetPixel2(i,j, R, G, B);
			}
		}
	}

	char imagefile[4096] = "sqrtz-branch.ppm";
	img.Save_PGM_P6(imagefile);
	system(imagefile); // 'double click' on imagefile

	system("pause");
	return 0;
}
