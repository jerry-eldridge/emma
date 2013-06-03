#include "core/core.h"
#include <math.h>

#include <iostream>
using namespace std;

void Ellipse(int *img, int w, int h, 
			 double cx, double cy, double rx, double ry, int val)
{
	double x, y, a, da;
	int N = 60;
	da = 2*PI/N;
	a = 0;
	double lx, ly;
	lx = rx + cx; ly = cy;
	while (a < 2*PI+2*da) {
		x = rx*cos(a) + cx;
		y = ry*sin(a) + cy;
		x = round(x); y = round(y);
		DrawLine(img, w, h, lx, ly, x, y, val);
		lx = x; ly = y;
		a = a + da;
	}

}

void FillEllipse(int *img, int w, int h, 
			 double cx, double cy, double rx, double ry, int val)
{
	int i, j;
	int i0, i1, j0, j1;
	i0 = cx - rx; i1 = cx + rx;
	j0 = cy - ry; j1 = cy + ry;
	i0 = max(0,i0); i1 = min(w, i1);
	j0 = max(0,j0); j1 = min(h, j1);
	for (j=j0; j<j1; j++) {
		for (i=i0; i<i1; i++) {
			double xx, yy;
			xx = (i-cx)/rx; yy = (j-cy)/ry;
			bool support = (xx*xx+yy*yy <= 1.0);
			if (support) img[j+i*h] = val;
		}
	}
}
