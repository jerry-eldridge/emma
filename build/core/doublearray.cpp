#include <stdio.h>
#include <iostream>
using namespace std;

#include "core/core.h"
#include <math.h>

// [Could pass N, the size of arrs, and check if each label is within range.]
// Grid Paint By Numbers in "labels" L1xL2. Texture or Paint in **arrs  M1xM2 each. Result is arr, N1 x N2
void PaintByNumbersDoubleArray(double **arrs, int M1, int M2, int *labels, int L1, int L2, double *&arr, int &N1, int &N2)
{
	N1 = M1*L1;
	N2 = M2*L2;
	arr = new double[N1*N2];
	ZeroDoubleArray(arr, N1, N2);
	int i, j;
	double x, y;
	for (i=0; i<L1; i++) { for (j=0; j<L2; j++) {
		x = i*M1; y = j*M2;
		PasteDoubleArray(arr, arrs[labels[j+L2*i]], x, y, N1, N2, M1, M2);
	}}
}

void EdgesLaplacianDoubleArray(double *arr, double *&arrOut, int N1, int N2)
{
	static double Laplacian[] = {
		0,1,0,
		1,-4,1,
		0,1,0
	};
	ConvolveDoubleArrays(arr, Laplacian, arrOut, N1, N2, 3, 3);
}

void EdgesSobelDoubleArray(double *arr, double *&arrOut, int N1, int N2)
{
	static double SobelGx[] = {
		1,2,1,
		0,0,0,
		-1,-2,-1
	};
	static double SobelGy[] = {
		-1,0,1,
		-2,0,2,
		-1,0,1
	};
	double *arr1, *arr2;
	arr1 = new double[N1*N2];
	arr2 = new double[N1*N2];
	ConvolveDoubleArrays(arr, SobelGx, arr1, N1, N2, 3, 3);
	ConvolveDoubleArrays(arr, SobelGy, arr2, N1, N2, 3, 3);
	int n;
	for (n=0; n<N1*N2; n++) {
		arrOut[n] = fabs(arr1[n])+fabs(arr2[n]); // approx L1 norm
		//arrOut[n] = sqrt(arr1[n]*arr1[n]+arr2[n]*arr2[n]); L2 norm
	}
	delete []arr1;
	delete []arr2;
}

void StretchDoubleArray(double *&arr, int N1, int N2)
{
	int n;
	double x, max1, min1;

	////////////////////
	//// The routine doesn't calculate correctly unless you
	//// divide here by min1
	//max1 = -INFINITY; min1 = INFINITY;
	//for (n=0; n<N1*N2; n++) {
	//	if (arr[n] > max1) max1 = arr[n];
	//	if (arr[n] < min1) min1 = arr[n];
	//}
	//for (n=0; n<N1*N2; n++) {
	//	arr[n] = arr[n]/min1;
	//}
	////////////////////

	// recalculate min1 and max1
	max1 = -INFINITY; min1 = INFINITY;
	for (n=0; n<N1*N2; n++) {
		if (arr[n] > max1) max1 = arr[n];
		if (arr[n] < min1) min1 = arr[n];
	}
	// Linear Interpolate
	for (n=0; n<N1*N2; n++) {
		x = arr[n]; 
		arr[n] = (x-min1)/(max1-min1)*P2_MAXVAL;
	}
}

void DivideDoubleArrays(double *image1, double *image2, double *&imageOut, int N1, int N2)
{
	int i,j;
	double Y0, Y1, Y2;
	for (i = 0; i < N1; i++) {
		for (j = 0; j < N2; j++) {
			Y1 = image1[j+N2*i]+1;
			Y2 = image2[j+N2*i]+1;
			Y0 = fabs(1.0*Y2/Y1);
			imageOut[j+N2*i] = Y0;
		}
	}     
}

void ThresholdDoubleArray(double *&arr, double thresholdLow, double thresholdHigh, int N1, int N2)
{
	double val;
	int n;
	for (n=0; n<N1*N2; n++) {
		val = arr[n];
		if ( (val >= thresholdLow) && (val <= thresholdHigh) ) {
			val = P2_MAXVAL;
		} else {
			val = 0;
		}
		arr[n] = val;
	}

}

