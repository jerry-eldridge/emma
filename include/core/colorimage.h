#ifndef _COLORIMAGE_H
#define _COLORIMAGE_H

#include <stdio.h>
#include "core/common.h"

class ColorDoubleArray;

class ColorImage {
public:
	int *r;
	int *g;
	int *b;
	int N1;
	int N2;
	int MAXVAL;
	ColorImage();
	ColorImage(int n1, int N2);
	~ColorImage();
	void Clear(int R, int G, int B);
	void SetPixel(int n, int R, int G, int B);
	void GetPixel(int n, int &R, int &G, int &B);
	void SetPixel2(int i, int j, int R, int G, int B);
	void GetPixel2(int i, int j, int &R, int &G, int &B);
	void Load_PPM(char *filename);
	void Save_PGM_P6(char *filename);
	void alloc();
	void free();
	void Read_PPM_File(char *filename);
	void Read_PPM_P6_File_Helper(FILE *&fp);
	void CopyDouble(ColorDoubleArray colDblArray);
};

// Routines on Color Images
void TransposeColorArray(color *image, int N1, int N2, color *&imageT, int &M1, int &M2);

#endif