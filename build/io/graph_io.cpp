#include "core/core.h"
#include "io/io.h"

#include <math.h>

void DisplayGraphFile(char *graph_file, char *img_file,
		int w, int h)
{
	Graph G;
	G.Load(graph_file);

	int maxval = 255;
	int *img = new int[w*h];
	SetIntArray(img, w, h, maxval);

	//srand(time(0));
	int i, nv;
	nv = G.V.size();
	pointDouble *pts = new pointDouble[nv];
	for (i=0; i<nv; i++) {
		//pts[i].x = rand()%w;
		//pts[i].y = rand()%h;
		pts[i].x = w/2.0 + (w/2.0-50)*cos(2*PI*i/nv);
		pts[i].y = h/2.0 + (h/2.0-50)*sin(2*PI*i/nv);
	}
	DrawGraph(img,w,h,&G,pts);
	PGM_P2_From_Image(img_file, img, w, h, maxval);

	delete []img;
	delete []pts;
}