void MinimumMaximumOfArray(double *arr, int N1, int N2, double &min1, double &max1)
{
	int n;
	max1 = -INFINITY; min1 = INFINITY;
	for (n=0; n<N1*N2; n++) {
		if (arr[n] > max1) max1 = arr[n];
		if (arr[n] < min1) min1 = arr[n];
	}
}

void LogDoubleArray(double *arr, int N1, int N2)
{
	int i,j;
	double min1, max1, val;
	int cLog, Y;

	MinimumMaximumOfArray(arr, N1, N2, min1, max1);
	//http://homepages.inf.ed.ac.uk/rbf/HIPR2/pixlog.htm
	// Apply Logarithm Function To Pixels
	cLog = floor( P2_MAXVAL/log(1+fabs(max1)) + 0.5);
	for (i = 0; i < N1; i++) {
		for (j = 0; j < N2; j++) {
			val = arr[j+N2*i];
			Y = floor(cLog*log(1.0+val) + 0.5);
			arr[j+N2*i] = Y;
		}
	} 
}

void ScaleDoubleArray(double *&arr, double scalar, int N1, int N2)
{
	double val;
	int n;
	for (n=0; n<N1*N2; n++) {
		val = scalar*arr[n];
		arr[n] = val;
	}
}

void OutputDoubleArrayToFile(char *filename, double *arr, int N1, int N2)
{
	int i, j;
	FILE *fp;
	fp = fopen(filename, "w");
	for (i = 0; i < N1; i++) {
		for (j = 0; j < N2; j++) {
			fprintf(fp, "%f ", arr[j+N2*i]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
}

void CopyDoubleToDoubleArray(double *arr, double *&arrOut, int N1, int N2)
{
	memcpy(arrOut, arr, sizeof(double)*N1*N2);
}

// [FIREBAUGH] 142
void DrawLineInDoubleArray_DDA(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val)
{
	double m, dx, dy, range, x, y;
	int i,j;
	bool support;

	// Line is a Point
	dy = y2-y1;
	dx = x2-x1;
	if ((dy == 0) && (dx == 0)) {
		i = round(x1); j = round(y1);
		support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
		if (!support) {
			arr[j+N2*i] = val;
		}
		return;
	}

	range = max(fabs(dx), fabs(dy));
	// DeltaX = 0
	if ( dx == 0) {
		dy = (dy >= 0) ? 1 : -1;
		i = round(x1);
		for (j = 1; j<=range; j++) {
			j = round(y1+dy);
			arr[j+N2*i] = val;
		}
	}
	m = dy/dx;

	dx = dx/range; 
	dy = dy/range;
	x = x1; y = y1;
	int r, irange;
	irange = round(range);
	for (r = 0; r<irange; r++) {
		i = round(x); j = round(y);
		support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
		if (!support) {
			arr[j+N2*i] = val;
		}
		x += dx;
		y += dy;
	}
}

void PolygonDoubleArray(double *arr, int N1, int N2, pointDouble *p, int N, double x, double y, double W, double H, double val)
{
	bool support;
	int pointtest;
	int i,j;
	int i0, i1, j0, j1;
	i0 = round(x); j0 = round(y);
	i1 = round(x+W); j1 = round(y+H);
	i0 = (i0<0) ? 0 : i0;
	i1 = (i1>=N1) ? N1 : i1;
	j0 = (j0<0) ? 0 : j0;
	j1 = (j1>=N2) ? N2 : j1;
	support = (i0>=N1)||(i1<0)||(j0>=N2)||(j1<0);
	if (support) return;
	for (i=i0; i<=i1; i++) { for (j=j0; j<=j1; j++) {
		pointtest = PointInPolygonTest(p, N, i, j);
		if (pointtest) {
			arr[j+N2*i] = val;
		}
	}}
}

void RotateAngleDoubleArray(double *arr, double *&arrOut, int N1, int N2, double Radians)
{
	int i,j, ii, jj, n;
	double x, y, xx, yy;
	bool support;
	static int UNDEFINED = -1;

	int *count;
	count = new int[N1*N2];

	for (n=0; n<N1*N2; n++) {
		arrOut[n] = UNDEFINED;
		count[n] = 1;
	}
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		x = i-N1/2.0;
		y = j-N2/2.0;
		xx = cos(Radians)*x + sin(Radians)*y;
		yy = -sin(Radians)*x + cos(Radians)*y;
		x = xx+N1/2.0;
		y = yy+N2/2.0;
		ii = round(x); jj = round(y);
		support = (ii<0)||(ii>=N1)||(jj<0)||(jj>=N2);
		if (!support) {
			if (arrOut[jj+N2*ii] == UNDEFINED) {
				arrOut[jj+N2*ii] = arr[j+N2*i];
			} else {
				arrOut[jj+N2*ii] += arr[j+N2*i];
				count[jj+N2*ii] += 1;
			}
		} 
	}}

	// Avg Multiple Hits
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		if (count[j+N2*i] > 1) {
			arrOut[j+N2*i] = round(1.0*arrOut[j+N2*i]/count[j+N2*i]);
		}
	}}

	// Displays Multiplt Hit Pattern - which is evenly distributed across image
	//for (n=0; n<N1*N2; n++) {
	//	if (count[n]>1) {
	//		count[n] = P2_MAXVAL;
	//	} else {
	//		count[n] = 0;
	//	}
	//}
	//PGM_P2_From_Image("counts.pgm", count, N1, N2);

	double *arrOut2;
	arrOut2 = new double[N1*N2];
	CopyDoubleToDoubleArray(arrOut, arrOut2, N1, N2);

	// Do Some Sort of Interpolation
	int sum, cnt;
	int iii, jjj;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		if (arrOut[j+N2*i] == UNDEFINED) {
			sum = 0;
			cnt = 0;
			for (ii=-1; ii<1; ii++) { for (jj=-1; jj<1; jj++) {
				iii = i+ii; jjj = j+jj;
				support = (iii<0)||(iii>=N1)||(jjj<0)||(jjj>=N2);
				if (!support) {
					if (arrOut[jjj+N2*iii]!=UNDEFINED) {
						sum += arrOut[jjj+N2*iii];
						cnt++;
					}
				}
			}}
			if (cnt > 0) {
				arrOut2[j+N2*i] = round(1.0*sum/cnt);
			} else {
				arrOut2[j+N2*i] = 0;
			}
		}
	}}

	CopyDoubleToDoubleArray(arrOut2, arrOut, N1, N2);
	delete []arrOut2;

	delete []count;

}

