#include <iostream>
using namespace std;

#include "core/core.h"
#include "io/io.h"

#include <fstream>
#include <math.h>
#include <time.h>

// Read Ema graphic file (partial implem. like Wavefront OBJ)
//
// ema format: [nv = number of total vertices, nf = number of vertices on face]
// nv
// x y z (vertex 1)
// ... 
// x y z (vertex vn)
// nf
// n v_1 v_2 ... v_n (face 1, vertices on face)
// ... (nf number of faces)
// Eg,
// 4
// 100 200 40.0
// 200 100 -300.0
// 0.0 50.0 300.0
// 30.0 100.0 200.0
// 2
// 3 1 2 3
// 3 1 3 4
//
// Camera and Center is used to view the 3D model
// Eg, Camera = (0,0,400); Center = (250,250,0)
//
void Read_Ema_File(char *filename, int &MAXVAL, 
				   int &N1, int &N2, int *&img,
				   Vector3D camera, Vector3D center)
{
	// projector of camera
	Vector3D proj;
	proj = VectorSubtract(center, camera);

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
		point3 *VV = new point3[M];
		for (j=0; j<M; j++) {
			int vtx;
			in >> vtx;
			VV[j] = V[vtx-1];
			F[j] = Projection(V[vtx-1], proj);
		}
		bool visible = BackFaceTest(VV, M, proj);
		int black = 0;
		if (visible) DrawPolygon(img, N1, N2, F, M, black);
		
		delete []VV;
		delete []F;
	}
	delete []V;
	in.close();
}

pointDouble Projection(point3 P, Vector3D proj) 
{
	pointDouble Q;
	double s;

	P.x = P.x + proj.x;
	P.y = P.y + proj.y;
	double D = proj.z;

	s = 1.0/(P.z/D + 1);
	Q.x = P.x*s;
	Q.y = P.y*s;

	return Q;
}

// compare for bubblesort
int compare(point3 *P, Vector3D proj)
{
	pointDouble v[3];
	int i;
	for (i=0; i<3; i++) {
		v[i] = Projection(P[i], proj);
	}

	double prod;
	prod = (v[1].x - v[0].x)*(v[2].y - v[0].y) -
		(v[2].x - v[0].x)*(v[1].y - v[0].y);

	if (prod > 0) {
		return -1; 
	} else if (prod < 0) { 
		return 1; 
	} else {
		double xx, yy, m1, m2;
		xx = v[1].x - v[0].x; yy = v[1].y - v[0].y;
		m1 = sqrt(xx*xx + yy*yy);
		xx = v[2].x - v[0].x; yy = v[2].y - v[0].y;
		m2 = sqrt(xx*xx + yy*yy);
		if (m1 < m2) { 
			return 1; 
		} else if (m1 > m2) { 
			return -1; 
		} else { return 0; }
	}

}

// bubblesort - sorts face vertices
void bubblesort(point3 *&VV, int M, Vector3D proj)
{
	int pairs = M-1;
	bool done;
	do {
		done = true;
		int i;
		for (i=0; i<pairs; i++) {
			point3 v[3];
			v[0] = VV[(i-1) % M];
			v[1] = VV[i % M];
			v[2] = VV[(i+1) % M];
			if ( compare(v, proj) < 0 ) {
				VV[i % M] = v[2];
				VV[(i+1) % M] = v[1];
				done = false;
			}
		}
		pairs--;
	} while (!done);
}

bool BackFaceTest(point3 *VV, int M, Vector3D Proj)
{
	// sort VV in clockwise fashion (assumed sorted for now)
	bubblesort(VV, M, Proj);

	bool visible = false;
	Vector3D v[3];
	int i;
	for (i=0; i<3; i++) {
		v[i].x = VV[i].x;
		v[i].y = VV[i].y;
		v[i].z = VV[i].z;
	}
	Vector3D u, w, N;
	u = VectorSubtract(v[1], v[0]);
	w = VectorSubtract(v[2], v[1]);
	N = VectorCross(u, w);

	float prod = VectorDot(N, Proj);
	visible = (prod >= 0.0);

	return visible;
}

// Read Em2 graphic file (partial implem. like a 2D Wavefront OBJ)
//
// em2 format: [nv = number of total vertices, 
//    nl = number of vertices on multilines]
// nv
// x y (vertex 1)
// ... 
// x y (vertex vn)
// nl
// n v_1 v_2 ... v_n (multiline 1, vertices on lines)
// ... (nl number of multilines)
// Eg,
// 4
// 100 200
// 200 100
// 0.0 50.0
// 30.0 100.0
// 2
// 3 1 2 3  (lines: 1 to 2, 2 to 3)
// 4 1 3 4 1 (lines: 1 to 3, 3 to 4, 4 to 1)
//
void Read_Em2_File(char *filename, int &MAXVAL, 
				   int &N1, int &N2, int *&img)
{
	int i, j;
	ifstream in(filename);
	int nv;
	in >> nv;
	cout << "Reading in nv = " << nv << " points." << endl;
	int NV_LIMIT = 20000;
	if (nv > NV_LIMIT) {
		cout << "Max points = 20,000 exceeded. " <<
			"See build\\core\\ema-fmt.cpp to change limit!" << endl;
		return;
	}
	point *V = new point[nv];
	for (i=0; i<nv; i++) {
		in >> V[i].x >> V[i].y;
	}
	int nl;
	in >> nl;
	cout << "Reading in nl = " << nl << " drawlines." << endl;
	for (i=0; i<nl; i++) {
		int M;
		in >> M;
		pointDouble *F = new pointDouble[M];
		for (j=0; j<M; j++) {
			int vtx;
			in >> vtx;
			F[j].x = V[vtx-1].x;
			F[j].y = V[vtx-1].y;
		}
		int black = 0;
		DrawLines(img, N1, N2, F, M, black);
		
		delete []F;
	}
	delete []V;
	in.close();
}
