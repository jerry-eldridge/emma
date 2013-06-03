#ifndef _COLORDOUBLEARRAY_H
#define _COLORDOUBLEARRAY_H

#include "core/common.h"
#include "core/colorimage.h"

class ColorDoubleArray {
public:
	double *r;
	double *g;
	double *b;
	int N1;
	int N2;
	int MAXVAL;
	ColorDoubleArray();
	ColorDoubleArray(int n1, int n2);
	ColorDoubleArray(ColorImage colImage);
	~ColorDoubleArray();
	void Clear(double R, double G, double B);
	void SetPixel(int n, double R, double G, double B);
	void GetPixel(int n, double &R, double &G, double &B);
	void SetPixel2(int i, int j, double R, double G, double B);
	void GetPixel2(int i, int j, double &R, double &G, double &B);
	double Greyscale(int n);
	double Greyscale2(int i, int j);
	void alloc();
	void free();
	void CopyInt(ColorImage colImage);
};


#endif
