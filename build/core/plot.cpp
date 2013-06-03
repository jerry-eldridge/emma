#include "core/core.h"
#include "io/io.h"
#include <math.h>

#include <iostream>
using namespace std;
#include <fstream>

void Plot(char *data_file, int *img, int w, int h, int maxval,
		  int x0, int y0, int x1, int y1, bool plot_points,
		  bool draw_lines, bool draw_bars)
{

	SetIntArray(img, w, h, maxval);
	int ni,nj;
	nj = 5; ni = 10;
	double dx, dy;
	dy = 1.0*(y1-y0)/nj; dx = 1.0*(x1-x0)/ni;

	// Assign Colors (Grayscale)
	// use three images (R,G,B) to do color
	int black = 0;
	int color_text, color_box, color_point, color_line;
	color_text = color_box = color_point = black;
	color_line = 255/2;
	int point_radius = 2;

	// Draw Title
	PutText(img,w,h,data_file,11,11,FONT_PLAIN,20,20,0.42,color_text);

	// DrawBox
	DrawLine(img,w,h, x0,y0, x1,y0, color_box);
	DrawLine(img,w,h, x0,y0, x0,y1, color_box);
	DrawLine(img,w,h, x0,y1, x1,y1, color_box);
	DrawLine(img,w,h, x1,y1, x1,y0, color_box);

	ifstream in3(data_file);
	double x, y, xp, yp;
	double xmin, xmax, ymin, ymax;
	xmin = ymin = INFINITY;
	xmax = ymax = -INFINITY;
	while (!in3.eof()) {
		in3 >> x >> y;
		xmin = min(xmin, x);
		xmax = max(xmax, x);
		ymin = min(ymin, y);
		ymax = max(ymax, y);
	}
	in3.close();
	//cout << "xmin,xmax, ymin,ymax = " <<
	//	xmin << " " << xmax << ", " << ymin << " " << ymax << endl;

	// Draw Markers
	int i;
	for (i=0; i<=nj; i++) {
		int ya = y0 + dy*i;
		int yb = ya;
		int xa = x0;
		int xb = x0 + 10;
		DrawLine(img,w,h, xa,ya, xb,yb, color_box);
		char str[4096] = "";
		double data = ymin + i*1.0*(ymax-ymin)/nj;
		sprintf(str, "%3.1f", data);
		int xc = x0 - 23;
		int yc = ya;
		PutText(img,w,h, str, xc,yc, FONT_PLAIN, 15,15,0.35,color_text);
	}
	for (i=0; i<=ni; i++) {
		int ya = y0;
		int yb = ya-10;
		int xa = x0 + dx*i;
		int xb = xa;
		DrawLine(img,w,h, xa,ya, xb,yb, color_box);
		char str[1024];
		double data = xmin + i*1.0*(xmax-xmin)/ni;
		sprintf(str, "%3.1f", data);
		int xc = xa;
		int yc = ya+10;
		PutText(img,w,h, str, xc,yc, FONT_PLAIN, 15,15,0.35,color_text);
	}

	ifstream in2(data_file);
	double lxp, lyp;
	lxp = x0; lyp = y0;
	double mx, my, yz;
	while (!in2.eof()) {
		in2 >> x >> y;
		mx = 1.0*(x1-x0)/(xmax-xmin);
		xp = mx*(x-xmin) + x0;
		my = 1.0*(y1-y0)/(ymax-ymin);
		yp = my*(y-ymin) + y0;
		if (plot_points) Ellipse(img,w,h, xp,yp, 
			point_radius,point_radius, color_point);
		if (draw_lines) {
			DrawLine(img,w,h, lxp,lyp,xp,yp, color_line);
			Ellipse(img,w,h, xp,yp, 
				.5,.5, color_line);
		}
		yz = my*(0-ymin) + y0;
		if (draw_bars) DrawLine(img,w,h, xp,yz, xp,yp, color_point);
		lxp = xp; lyp = yp;
	}
	DrawLine(img,w,h, x0,yz, x1,yz, color_box);

	in2.close();
	in2.clear();
}

void GraphPaper(int *&img, int w, int h, int maxval,
				 int ni, int nj, int col)
{
	SetIntArray(img, w, h, maxval);

	int i, j;
	for (j=0; j<h/nj; j++) {
		DrawLine(img,w,h, 0,j*nj, w,j*nj, col);
		char buff[4096] = "";
		sprintf(buff, "%d", j);
		PutText(img,w,h, buff, 0,(h/nj-1)*nj-j*nj, FONT_PLAIN, ni, nj);
	}
	for (i=0; i<w/ni; i++) {
		DrawLine(img,w,h, i*ni,0, i*ni,h, col);
		char buff[4096] = "";
		sprintf(buff, "%d", i);
		PutText(img,w,h, buff, i*ni,h-nj, FONT_PLAIN, ni, nj);
	}
}

void GraphPolygon(int *img, int w, int h, int maxval,
				  char *filename, int xsize, int ysize, 
				  int line_color, int grid_color, bool draw_ellipse)
{
	GraphPaper(img, w, h, maxval, w/xsize, h/ysize, grid_color);
	polygon ship;
	ship.parts.push(-1); // for debuggger, ignored
	ReadPolygon(filename, &ship);

	int i = 0;
	point last_pt = ship.p[0];
	do {
		point pt = ship.p[i];
		double sx, sy;
		sx = w/xsize; sy = h/ysize;
		DrawLine(img,w,h,
			last_pt.x*sx+0.5*sx,h-last_pt.y*sy-0.5*sy,
			pt.x*sx+0.5*sx,h-pt.y*sy-0.5*sy,line_color);
		if (draw_ellipse)
			Ellipse(img,w,h, pt.x*sx+0.5*sx, h-pt.y*sy-0.5*sy,
				sx*0.25, sy*0.25, line_color);
		i++;
		last_pt = pt;
	} while (i<ship.np); 

}

void GraphPolygon2(int *img, int w, int h, int maxval,
				  polygon *ship, int xsize, int ysize, 
				  int line_color, int grid_color, bool draw_ellipse)
{
	GraphPaper(img, w, h, maxval, w/xsize, h/ysize, grid_color);

	int i = 0;
	point last_pt = ship->p[0];
	do {
		point pt = ship->p[i];
		double sx, sy;
		sx = w/xsize; sy = h/ysize;
		DrawLine(img,w,h,
			last_pt.x*sx+0.5*sx,h-last_pt.y*sy-0.5*sy,
			pt.x*sx+0.5*sx,h-pt.y*sy-0.5*sy,line_color);
		if (draw_ellipse)
			Ellipse(img,w,h, pt.x*sx+0.5*sx, h-pt.y*sy-0.5*sy,
				sx*0.25, sy*0.25, line_color);
		i++;
		last_pt = pt;
	} while (i<ship->np); 

}