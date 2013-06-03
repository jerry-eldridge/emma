#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"

#include "io/jpg.h"

int main() 
{
	int w = 500, h = 500; // width, height
	ColorImage img(w,h);
	img.Clear(255, 255, 255);
	int i, j;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			img.SetPixel2(i,j, 255.0*j/h, 100, 200);
		}
	}

	char imagefile[4096] = "gradient.ppm";
	img.Save_PGM_P6(imagefile);
	system(imagefile); // 'double click' on imagefile

	char imagefile2[4096] = "gradient.jpg";
	Save_JPG_P6(&img, imagefile2);
	system(imagefile2); // 'double click' on imagefile

	system("pause");
	return 0;
}