void RotateRightDoubleArray(double *arr, int N1, int N2, double *&arrOut, int &M1, int &M2)
{
	M1 = N2; M2 = N1;
	int i,j, ii, jj;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		ii = j;
		jj = N1-1-i;
		arrOut[jj+N1*ii] = arr[j+N2*i];
	}}
}

void RotateLeftDoubleArray(double *arr, int N1, int N2, double *&arrOut, int &M1, int &M2)
{
	M1 = N2; M2 = N1;
	int i,j, ii, jj;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		ii = N2-1-j;
		jj = i;
		arrOut[jj+N1*ii] = arr[j+N2*i];
	}}
}

void DrawLineInDoubleArray(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val)
{
	DrawLineInDoubleArray_Bresenham(arr, N1, N2, x1, y1, x2, y2, val);
}

void DrawLineInDoubleArray_N(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val, int N)
{
	if (N == 1) {
		DrawLineInDoubleArray_Bresenham(arr, N1, N2, x1, y1, x2, y2, val);
		return;
	}
	DrawLineInDoubleArray_DDA_N(arr, N1, N2, x1, y1, x2, y2, val, N);
}

void DrawLineInDoubleArray_Bresenham_N(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val, int N)
{
	static int minThickness = 0;
	static int maxThickness = 200;
	double dx, dy, mperp;
	int dn, i;
	dn = N-1;
	if ( (dn<minThickness) || (dn>maxThickness) ) return;
	// Regular Line
	if (N == 1) {
		DrawLineInDoubleArray_Bresenham(arr, N1, N2, x1, y1, x2, y2, val);
		return;
	}
	dx = x2-x1;
	dy = y2-y1;
	// Vertical Line
	if (dy == 0) {
		for (i=-dn; i<=dn; i++) {
			DrawLineInDoubleArray_Bresenham(arr, N1, N2, x1+i, y1, x2+i, y2, val);
			return;
		}
	}
	mperp = -dx/dy;
	double dxx, dyy;
	for (i=-dn*3; i<=dn*3; i++) {
		dxx = i/3.0;
		dyy = i/3.0*mperp;
		DrawLineInDoubleArray_Bresenham(arr, N1, N2, x1+dxx, y1+dyy, x2+dxx, y2+dyy, val);
	}
}

