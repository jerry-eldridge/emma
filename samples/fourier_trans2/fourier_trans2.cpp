#include <iostream>
using namespace std;

#include <complex>
#include <math.h>

typedef complex<double> Complex;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"

#include <fstream>

Complex FT_Helper(double *x, int len, double Omega);
void FT(double *x, int len, double *&re, double *&im, int L);
void IFT(double *re, double *im, int L, double *&x, int len);
void Filter(double *x, int len, int L, char *dfile, char *ifile);

int main()
{
	int i, n;
	int L = 30;

	double x1[] = {0.5, 0.5};
	Filter(x1,2, L, "haar-lowpass.txt", "haar-lowpass.pgm");
	double x2[] = {-0.5, 0.5};
	Filter(x2,2, L, "haar-highpass.txt", "haar-highpass.pgm");
	double x3[] = {0.5, 1.0, 0.5};
	Filter(x3,3, L, "lilowpass.txt", "lilowpass.pgm");
	double x4[] = {0, -0.5, 0, 0.5};
	Filter(x4,4, 100, "upsampling.txt", "upsampling.pgm");
	double x5[] = {-1, 0, 9, 16, 9, 0, -1};
	n = sizeof(x5)/sizeof(double);
	for (i=0; i<n; i++) x5[i] /= 16.0;
	Filter(x5,n, L, "downsampling.txt", "downsampling.pgm");
	double x6[] = {-1, 9, 9, -1};
	n = sizeof(x6)/sizeof(double);
	for (i=0; i<n; i++) x6[i] /= 16.0;
	Filter(x6,n, L, "downsampling2.txt", "downsampling2.pgm");

	double x7[] = {1, 1, 1};
	n = sizeof(x7)/sizeof(double);
	for (i=0; i<n; i++) x7[i] /= 3.0;
	Filter(x7,n, L, "fir_wiki.txt", 
		"fir_wiki.pgm");

	system("pause");
	return 0;
}

void Filter(double *x, int len, int L, char *dfile, char *ifile)
{
	double *re = new double[L];
	double *im = new double[L];

	ofstream out(dfile);

	FT(x, len, re, im, L);
	int i;
	for (i=0; i<L; i++) {
		Complex z(re[i],im[i]);
		out << arg(z) << " " << norm(z) << endl;
		//out << re[i] << " " << im[i] << endl;
	}

	out.close();
	Plot(dfile, ifile);
	system(ifile);

	delete []re;
	delete []im;
}

Complex FT_Helper(double *x, int len, double Omega)
{
	int n;
	Complex sum(0,0);
	for (n=0; n<len; n++) {
		Complex xp(x[n],0);
		Complex z(cos(-Omega*n),sin(-Omega*n));
		sum = sum + xp*z;
	}
	return sum;
}

// Fourier Transform
void FT(double *x, int len, double *&re, double *&im, int L)
{
	int i;
	for (i=0; i<L; i++) {
		double Omega = 2*PI*i/L;
		Complex z = FT_Helper(x, len, Omega);
		re[i] = real(z);
		im[i] = imag(z);
	}
}

void IFT(double *re, double *im, int L, double *&x, int len)
{
	int n;
	for (n=0; n<len; n++) {
		Complex sum(0,0);
		int i;
		for (i=0; i<L; i++) {
			Complex X;
			X = Complex(re[i],im[i]);
			double Omega = 2*PI*i/L;
			Complex z(cos(Omega*n),sin(Omega*n));
			double dw = 2*PI/L;
			sum = sum + X*z*dw;
		}
		double tot = real(sum)/(2*PI);
		x[n] = tot;
	}
}
