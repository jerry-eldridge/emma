#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include "core/core.h"
#include "io/io.h"
#include "io/jpg.h"

void CreatePaper(int *&img, int w, int h, int maxval,
				 int ni, int nj);
int main() 
{

	int maxval = 255;
	int w = 500, h = 500;
	int *img = new int[w*h];

	CreatePaper(img, w, h, maxval, 25, 25);
	char filename[4098] = "paper25.jpg";
	JPG_From_Image(filename,img,w,h);
	system(filename);

	CreatePaper(img, w, h, maxval, 50, 50);
	char filename2[4098] = "paper50.jpg";
	JPG_From_Image(filename2,img,w,h);
	system(filename2);

	delete []img;
}

void CreatePaper(int *&img, int w, int h, int maxval,
				 int ni, int nj)
{
	SetIntArray(img, w, h, maxval);
	int col = 0; // black

	int i, j;
	for (j=0; j<h/nj; j++) {
		DrawLine(img,w,h, 0,j*nj, w,j*nj, col);
		char buff[4096] = "";
		sprintf(buff, "%d", j);
		PutText(img,w,h, buff, 0,(h/nj-1)*nj-j*nj, "font3", ni, nj);
	}
	for (i=0; i<w/ni; i++) {
		DrawLine(img,w,h, i*ni,0, i*ni,h, col);
		char buff[4096] = "";
		sprintf(buff, "%d", i);
		PutText(img,w,h, buff, i*ni,h-nj, "font3", ni, nj);
	}
}