// [FIREBAUGH] pg143
void DrawLineInDoubleArray_Bresenham(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val)
{
	enum axes {XAXIS, YAXIS};
	enum axes axis;
	double dx, dy, range, errp; 
	int xp, yp;
	int i, j, irange, dxs, dys;
	bool support;

	// Line is a Point
	dy = y2-y1;
	dx = x2-x1;
	if ((dy == 0) && (dx == 0)) {
		i = round(x1); j = round(y1);
		support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
		if (!support) {
			arr[j+N2*i] = val;
		}
	}

	range = max(fabs(dx), fabs(dy));
	irange = round(range);
	if (fabs(dx) >= fabs(dy)) {
		axis = XAXIS;
	} else {
		axis = YAXIS;
	}
	errp = 2*dy-dx;
	dxs = (dx >= 0) ? 1 : -1;
	dys = (dy >= 0) ? 1 : -1;
	xp = round(x1);
	yp = round(y1);

	switch (axis) {
		case XAXIS:
			for (i=0; i<irange; i++) {
				support = (xp<0)||(xp>=N1)||(yp<0)||(yp>=N2);
				if (!support) {
					arr[yp+N2*xp] = val;
				}
				if (errp > 0) {
					yp += dys;
					errp += -2*dx*dxs;
				}
				xp += dxs;
				errp += 2*dy*dys;
			}
			break;
		case YAXIS:
			for (i=0; i<irange; i++) {
				support = (xp<0)||(xp>=N1)||(yp<0)||(yp>=N2);
				if (!support) {
					arr[yp+N2*xp] = val;
				}
				if (errp > 0) {
					xp += dxs;
					errp += -2*dy*dys;
				}
				yp += dys;
				errp += 2*dx*dxs;
			}
			break;
	}
}

// Else recode using DrawLineInDoubleArray, to avoid preprocessing
void DrawLineInDoubleArray_DDA_N(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val, int N)
{
	static int minThickness = 0;
	static int maxThickness = 200;
	int dn;
	dn = N-1;
	if ( (dn<minThickness) || (dn>maxThickness) ) return;
	if (N == 1) {
		DrawLineInDoubleArray_DDA(arr, N1, N2, x1, y1, x2, y2, val);
		return;
	}
	DrawLineInDoubleArray_DDA_N_Helper(arr, N1, N2, x1, y1, x2, y2, val, dn);
}

void DrawLineInDoubleArray_DDA_N_Helper(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val, int dn)
{
	double m, dx, dy, range, x, y, mperp;
	int i,j;
	bool support;

	// Line is a Point
	dy = y2-y1;
	dx = x2-x1;
	if ((dy == 0) && (dx == 0)) {
		i = round(x1); j = round(y1);
		support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
		if (!support) {
			arr[j+N2*i] = val;
		}
		return;
	}
	range = max(fabs(dx), fabs(dy));
	// DeltaX = 0
	if ( dx == 0) {
		dy = (dy >= 0) ? 1 : -1;
		i = round(x1);
		for (j = 1; j<=range; j++) {
			j = round(y1+dy);
			arr[j+N2*i] = val;
		}
	}
	m = dy/dx;
	
	dx = dx/range; 
	dy = dy/range;
	x = x1; y = y1;
	int n;
	int r, irange;
	irange = round(range);
	for (r = 0; r<irange; r++) {
		for (n = -dn*2; n<=dn*2; n++) {
			if (dy == 0) {
				i = round(x); j = round(y+n/2*dy);
			} else {
				mperp = -1.0/m;
				i = round(x+n/2.0); j = round(y+n/2.0*mperp);
			}
			support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
			if (!support) {
				arr[j+N2*i] = val;
			}
		}
		
		x += dx;
		y += dy;
	}
}


