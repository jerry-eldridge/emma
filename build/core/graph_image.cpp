#include "core/core.h"
#include <list>
#include <math.h>

void DrawGraph(int *img, int w, int h, Graph *G, pointDouble *pts) 
{
	int nv = G->V.size();
	int color = 0;
	int i;
	list<Node>::iterator p;
	double *rr = new double[nv];
	i = 0;
	for (p=G->V.begin(); p!=G->V.end(); p++) {
		DrawNode(img,w,h, *p, pts[i], rr[i]);
		i++;
	}
	list<Edge>::iterator q;
	for (q=G->E.begin(); q!=G->E.end(); q++) {
		Edge e = *q;
		double rp = 15;
		double r = 15;
		double phi = PI/10;
		double x1, y1, x2, y2;
		x1 = pts[e.i].x; y1 = pts[e.i].y;
		x2 = pts[e.j].x; y2 = pts[e.j].y;
		double r1, r2;
		r1 = rr[e.i]; r2 = rr[e.j];
		double psi = atan2(y2-y1,x2-x1);
		x1 = x1 + r1*cos(psi); y1 = y1 + r1*sin(psi);
		x2 = x2 + r2*cos(psi+PI); y2 = y2 + r2*sin(psi+PI);
		DrawArrow(img,w,h, x1,y1, x2,y2, color, r,phi);
	}
	delete []rr;
}

void DrawArrow(int *&img, int w, int h, 
			   double x1, double y1, double x2, double y2, int color,
			   double r, double phi)
{
	double psi = atan2(y2-y1,x2-x1);
	pointDouble p2, p3, p4, p5, p6;
	p2.x = x2;
	p2.y = y2;
	p3.x = r*cos(psi-phi);
	p3.y = r*sin(psi-phi);
	p4.x = r*cos(psi+phi);
	p4.y = r*sin(psi+phi);
	p5.x = p2.x - p3.x;
	p5.y = p2.y - p3.y;
	p6.x = p2.x - p4.x;
	p6.y = p2.y - p4.y;
	DrawLine(img,w,h,x1,y1,x2,y2,color);
	pointDouble p[3] = {p2,p5,p6};
	PolygonFill(img,w,h, p,3, color);

}

void DrawNode(int *img, int w, int h, Node v, pointDouble p, double &r)
{
	r = 15;
	int color = 0;
	char str[1024]="";

	if (v.box == none) {
		double kern = 0.42;
		int font_size = 20;
		r = strlen(v.label)*font_size*kern/2.0;
		PutText(img,w,h, v.label, p.x-r,p.y-font_size,FONT_PLAIN,
			font_size,font_size,kern,color);
		r = 0;
	} else if (v.box == rectangle) {
		double kern = 0.42;
		int font_size = 20;
		r = (strlen(v.label)+2)*font_size*kern/2.0;
		pointDouble p1,p2,p3,p4;
		p1.x = p.x - r;
		p1.y = p.y - font_size;
		p4.x = p1.x;
		p4.y = p1.y + font_size;
		p2.x = p.x + r;
		p2.y = p1.y;
		p3.x = p2.x;
		p3.y = p4.y;
		pointDouble pp[4] = {p1,p2,p3,p4};
		DrawPolygon(img,w,h, pp,4, 0);
		PutText(img,w,h, v.label, p.x-r+font_size*kern,p.y-font_size,
			FONT_PLAIN, font_size,font_size,kern,color);
		r = 0;
	} else if (v.box == circle) {
		int font_size = 20;
		r = strlen(v.label)*font_size/2.0;
		Ellipse(img,w,h,p.x,p.y,r,r,color);
		PutText(img,w,h, v.label, p.x-r,p.y-r,FONT_PLAIN,
			font_size,font_size,0.42,color);
	} else if (v.box == connection) {
		r = 3;
		FillEllipse(img,w,h,p.x,p.y,r,r,color);
	} else {
		r = 0;
	}

}
