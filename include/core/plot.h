#ifndef _PLOT_H
#define _PLOT_H

#include "core/comp_geometry.h"

void Plot(char *data_file, int *img, int w, int h, int maxval,
		  int x0, int y0, int x1, int y1, bool plot_points = true,
		  bool draw_lines = true, bool draw_bars = false);
void GraphPaper(int *&img, int w, int h, int maxval,
				 int ni=25, int nj=25, int col = 0);
void GraphPolygon(int *img, int w, int h, int maxval,
				  char *filename, int xsize = 20, int ysize = 20, 
				  int line_color = 0, int grid_color = 127,
				  bool draw_ellipse = true);
void GraphPolygon2(int *img, int w, int h, int maxval,
				  polygon *P, int xsize = 20, int ysize = 20, 
				  int line_color = 0, int grid_color = 127,
				  bool draw_ellipse = true);

#endif
