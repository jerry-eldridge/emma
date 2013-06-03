#include <stdio.h>
#include <iostream>
using namespace std;

#include "core/common.h"
#include "core/int_images.h"
#include "core/colorimage.h"
#include "io/ppm.h"

void Read_PGM_Header(FILE *&fp, char header[], int &MAXVAL, int &N1, int &N2)
{
	int flag = false;
	fscanf(fp, "%s", header);
	flag = !strcmp(header,"P2") || !strcmp(header,"P5");
	if (!flag) {
		cout << "Can't read PGM file. Unsupported Header. Must be P2 or P5" << endl;
		system("PAUSE");
		exit(1);		// check that header = "P2"
	}
#ifdef IRFANVIEW
	char comment[1024];
	fgets(comment,1024, fp);			// get newline left over from reading header
	fgets(comment,1024, fp);
#endif
	fscanf(fp, "%d %d", &N2, &N1);
	fscanf(fp, "%d", &MAXVAL);
#ifdef _MAXVAL_ONLY_255
	if (MAXVAL != 255) 	{
		cout << "Can't read PGM file. Unsupported Maxval. Must be 255" << endl;
		system("PAUSE");
		exit(1);		// check that header = "P2"
	}
#endif

}

void Read_PGM_File(char *filename, int &MAXVAL, int &N1, int &N2, int *&image)
{
	char header[512];
	FILE *fp;
	fp = fopen(filename, "rb");
	Read_PGM_Header(fp, header, MAXVAL, N1, N2);
	if (!strcmp(header, "P2")) {
		Read_PGM_P2_File_Helper(fp, N1, N2, image);
	} else if (!strcmp(header, "P5")) {
		Read_PGM_P5_File_Helper(fp, N1, N2, image);
	} else {
		cout << "Can't read PGM file. Must be either P2 or P5 file." << endl;
		system("PAUSE");
		exit(1);		// check that header = "P2"
	}
	fclose(fp);
}

void Read_PPM_File(char *filename, int &MAXVAL, int &N1, int &N2, color *&image)
{
	char header[512];
	FILE *fp;
	fp = fopen(filename, "rb");
	Read_PPM_Header(fp, header, MAXVAL, N1, N2);
	if (!strcmp(header, "P3")) {
		cout << "PPM P3 is not yet supported" << endl;
	} else if (!strcmp(header, "P6")) {
		Read_PPM_P6_File_Helper(fp, N1, N2, image);
	} else {
		cout << "Can't read PPM file. Must be either P3 or P6 file." << endl;
		system("PAUSE");
		exit(1);		// check that header = "P2"
	}
	fclose(fp);
}

void Read_PGM_P2_File_Helper(FILE *&fp, int &N1, int &N2, int *&image)
{
	int i;
	int *imageT;
	int M1, M2;
	imageT = new int[N1*N2];
	image = new int[N1*N2];

	for (i=0; i<N1*N2; i++) {
		fscanf(fp, "%d", &imageT[i]);
	}
	TransposeIntArray(imageT, N1, N2, image, M1, M2);
	N1 = M1;
	N2 = M2;
	delete []imageT;
}

void Read_PGM_P5_File_Helper(FILE *&fp, int &N1, int &N2, int *&image)
{
	int n;
	unsigned char *bytes;
	unsigned char byte;

	bytes = new unsigned char[N1*N2];
	fread(bytes, sizeof(unsigned char), N1*N2, fp);
	int *imageT;
	int M1, M2;
	imageT = new int[N1*N2];
	image = new int[N1*N2];
	for (n=0; n<N1*N2; n++) {
		byte = bytes[n];
		imageT[n] = byte;
	}
	delete []bytes;
	TransposeIntArray(imageT, N1, N2, image, M1, M2);
	N1 = M1;
	N2 = M2;
	delete []imageT;
}

void Read_PPM_P6_File_Helper(FILE *&fp, int &N1, int &N2, color *&image)
{
	int n;
	color *colors;
	color col;

	colors = new color[N1*N2];
	fread(colors, sizeof(color), N1*N2, fp);
	image = new color[N1*N2];
	for (n=0; n<N1*N2; n++) {
		// (r,g,b) <- (g,b,r)
		col.r = colors[n].g;
		col.g = colors[n].b;
		col.b = colors[n].r;
		image[n] = col;
	}
	delete []colors;
}

void PGM_P2_From_Image(char *filename, int *image, int N1, int N2, int maxval)
{
	FILE *fp;
	fp = fopen(filename,"w");
	int i,j;
	fprintf(fp, "P2\n%d %d\n%d\n", N1, N2, maxval);
	for (j = 0; j < N2; j++) {
		for (i = 0; i < N1; i++) {
			fprintf(fp, "%d ", image[j+N2*i]);
		}
		fprintf(fp, "\n");
	} 
	fprintf(fp, "\n");
	fclose(fp);
}

void PGM_P5_From_Image(char *filename, int *image, int N1, int N2)
{
	int *imageT;
	imageT = new int[N1*N2];
	int M1, M2;
	TransposeIntArray(image, N1, N2, imageT, M1, M2);
	FILE *fp;
	fp = fopen(filename,"wb");
	int n;
	unsigned char *bytes;
	unsigned char byte;
	bytes = new unsigned char[N1*N2];
	for (n=0; n<N1*N2; n++) {
		byte = imageT[n];
		bytes[n] = byte;
	}
	fprintf(fp, "P5\n%d %d\n%d\n", N1, N2, 255);
	fwrite(bytes, sizeof(unsigned char), N1*N2, fp);
	delete []bytes;
	delete []imageT;

	fclose(fp);
}

void PPM_P6_From_ColorImage(char *filename, color *ColorImage, int N1, int N2)
{
	FILE *fp;
	fp = fopen(filename,"wb");
	fprintf(fp, "P6\n%d %d\n%d\n", N1, N2, 255);
	fwrite(ColorImage, sizeof(color), N1*N2, fp);
	fclose(fp);
}


void Read_PPM_Header(FILE *&fp, char header[], int &MAXVAL, int &N1, int &N2)
{
	int flag = false;
	fscanf(fp, "%s", header);
	flag = !strcmp(header,"P3") || !strcmp(header,"P6");
	if (!flag) {
		cout << "Can't read PPM file. Unsupported Header. Must be P3 or P6" << endl;
		system("PAUSE");
		exit(1);		// check that header = "P2"
	}
#ifdef IRFANVIEW
	char comment[1024];
	fgets(comment,1024, fp);			// get newline left over from reading header
	fgets(comment,1024, fp);
#endif
	fscanf(fp, "%d %d", &N1, &N2);
	fscanf(fp, "%d", &MAXVAL);
#ifdef _MAXVAL_ONLY_255
	if (MAXVAL != 255) 	{
		cout << "Can't read PPM file. Unsupported Maxval. Must be 255" << endl;
		system("PAUSE");
		exit(1);		// check that header = "P2"
	}
#endif

}