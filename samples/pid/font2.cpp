#include <iostream>
using namespace std;

#include "core/core.h"
#include <fstream>

point PID_Symbol(point pt, point e, point &p, point &v, 
				 point &last_e, point &sum_e,
				 double dt, double omega, double nu, double eta);

void PutSymbolPID(int *img, int N1, int N2,
			   char ch, int x0, int y0, 
			   char *font, int sx, int sy,
			   int color,
			   double dt, double omega, double nu, double eta
			   )
{
	point p, v, e, last_e, sum_e;
	int x,y;
	x = y = 0;
	point pt_start, pt, last_pt, new_pt, last_pt2, pt2;
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
			last_pt2.x = pt.x;
			last_pt2.y = pt.y;
			new_pt.x = last_pt2.x;
			new_pt.y = last_pt2.y;
			pen_down = true;

			point zero;
			zero.x = 0;
			zero.y = 0;
			v = zero; p = pt; last_e = zero; sum_e = zero;

			//cout << "Pen down" << endl;
			in.getline(buff, 4096);
		} else if (command == 'M') {
			in >> x >> y;
			in.getline(buff, 4096);
			PutSymbolTransform(x,y, sx, sy);
			pt.x = pt_start.x + x;
			pt.y = pt_start.y + y;

			e.x = new_pt.x - pt.x;
			e.y = new_pt.y - pt.y;
			new_pt = PID_Symbol(pt,e,p,v,last_e,sum_e,
				dt,omega,nu,eta);

			//if (pen_down) {
			//	DrawLine(img, N1, N2, last_pt, pt, color);
			//	last_pt = pt;
			//}
			if (pen_down) {
				// lines aren't drawn correctly without eps added
				double eps = 0.7; 
				DrawLine(img, N1, N2, last_pt2.x, last_pt2.y,
					new_pt.x+eps, new_pt.y+eps, color);
				//cout << "DrawLine(" << last_pt2.x - new_pt.x
				//	<< ", " << last_pt2.y - new_pt.y << ");" << endl;
				last_pt2 = new_pt;
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

point PID_Symbol(point pt, point e, point &p, point &v, 
				 point &last_e, point &sum_e,
				 double dt, double omega, double nu, double eta)
{
	point a;

	// A standard PID equation was used. See PID equation from
	// "Line Drawing as a Dynamic Process", Donald H. House, 
	// Mayank Singh (Texas A&M University)
	// Eg, see encyclopedia or reference on Proportional Integral
	// Derivative (PID) in control theory.

	sum_e.x = sum_e.x + e.x;
	sum_e.y = sum_e.y + e.y;

	a.x = -omega*omega*e.x - 2*eta*omega*(e.x-last_e.x)/dt-nu*sum_e.x*dt;
	a.y = -omega*omega*e.y - 2*eta*omega*(e.y-last_e.y)/dt-nu*sum_e.y*dt;

	v.x = v.x + a.x*dt;
	v.y = v.y + a.y*dt;
	p.x = p.x + v.x*dt;
	p.y = p.y + v.y*dt;

	last_e.x = e.x;
	last_e.y = e.y;

	return p;
}

void PutTextPID(int *img, int N1, int N2,
			   char *str, int x0, int y0, 
			   char *font, int sx, int sy,
			   double kern, int color,
			   double dt, double omega, double nu, double eta
			   )
{
	int step = kern*sx;
	int i;
	for (i=0; i<strlen(str); i++) {
		PutSymbolPID(img, N1, N2, str[i], x0+i*step, y0, font, 
			sx,sy, color, dt, omega, nu, eta);
	}
}