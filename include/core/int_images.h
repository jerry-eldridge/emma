#ifndef _INT_IMAGES_H
#define _INT_IMAGES_H

#include "core/common.h"

// Routines on int Images
void CreateImageAutocorrelation(int *arr, int *&image, int N1, int N2);
void ConcatTwoImagesByWidth(int *imageA, int *imageB, int *&imageOut, int WidthA, int WidthB, int Height);
void ConvolveIntArrays(int *image1, int *image2, int*&image3, int N1, int N2, int M1, int M2);
void CorrectSignedByteImage(int *&image, int N1, int N2);
void TransposeIntArray(int *image, int N1, int N2, int *&imageT, int &M1, int &M2);
void CorrectSignedWordImage(int *&image, int N1, int N2);
void ZeroIntArray(int *&image, int N1, int N2);
void SetIntArray(int *&image, int N1, int N2, int val);

// Routines on Double and Int Arrays
void CopyDoubleToIntArray(double *arr, int *&image, int N1, int N2);
void CopyIntToDoubleArray(int *image, double *&arr, int N1, int N2);

#endif
