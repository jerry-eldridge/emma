#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include <math.h>
#include <fstream>
#include <string>
#include "core/core.h"
#include "io/io.h"

#include <deque>
#include <iomanip>

int *gimg = 0;
int gw = 500, gh = 500;
int gmaxval = 255;

void Read_Ema_File(int *&img, char *filename);
void Read_Obj_File(int *&img, char *filename, 
				   double &area_surface, double &volume);
void Calc3dPolygonArea(point3 *F, int np, 
					   double &area, point3 &normal);
pointDouble Projection(point3 P);

int main()
{
	int w = gw;
	int h = gh;
	gimg = new int[w*h];
	SetIntArray(gimg, w, h, gmaxval);

	double area_surface, volume;
	Read_Obj_File(gimg, 
		"3d-printer-web-test.obj",
		//"cube.obj",
		area_surface,volume);

	cout << "Volume (Divergence Theorem) = " << setprecision(10) << fabs(volume) << endl;
	cout << "Surface Area = " << setprecision(10) << area_surface << endl;

	system("pause");

	PGM_P5_From_Image("torus-like.pgm", gimg, w, h);
	system("torus-like.pgm");

	delete []gimg;
}

// Read Wavefront's OBJ graphic file (partial implem.)
void Read_Ema_File(int *&img, char *filename)
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

	P.x = P.x+250;
	P.y = P.y+250;

	s = 1.0/(P.z/D + 1);
	Q.x = P.x*s;
	Q.y = P.y*s;

	return Q;
}

