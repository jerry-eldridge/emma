#ifndef _DOUBLEARRAY_H
#define _DOUBLEARRAY_H

// [Could pass N, the size of arrs, and check if each label is within range.]
// Grid Paint By Numbers in "labels" L1xL2. Texture or Paint in **arrs  M1xM2 each. Result is arr, N1 x N2
void PaintByNumbersDoubleArray(double **arrs, int M1, int M2, int *labels, int L1, int L2, double *&arr, int &N1, int &N2);
void EdgesLaplacianDoubleArray(double *arr, double *&arrOut, int N1, int N2);
void EdgesSobelDoubleArray(double *arr, double *&arrOut, int N1, int N2);
void StretchDoubleArray(double *&arr, int N1, int N2);
void DivideDoubleArrays(double *image1, double *image2, double *&imageOut, int N1, int N2);
void ThresholdDoubleArray(double *&arr, double thresholdLow, double thresholdHigh, int N1, int N2);
void MinimumMaximumOfArray(double *arr, int N1, int N2, double &min1, double &max1);
void LogDoubleArray(double *arr, int N1, int N2);
void ScaleDoubleArray(double *&arr, double scalar, int N1, int N2);
void OutputDoubleArrayToFile(char *filename, double *arr, int N1, int N2);
void CopyDoubleToDoubleArray(double *arr, double *&arrOut, int N1, int N2);
// [FIREBAUGH] 142
void DrawLineInDoubleArray_DDA(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val);
void PolygonDoubleArray(double *arr, int N1, int N2, pointDouble *p, int N, double x, double y, double W, double H, double val);
void RotateAngleDoubleArray(double *arr, double *&arrOut, int N1, int N2, double Radians);
void RotateRightDoubleArray(double *arr, int N1, int N2, double *&arrOut, int &M1, int &M2);
void RotateLeftDoubleArray(double *arr, int N1, int N2, double *&arrOut, int &M1, int &M2);
void DrawLineInDoubleArray(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val);
void DrawLineInDoubleArray_N(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val, int N);
void DrawLineInDoubleArray_Bresenham_N(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val, int N);
// [FIREBAUGH] pg143
void DrawLineInDoubleArray_Bresenham(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val);
// Else recode using DrawLineInDoubleArray, to avoid preprocessing
void DrawLineInDoubleArray_DDA_N(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val, int N);
void DrawLineInDoubleArray_DDA_N_Helper(double *&arr, int N1, int N2, double x1, double y1, double x2, double y2, double val, int dn);
// O(N*M) algorithm to convolve two images
void ConvolveDoubleArrays(double *arr1, double *arr2, double*&arr3, int N1, int N2, int M1, int M2);
void FlipVerticalDoubleArray(double *arr, double *arrOut, int N1, int N2);
void FlipHorizontalDoubleArray(double *arr, double *arrOut, int N1, int N2);
void LocateMinMaxDoubleArray(double *arr, int N1, int N2, double &min1, double &max1, 
							 int &mini, int &minj, int &maxi, int &maxj);
void PasteWithMaskDoubleArray(double *&arr1, double *arr2, double *mask2, double x, double y, int N1, int N2, int M1, int M2);
void ClipDoubleArrayUsingZScore(double *&arr, double mean, double sigma, 
									  double ZScore, int N1, int N2);
void StatisticsOfDoubleArray(double *arr, double &mean, double &sigma, int N1, int N2);
void SubtractScalarFromDoubleArray(double *&arr, double scalar, int N1, int N2);
void SubtractDoubleArrays(double *arr1, double *arr2, double *&arrOut, int N1, int N2);
void CloseDoubleArray2(double *arr, double *&arrOut, int N1, int N2);
void OpenDoubleArray2(double *arr, double *&arrOut, int N1, int N2);
void TransposeDoubleArray(double *arr, int N1, int N2, double *&arrOut, int &M1, int &M2);
void MultiplyDoubleArrays(double *arr1, double *arr2, double *&arrOut, int N1, int N2, int N3);
void CloseDoubleArray(double *&arr, int N1, int N2);
void OpenDoubleArray(double *&arr, int N1, int N2);
void DisplayDoubleArray(double *arr, int ROW, int COL);
void DilateDoubleArray(double *&arr, int N1, int N2);
void ErodeDoubleArray(double *&arr, int N1, int N2);
void CenterDoubleArray(double *&arr, int N1, int N2);
void ScaleSizeDoubleArray(double *arr, double *&arrOut, double sx, double sy, int N1, int N2, int &M1, int &M2);
void TranslateDoubleArray(double *arr, double *&arrOut, double tx, double ty, int N1, int N2);
void DilateDoubleArray2(double *arr, double *&arrOut, int N1, int N2);
void ErodeDoubleArray2(double *arr, double *&arrOut, int N1, int N2);
void ZeroDoubleArray(double *&arr, int N1, int N2);
void AddDoubleArray2(double *&arr1, double *arr2, double x, double y, int N1, int N2, int M1, int M2);
void SubtractDoubleArray2(double *&arr1, double *arr2, double x, double y, int N1, int N2, int M1, int M2);
void PasteDoubleArray(double *&arr1, double *arr2, double x, double y, int N1, int N2, int M1, int M2);
void ExtendDoubleArray(double *arr, double *&arrOut, double x, double y, int N1, int N2, int M1, int M2);
void AddDoubleArray(double *arr1, double *arr2, double *&arrOut, int N1, int N2);
void AbsDoubleArray(double *&arr, int N1, int N2);

#endif