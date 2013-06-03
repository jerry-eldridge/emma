#ifndef _PPM_H
#define _PPM_H

#include <stdio.h>
#include "core/common.h"

// WriteFile Routines. Write Images.
void PGM_P2_From_Image(char *filename, int *image, int N1, int N2, int maxval);
void PGM_P5_From_Image(char *filename, int *image, int N1, int N2);
void PPM_P6_From_ColorImage(char *filename, color *ColorImage, int N1, int N2);

// ReadFile Routines. Read Images
void Read_PGM_File(char *filename, int &MAXVAL, int &N1, int &N2, int *&image);
void Read_PPM_File(char *filename, int &MAXVAL, int &N1, int &N2, color *&image);
// Helper files
void Read_PGM_P2_File_Helper(FILE *&fp, int &N1, int &N2, int *&image);
void Read_PGM_P5_File_Helper(FILE *&fp, int &N1, int &N2, int *&image);
void Read_PGM_Header(FILE *&fp, char header[], int &MAXVAL, int &N1, int &N2);
void Read_PPM_Header(FILE *&fp, char header[], int &MAXVAL, int &N1, int &N2);
void Read_PPM_P6_File_Helper(FILE *&fp, int &N1, int &N2, color *&image);


#endif