// O(N*M) algorithm to convolve two images
void ConvolveDoubleArrays(double *arr1, double *arr2, double*&arr3, int N1, int N2, int M1, int M2)
{
	double sum;
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
			  sum += arr2[tau]*arr1[t-tau];
		   }
	   }
	   arr3[t] = sum;
	}
}

void FlipVerticalDoubleArray(double *arr, double *arrOut, int N1, int N2)
{
	int i,j;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		arrOut[j+i*N2] = arr[(N2-j-1)+i*N2];
	}}
}
void FlipHorizontalDoubleArray(double *arr, double *arrOut, int N1, int N2)
{
	int i,j;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		arrOut[j+i*N2] = arr[j+(N1-i-1)*N2];
	}}
}

void LocateMinMaxDoubleArray(double *arr, int N1, int N2, double &min1, double &max1, 
							 int &mini, int &minj, int &maxi, int &maxj)
{
	max1 = -INFINITY; min1 = INFINITY;
	mini = minj = maxi = maxj = 0;
	int i,j;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		if (arr[j+N2*i] > max1) {
			max1 = arr[j+N2*i];
			maxi = i;
			maxj = j;
		}
		if (arr[j+N2*i] < min1) {
			min1 = arr[j+N2*i];
			mini = i;
			minj = j;
		}
	}}
}
void PasteWithMaskDoubleArray(double *&arr1, double *arr2, double *mask2, double x, double y, int N1, int N2, int M1, int M2)
{
	bool support;
	int i,j,ii,jj;
	for (ii=0; ii<M1; ii++) { for (jj=0; jj<M2; jj++) {
		i = round(ii+x);
		j = round(jj+y);
		support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
		if (!support && mask2[jj+M2*ii]) {
			arr1[j+N2*i] = arr2[jj+M2*ii];
		}
	}}
}

void ClipDoubleArrayUsingZScore(double *&arr, double mean, double sigma, 
									  double ZScore, int N1, int N2)
{
	double min1, max1;
	int n;
	min1 = mean - ZScore*sigma;
	max1 = mean + ZScore*sigma;
	for (n=0; n<N1*N2; n++) {
		arr[n] = (arr[n] < min1) ? min1 : arr[n];
		arr[n] = (arr[n] > max1) ? max1 : arr[n];
	}
}

void StatisticsOfDoubleArray(double *arr, double &mean, double &sigma, int N1, int N2)
{
	int n;
	mean = 0;
	for (n=0; n<N1*N2; n++) {
		mean += arr[n];
	}
	mean /= 1.0*N1*N2;
	sigma = 0;
	for (n=0; n<N1*N2; n++) {
		sigma += (arr[n] - mean)*(arr[n] - mean);
	}
	sigma = sqrt(sigma);
	
}

void SubtractScalarFromDoubleArray(double *&arr, double scalar, int N1, int N2)
{
	int n;
	for (n=0; n<N1*N2; n++) {
		arr[n] -= scalar;
	}
}

void SubtractDoubleArrays(double *arr1, double *arr2, double *&arrOut, int N1, int N2)
{
	int n;
	for (n=0; n<N1*N2; n++) {
		arrOut[n] = arr2[n] - arr1[n];
	}
}

void CloseDoubleArray2(double *arr, double *&arrOut, int N1, int N2)
{
	double *arrtmp;
	arrtmp = new double[N1*N2];
	DilateDoubleArray2(arr, arrtmp, N1, N2);
	ErodeDoubleArray2(arrtmp, arrOut, N1, N2);
	delete []arrtmp;
}

void OpenDoubleArray2(double *arr, double *&arrOut, int N1, int N2)
{
	double *arrtmp;
	arrtmp = new double[N1*N2];
	ErodeDoubleArray2(arr, arrtmp, N1, N2);
	DilateDoubleArray2(arrtmp, arrOut, N1, N2);
	delete []arrtmp;
}


