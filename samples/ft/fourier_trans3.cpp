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

int main()
{
	double M1 = 0, M2 = 4;
	int N = 200;
	double *h = new double[N];
	int i;
	for (i=0; i<N; i++) {
		bool support = (i<M1+M2+1);
		h[i] = (support) ? 1.0/(M1+M2+1) : 0;
	}
	double *re = new double[N];
	double *im = new double[N];
	FT(h, N, re, im);
	char datfile[1024] = "oppen-p42-H-amp.txt";
	char imgfile[1024] = "oppen-p42-H-amp.pgm";
	ofstream out(datfile);
	for (i=0; i<N; i++) {
		Complex z(re[i],im[i]);
		double val = norm(z);
		double omega = 2*PI*i/N;
		out << omega << " " << val << endl;
	}
	out.close();
	Plot(datfile,imgfile, false);
	system(imgfile);

	char datfile2[1024] = "oppen-p42-H-phase.txt";
	char imgfile2[1024] = "oppen-p42-H-phase.pgm";
	out.open(datfile2);
	for (i=0; i<N; i++) {
		Complex z(re[i],im[i]);
		double val = arg(z);
		double omega = 2*PI*i/N;
		out << omega << " " << val << endl;
	}
	out.close();
	Plot(datfile2,imgfile2, false);
	system(imgfile2);

	delete []h;
	delete []re;
	delete []im;
	system("pause");
	return 0;
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