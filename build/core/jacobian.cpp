#include <iostream>
using namespace std;
#include <math.h>

#include "core/jacobian.h"

// The derivative Deriv(F,Q,n,i,h) = dF/dQ[i] using epsilon h
double Deriv(double (*F)(double *, int), double *Q, int n, int i, double h)
{
	double *QP = new double[n];
	int j;
	for (j=0; j<n; j++) {
		QP[j] = (j==i) ? Q[j] + h : Q[j];
	}
	double d;
	d = 1.*(F(QP,n) - F(Q,n))/h; // derivative
	delete []QP;
	return d;
}

// The Jacobian Jacobian(F,Q,n,J,N1,N2,h) = J = dF/dQ using epsilon h
// (column major J)
void Jacobian(double (*F[])(double *Q, int n), double *Q, int n, 
			  double *J, int N1, int N2, double h)
{
	int i,j;

	for (j=0; j<N2; j++) {
		for (i=0; i<N1; i++) {
			J[i+N2*j] = Deriv(F[j],Q,n,i,h); // Transpose(J)
		}
	}
}
