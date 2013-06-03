#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include "core/core.h"
#include "io/io.h"
#include "io/jpg.h"

int main()
{
	int maxval = 255;
	int w = 500, h = 500;
	int *img = new int[w*h];

	int iw, ih;
	iw = ih = 20;
	GraphPaper(img, w, h, maxval, w/iw, h/ih,210);
	char filename[4098] = "paper20.jpg";
	JPG_From_Image(filename,img,w,h);
	system(filename);

	system("pause");
	return 0;
}
