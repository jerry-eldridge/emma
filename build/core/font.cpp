#include <iostream>
using namespace std;

#include "core/core.h"
#include <fstream>

void PutSymbol(int *img, int N1, int N2,
			   char ch, int x0, int y0, 
			   char *font, int sx, int sy,
			   int color, double rx, double ry)
{
	int x,y;
	x = y = 0;
	point pt_start, pt, last_pt;
	pt_start.x = x0; pt_start.y = y0;
	char fontfile[4096] = "";
	sprintf(fontfile, "%s\\%s\\%d.txt", FONT_DIR, font, ch);

	//cout << "Loading..." << fontfile << endl;
	ifstream in(fontfile);
	bool done = false;
	bool pen_down = false;
	while (!done) {
		char command = ' ';
		char buff[4096] = "";
		in >> command;
		if (command == 'D') {
			in >> x >> y;
			PutSymbolTransform(x,y, sx, sy);
			pt.x = pt_start.x + x;
			pt.y = pt_start.y + y;

			last_pt = pt;
			pen_down = true;
			//cout << "Pen down" << endl;
			in.getline(buff, 4096);
		} else if (command == 'M') {
			in >> x >> y;
			in.getline(buff, 4096);
			PutSymbolTransform(x,y, sx, sy);
			pt.x = pt_start.x + x;
			pt.y = pt_start.y + y;
			if (pen_down) {
				DrawLine2(img, N1, N2, last_pt, pt, color, rx,ry);
				last_pt = pt;
			}
		} else if (command == 'U') {
			pen_down = false;
			in.getline(buff, 4096);
			//cout << "Pen up" << endl;
		} else if (command == 'E') {
			done = true;
			in.getline(buff, 4096);
			//cout << "Exiting..." << fontfile << endl;
		} else {
			cout << "Error in font command" << endl;
			done = true;
		}
	}
	in.close();
}

// Input (x,y) are values within interval [0,200]x[0,200].
// Output (x,y) are a CvPoint in pixels relative to pt_start
void PutSymbolTransform(int &x, int &y, int sx, int sy)
{
	// normalize (x,y) by mapping to [0,1]x[0,1]
	double xx = x/200.0;
	double yy = y/200.0;
	x = xx*sx;
	y = yy*sy;
}

void PutText(int *img, int N1, int N2,
			   char *str, int x0, int y0, 
			   char *font, int sx, int sy,
			   double kern, int color, double rx, double ry)
{
	int step = kern*sx;
	int i;
	for (i=0; i<strlen(str); i++) {
		PutSymbol(img, N1, N2, str[i], x0+i*step, y0, font, sx,sy, 
			color, rx, ry);
	}
}
