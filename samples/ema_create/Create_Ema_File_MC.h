#ifndef _CREATE_EMA_FILE_MC_H
#define _CREATE_EMA_FILE_MC_H

#include <stdio.h>
#include <iostream>
using namespace std;
#include <fstream>

void CreatePrefix(FILE *fp);
void CreateSuffix(FILE *fp);

void MC_Create_Ema_File(const char *filename, float VoxelScaleSize, float Threshold);

#endif
