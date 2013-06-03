#include <iostream>
using namespace std;

#include <complex>
#include <math.h>

typedef complex<double> Complex;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"

//#include "io/jpg.h"

double x(int n);

int main() 
{
	double bound = 1000;//1000; 

	int w = 500, h = 500; // width, height
	ColorImage img(w,h);
	img.Clear(255, 255, 255);
	Complex z;
	point p;
	int i, j, n;
	cout << "Computing z-transform..." << endl;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			z = Complex(1.0*(i-w/2.0)/w,1.0*(j-h/2.0)/h);
			//z = z/norm(z); // Fourier if z <- z/norm(z) else z-transform
			Complex sum = Complex(0,0);
			int n = 0;
			sum = sum + x(0);
			while ((norm(sum) < bound) && (n < 255)) { 
				sum += x(-n)*pow(z, n) + x(n)*pow(z, -n);
				n++;
			}			
			//cout << n << endl;
			int r, g, b;
			FalseColor(n, 6, r, g, b);
			//img.SetPixel(j + h*i, r, g, b);
			img.SetPixel2(i,j, r, g, b);

		}
		cout << ".";
	}
	cout << endl;

	char imagefile[4096] = "z-trans.ppm";
	img.Save_PGM_P6(imagefile);

	//char imagefile[4096] = "z-trans.jpg";
	//color *cimg = new color[w*h];
	//for (n=0; n<w*h; n++) {
	//	cimg[n].r = img.r[n];
	//	cimg[n].g = img.g[n];
	//	cimg[n].b = img.b[n];
	//}
	//JPG_From_ColorImage(imagefile, cimg, w, h);
	//delete []cimg;

	system(imagefile); // 'double click' on imagefile

	system("pause");
	return 0;
}

double delta(int n)
{
	double res = (n == 0) ? 1 : 0;
	return res;
}

double u(int n)
{
	double res = (n >= 0) ? 1 : 0;
	return res;
}

double x(int n)
{
	double xn;
	float a = 1.0/3.0;
	//xn = pow(a,n)*u(n);//255.0;//cos(omega0*n);
	//xn = -pow(a,n)*u(-n-1);
	//xn = (pow(1.0/2,n)+pow(-1.0/3,n))*u(n);
	xn = pow(-1.0/3,n)*u(n)-pow(1.0/2,n)*u(-n-1);
	//int N = 3;
	//xn = ((n>=0)&&(n<=N-1))? pow(a,n) : 0;

	//xn = 2*delta(n) - 9*pow(1.0/2,n)*u(n) + 8*u(n);

	//xn = delta(n+2)-1.0/2*delta(n+1)-delta(n)+1.0/2*delta(n-1);

	//xn = 1.0/sqrt(2.0)*(delta(n) + delta(n-1));

	return xn;
}
