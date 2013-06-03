#include <iostream>
using namespace std;

#include <complex>
#include <math.h>

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"
#include "io/jpg.h"

#include "sequence.h"

int *gimg = 0;
int maxval, n1, n2;

void lowpass(Sequence x, Sequence &y);
void highpass(Sequence x, Sequence &y);

int main()
{
	Read_PGM_File("paint2.pgm", maxval, n1, n2, gimg);

	Sequence x(gimg, n1, n2);
	Sequence y(gimg, n1, n2);
	highpass(x,y);

	int *lpimg = new int[n1*n2];
	int n;
	for (n=0; n<n1*n2; n++) {
		lpimg[n] = real(y.Get(n));
	}
	char ifile[1024]="highpass.pgm";
	PGM_P5_From_Image(ifile, lpimg, n1, n2);
	system(ifile);

	delete []lpimg;
	delete []gimg;

	system("pause");
	return 0;
}

void lowpass(Sequence x, Sequence &y)
{
	int n;
	Complex z = 0.5*x.Get(0);
	y.Set(0, z);
	for (n=1; n<y.len; n++) {
		z = 0.5*x.Get(n) + 0.5*x.Get(n-1);
		y.Set(n, z);
	}
}

void highpass(Sequence x, Sequence &y)
{
	int n;
	Complex z = 0.5*x.Get(0);
	y.Set(0, z);
	for (n=1; n<y.len; n++) {
		z = 0.5*x.Get(n) - 0.5*x.Get(n-1);
		y.Set(n, z);
	}
}