#include <iostream>
using namespace std;
#include <iomanip>
#include "core/elim.h"
#include "core/norm.h"
#include "core/defs.h"
#include "core/matrix.h"

// assumes N1,N2 <= MAXSIZE (else increase MAXSIZE in defs.h)
// A (nxn) -> Ainv (nxn), using A_nxn*X_nxm = B = I_nxm, the identity
// Finds inverse Ainv of A and calculates det(Ainv) = 1/det(A)
// A[0..n-1][0..n-1], Ainv[0..n-1][0..n-1] using
// a[1..n][1..n] = A, b[1..n][1..n] = I, x[1..n][1..n] = Ainv 
void Inv(double *A, double *AInv, int n, double &det)
{
	float a[MAXSIZE][MAXSIZE];
	float xx[MAXSIZE][MAXSIZE];
	float b[MAXSIZE][MAXSIZE];
	float fdet = 0;

	int i,j;
	for (j=0; j<n; j++) {
		for (i=0; i<n; i++) {
			a[j+1][i+1] = A[j+n*i];
			b[j+1][i+1] = (i == j) ? 1.0 : 0.0; // identity matrix
		}
	}

	elim(a,xx,b,n,n,fdet);
	det = fdet;

	for (j=0; j<n; j++) {
		for (i=0; i<n; i++) {
			AInv[i+n*j] = xx[j+1][i+1]; // xx.transpose()
		}
	}

}

// A (nxn) * X (nxm) = B (nxm). Solve for X in system of
// linear equations A*X = B using Gaussian Elimination. 
// A[0..n-1][0..n-1], X[0..n-1][0..m-1], B[0..n-1][0..m-1] using
// a[1..n][1..n] = A^T, b[1..m][1..n] = B^T, x[1..m][1..n] = X^T
// (transposing matrices when necessary). A*X = B and
// (A*X)^T = B^T or X^T * A^T = B^T or x*a = b.
void Solve(double *A, double *X, double *B, int n, int m, 
		   double &det)
{
	double *Ainv = new double[n*n];
	Inv(A,Ainv, n, det);
	Mult(Ainv,B,X,n,n,m);

	delete []Ainv;
}