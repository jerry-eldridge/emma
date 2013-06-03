#ifndef _LINE_H
#define _LINE_H

#include "core/common.h"

void DrawLine(int *&display, int N1, int N2, point p1, point p2, int val);
void DrawLine(int *&display, int N1, int N2, 
			  double x1, double y1, double x2, double y2, int val);
void DrawLine_Bresenham(int *&arr, int N1, int N2, double x1, double y1, double x2, double y2, int val);

void DrawLine(ColorImage display, point p1, point p2, color col);

#endif
