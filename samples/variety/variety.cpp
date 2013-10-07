#include <iostream>
using namespace std;

#include <core/core.h>
#include <io/io.h>
#include <io/jpg.h>
#pragma comment(lib, "emma.lib")

#include <math.h>

#include <fstream>

float f(float x, float y, float a);
void Draw(int *img, int w, int h, float a);

int main()
{
	int w, h;
	w = 500; h = 500;
	int *img = new int[w*h];
	SetIntArray(img,w,h,255);

	Draw(img,w,h,.4);
	Draw(img,w,h,-.4);

	char filename[4096]="variety.jpg";

	JPG_From_Image(filename,img,w,h);
	system(filename);

	delete []img;

	system("pause");
	return 0;
}

void Draw(int *img, int w, int h, float a)
{
	float eps = .1;
	int i,j;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			float x, y;
			x = 1.*(i-w/2)/w*10;
			y = 1.*(j-h/2)/h*10;
			if (fabs(f(x,y,a)) < eps) {
				int r = 1;
				Ellipse(img,w,h,i,j,r,r,0);
				//img[j+h*i] = 0;
			}
		}
	}
}

float f(float x, float y, float a)
{
	float F;
	F = x*x - y*y*y + a;
	return F;
}
