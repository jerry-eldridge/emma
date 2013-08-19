#include "core/core.h"
#include <math.h>

#include <iostream>
using namespace std;

// ColorImage img would have img.r, img.g, img.b
void DrawLine(ColorImage img, point p1, point p2, color col)
{
	int w, h;
	w = img.N1, h = img.N2;
	DrawLine(img.r, w, h, p1, p2, col.r);
	DrawLine(img.g, w, h, p1, p2, col.g);
	DrawLine(img.b, w, h, p1, p2, col.b);
}

void DrawLine(int *&arr, int N1, int N2, point p1, point p2, int val)
{
	double x1, x2, y1, y2;
	x1 = p1.x; y1 = p1.y; x2 = p2.x; y2 = p2.y;
	DrawLine(arr, N1, N2, x1, y1, x2, y2, val);
}

void DrawLine(int *&arr, int N1, int N2, 
			  double x1, double y1, double x2, double y2, int val)
{
	DrawLine_Bresenham(arr, N1, N2, x1, y1, x2, y2, val);
}
// [FIREBAUGH] pg143
void DrawLine_Bresenham(int *&arr, int N1, int N2, double x1, double y1, double x2, double y2, int val)
{
	enum axes {XAXIS, YAXIS};
	enum axes axis;
	double dx, dy, range, errp; 
	int xp, yp;
	int i, j, irange, dxs, dys;
	bool support;

	// Line is a Point
	dy = y2-y1;
	dx = x2-x1;
	if ((dy == 0) && (dx == 0)) {
		i = round(x1); j = round(y1);
		support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
		if (!support) {
			arr[j+N2*i] = val;
		}
		return;
	}

	range = max(fabs(dx), fabs(dy));
	irange = round(range);
	if (fabs(dx) >= fabs(dy)) {
		axis = XAXIS;
	} else {
		axis = YAXIS;
	}
	errp = 2*dy-dx;
	dxs = (dx >= 0) ? 1 : -1;
	dys = (dy >= 0) ? 1 : -1;
	xp = round(x1);
	yp = round(y1);

	switch (axis) {
		case XAXIS:
			for (i=0; i<irange; i++) {
				support = (xp<0)||(xp>=N1)||(yp<0)||(yp>=N2);
				if (!support) {
					arr[yp+N2*xp] = val;
				}
				if (errp > 0) {
					yp += dys;
					errp += -2*dx*dxs;
				}
				xp += dxs;
				errp += 2*dy*dys;
			}
			break;
		case YAXIS:
			for (i=0; i<irange; i++) {
				support = (xp<0)||(xp>=N1)||(yp<0)||(yp>=N2);
				if (!support) {
					arr[yp+N2*xp] = val;
				}
				if (errp > 0) {
					xp += dxs;
					errp += -2*dy*dys;
				}
				yp += dys;
				errp += 2*dx*dxs;
			}
			break;
	}
}

// ColorImage img would have img.r, img.g, img.b
void DrawLine2(ColorImage img, point p1, point p2, color col, 
			   double rx, double ry)
{
	int w, h;
	w = img.N1, h = img.N2;
	DrawLine2(img.r, w, h, p1, p2, col.r, rx, ry);
	DrawLine2(img.g, w, h, p1, p2, col.g, rx, ry);
	DrawLine2(img.b, w, h, p1, p2, col.b, rx, ry);
}

void DrawLine2(int *&arr, int N1, int N2, point p1, point p2, 
			   int val, double rx, double ry)
{
	double x1, x2, y1, y2;
	x1 = p1.x; y1 = p1.y; x2 = p2.x; y2 = p2.y;
	DrawLine2(arr, N1, N2, x1, y1, x2, y2, val, rx, ry);
}

void DrawLine2(int *&arr, int N1, int N2, 
			  double x1, double y1, double x2, double y2, int val,
			  double rx, double ry)
{
	DrawLine_Bresenham2(arr, N1, N2, x1, y1, x2, y2, val, rx, ry);
}
// [FIREBAUGH] pg143
void DrawLine_Bresenham2(int *&arr, int N1, int N2, 
						 double x1, double y1, double x2, double y2, 
						 int val, double rx, double ry)
{
	enum axes {XAXIS, YAXIS};
	enum axes axis;
	double dx, dy, range, errp; 
	int xp, yp;
	int i, j, irange, dxs, dys;
	bool support;

	// Line is a Point
	dy = y2-y1;
	dx = x2-x1;
	if ((dy == 0) && (dx == 0)) {
		i = round(x1); j = round(y1);
		support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
		if (!support) {
			if ((rx <= 1) && (ry <= 1)) {
				arr[j+N2*i] = val;
			} else {
				FillEllipse(arr,N1,N2,i,j,rx,ry,val);
			}
		}
		return;
	}

	range = max(fabs(dx), fabs(dy));
	irange = round(range);
	if (fabs(dx) >= fabs(dy)) {
		axis = XAXIS;
	} else {
		axis = YAXIS;
	}
	errp = 2*dy-dx;
	dxs = (dx >= 0) ? 1 : -1;
	dys = (dy >= 0) ? 1 : -1;
	xp = round(x1);
	yp = round(y1);

	switch (axis) {
		case XAXIS:
			for (i=0; i<irange; i++) {
				support = (xp<0)||(xp>=N1)||(yp<0)||(yp>=N2);
				if (!support) {	
					if ((rx <= 1) && (ry <= 1)) {
						arr[yp+N2*xp] = val;
					} else {
						FillEllipse(arr,N1,N2,xp,yp,rx,ry,val);
					}
				}
				if (errp > 0) {
					yp += dys;
					errp += -2*dx*dxs;
				}
				xp += dxs;
				errp += 2*dy*dys;
			}
			break;
		case YAXIS:
			for (i=0; i<irange; i++) {
				support = (xp<0)||(xp>=N1)||(yp<0)||(yp>=N2);
				if (!support) {	
					if ((rx <= 1) && (ry <= 1)) {
						arr[yp+N2*xp] = val;
					} else {
						FillEllipse(arr,N1,N2,xp,yp,rx,ry,val);
					}
				}
				if (errp > 0) {
					xp += dxs;
					errp += -2*dy*dys;
				}
				yp += dys;
				errp += 2*dx*dxs;
			}
			break;
	}
}

