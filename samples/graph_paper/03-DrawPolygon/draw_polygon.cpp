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

	GraphPolygon(img,w,h,maxval,"space_ship.txt",20,20,
		0, 210);
	//GraphPolygon(img,w,h,maxval,"space_ship.txt",20,20,
	//	0, 210, false);

	char filename[4098] = "paper25.jpg";
	JPG_From_Image(filename,img,w,h);
	system(filename);

	//system("pause");
	return 0;
}
