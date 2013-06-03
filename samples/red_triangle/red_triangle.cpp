#include <iostream>
using namespace std;

#include <math.h>

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"

void DrawLine(ColorImage *img, int w, int h, 
	   point A, point B, color col);
void DrawTriangle(ColorImage *img, int w, int h,
		point A, point B, point C, color col);
void PolygonFill(ColorImage *img, int w, int h,
		 pointDouble *p, int N, color col);
void DrawPolygon(ColorImage *img, int w, int h,
		 pointDouble *p, int N, color col);
void PolygonFill(ColorImage *img, int w, int h,
		polygon *poly, color col, int skip = 1);

int main() 
{

	int w = 500, h = 500; // width, height
	ColorImage img(w,h);
	img.Clear(255, 255, 255);

	point p1, p2, p3;
	p1.x = 40; p1.y = 100;
	p2.x = 60; p2.y = 300;
	p3.x = 300; p3.y = 300;

	const int N  = 4;
	pointDouble *p = new pointDouble[N];
	p[0].x = p1.x; p[0].y = p1.y;
	p[1].x = p2.x; p[1].y = p2.y;
	p[2].x = p3.x; p[2].y = p3.y;
	p[3].x = p1.x; p[3].y = p1.y;

	color col, green;
	col.r = 255; col.g = 0; col.b = 0;
	//DrawTriangle(&img, w, h, p1, p2, p3, col); 
	PolygonFill(&img, w, h, p, N, col);

	polygon poly;
	int i;
	double scale = 0.25;
	ReadPolygon("tree_polygon.txt", &poly);
	int skip = 5;
	for (i=0; i<poly.np; i++) {
		poly.p[i].x *= scale;
		poly.p[i].y *= scale;
	}
	col.r = 50; col.g = 100; col.b = 30;
	PolygonFill(&img, w, h, &poly, col, skip);

	char ppmfile[4096] = "red_triangle.ppm";

	img.Save_PGM_P6(ppmfile);
	system(ppmfile);

	char jpgfile[4096] = "red_triangle.jpg";

	char command[1024];
	static char path[1024] = "C:\\_Program Files\\GnuWin32\\bin\\";
	static char prog[1024] = "cjpeg.exe"; //jpg to pgm, and other file formats
	static char switches[1024] = "";
	sprintf(command, "\"%s%s\" %s -outfile .\\%s %s", path, prog, switches, jpgfile, ppmfile);
	system(command);

	system(jpgfile);

	delete []p;

	system("pause");
	return 0;
}

void DrawLine(ColorImage *img, int w, int h, 
	   point A, point B, color col)
{
	DrawLine(img->r, w, h, A, B, col.r); // red plane
	DrawLine(img->g, w, h, A, B, col.g); // green plane
	DrawLine(img->b, w, h, A, B, col.b); // blue plane
}

void DrawTriangle(ColorImage *img, int w, int h,
		point A, point B, point C, color col)
{
	DrawLine(img, w,h, A, B, col);
	DrawLine(img, w,h, B, C, col);
	DrawLine(img, w,h, C, A, col);
}

void DrawPolygon(ColorImage *img, int w, int h,
		 pointDouble *p, int N, color col)
{
	DrawPolygon(img->r, w, h, p, N, col.r);
	DrawPolygon(img->g, w, h, p, N, col.g);
	DrawPolygon(img->b, w, h, p, N, col.b);
}

void PolygonFill(ColorImage *img, int w, int h,
		 pointDouble *p, int N, color col)
{
	PolygonFill(img->r, w, h, p, N, col.r);
	PolygonFill(img->g, w, h, p, N, col.g);
	PolygonFill(img->b, w, h, p, N, col.b);
}

void PolygonFill(ColorImage *img, int w, int h,
		polygon *poly, color col, int skip)
{
	if (skip < 1) return;
	int nparts, np, inp, idx1, idx2;
	nparts = poly->parts.size();
	np = poly->np;
	if (nparts > 0) {
		inp = nparts;
		idx1 = poly->parts.front();
		while (inp > 0) {
			poly->parts.pop(); 
			inp--;
			poly->parts.push(idx1);
			if (inp > 0) {
				idx2 = poly->parts.front();
			} else {
				idx2 = np-1;
			}
			const int np2 = (idx2-idx1)/skip;
			pointDouble *p = new pointDouble[np2 + 1];
			int i;
			for (i=0; i<idx2-idx1; i = i+skip) {
				p[i/skip].x = ((poly->p)+idx1)[i].x;
				p[i/skip].y = ((poly->p)+idx1)[i].y;
			}
			PolygonFill(img, w, h, p, np2, col);
			delete []p;
			idx1 = idx2;
		}
	}
}