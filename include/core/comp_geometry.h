#ifndef _COMP_GEOMETRY_H
#define _COMP_GEOMETRY_H

#include "core/common.h"
#include <iostream>
using namespace std;
#include <string>
#include <queue>

class polygon {
public:
	point *p;
	int np;
	queue<int> parts;
	point centroid;
	string name;
	polygon() {p = 0; np = 0; name = ""; }
	~polygon() { if (p) delete []p; np = 0; }
};

point PolygonCentroid(point *p, int np, double *area = 0);
bool SegmentIntersect(double Ax, double Ay,double Bx, double By,
	double Cx, double Cy,double Dx, double Dy,
	double &X, double &Y);
int PointInPolygonTest(point *p, int N, double x, double y);
bool PolyPolyIntersect(point *p, int np, point *q, int nq);
void ReadPolygon(char *poly_file, polygon *poly);
void SavePolygon(polygon *poly, char *poly_file);

#endif
