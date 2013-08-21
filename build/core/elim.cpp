//
// elim.cpp - Gaussian Elimination Algorithm
//
// INPUTS: a, b, m, n
//	   a - input coefficient matrix nxn
//	   b - input solution matrix mxn
//	   m - number of columns of solution vectors in solution matrix
//	   n - A is a n x n coefficient matrix
// OUTPUTS: a, b, X
//	   X - the resulting solution matrix mxn
//
// a[1..n][1..n], b[1..m][1..n], x[1..m][1..n] 
// Solves x*a = b
#include <iostream>
using namespace std;
#include <iomanip>
#include "core/elim.h"
#include "core/defs.h"

void elim(float a[MAXSIZE][MAXSIZE], 
	  float X[MAXSIZE][MAXSIZE], 
	  float b[MAXSIZE][MAXSIZE], unsigned m, 
	  unsigned n, 
	  float &det)
{
   float pvt;
   int pivot[MAXSIZE];
   int ipvt_store;
   int rowswap_count = 0;
   float temp;
   float A[MAXSIZE][MAXSIZE], B[MAXSIZE][MAXSIZE];

   for (unsigned i=1; i<=n; i++) 
      for (unsigned j=1; j<=n; j++)
         A[i][j] = a[i][j];

   for (unsigned l=1; l<=m; l++)
      for (unsigned i=1; i<=n; i++) 
         B[l][i] = b[l][i];

   // Get Diagonal matrix for A
   for (int j=1; j<=n-1; j++) {
      pvt = ABS(A[j][j]);
      pivot[j] = j;

      // Find Pivot Row
      for (int i=j+1; i<=n; i++) {
         if (ABS(A[i][j]) > pvt) {
            pvt = ABS(A[i][j]);
            ipvt_store = i;
         } else {
            ipvt_store = pivot[j];
         }
      }

      // Switch Rows if Necessary
      if (pivot[j] != ipvt_store) {
         pivot[j] = ipvt_store;
         pivot[ipvt_store] = j;
         rowswap_count++;
         // swap row elements
         for (int k=1; k<=n; k++) {
            temp = A[j][k];
            A[j][k] = A[pivot[j]][k];
            A[pivot[j]][k] = temp;
         }
         for (int l=1; l<=m; l++) {
            temp = B[l][j];
            B[l][j] = B[l][pivot[j]];
            B[l][pivot[j]] = temp;
         }
      }

      // Store multipliers
      for (int i=j+1; i<=n; i++)
         A[i][j] = A[i][j]/A[j][j];

      // Create zeros below main diagonal
      for (int i=j+1; i<=n; i++) {
         for (int k=j+1; k<=n; k++)
            A[i][k] = A[i][k] - A[i][j]*A[j][k];
         for (int l=1; l<=m; l++) {
            B[l][i] = B[l][i] - A[i][j]*B[l][j];
         }
      }
   } 

   // Compute determinant
   det = 1.0;
   for (int i=1; i<=n; i++)
      det *= A[i][i];
   if ((rowswap_count % 2) == 1)
      det = -det;

   // Back-substitution part
   for (int l=1; l<=m; l++) {
      X[l][n] = B[l][n]/A[n][n];
      for (int j=n-1; j>=1; j--) {
         X[l][j] = B[l][j];
         for (int k=n; k>=j+1; k--)
            X[l][j] = X[l][j] - X[l][k]*A[j][k];
         X[l][j] = X[l][j]/A[j][j];
      }
   }

}
