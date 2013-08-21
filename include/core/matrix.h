#ifndef _MATRIX_H
#define _MATRIX_H

void PrintMat(double *A, int N1, int N2);

void Add(double *A, double *B, double *C, int N1, int N2);//C := A+B
void Sub(double *A, double *B, double *C, int N1, int N2);//C := A-B
void Mult(double *A, double *B, double *C, int N1, int N2, int N3);//C := A*B
void Copy(double *A, double *B, int N1, int N2); // B := A
void Transpose(double *A, double *B, int N1, int N2); // B := A^T

double Det2x2(double *A, int N1, int N2); // see inverse.h
void Inv2x2(double *A, double *Ainv, int N1, int N2);

void Identity(double *A, int N1, int N2); // A = I_nxm identity matrix

#endif