// Read Wavefront's OBJ graphic file (partial implem.)
void Read_Obj_File(int *&img, char *filename, 
				   double &area_surface, double &volume)
{
	int i, j;
	ifstream in(filename);
	int nv,nf,nvt;
	nv = 0;
	nf = 0;
	nvt = 0;
	while (!in.eof()) {
		char buff[4096] = "";
		in.getline(buff, 4096);
		string s = buff;
		int pos0, pos1;
		pos0 = 0;
		pos1 = s.find(" ",pos0);
		string ss = s.substr(pos0, pos1-pos0);
		pos0 = pos1 + 1;
		if (!strcmp("v",ss.c_str())) nv++;
		if (!strcmp("vt",ss.c_str())) nvt++;
		if (!strcmp("f",ss.c_str())) nf++;
	}
	cout << "nv,nvt,nf = " << nv << " " << nvt << " " << nf << endl;
	in.clear();
	in.seekg(ios::beg);
	point3 *V = new point3[nv];
	i = 0;
	point3 minV, maxV, centroid;
	minV.x = 1e8;
	minV.y = 1e8;
	minV.z = 1e8;
	maxV.x = -1e8;
	maxV.y = -1e8;
	maxV.z = -1e8;
	centroid.x = centroid.y = centroid.z = 0;
	while (!in.eof()) {
		if (i >= nv) break;
		char buff[4096] = "";
		in.getline(buff, 4096);
		string s = buff;
		int pos0, pos1;
		pos0 = 0;
		pos1 = s.find(" ",pos0);
		string ss = s.substr(pos0, pos1-pos0);
		pos0 = pos1 + 1;
		string sval;
		if (!strcmp("v",ss.c_str())) {
			pos1 = s.find(" ",pos0);
			sval = s.substr(pos0, pos1-pos0);
			pos0 = pos1 + 1;
			V[i].x = atof(sval.c_str());
			pos1 = s.find(" ",pos0);
			sval = s.substr(pos0, pos1-pos0);
			pos0 = pos1 + 1;
			V[i].y = atof(sval.c_str());
			pos1 = s.find(" ",pos0);
			sval = s.substr(pos0, pos1-pos0);
			pos0 = pos1 + 1;
			V[i].z = atof(sval.c_str());

			centroid.x += V[i].x;
			centroid.y += V[i].y;
			centroid.z += V[i].z;

			if (V[i].x < minV.x) minV.x = V[i].x;
			if (V[i].y < minV.y) minV.y = V[i].y;
			if (V[i].z < minV.z) minV.z = V[i].z;

			if (V[i].x > maxV.x) maxV.x = V[i].x;
			if (V[i].y > maxV.y) maxV.y = V[i].y;
			if (V[i].z > maxV.z) maxV.z = V[i].z;

			i++;
		};
	}

	centroid.x /= 1.*nv;
	centroid.y /= 1.*nv;
	centroid.z /= 1.*nv;

	double volume_bound = 0;
	volume_bound = fabs(maxV.x - minV.x)*fabs(maxV.y - minV.y)*
			fabs(maxV.z - minV.z);
	cout << "Volume (of Bounding Box) = " << setprecision(10) << 
		volume_bound << endl;

	in.clear();
	in.seekg(ios::beg);

	i = 0;
	queue<int> *F = new queue<int>[nf];
	while (!in.eof()) {
		if (i >= nf) break;
		char buff[4096] = "";
		in.getline(buff, 4096);
		string s = buff;
		int pos0, pos1;
		pos0 = 0;
		pos1 = s.find(" ",pos0);
		string ss = s.substr(pos0, pos1-pos0);
		pos0 = pos1 + 1;
		if (!strcmp("f",ss.c_str())) {
			bool done = false;
			while (!done) {
				pos1 = s.find_first_of(" ",pos0);
				string sval;
				if (pos1 != -1) {
					sval = s.substr(pos0, pos1-pos0);
				} else {
					sval = s.substr(pos0, s.size()-pos0);
					done = true;
				}
				pos0 = pos1 + 1;
				int pos = sval.find("/",0);
				string sv = sval.substr(0, pos);
				F[i].push(atoi(sv.c_str()));
			}
			i++;
		}
	}
	in.close();
	in.clear();

	area_surface = 0.0;
	double volume_cones = 0;
	for (i=0; i<nf; i++) {
		int M;
		M = F[i].size();
		pointDouble *FF = new pointDouble[M];
		point3 *F3 = new point3[M];
		for (j=0; j<M; j++) {
			int vtx;
			vtx = F[i].front(); 
			F[i].pop();
			F3[j] = V[vtx-1];
			FF[j] = Projection(V[vtx-1]);
		}
		// Use only 4 points of FF, not M to keep down clutter
		// else change this back to M. Only for Drawing though.
		DrawPolygon(img, gw, gh, FF, min(M,4), 0);

		// Convert to point for PolygonCentroid()
		double area = 0;
		point3 n;
		Calc3dPolygonArea(F3, M, area, n);
		area_surface += fabs(area);
		// Using F = 1/3<x,y,z> as vector field, div F = 1,
		// and use Divergence theorem, Int Int Int (div F) dV =
		// Int Int F*n dS. So V = Int Int F*n dS.
		// F*n = 1/3(x*nx + y*ny + z*nz). Use (x,y,z) = F3[0],
		// the first point, or use centroid, and dS = area
		double x,y,z;
		x = F3[0].x; y = F3[0].y; z = F3[0].z;
		double dot = (x*n.x + y*n.y + z*n.z)/3.;
		volume += dot*fabs(area); // doesn't work for cube

		double r,xx,yy,zz;
		xx = x - centroid.x;
		yy = y - centroid.y;
		zz = z - centroid.z;
		r = sqrt(xx*xx+yy*yy+zz*zz);
		volume_cones += fabs(area)*r/3.; // volume of cone from centroid

		delete []F3;
		delete []FF;
	}
	cout << "Volume (sum of pyramids) = " << volume_cones << endl;
		
	delete []F;
	delete []V;
}

void Calc3dPolygonArea(point3 *F, int np, 
					   double &area, point3 &normal)
{
	if (np < 3) {
		area = 0;
		return;
	}
	point3 u,v,w;
	u = F[0];
	v = F[1];
	w = F[2];

	point3 A, B;
	A.x = u.x - v.x;
	A.y = u.y - v.y;
	A.z = u.z - v.z;
	B.x = w.x - v.x;
	B.y = w.y - v.y;
	B.z = w.z - v.z;

	point3 n; // normal to polygon in plane, F
	n.x = A.y*B.z - B.y*A.z;
	n.y = -(A.x*B.z-B.x*A.z);
	n.z = A.x*B.y - B.x*A.y;
	double magn = 0.0;
	magn = sqrt(1.*n.x*n.x+n.y*n.y+n.z*n.z);
	if (magn < 1e-8) magn = 1.0;
	n.x /= magn;
	n.y /= magn;
	n.z /= magn;
	normal = n;
	area = 0;
	int i;
	for (i=0; i<np; i++) {
		point3 A,B,C;
		A = F[i]; 
		B = F[(i+1)%np];

		C.x = A.y*B.z - B.y*A.z;
		C.y = -(A.x*B.z-B.x*A.z);
		C.z = A.x*B.y - B.x*A.y;

		double dot = 0;
		dot = n.x*C.x + n.y*C.y + n.z*C.z;
		area += dot;
	}
	area = area/2.;
}