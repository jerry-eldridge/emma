#ifndef _COMMON_H
#define _COMMON_H

//#define _MAXVAL_ONLY_255

#define MAX_N1	2048
#define MAX_N2  2048

#define P1_MAXVAL 1
#define P2_MAXVAL 255
#define P3_MAXVAL 255

#define INFINITY 1e80
#define TWOPI 6.283185307179586476925286766559
#define PI 3.1415926535897932384626433832795

typedef struct point_ {
	double x;
	double y;
	void point(double x0, double y0) { x = x0; y = y0; } 
} point;

typedef struct point3_ {
	double x;
	double y;
	double z;
	// double w;
	void point3(double x0, double y0, double z0) 
		{ x = x0; y = y0; z = z0;} 
} point3;

typedef struct pointDouble_ {
	double x;
	double y;
	void pointDouble(double x0, double y0) { x = x0; y = y0; } 
} pointDouble;

typedef struct color_ {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	void color(	unsigned char r0, unsigned char g0, unsigned char b0) 
		{ r = r0; g = g0; b = b0; } 
} color;

#endif
