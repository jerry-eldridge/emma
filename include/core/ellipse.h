#ifndef _ELLIPSE_H
#define _ELLIPSE_H

#include "core/common.h"

void Ellipse(int *img, int w, int h, 
			 double cx, double cy, double rx, double ry, int val);
void FillEllipse(int *img, int w, int h, 
			 double cx, double cy, double rx, double ry, int val);

#endif
