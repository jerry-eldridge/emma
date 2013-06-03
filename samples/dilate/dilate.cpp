#include <iostream>
using namespace std;

#pragma comment(lib,"emma.lib")
#include "core/core.h"
#include "io/io.h"

int main()
{
	int w,h,maxval;
	w = 500; h = 500; maxval = 255;
	int *img = new int[w*h];
	SetIntArray(img,w,h,0);
	DrawLine(img,w,h,20,30,100,200,255);

	double *dimg = new double[w*h];
	CopyIntToDoubleArray(img,dimg,w,h);
	int i;
	for (i=0; i<10; i++) {
		DilateDoubleArray(dimg,w,h);
	}
	CopyDoubleToIntArray(dimg,img,w,h);
	delete []dimg;
	char filename[1024]="dilate.pgm";
	PGM_P5_From_Image(filename,img,w,h);
	system(filename);
	delete []img;

	return 0;
}