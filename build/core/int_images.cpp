#include "core/int_images.h"

#include <math.h>

void TransposeIntArray(int *image, int N1, int N2, int *&imageT, int &M1, int &M2)
{
	M1 = N2; M2 = N1;
	int i, j;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		imageT[i+N1*j] = image[j+N2*i];
	}}
}

void SetIntArray(int *&image, int N1, int N2, int val)
{
	int n;
	for (n=0; n<N1*N2; n++) {
		image[n] = val;
	}
}

void ZeroIntArray(int *&image, int N1, int N2)
{
	SetIntArray(image, N1, N2, 0);
}

void CopyDoubleToIntArray(double *arr, int *&image, int N1, int N2)
{
	int n;
	int Y;
	for (n=0; n<N1*N2; n++) {
		Y = floor(arr[n]+0.5);
		image[n] = Y;
	}
}

void CopyIntToDoubleArray(int *image, double *&arr, int N1, int N2)
{
	int n;
	double x;
	for (n=0; n<N1*N2; n++) {
		x = image[n];
		arr[n] = x;
	}
}

void ConcatTwoImagesByWidth(int *imageA, int *imageB, int *&imageOut, int WidthA, int WidthB, int Height)
{
	int i, j, n, nA, nB;
	int Width;
	Width = WidthA + WidthB;
	imageOut = new int[Width*Height];

	// Computes the transpose?? so swap everything
	nA = 0;
	for (j=0; j<Height; j++) {
		for (i=0; i<Width; i++) {
			n = i + Width*j;
			if (i < WidthA) {
				imageOut[n] = imageA[nA++];
			}
		}
	}
	nB = 0;
	for (j=0; j<Height; j++) {
		for (i=0; i<Width; i++) {
			n = i + Width*j;
			if ( i >= WidthA ) {
				imageOut[n] = imageB[nB++];
			}
		}
	}
}

// O(N*M) algorithm to convolve two images
void ConvolveIntArrays(int *image1, int *image2, int*&image3, int N1, int N2, int M1, int M2)
{
	int sum;
	bool support;
	int t, tau;
	int N, M;
	N = N1*N2;
	M = M1*M2;
	if (N < M) return;	// assert(N < M);
	for (t=0; t<N; t++) {
	   sum = 0;
	   for (tau=0; tau<M; tau++) {
		   support = (t-tau >= 0);
		   if (support) {
			  sum += image2[tau]*image1[t-tau];
		   }
	   }
	   image3[t] = sum;
	}
}

void CorrectSignedWordImage(int *&image, int N1, int N2)
{
	int pos, neg;
	int val;
	int n;
	for (n=0; n<N1*N2; n++) {
		val = image[n];
		pos = 0x7FFF & val;
		neg = 0x8000&val;
		val = pos-neg+0x8000;
		image[n] = val;
	}
}