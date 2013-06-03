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

Complex zeta(Complex s, int nmax);
void hsv2rgb(double h, double s, double v,
			 double &r, double &g, double &b) ;

int main() 
{
	int w = 1000, h = 1000;
	char imagefile1[4096] = "riemann-zeta.ppm";

	ColorImage cimg(w,h);
	Complex z;
	int i,j;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			double x, y;
			x = 80*(i-w/2.0)/w;
			y = 80*(j-h/2.0)/h;
			z = Complex(x,y);
			z = zeta(z, 7);
			double h = arg(z);
			double s = min(255,max(0,norm(z)));
			double v = 1.0;
			double r,g,b;
			hsv2rgb(h,s,v, r,g,b);
			cimg.SetPixel2(i,j,r,g,b);
		}
	}

	cimg.Save_PGM_P6(imagefile1);

	system(imagefile1);

	system("pause");
	return 0;
}

Complex zeta(Complex s, int nmax)
{
	Complex sum = Complex(0,0);
	int n;
	for (n=1; n<nmax; n++) {
		Complex w = Complex(n,0);
		Complex w2 = pow(w,-s);
		sum += w2;
	}
	return sum;

}

// http://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
void hsv2rgb(double h, double s, double v,
			 double &r, double &g, double &b) 
{
    h = fmod(fmod(h,1) + 1,1); // wrap hue

    int i = floor(h * 6);
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - s * f);
    double t = v * (1 - s * (1 - f));

    switch (i) {
        case 0: 
			r = 255*v; g = 255*t; b = 255*p;
			return;
        case 1: 
			r = 255*q; g = 255*v; b = 255*p;
			return;
        case 2: 
			r = 255*p; g = 255*v; b = 255*t;
			return;
        case 3: 
			r = 255*p; g = 255*q; b = 255*v;
			return;
        case 4: 
			r = 255*t; g = 255*p; b = 255*v;
			return;
        case 5: 
			r = 255*v; g = 255*p; b = 255*q;
			return;
    }
}
