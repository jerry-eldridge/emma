#include <iostream>
using namespace std;

#include <complex>
#include <math.h>

typedef complex<double> Complex;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"
#include "io/jpg.h"

int *gimg = 0;
int maxval, n1, n2;

Complex FT_Helper(int *x, int len, double omega);
void FT(int *x, int len, double *&re, double *&im);
void IFT(double *re, double *im, int *&x, int len);

int main()
{
	Read_JPG_File("gradient.jpg", maxval, n1, n2, gimg);

	double *re = new double[n1*n2];
	double *im = new double[n1*n2];
	FT(gimg, n1*n2, re, im);

	int n;
	double *norm0 = new double[n1*n2];
	double *arg0 = new double[n1*n2];
	for (n=0; n<n1*n2; n++) {
		Complex z(re[n],im[n]);
		norm0[n] = log(norm(z));
		arg0[n] = arg(z);
	}

	StretchDoubleArray(norm0, n1, n2); // changes im
	CopyDoubleToIntArray(norm0, gimg, n1, n2);

	char ifile[1024]="norm.pgm";
	PGM_P5_From_Image(ifile, gimg, n1, n2);
	system(ifile);

	IFT(re, im, gimg, n1*n2);

	char ifile2[1024]="fourier.pgm";
	PGM_P5_From_Image(ifile2, gimg, n1, n2);
	system(ifile2);

	delete []re;
	delete []im;
	delete []norm0;
	delete []arg0;
	delete []gimg;

	system("pause");
	return 0;
}

// Fourier Transform
void FT(int *x, int len, double *&re, double *&im)
{
	int i;
	for (i=0; i<n1*n2; i++) {
		double omega = 2*PI*i/(n1*n2);
		Complex z = FT_Helper(x, n1*n2, omega);
		re[i] = real(z);
		im[i] = imag(z);
	}
}

void IFT(double *re, double *im, int *&x, int len)
{
	int n;
	for (n=0; n<len; n++) {
		Complex sum(0,0);
		int i;
		for (i=0; i<len; i++) {
			Complex X;
			X = Complex(re[i],im[i]);
			double omega = 2*PI*i/(n1*n2);
			Complex z(cos(omega*n),sin(omega*n));
			double dw = 2*PI/(n1*n2);
			sum = sum + X*z*dw;
		}
		double tot = real(sum)/(2*PI);
		x[n] = tot;
	}
}

Complex FT_Helper(int *x, int len, double omega)
{
	int n;
	Complex sum(0,0);
	for (n=0; n<len; n++) {
		Complex w(x[n],0);
		Complex z(cos(-omega*n),sin(-omega*n));
		sum = sum + w*z;
	}
	return sum;
}