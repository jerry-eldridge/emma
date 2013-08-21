//
// elim.h - header file for LU decomposition algorithm file, lu.cpp
//
#ifndef ELIM_H
#define ELIM_H

#include "core/defs.h"
void elim(float a[MAXSIZE][MAXSIZE], 
	  float X[MAXSIZE][MAXSIZE], 
	  float b[MAXSIZE][MAXSIZE],
	  unsigned m, 
	  unsigned n, float &det); 
	// a[1..n][1..n], b[1..m][1..n], X[1..m][1..n] 

#endif
