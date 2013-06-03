#include "core/core.h"
#include "io/io.h"
#include <math.h>

#include <iostream>
using namespace std;

void Plot(char *data_file, char *image_file, bool plot_points,
		 bool draw_lines, bool draw_bars)
{
	int w,h,maxval;
	w = 654; h = 387; maxval = 255;
	int *img = new int[w*h];
	int y0,y1,x0,x1;
	y0 = 404 - 68; y1 = 77;
	x0 = 67; x1 = 623;
	Plot(data_file, img,w,h,maxval, x0,y0,x1,y1, plot_points,
		draw_lines, draw_bars);

	PGM_P2_From_Image(image_file, img, w, h, maxval);
	delete []img;
}