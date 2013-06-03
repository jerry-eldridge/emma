#ifndef _FONT2_H
#define _FONT2_H

void PutSymbolPID(int *img, int N1, int N2,
			   char ch, int x0, int y0, 
			   char *font, int sx, int sy,
			   int color,
			   double dt, double omega, double nu, double eta
			   );
void PutTextPID(int *img, int N1, int N2,
			   char *str, int x0, int y0, 
			   char *font = FONT_PLAIN, int sx = 100, int sy = 100,
			   double kern = 0.35, int color = 0,
			   double dt = 0.1, 
			   double omega = 0.4, double nu = 0.01, double eta = 0.707);
#endif
