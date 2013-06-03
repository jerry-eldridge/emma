#ifndef _DCM_H
#define _DCM_H

#include "core/common.h"

void Read_DCM_File(char *filename, int &MAXVAL, int &N1, int &N2, int *&image);
void Read_DCM_Options_File(char *filename, char *options, int &MAXVAL, int &N1, int &N2, int *&image);
void Read_DCM_File_Info(char *filename);

#endif
