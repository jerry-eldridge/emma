#ifndef _POLYGON_H
#define _POLYGON_H

#include "core/common.h"
void DrawLines(int *&img, int w, int h,
				 pointDouble *p, int N,
				 int val);
void DrawPolygon(int *&img, int w, int h,
				 pointDouble *p, int N,
				 int val);
int PointInPolygonTest(pointDouble *p, int N, double x, double y); //uses pbourke website
double BSpline_Patch(double u, double v, double *P);
double Bezier_Patch(double u, double v, double *P);

#endif
