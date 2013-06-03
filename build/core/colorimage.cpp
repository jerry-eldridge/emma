#include "core/core.h"
#include "io/io.h"

#include <iostream>
using namespace std;

void TransposeColorArray(color *image, int N1, int N2, color *&imageT, int &M1, int &M2)
{
	M1 = N2; M2 = N1;
	int i, j;
	for (i=0; i<N1; i++) { for (j=0; j<N2; j++) {
		imageT[i+N1*j].r = image[j+N2*i].r;
		imageT[i+N1*j].g = image[j+N2*i].g;
		imageT[i+N1*j].b = image[j+N2*i].b;
	}}
}

void ColorImage::CopyDouble(ColorDoubleArray colDblArray)
{
	CopyDoubleToIntArray(colDblArray.r, r, N1, N2);
	CopyDoubleToIntArray(colDblArray.g, g, N1, N2);
	CopyDoubleToIntArray(colDblArray.b, b, N1, N2);
}
ColorImage::ColorImage(int n1, int n2)
{
	r = g = b = 0;
	N1 = n1; N2 = n2;
	alloc();
}

void ColorImage::Clear(int R, int G, int B)
{
	int n;
	for (n=0; n<N1*N2; n++) {
		r[n] = R;
		g[n] = G;
		b[n] = B;
	}
}
void ColorImage::SetPixel(int n, int R, int G, int B)
{
	r[n] = R; g[n] = G; b[n] = B;
}
void ColorImage::GetPixel(int n, int &R, int &G, int &B)
{
	R = r[n]; G = g[n]; B = b[n];
}
void ColorImage::SetPixel2(int i, int j, int R, int G, int B)
{
	r[j+N2*i] = R; g[j+N2*i] = G; b[j+N2*i] = B;
}
void ColorImage::GetPixel2(int i, int j, int &R, int &G, int &B)
{
	R = r[j+N2*i]; G = g[j+N2*i]; B = b[j+N2*i];
}
ColorImage::ColorImage()
{
	r = g = b = 0;
}

ColorImage::~ColorImage()
{
	free();
}

void ColorImage::Load_PPM(char *filename)
{
	Read_PPM_File(filename);
}

void ColorImage::Read_PPM_File(char *filename)
{
	char header[512];
	FILE *fp;
	fp = fopen(filename, "rb");
	Read_PPM_Header(fp, header, MAXVAL, N1, N2);
	if (!strcmp(header, "P3")) {
		cout << "PPM P3 is not yet supported" << endl;
	} else if (!strcmp(header, "P6")) {
		Read_PPM_P6_File_Helper(fp);
	} else {
		cout << "Can't read PPM file. Must be either P3 or P6 file." << endl;
		system("PAUSE");
		exit(1);		// check that header = "P2"
	}
	fclose(fp);
}

void ColorImage::Read_PPM_P6_File_Helper(FILE *&fp)
{
	int n;
	int ir, ig, ib;
	color *image;
	image = new color[N1*N2];
	fread(image, sizeof(color), N1*N2, fp);

	int tmp;
	tmp = N2;
	N2 = N1;
	N1 = tmp;

	r = new int[N1*N2];
	g = new int[N1*N2];
	b = new int[N1*N2];

	int M1, M2;
	color *image2;
	image2 = new color[N1*N2];
	TransposeColorArray(image, N1, N2, image2, M1, M2);
	delete []image;
	N1 = M1;
	N2 = M2;

	for (n=0; n<N1*N2; n++) {
		// permutation is (rgb). And (rgb)r = g, (rgb)g = b, (rgb)b = r.
		ir = image2[n].g;
		ig = image2[n].b;
		ib = image2[n].r;
		r[n] = ir;
		g[n] = ig;
		b[n] = ib;
	}
	delete []image2;
}

void ColorImage::alloc()
{
	r = new int[N1*N2];
	g = new int[N1*N2];
	b = new int[N1*N2];
}

void ColorImage::free()
{
	if (!r) delete []r;
	if (!g) delete []g;
	if (!b) delete []b;
	r = g = b = 0;
}

// todo check transpose of ColorImage
void ColorImage::Save_PGM_P6(char *filename)
{
	color *ColorImage;
	ColorImage = new color[N1*N2];
	int n;
	bool support;
	if (!r) {
		printf("plane undefined: Red\n");
		return;
	}
	if (!g) {
		printf("Image plane undefined: Green\n");
		return;
	}
	if (!b) {
		printf("Image plane undefined: Blue\n");
		return;
	}
	for (n=0; n<N1*N2; n++) {
		ColorImage[n].r = r[n];
		ColorImage[n].g = g[n];
		ColorImage[n].b = b[n];
	}
	color *ColorImageT;
	ColorImageT = new color[N1*N2];
	int M1, M2;
	TransposeColorArray(ColorImage, N1, N2, ColorImageT, M1, M2);
	delete []ColorImage;

	FILE *fp;
	fp = fopen(filename,"wb");
	fprintf(fp, "P6\n%d %d\n%d\n", N1, N2, 255);
	fwrite(ColorImageT, sizeof(color), N1*N2, fp);
	fclose(fp);
	delete []ColorImageT;
}
