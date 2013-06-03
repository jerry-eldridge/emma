#include <iostream>
using namespace std;

#include <core/core.h>
#include <io/io.h>
#pragma comment(lib, "emma.lib")

#include <math.h>
void SaveDoubleImage(char *filename, double *dimg, 
					 int w, int h, int maxval);
void Downsample(double *x, int N,
				double *&y, int &M, int L);
void Upsample(double *x, int N,
				double *&y, int &M, int L);
void Analysis(double *x,int nx, double *h_filter,int nh,
			  double *&y,int &ny);
void Synthesis(double *y,int ny, double *f_filter,int nf,
			   double *&v,int &nv);

int main()
{
	char filename_in[1024] = "ellipse.pgm";
	char filename_out[1024] = "ellipse-reconstructed.pgm";
	int *img = 0;
	int w, h, maxval;
	Read_PGM_File(filename_in, maxval, w, h, img);
	system(filename_in);
	int nx = w*h;
	double *x = new double[nx]; 
	CopyIntToDoubleArray(img,x,nx,1);

	const int nn = 2, mm = 2;
	int i;
	double h0[nn] = {1,-1};
	double f0[mm] = {-1,1};
	double h1[mm] = {0.0};
	double f1[nn] = {0.0};
	double aa = 0.0, bb = 0.0;
	for (i=0; i<nn; i++) {
		aa += 1.0*h0[i]*h0[i];
	}
	aa = sqrt(aa);
	for (i=0; i<mm; i++) {
		bb += 1.0*f0[i]*f0[i];
	}
	bb = sqrt(bb);

	for (i=0; i<nn; i++) {
		h0[i] /= aa;
		f1[i] = pow(-1.0, i+1)*h0[i];
	}
	for (i=0; i<mm; i++) {
		f0[i] /= bb;
		h1[i] = pow(-1.0, i)*f0[i];
	}

	double *y0 = 0;
	double *y1 = 0;
	int ny0, ny1;
	Analysis(x,nx, h0,nn, y0, ny0);
	Analysis(x,nx, h1,mm, y1, ny1);

	cout << "y0[n] data KB = " << ny0*sizeof(double)/1024 << endl;
	cout << "y1[n] data KB = " << ny1*sizeof(double)/1024 << endl;

	double *y00 = 0, *y01 = 0, *y10 = 0, *y11 = 0;
	int ny00,ny01,ny10,ny11;
	Analysis(y0,ny0, h0,nn, y00,ny00);
	Analysis(y0,ny0, h1,mm, y01,ny01);
	Analysis(y1,ny1, h0,nn, y10,ny10);
	Analysis(y1,ny1, h1,mm, y11,ny11);

	double *v00 = 0, *v01 = 0, *v10 = 0, *v11 = 0;
	int nv00,nv01,nv10,nv11;
	Synthesis(y00,ny00, f0,nn, v00,nv00);
	Synthesis(y01,ny01, f1,mm, v01,nv01);
	Synthesis(y10,ny10, f0,nn, v10,nv10);
	Synthesis(y11,ny11, f1,mm, v11,nv11);

	double *w0 = new double[ny0];
	double *w1 = new double[ny1];
	double *v0 = new double[w*h];
	double *v1 = new double[w*h];
	int nv0, nv1;
	AddDoubleArray(v00,v01, w0,ny0,1);
	Synthesis(w0,ny0, f0,nn, v0,nv0);
	AddDoubleArray(v10,v11, w1,ny0,1);
	Synthesis(w1,ny1, f1,mm, v1,nv1);
	double *x_hat = new double[w*h];
	AddDoubleArray(v0,v1,x_hat,w*h,1);

	SaveDoubleImage(filename_out,x_hat,w,h,maxval);
	system(filename_out);

	// use "CopyDoubleToIntArray(x_hat, img_hat, w, h);" to get image.

	delete []y0;
	delete []y1;
	delete []y00;
	delete []y01;
	delete []y10;
	delete []y11;
	delete []v00;
	delete []v01;
	delete []v10;
	delete []v11;
	delete []v0;
	delete []v1;

	delete []img;
	delete []x;
	delete []x_hat;

	system("pause");
	return 0;
}

void Analysis(double *x,int nx, double *h_filter,int nh,
			  double *&y,int &ny)
{
	// Convolve by filter
	double *r = new double[nx];
	ConvolveDoubleArrays(x, h_filter, r, nx,1, 2,1);
	// Downsample (Down 2)
	Downsample(r,nx, y, ny, 2); // allocates y0

	delete []r; // caller deallocates y
}

void Synthesis(double *y,int ny, double *f_filter,int nf,
			   double *&v,int &nv)
{
	double *t = 0;
	int nt;
	// Upsample (Up 2)
	Upsample(y,ny, t,nt, 2);

	// Convolve by filter
	if (!v) v = new double[nt]; // deallocate v if allocated
	ConvolveDoubleArrays(t, f_filter, v, nt,1, nf,1);
	delete []t; // caller deallocates v
}

// Downsamples, will allocate y
void Downsample(double *x, int N,
				double *&y, int &M, int L)
{
	M = 1.0*N/L;
	if (!y) delete []y; // deallocate y if already allocated
	y = new double[M]; // allocate y
	int n;
	for (n=0; n<M; n++) {
		y[n] = x[L*n];
	}
}

// Upsamples, will allocate y
void Upsample(double *x, int N,
				double *&y, int &M, int L)
{
	M = N*L;
	if (!y) delete []y; // deallocate y if already allocated
	y = new double[M]; // allocate y
	int n;
	for (n=0; n<M; n++) {
		y[n] = (n%L == 0) ? x[n/L] : 0.0;
	}
}

// SaveDoubleImage - attempts to save a double image
// to integer image. Really, I should scale to 0 to maxval
// but this isn't correct...trying to show double as nonnegative.
void SaveDoubleImage(char *filename, double *dimg, 
					 int w, int h, int maxval)
{
	int *img = new int[w*h];
	CopyDoubleToIntArray(dimg,img,w,h);
	PGM_P2_From_Image(filename, img,w,h,maxval);
	delete []img;
}