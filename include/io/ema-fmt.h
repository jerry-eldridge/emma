#ifndef _EMAFMT_H
#define _EMAFMT_H

#include "core/common.h"
#include "core/vector3d.h"

// Similar to Wavefront OBJ format but simpler
void Read_Ema_File(char *filename, int &MAXVAL, 
				   int &N1, int &N2, int *&image,
				   Vector3D camera, Vector3D center);
bool BackFaceTest(point3 *VV, int M, Vector3D proj);
pointDouble Projection(point3 P, Vector3D proj);
void Read_Em2_File(char *filename, int &MAXVAL, 
				   int &N1, int &N2, int *&img);
#endif