#ifndef _USR_MISC_H
#define _USR_MISC_H

#include "core/common.h"

int round(double x);
double My_atan2(double x, double y);
char *StringToUppercase(char *&str);
bool Array_Support(int N1, int N2, int x, int y);
void FalseColor(double t, double mid, int &r, int &g, int &b);
double Fleck_L(double x); // Margaret Fleck function
void swap(double x, double y);
void CorrectSignedByteImage(int *&image, int N1, int N2); //useful for DICOM
double MapTo(double x1, double y1, double x2, double y2, double x);

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif
