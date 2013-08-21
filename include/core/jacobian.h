#ifndef _JACOBIAN_H
#define _JACOBIAN_H

double Deriv(double (*F)(double *, int), double *Q, int n, int i, double h); // Derivative
void Jacobian(double (*F[])(double *Q, int n), double *Q, int n, 
			  double *J, int N1, int N2, double h);

#endif
