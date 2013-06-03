#include <iostream>
using namespace std;
#include <math.h>
#include <fstream>
#include <queue>

#include "core/common.h"
#include "core/comp_geometry.h"

// http://en.wikipedia.org/wiki/Centroid#Centroid_of_polygon
point PolygonCentroid(point *p, int np, double *area)
{
    double Cx, Cy;
	double A; 
	int i;

	A = 0;
	for (i=0; i<np-1; i++) {
		A += (p[i].x*p[i+1].y-p[i+1].x*p[i].y);
	}
	i = np-1;
	A += (p[i].x*p[0].y-p[0].x*p[i].y);
	A /= 2.0;

	Cx = 0; Cy = 0;
	for (i=0; i<np-1; i++) {
		Cx += (p[i].x+p[i+1].x)*(p[i].x*p[i+1].y-p[i+1].x*p[i].y);
		Cy += (p[i].y+p[i+1].y)*(p[i].x*p[i+1].y-p[i+1].x*p[i].y);
	}
	i = np-1;
	Cx += (p[i].x+p[0].x)*(p[i].x*p[0].y-p[0].x*p[i].y);
	Cy += (p[i].y+p[0].y)*(p[i].x*p[0].y-p[0].x*p[i].y);
	Cx /= (6.0*A);
	Cy /= (6.0*A);

	point centroid;
	centroid.x = Cx;
	centroid.y = Cy;
	if (area != 0) *area = A;
	return centroid;
}

//  public domain function by Darel Rex Finley, 2006
//  Determines the intersection point of the line segment defined by points A and B
//  with the line segment defined by points C and D.
//  Returns YES if the intersection point was found, and stores that point in X,Y.
//  Returns NO if there is no determinable intersection point, in which case X,Y will
//  be unmodified. [with minor edits by JGE]
bool SegmentIntersect(double Ax, double Ay,double Bx, double By,
	double Cx, double Cy,double Dx, double Dy,
	double &X, double &Y) 
{

  double  distAB, theCos, theSin, newX, ABpos ;

  //  Fail if either line segment is zero-length.
  if (Ax==Bx && Ay==By || Cx==Dx && Cy==Dy) return false;

  //  Fail if the segments share an end-point.
  if (Ax==Cx && Ay==Cy || Bx==Cx && By==Cy
  ||  Ax==Dx && Ay==Dy || Bx==Dx && By==Dy) {
    return false; }

  //  (1) Translate the system so that point A is on the origin.
  Bx-=Ax; By-=Ay;
  Cx-=Ax; Cy-=Ay;
  Dx-=Ax; Dy-=Ay;

  //  Discover the length of segment A-B.
  distAB=sqrt(Bx*Bx+By*By);

  //  (2) Rotate the system so that point B is on the positive X axis.
  theCos=Bx/distAB;
  theSin=By/distAB;
  newX=Cx*theCos+Cy*theSin;
  Cy  =Cy*theCos-Cx*theSin; Cx=newX;
  newX=Dx*theCos+Dy*theSin;
  Dy  =Dy*theCos-Dx*theSin; Dx=newX;

  //  Fail if segment C-D doesn't cross line A-B.
  if (Cy<0. && Dy<0. || Cy>=0. && Dy>=0.) return false;

  //  (3) Discover the position of the intersection point along line A-B.
  ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);

  //  Fail if segment C-D crosses line A-B outside of segment A-B.
  if (ABpos<0. || ABpos>distAB) return false;

  //  (4) Apply the discovered position to line A-B in the original coordinate system.
  X=Ax+ABpos*theCos;
  Y=Ay+ABpos*theSin;

  //  Success.
  return true; 
} 

// http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/ Point in Polygon Test
// "The following code is by Randolph Franklin, it returns 1 for interior points and 0 for exterior points." 
// -- pbourke webpage. Code below based on the webpage code.
int PointInPolygonTest(point *p, int N, double x, double y)
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

// (temporary implemention) Routine to test polygon-polygon intersection
bool PolyPolyIntersect(point *p, int np, point *q, int nq)
{
	int i, j;
	for (i=0; i<np; i++) {
		for (j=0; j<nq; j++) {
			double Ax, Ay, Bx, By, Cx, Cy, Dx, Dy, X, Y;
			Ax = p[i].x; Ay = p[i].y; 
			Bx = p[(i+1)%np].x; By = p[(i+1)%np].y;
			Cx = q[j].x; Cy = q[j].y; 
			Dx = q[(j+1)%nq].x; Dy = q[(j+1)%nq].y;
			bool found = SegmentIntersect(Ax,Ay,Bx,By,Cx,Cy,Dx,Dy,X,Y);
			if (found) {
				return true;
			}
		}
	}
	return false;
}

void ReadPolygon(char *poly_file, polygon *poly)
{
	ifstream in(poly_file);
	int np, n_parts;
	double x, y;
	int part;
	in >> np;
	poly->name = "";
	poly->p = new point[np];
	poly->np = np;
	int i;
	for (i=0; i<np; i++) {
		in >> x >> y;
		poly->p[i].x = x;
		poly->p[i].y = y;
	}
	in >> n_parts;
	while (!poly->parts.empty()) {
		poly->parts.pop();
	}
	for (i=0; i<n_parts; i++) {
		in >> part;
		poly->parts.push(part);
	}
	poly->centroid = PolygonCentroid(poly->p,poly->np);

	in.close();
}

void SavePolygon(polygon *poly, char *poly_file)
{
	int np, n_parts;
	double x, y;
	int part;
	np = poly->np;
	n_parts = poly->parts.size();
	ofstream out(poly_file);
	out << np << endl;
	int i;
	for (i=0; i<np; i++) {
		x = poly->p[i].x;
		y = poly->p[i].y;
		out << x << " " << y << endl;
	}
	out << n_parts << endl;
	for (i=0; i<n_parts; i++) {
		part = poly->parts.front(); poly->parts.pop();
		poly->parts.push(part);
		out << part << endl;
	}
	out.close();
}