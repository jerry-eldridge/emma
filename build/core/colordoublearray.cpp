#include "core/colordoublearray.h"
#include "core/int_images.h"

void ColorDoubleArray::CopyInt(ColorImage colImage)
{
	CopyIntToDoubleArray(colImage.r, r, N1, N2);
	CopyIntToDoubleArray(colImage.g, g, N1, N2);
	CopyIntToDoubleArray(colImage.b, b, N1, N2);
}


ColorDoubleArray::ColorDoubleArray(int n1, int n2)
{
	r = g = b = 0;
	N1 = n1; N2 = n2;
	alloc();
}

ColorDoubleArray::ColorDoubleArray(ColorImage colImage)
{
	r = g = b = 0;
	N1 = colImage.N1; N2 = colImage.N2;
	alloc();
}

ColorDoubleArray::ColorDoubleArray()
{
	r = g = b = 0;
}
ColorDoubleArray::~ColorDoubleArray()
{
	free();
}
void ColorDoubleArray::Clear(double R, double G, double B)
{
	int n;
	for (n=0; n<N1*N2; n++) {
		r[n] = R;
		g[n] = G;
		b[n] = B;
	}
}
double ColorDoubleArray::Greyscale2(int i, int j)
{
	return 0.3*r[j+N2*i]+0.59*g[j+N2*i]+0.11*b[j+N2*i];
}

void ColorDoubleArray::alloc()
{
	r = new double[N1*N2];
	g = new double[N1*N2];
	b = new double[N1*N2];
}
void ColorDoubleArray::free()
{
	if (!r) delete []r;
	if (!g) delete []g;
	if (!b) delete []b;
	r = g = b = 0;
}
void ColorDoubleArray::SetPixel(int n, double R, double G, double B)
{
	r[n] = R; g[n] = G; b[n] = B;
}
void ColorDoubleArray::GetPixel(int n, double &R, double &G, double &B)
{
	R = r[n]; G = g[n]; B = b[n];
}
void ColorDoubleArray::SetPixel2(int i, int j, double R, double G, double B)
{
	r[j+N2*i] = R; g[j+N2*i] = G; b[j+N2*i] = B;
}
void ColorDoubleArray::GetPixel2(int i, int j, double &R, double &G, double &B)
{
	R = r[j+N2*i]; G = g[j+N2*i]; B = b[j+N2*i];
}
double ColorDoubleArray::Greyscale(int n)
{
	return 0.3*r[n]+0.59*g[n]+0.11*b[n];
}
