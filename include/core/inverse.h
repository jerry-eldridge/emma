#ifndef INVERSE_H
#define INVERSE_H

void Inv(double *A, double *AInv, int n, double &det); // Inverse
void Solve(double *A, double *X, double *B, int n, int m, // A*X = B
		   double &det);

#endif
