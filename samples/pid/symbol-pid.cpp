#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"
#include "io/jpg.h"

#include "font2.h"
#include <math.h>

int gw = 500, gh = 500;
int gmaxval = 255;
int *gimg = 0;

int main() 
{
	double dt = 0.1;
	double omega = 0.4;// 1.6
	double nu = 0.01;
	double eta = 0.1; // 0.707

	int w = gw, h = gh;
	gimg = new int[w*h];

	char ifile[2048] = "mothersday.jpg";
	char str[2048] = "Happy Mother's Day";
	int i;
	char ifile2[2048] = "";
	SetIntArray(gimg, w, h, gmaxval);
	PutText(gimg,w,h,str,10,50,"font3",50,50,0.42,0);
	int n = 7;
	for (i=0; i<n; i++) {
		PutTextPID(gimg,w,h,str,10,100+50*i,"font3",50,50,0.42,0,
				dt, omega, nu, eta+0.6*i/n);
	}
	JPG_From_Image(ifile, gimg, w, h);
	//PGM_P2_From_Image(ifile, gimg, w, h, gmaxval);
	system(ifile);

	delete []gimg;

}
