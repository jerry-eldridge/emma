//
// Computes Re(cos(z))
//
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
	int w = 500, h = 500;
	char imagefile1[4096] = "recosz.pgm";

	int *img = new int[w*h];
	Complex z;
	int i,j;
	double *dimg = new double[w*h];
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			double x, y;
			x = 15.0*(i-w/2.0)/w;
			y = 15.0*(j-h/2.0)/h;
			z = Complex(x,y);
			double f;
			f = real(cos(z));
			dimg[j+h*i] = f;
		}
	}
	StretchDoubleArray(dimg, w, h);
	CopyDoubleToIntArray(dimg, img, w, h);
	PGM_P5_From_Image(imagefile1, img, w, h);

	system(imagefile1);
	delete []dimg;
	delete []img;

	system("pause");
	return 0;
}