#ifndef _PAINT_H
#define _PAINT_H

#include "core/common.h"

void FillBucket(int *&arr, int N1, int N2, double x, double y, double val, double threshold);
void PolygonFill(int *arr, int N1, int N2, pointDouble *p, int N, double val);
int PointInPolygonTest(pointDouble *p, int N, double x, double y);
void PolygonFillMean(int *arr, int N1, int N2, pointDouble *pp, int N, double val);

#endif
