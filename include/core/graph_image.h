#ifndef _GRAPH_IMAGE_H
#define _GRAPH_IMAGE_H

#include "graph.h"
#include "core/core.h"

void DrawGraph(int *img, int w, int h, Graph *G, pointDouble *pts);
void DrawNode(int *img, int w, int h, Node v, pointDouble p, double &r);
void DrawArrow(int *&img, int w, int h, 
			   double x1, double y1, double x2, double y2, int color,
			   double r, double phi);

#endif