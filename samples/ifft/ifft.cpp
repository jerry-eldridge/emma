#include <iostream>
using namespace std;

#include <complex>
#include <math.h>

#include <fstream>

typedef complex<double> Complex;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"
#include "io/jpg.h"

Complex FT_Helper(double *x, int N, double omega);
void FT(double *x, int N, double *&re, double *&im);
void IFT(double *re, double *im, double *&x, int N);
Complex XX(Complex z);
Complex HH(double omega);

int main()
{
	int N = 50;
	Complex *X = new Complex[N];
	double *re = new double[N];
	double *im = new double[N];
	int i;
	for (i=0; i<N; i++) {
		double omega = 2*PI*i/N;
		Complex z(cos(omega),sin(omega));
		//X[i] = XX(z);
		X[i] = HH(omega);
		re[i] = real(X[i]);
		im[i] = imag(X[i]);
	}
	char datfile1[1024] = "oppen-p49-H-magn.txt";
	char imgfile1[1024] = "oppen-p49-H-magn.pgm";
	ofstream out(datfile1);
	for (i=0; i<N; i++) {
		double omega = 2*PI*i/N;
		out << omega << " " << norm(X[i]) << endl;
	}
	out.close();
	Plot(datfile1,imgfile1, false,true,false);
	system(imgfile1);

	char datfile2[1024] = "oppen-p49-H-phase.txt";
	char imgfile2[1024] = "oppen-p49-H-phase.pgm";
	out.open(datfile2);
	for (i=0; i<N; i++) {
		double omega = 2*PI*i/N;
		out << omega << " " << arg(X[i]) << endl;
	}
	out.close();
	Plot(datfile2,imgfile2, false,true,false);
	system(imgfile2);

	double *x = new double[N];
	IFT(re,im, x, N);

	char datfile[1024] = "oppen-p49-h.txt";
	char imgfile[1024] = "oppen-p49-h.pgm";
	out.open(datfile);
	for (i=0; i<N; i++) {
		out << i << " " << x[i] << endl;
	}
	out.close();
	Plot(datfile,imgfile, true, false, true);
	system(imgfile);

	delete []x;
	delete []X;
	delete []re;
	delete []im;
	system("pause");
	return 0;
}

// Define z function here
Complex XX(Complex z)
{
	double b = .9; // choose |a| < 1 for absolute summability (Oppenheim, p48)
	Complex a(b,0), one(1,0);
	Complex X = 1.0/(one-a*pow(z,-1));
	return X;
}

// Or, Define omega function here
Complex HH(double omega) // omega in [0, 2*PI)
{
	double omega_c = PI/2; // choose cutoff frequency
	Complex one(1,0), zero(0,0);
	omega = omega - PI; 
	if (abs(omega) < omega_c) {
		return one;
	} else if ((omega_c < abs(omega)) && (abs(omega) <= PI) ) {
		return zero;
	}
}

// Fourier Transform
void FT(double *x, int N, double *&re, double *&im)
{
	int i;
	for (i=0; i<N; i++) {
		double omega = 2*PI*i/N;
		Complex z = FT_Helper(x, N, omega);
		re[i] = real(z);
		im[i] = imag(z);
	}
}

void IFT(double *re, double *im, double *&x, int N)
{
	int n;
	for (n=0; n<N; n++) {
		Complex sum(0,0);
		int i;
		for (i=0; i<N; i++) {
			Complex X;
			X = Complex(re[i],im[i]);
			double omega = 2*PI*i/N;
			Complex z(cos(omega*n),sin(omega*n));
			double dw = 2*PI/N;
			sum = sum + X*z*dw;
		}
		double tot = real(sum)/(2*PI);
		x[n] = tot;
	}
}

Complex FT_Helper(double *x, int N, double omega)
{
	int n;
	Complex sum(0,0);
	for (n=0; n<N; n++) {
		Complex w(x[n],0);
		Complex z(cos(-omega*n),sin(-omega*n));
		sum = sum + w*z;
	}
	return sum;
}