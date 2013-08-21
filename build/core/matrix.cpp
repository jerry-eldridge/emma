#include <iostream>
using namespace std;
#include <math.h>

#include "core/doublearray.h"
#include "core/matrix.h"

// Determinant of Matrix, 2x2 matrices only (see inverse.h)
double Det2x2(double *A, int N1, int N2)
{
	double val;
	val = A[0+N1*0]*A[1+N1*1] - A[1+N1*0]*A[0+N1*1];
	return val;
}

// Inverse Matrix, 2x2 matrices only (see inverse.h)
void Inv2x2(double *A, double *Ainv, int N1, int N2)
{
	double det = Det2x2(A,N1,N2);
	Ainv[0+N1*0] = A[1+N1*1]/det;
	Ainv[1+N1*1] = A[0+N1*0]/det;
	Ainv[1+N1*0] = -A[1+N1*0]/det;
	Ainv[0+N1*1] = -A[0+N1*1]/det;
}

// Print Matrix (column major)
void PrintMat(double *A, int N1, int N2)
{
	int i,j;

	for (i=0; i<N1; i++) {
		for (j=0; j<N2; j++) {
			cout << A[j+N2*i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// C = A + B, with column-major matrices (equivalent to row-major)
void Add(double *A, double *B, double *C, int N1, int N2)
{
	AddDoubleArray(A,B,C,N1,N2);
}

// C = A - B, with column-major matrices (equivalent to row-major)
void Sub(double *A, double *B, double *C, int N1, int N2)
{
	SubtractDoubleArrays(B,A,C,N1,N2);
}

// C = A * B, with column-major matrices (equivalent to row-major)
void Mult(double *A, double *B, double *C, int N1, int N2, int N3)
{
	double *CC = new double[N1*N3];
	MultiplyDoubleArrays(A,B,CC,N1,N2,N3);
	Copy(CC,C,N1,N3);
	delete []CC;
}

// B := A with column-major matrices (equivalent to row-major)
void Copy(double *A, double *B, int N1, int N2)
{
	CopyDoubleToDoubleArray(A,B,N1,N2);
}

// B := A^T
void Transpose(double *A, double *B, int N1, int N2)
{
	double *C = new double[N1*N2];
	int M1, M2;
	TransposeDoubleArray(A,N1,N2,C,M1,M2);
	Copy(C,B,M1,M2);
	delete []C;
}

// A = I_nxm Idenity Matrix
void Identity(double *A, int N1, int N2) 
{
	int i,j;
	for (j=0; j<N2; j++) {
		for (i=0; i<N1; i++) {
			A[j+N2*i] = (i==j) ? 1 : 0;
		}
	}
}