void TransposeDoubleArray(double *arr, int N1, int N2, double *&arrOut, int &M1, int &M2)
{
	M1 = N2; M2 = N1;
	int i, j;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		arrOut[i+N1*j] = arr[j+N2*i];
	}}
}

void MultiplyDoubleArrays(double *arr1, double *arr2, double *&arrOut, int N1, int N2, int N3)
{ 
	int i,j,k;
	double sum;
	for (i=0; i<N1; i++) { for (j=0; j<N3; j++) { 
		sum = 0;
		for (k=0; k<N2; k++) { 
			sum += arr1[k+N2*i]*arr2[j+N3*k];
		}
		arrOut[j+N3*i] = sum;
	}}
}

void CloseDoubleArray(double *&arr, int N1, int N2)
{
	double *arrOut;
	arrOut = new double[N1*N2];
	CloseDoubleArray2(arr, arrOut, N1, N2);
	memcpy(arr, arrOut, sizeof(double)*N1*N2);
	delete []arrOut;
}

void OpenDoubleArray(double *&arr, int N1, int N2)
{
	double *arrOut;
	arrOut = new double[N1*N2];
	OpenDoubleArray2(arr, arrOut, N1, N2);
	memcpy(arr, arrOut, sizeof(double)*N1*N2);
	delete []arrOut;
}

void DisplayDoubleArray(double *arr, int ROW, int COL)
{
	int i,j;
	for (j=0; j<COL; j++) {
		for (i=0; i<ROW; i++) { 
			cout << arr[j+COL*i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void DilateDoubleArray(double *&arr, int N1, int N2)
{
	double *arrOut;
	arrOut = new double[N1*N2];
	DilateDoubleArray2(arr, arrOut, N1, N2);
	memcpy(arr, arrOut, sizeof(double)*N1*N2);
	delete []arrOut;
}

void ErodeDoubleArray(double *&arr, int N1, int N2)
{
	double *arrOut;
	arrOut = new double[N1*N2];
	ErodeDoubleArray2(arr, arrOut, N1, N2);
	memcpy(arr, arrOut, sizeof(double)*N1*N2);
	delete []arrOut;
}

void CenterDoubleArray(double *&arr, int N1, int N2)
{
	int i,j, ii, jj;
	int xshift = round(N1/2.0-1), yshift = round(N2/2.0-1);
	double *arr2;
	arr2 = new double[N1*N2];
	for (i = 0; i < N1; i++) {
		for (j = 0; j < N2; j++) {
			ii = (xshift+i)%N1;
			jj = (yshift+j)%N2;
			arr2[j+N2*i] = arr[jj+N2*ii];
		}
	}
	for (i = 0; i < N1; i++) {
		for (j = 0; j < N2; j++) {
			arr[j+N2*i] = arr2[j+N2*i];
		}
	}
	delete []arr2;
}

void ScaleSizeDoubleArray(double *arr, double *&arrOut, double sx, double sy, int N1, int N2, int &M1, int &M2)
{
	bool support;
	M1 = round(sx*N1);
	M2 = round(sy*N2);
	arrOut = new double[M1*M2];
	int i,j,ii,jj;
	for (i=0; i<M1; i++) { for (j=0; j<M2; j++) {
		ii = round(i/sx);
		jj = round(j/sy);
		support = (ii<0)||(ii>=N1)||(jj<0)||(jj>=N2);
		if (!support) {
			arrOut[j+M2*i] = arr[N2*ii+jj];
		}
	}}
}

void TranslateDoubleArray(double *arr, double *&arrOut, double tx, double ty, int N1, int N2)
{
	bool support;
	int i,j,ii,jj,n;
	for (n=0; n<N1*N2; n++) {
		arrOut[n] = 0;
	}
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		ii = round(i-tx);
		jj = round(j-ty);
		support = (ii<0)||(ii>=N1)||(jj<0)||(jj>=N2);
		if (!support) {
			arrOut[j+N2*i] = arr[jj+N2*ii];
		}
	}}
}

void DilateDoubleArray2(double *arr, double *&arrOut, int N1, int N2)
{
	bool dilate, support;
	static double threshold = P2_MAXVAL;
	static double background = 0;
	static double foreground = P2_MAXVAL;
	int i,j,ii,jj,x,y;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		if (arr[j+N2*i] < threshold) { // background
			dilate = false;
			for (x=-1; x<1; x++) { for (y=-1; y<1; y++) {
				ii = i+x;
				jj = j+y;
				support = (ii<0)||(ii>=N1)||(jj<0)||(jj>=N2);
				if (support) continue;
				dilate = dilate || (arr[jj+N2*ii] >= threshold);
			}}
			if (dilate) {
				arrOut[j+N2*i] = foreground;
			} else {
				arrOut[j+N2*i] = background;
			}
		} else { // foreground
			arrOut[j+N2*i] = foreground;
		}
	}}
}

