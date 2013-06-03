#ifndef _JPG_H
#define _JPG_H

#include "core/common.h"
#include "core/colorimage.h"

// Compress Image to JPG FROM PGM
void JPG_From_Image(char *filename, int *image, int N1, int N2);
void JPG_From_ColorImage(char *filename, color *image, int N1, int N2);

void Save_JPG_P6(ColorImage *img, char *imagefile);

void Read_JPG_File(char *filename, int &MAXVAL, int &N1, int &N2, int *&image);
void Read_Color_JPG_File(char *filename, int &MAXVAL, int &N1, int &N2, color *&image);

#endif
