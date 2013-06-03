#include <iostream>
using namespace std;

#include <core/core.h>
#include <io/io.h>
#pragma comment(lib, "emma.lib")

#include <fstream>
#include <math.h>

void Read_Ema_File_Shade(char *filename, int &MAXVAL, 
				   int &N1, int &N2, int *&img,
				   Vector3D camera, Vector3D center,
				   Vector3D light);

int bkgd = 255;

int main()
{
	int w, h, maxval;
	w = h = 500; maxval = 255;
	int *img = new int[w*h];
	SetIntArray(img,w,h,bkgd);

	// Lightbulb
	Vector3D light;
	light.x = 300; light.y = 500; light.z = 200;

	Vector3D camera, center;
	camera.x = 200; camera.y = 200; camera.z = 500;
	center.x = w/2; center.y = h/2; center.z = 0;
	Read_Ema_File_Shade("..\\data\\cube.ema",maxval,w,h,img,
		camera,center,light);

	char imgfile[1024] = "cube.pgm";
	PGM_P5_From_Image(imgfile,img,w,h);
	system(imgfile);

	delete []img;
	system("pause");
}


void Read_Ema_File_Shade(char *filename, int &MAXVAL, 
				   int &N1, int &N2, int *&img,
				   Vector3D camera, Vector3D center,
				   Vector3D light)
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

		// Figure color, shade = (normal * light), 
		// normal is to polygon face
		int white = 255;
		Vector3D v1, v2, v3, u1, u2, lite, normal;
		v1.x = VV[0].x; v1.y = VV[0].y; v1.z = VV[0].z;
		v2.x = VV[1].x; v2.y = VV[1].y; v2.z = VV[1].z;
		v3.x = VV[2].x; v3.y = VV[2].y; v3.z = VV[2].z;
		u1 = VectorSubtract(v2,v3);
		u2 = VectorSubtract(v1,v2);
		normal = VectorCross(u1,u2);
		normal = VectorNormalize(normal);
		lite = VectorNormalize(light);
		float shade = VectorDot(lite,normal);
		int color = white*fabs(shade);

		if (visible) {
			DrawPolygon(img, N1, N2, F, M, black);
			PolygonFill(img,N1,N2,F,M,color);

			//char imgfile2[1024] = "cube3.pgm";
			//PGM_P5_From_Image(imgfile2,img,N1,N2);
			//system(imgfile2);
		}
		
		delete []VV;
		delete []F;
	}
	delete []V;
	in.close();
}