#ifndef _FONT_H
#define _FONT_H

#include "core/common.h"

#define FONT_DIR "c:\\emma\\fonts"
#define FONT_PLAIN "font3"
#define FONT_CURSIVE "fontc02"
#define FONT_SYMBOL "fsymbol"
#define FONT_PHONEME "fparker"

void PutSymbolTransform(int &x, int &y, int sx, int sy);
void PutSymbol(int *img, int N1, int N2,
			   char ch, int x0, int y0, 
			   char *font, int sx, int sy,
			   int color);
void PutText(int *img, int N1, int N2,
			   char *str, int x0, int y0, 
			   char *font = FONT_PLAIN, int sx = 50, int sy = 50,
			   double kern = 0.35, int color = 0);

#endif
