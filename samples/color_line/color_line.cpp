#include <iostream>
using namespace std;

#include <complex>
#include <math.h>

typedef complex<double> Complex;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"

int main() 
{
	Complex a, b, c, d;

	a = Complex(0,0);
	b = Complex(1,0);
	c = Complex(1,1);
	d = Complex(2, -1);

	cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " 
		<< d << endl;
	cout << "a + b = " << a + b << endl;
	cout << "d * b = " << d*b << endl;
	cout << "d * c = " << d*c << endl;
	cout << "d^3 = d*d*d = " << d*d*d << endl;

	cout << " exp(z) = exponential function, z a complex number" << endl;
	cout << " exp(a) = " << exp(a) << endl;
	cout << " exp(b) = " << exp(b) << endl;
	cout << " exp(c) = " << exp(c) << endl;

	int w = 500, h = 500; // width, height
	ColorImage img(w,h);
	img.Clear(180, 180, 255);
	point p1, p2, p3;
	p1.x = 40; p1.y = 100;
	p2.x = 200; p2.y = 200;
	p3.x = 400; p3.y = 500;
	color col, green;
	col.r = 255; col.g = 0; col.b = 0;
	green.r = 255; green.g = 255; green.b = 0;
	DrawLine(img.r, w, h, p1, p2, col.r); // red plane
	DrawLine(img.g, w, h, p1, p2, col.g); // green plane
	DrawLine(img.b, w, h, p1, p2, col.b); // blue plane

	DrawLine(img, p2, p3, green); // (red, green, blue) planes

	char imagefile[4096] = "exp.ppm";
	img.Save_PGM_P6(imagefile);
	system(imagefile);

	system("pause");
	return 0;
}
