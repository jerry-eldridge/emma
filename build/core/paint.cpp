#include "core/core.h"
#include <deque>
#include <iostream>
using namespace std;
#include <math.h>

// Point in Polygon + Fill Bucket using Mean as Picked point
void PolygonFillMean(int *arr, int N1, int N2, pointDouble *pp, int N, double val)
{
	int n;
	int *visited;
	visited = new int[N1*N2];
	for (n=0; n<N1*N2; n++) {
		visited[n] = 0;
	}
	bool support, neighbor;
	deque<point> neighbors;
	point p, p4[4];
	double x, y;
	// Calculate mean mu = (x,y)
	int k;
	x = 0; y = 0;
	for (k=0; k<N; k++) {
		x += pp[k].x;
		y += pp[k].y;
	}
	x = x/N; y = y/N;

	p.x = round(x);
	p.y = round(y);
	neighbors.push_back(p);
	int i, ii, jj;
	while (!neighbors.empty()) {
		p = neighbors.front();
		neighbors.pop_front();
		support = Array_Support(N1,N1,p.x,p.y);
		if (support) {
			ii = p.x; jj = p.y;
			if (visited[jj+N2*ii]) continue;
			arr[jj+N2*ii] = val;
			visited[jj+N2*ii] = 1;
		}
		// Defined N4 neighbors
		p4[0].x = p.x-1;
		p4[2].x = p.x+1;
		p4[0].y = p4[2].y = p.y;
		p4[1].y = p.y-1;
		p4[3].y = p.y+1;
		p4[1].x = p4[3].x = p.x;
		for (i=0; i<4; i++) {
			p = p4[i];
			support = Array_Support(N1,N1,p.x,p.y);
			if (!support) continue;
			ii = p.x; jj = p.y;
			neighbor = PointInPolygonTest(pp, N, ii, jj);
			support = support & neighbor;
			if (support) {
				neighbors.push_back(p);
			}
		}	
	}
	delete []visited;
}

void PolygonBounds(pointDouble *p, int N, 
				   int &i0, int &i1, int &j0, int &j1)
{
	int infty = 1e8;
	i0 = j0 = infty;
	i1 = j1 = -infty;
	int i;
	for (i=0; i<N; i++) {
		i0 = min(p[i].x, i0);
		i1 = max(p[i].x, i1);
		j0 = min(p[i].y, j0);
		j1 = max(p[i].y, j1);
	}
}

// This may be inefficient.
void PolygonFill(int *arr, int N1, int N2, pointDouble *p, int N, double val)
{
	int i0, i1, j0, j1;
	PolygonBounds(p, N, i0, i1, j0, j1);
	i0 = max(i0,0); j0 = max(j0,0);
	i1 = min(i1,N1); j1 = min(j1,N2);
	bool support;
	int pointtest;
	int i,j;
	for (i=i0; i<i1; i++) { for (j=j0; j<j1; j++) {
		pointtest = PointInPolygonTest(p, N, i, j);
		if (pointtest) {
			arr[j+N2*i] = val;
		}
	}}
}

void FillBucket(int *&arr, int N1, int N2, double x, double y, double val, double threshold)
{
	int n;
	int *visited;
	visited = new int[N1*N2];
	for (n=0; n<N1*N2; n++) {
		visited[n] = 0;
	}

	if (val <= threshold) {
		val = threshold+1;
	}
	bool support, neighbor;
	deque<point> neighbors;
	point p, p4[4];
	p.x = round(x);
	p.y = round(y);
	neighbors.push_back(p);
	int i, ii, jj;
	while (!neighbors.empty()) {
		p = neighbors.front();
		neighbors.pop_front();
		support = Array_Support(N1,N1,p.x,p.y);
		if (support) {
			ii = p.x; jj = p.y;
			if (visited[jj+N2*ii]) continue;
			arr[jj+N2*ii] = val;
			visited[jj+N2*ii] = 1;
		}
		// Defined N4 neighbors
		p4[0].x = p.x-1;
		p4[2].x = p.x+1;
		p4[0].y = p4[2].y = p.y;
		p4[1].y = p.y-1;
		p4[3].y = p.y+1;
		p4[1].x = p4[3].x = p.x;
		for (i=0; i<4; i++) {
			p = p4[i];
			support = Array_Support(N1,N1,p.x,p.y);
			if (!support) continue;
			ii = p.x; jj = p.y;
			neighbor = (arr[jj+N2*ii] <= threshold);
			support = support & neighbor;
			if (support) {
				neighbors.push_back(p);
			}
		}	
	}
	delete []visited;
}