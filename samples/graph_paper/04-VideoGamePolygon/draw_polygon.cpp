#include <iostream>
using namespace std;
#include <math.h>

#pragma comment(lib, "emma.lib")

#include "core/core.h"
#include "io/io.h"
#include "io/jpg.h"

int main()
{
	int maxval = 255;
	int w = 500, h = 500;
	int *img = new int[w*h];

	char filename0[4096] = "space_ship.txt";

	// Need to compile with Release version (eg, in VC++2008)
	polygon ship;
	ship.parts.push(-1);
	ReadPolygon(filename0, &ship);

	GraphPolygon2(img,w,h,maxval,&ship,20,20,
		0, 210);
	char filename1[4098] = "ship.jpg";
	JPG_From_Image(filename1,img,w,h);
	system(filename1);

	int i;
	int np = ship.np;
	for (i=0; i<np; i++) {
		ship.p[i].x *= 0.75;
		ship.p[i].y *= 0.75;
	}
	memset(img, 255, w*h);
	GraphPolygon2(img,w,h,maxval,&ship,20,20,
		0, 210);
	char filename2[4098] = "ship-75.jpg";
	JPG_From_Image(filename2,img,w,h);
	system(filename2);
	SavePolygon(&ship, "space_ship_75.txt");

	double area;
	ship.centroid = PolygonCentroid(ship.p, ship.np, &area);
	// translate to origin
	for (i=0; i<np; i++) {
		ship.p[i].x -= ship.centroid.x;
		ship.p[i].y -= ship.centroid.y;
	}
	// rotate about origin
	double theta = 30*(2*PI/360); // 30 degrees
	for (i=0; i<np; i++) {
		double xx, yy;
		xx = ship.p[i].x;
		yy = ship.p[i].y;
		ship.p[i].x = xx*cos(theta)+yy*sin(theta);
		ship.p[i].y = -xx*sin(theta)+yy*cos(theta);
	}
	// translate back from origin
	for (i=0; i<np; i++) {
		ship.p[i].x += ship.centroid.x;
		ship.p[i].y += ship.centroid.y;
	}
	memset(img, 255, w*h);
	GraphPolygon2(img,w,h,maxval,&ship,20,20,
		0, 210);
	char filename3[4098] = "ship-rotate.jpg";
	JPG_From_Image(filename3,img,w,h);
	system(filename3);
	SavePolygon(&ship, "space_ship_rotate.txt");


	//system("pause");
	return 0;
}
