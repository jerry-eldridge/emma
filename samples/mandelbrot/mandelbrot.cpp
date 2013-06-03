#include <iostream>
using namespace std;

#include <complex>
#include <math.h>

typedef complex<double> Complex;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"

void mandelbrot(char *imagefile, int w, int h, double mid);

int main() 
{
	int w = 500, h = 500;
	char imagefile1[4096] = "mandelbrot.ppm";
	mandelbrot(imagefile1, w, h, 20);
	system(imagefile1);

	system("pause");
	return 0;
}

void mandelbrot(char *imagefile, int w, int h, double mid)
{
	cout << "Computing mandelbrot..." << endl;
	ColorImage img(w,h);
	img.Clear(180, 180, 255);
	Complex z, c;
	point p;
	int i, j, k;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			double x, y;
			x = i; y = j; // [0,w) x [0,h)
			x = 1.0*x/w; y = 1.0*y/h; // [0,1) x [0,1)

			// Wikipedia mentions x in [-2.5, 1.0), y in [-1.0,1.0) as camera
			x = 3.5*x - 2.5; y = 2.0*y - 1.0; // [-2.5,1.0) x [-1.0,1.0) 

			// Change c to get the mandelbrot set or any julia set
			// mandelbrot
			c = Complex(x,y);
			// julia sets (example c's from OpenGL Shading Language, Rost)
			//c = Complex(0.32,0.043); // a julia set
			//c = Complex(-0.765,0.11);
			//c = Complex(-1.5,0.0);
			//c = Complex(-1.36, 0.11);
			
			z = Complex(x,y);
			double bound = 4.0;
			int iter = 0;
			while ((norm(z) < bound) && (iter < 255)) { 
				z = z*z + c;
				iter = iter + 1;
			}
			int r, g, b;
			FalseColor(iter, mid, r, g, b);
			img.SetPixel2(i,j, r, g, b);

		}
	}

	img.Save_PGM_P6(imagefile);

}