//
// norm.cpp - calculates the norm of a matrix
//
// INPUT: A, n
// 	A - input coefficient matrix
//	n - the size of the coefficient matrix, n x n matrix
// OUTPUT: norm
//	the norm is returned by the function call. Note A and n are
//	left unchanged
//
#include <iostream>
using namespace std;
#include "core/defs.h"
#include "core/norm.h"
#include "core/elim.h"

// Condition of Matrix A. Assumes A[1..n][1..n] not 0..n-1
float ConditionMat(float A[MAXSIZE][MAXSIZE], unsigned n)
{
   float M[MAXSIZE][MAXSIZE] = {{0}};
   float AINV[MAXSIZE][MAXSIZE] = {{0}};
   float MINV[MAXSIZE][MAXSIZE] = {{0}};
   float b[MAXSIZE][MAXSIZE] = {{0}};
   float det;
   float Mnorm, MINVnorm;
 
   // Make copy of A and place it into M
   for (int i=1; i<=n; i++) 
      for (int j=1; j<=n; j++) 
         M[i][j] = A[i][j];

   // Calculate norm of M
   Mnorm = NormMat(M, n);

   // Find the inverse of M
   unsigned m = n;
   for (unsigned i=1; i<=n; i++)
      for (unsigned l=1; l<=m; l++) 
         b[l][i] = ((i == l) ? 1.0 : 0.0);
   elim(M, AINV, b, m, n, det);
   for (unsigned i=1; i<=n; i++) 
      for (unsigned j=1; j<=n; j++)
         MINV[i][j] = AINV[j][i];

   // Calculate the norm of M inverse
   MINVnorm = NormMat(MINV, n);

   return (Mnorm*MINVnorm);
}

//
// NormMat() - calculates the infinity norm of the matrix. That is, the 
//          maximum row sum
// Assumes A[1..n] not 0..n-1
float NormMat(float A[MAXSIZE][MAXSIZE], unsigned n)
{
   float max = -1;
   float sum;

   for (unsigned i=1; i<=n; i++) {
      sum = 0.0;
      for (unsigned j=1; j<=n; j++)
         sum += ABS(A[i][j]);
      max = ((sum > max) ? sum : max);
   }
   return max;
}
