#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include <fstream>
#include "core/core.h"
#include "io/io.h"

#include <deque>

int *gimg = 0;
int gw = 500, gh = 500;
int gmaxval = 255;

void Read_Obj_File(int *&img, char *filename);
pointDouble Projection(point3 P);

int main()
{
	int w = gw;
	int h = gh;
	gimg = new int[w*h];
	SetIntArray(gimg, w, h, gmaxval);

	Read_Obj_File(gimg, "..\\data\\crypto.ema");

	PGM_P5_From_Image("crypto-1.pgm", gimg, w, h);
	system("crypto-1.pgm");

	delete []gimg;
}

// Read Wavefront's OBJ graphic file (partial implem.)
void Read_Obj_File(int *&img, char *filename)
{
	int i, j;
	ifstream in(filename);
	int nv;
	in >> nv;
	point3 *V = new point3[nv];
	for (i=0; i<nv; i++) {
		point3 p;
		in >> V[i].x >> V[i].y >> V[i].z;
	}
	int nf;
	in >> nf;
	for (i=0; i<nf; i++) {
		int M;
		in >> M;
		pointDouble *F = new pointDouble[M];
		for (j=0; j<M; j++) {
			int vtx;
			in >> vtx;
			F[j] = Projection(V[vtx-1]);
		}
		DrawPolygon(img, gw, gh, F, M, 0);
		
		delete []F;
	}
	delete []V;
	in.close();
}

pointDouble Projection(point3 P) 
{
	pointDouble Q;
	double D = 1000.0; // camera distance
	double s;

	P.x = P.x + 200;
	P.y = P.y + 200;

	s = 1.0/(P.z/D + 1);
	Q.x = P.x*s;
	Q.y = P.y*s;

	return Q;
}