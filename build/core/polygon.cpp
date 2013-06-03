#include "core/core.h"
#include <math.h>

#include <iostream>
using namespace std;

void DrawLines(int *&image, int w, int h,
				 pointDouble *p, int N,
				 int val)
{
	int i;
	for (i = 0; i<N-1; i++) {
		DrawLine(image, w, h, p[i].x, p[i].y, p[i+1].x, p[i+1].y, val);
	}
}

void DrawPolygon(int *&image, int w, int h,
				 pointDouble *p, int N,
				 int val)
{
	DrawLines(image, w, h, p, N, val);
	if (N < 3) return;
	DrawLine(image, w, h, p[N-1].x, p[N-1].y, p[0].x, p[0].y, val);
}

// http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/ Point in Polygon Test
// "The following code is by Randolph Franklin, it returns 1 for interior points and 0 for exterior points." 
// -- pbourke webpage. Code below based on the webpage code.
int PointInPolygonTest(pointDouble *p, int N, double x, double y)
{
	bool support;
	int i, j, c = 0;
	for (i = 0, j = N-1; i < N; j = i++) {
		support = ((((p[i].y <= y) && (y < p[j].y)) ||
             ((p[j].y <= y) && (y < p[i].y))) &&
            (x < (p[j].x - p[i].x) * (y - p[i].y) / (p[j].y - p[i].y) + p[i].x));
		if (support) {
			c = !c;
		}
	}
	return c;
}


double BSpline_Patch(double u, double v, double *P)
{
	double val;
	double U[4], V[4];
	static double B[] = {
		-1, 3, -3, 1,
		3, -6, 3, 0,
		-3, 0, 3, 0,
		1, 4, 1, 0
	};
	static double BT[] = {
		-1, 3, -3, 1,
		3, -6, 0, 4,
		-3, 3, 3, 1,
		1, 0, 0, 0
	};	
	int i;
	double prod;
	prod = 1;
	for (i=3; i>=0; i--) {
		U[i] = prod;
		prod *= u;
	}
	prod = 1;
	for (i=3; i>=0; i--) {
		V[i] = prod;
		prod *= v;
	}

	double *A1, *A2, *A3, *A4;
	A1 = new double[4*1];
	MultiplyDoubleArrays(BT, V, A1, 4,4,1);
	A2 = new double[4*1];
	MultiplyDoubleArrays(P, A1, A2, 4,4,1);
	A3 = new double[4*1];
	MultiplyDoubleArrays(B, A2, A3, 4,4,1);
	A4 = new double[1*1];
	MultiplyDoubleArrays(U, A3, A4, 1,4,1);

	val = A4[0]/36.0;

	delete []A1;
	delete []A2;
	delete []A3;
	delete []A4;

	return val;
}

double Bezier_Patch(double u, double v, double *P)
{
	double val;
	double U[4], V[4];
	static double B[] = {
		-1, 3, -3, 1,
		3, -6, 3, 0,
		-3, 3, 0, 0,
		1, 0, 0, 0
	};
	int i;
	double prod;
	prod = 1;
	for (i=3; i>=0; i--) {
		U[i] = prod;
		prod *= u;
	}
	prod = 1;
	for (i=3; i>=0; i--) {
		V[i] = prod;
		prod *= v;
	}

	double *A1, *A2, *A3, *A4;
	A1 = new double[4*1];
	MultiplyDoubleArrays(B, V, A1, 4,4,1);
	A2 = new double[4*1];
	MultiplyDoubleArrays(P, A1, A2, 4,4,1);
	A3 = new double[4*1];
	MultiplyDoubleArrays(B, A2, A3, 4,4,1);
	A4 = new double[1*1];
	MultiplyDoubleArrays(U, A3, A4, 1,4,1);

	val = A4[0];

	delete []A1;
	delete []A2;
	delete []A3;
	delete []A4;

	return val;
}