void ErodeDoubleArray2(double *arr, double *&arrOut, int N1, int N2)
{
	bool erode, support;
	static double threshold = P2_MAXVAL;
	static double background = 0;
	static double foreground = P2_MAXVAL;
	int i,j,ii,jj,x,y;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		if (arr[j+N2*i] >= threshold) { // foreground
			erode = true;
			for (x=-1; x<1; x++) { for (y=-1; y<1; y++) {
				ii = i+x;
				jj = j+y;
				support = (ii<0)||(ii>=N1)||(jj<0)||(jj>=N2);
				if (support) continue;
				erode = erode && (arr[jj+N2*ii] >= threshold);
			}}
			if (erode) {
				arrOut[j+N2*i] = foreground;
			} else {
				arrOut[j+N2*i] = background;
			}
		} else { // background
			arrOut[j+N2*i] = background;
		}
	}}
}


void ZeroDoubleArray(double *&arr, int N1, int N2)
{
	int n;
	for (n=0; n<N1*N2; n++) {
		arr[n] = 0;
	}
}

void AddDoubleArray2(double *&arr1, double *arr2, double x, double y, int N1, int N2, int M1, int M2)
{
	bool support;
	int i,j,ii,jj;
	for (ii=0; ii<M1; ii++) { for (jj=0; jj<M2; jj++) {
		i = round(ii+x);
		j = round(jj+y);
		support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
		if (!support) {
			arr1[j+N2*i] += arr2[jj+M2*ii];
		}
	}}
}

void SubtractDoubleArray2(double *&arr1, double *arr2, double x, double y, int N1, int N2, int M1, int M2)
{
	bool support;
	int i,j,ii,jj;
	for (ii=0; ii<M1; ii++) { for (jj=0; jj<M2; jj++) {
		i = round(ii+x);
		j = round(jj+y);
		support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
		if (!support) {
			arr1[j+N2*i] -= arr2[jj+M2*ii];
		}
	}}
}

void PasteDoubleArray(double *&arr1, double *arr2, double x, double y, int N1, int N2, int M1, int M2)
{
	bool support;
	int i,j,ii,jj;
	for (ii=0; ii<M1; ii++) { for (jj=0; jj<M2; jj++) {
		i = round(ii+x);
		j = round(jj+y);
		support = (i<0)||(i>=N1)||(j<0)||(j>=N2);
		if (!support) {
			arr1[j+N2*i] = arr2[jj+M2*ii];
		}
	}}
}

void ExtendDoubleArray(double *arr, double *&arrOut, double x, double y, int N1, int N2, int M1, int M2)
{
	bool support;
	int i,j,ii,jj,n;
	for (n=0; n<M1*M2; n++) {
		arrOut[n] = 0;
	}
	for (i=0; i<M1; i++) { for (j=0; j<M2; j++) {
		ii = round(i-x);
		jj = round(j-y);
		support = (ii<0)||(ii>=N1)||(jj<0)||(jj>=N2);
		if (!support) {
			arrOut[j+M2*i] = arr[jj+N2*ii];
		}
	}}
}

void AddDoubleArray(double *arr1, double *arr2, double *&arrOut, int N1, int N2)
{
	int n;
	for (n=0; n<N1*N2; n++) {
		arrOut[n] = arr1[n] + arr2[n];
	}
}

void AbsDoubleArray(double *&arr, int N1, int N2)
{
	int n;
	for (n=0; n<N1*N2; n++) {
		arr[n] = fabs(arr[n]);
	}
}

