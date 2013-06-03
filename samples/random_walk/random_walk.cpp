#include <iostream>
using namespace std;

#include <core/core.h>
#include <io/io.h>
#pragma comment(lib, "emma.lib")

#include <math.h>
#include <time.h>

int main()
{
	int w, h;
	w = h = 500;
	int *img = new int[w*h];
	SetIntArray(img,w,h, 255);

	srand(time(0));

	int color = 0;
	int x = rand()%w;
	int y = rand()%h;
	int lx, ly;
	lx = x; ly = y;
	int r = 5;
	int i;
	for (i=0; i<10000; i++) {
		int a = rand()%500;
		float theta = 2*PI*a/500;
		float dx = r*cos(theta);
		float dy = r*sin(theta);
	
		x = round(x + dx)%w;
		y = round(y + dy)%h;
		DrawLine(img,w,h, lx,ly,x,y,color);
		lx = x; ly = y;
	}

	char imgfile[1024] = "random_walk.pgm";
	PGM_P5_From_Image(imgfile, img,w,h);
	system(imgfile);

	delete []img;
	system("pause");
	return 0;
}