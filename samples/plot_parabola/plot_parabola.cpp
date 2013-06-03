#include <iostream>
using namespace std;

#include <core/core.h>
#include <io/io.h>
#pragma comment(lib, "emma.lib")

#include <math.h>
#include <complex>

#include <fstream>

float f(float x);

int main()
{
	char filea[1024] = "W.txt";
	ofstream out(filea);
	float x,dx,xmin,xmax;
	xmin = -10;
	xmax = 10;
	x = xmin;
	dx = 0.1;
	while (x < xmax) {
		out << x << " " << f(x) << endl;
		x += dx;
	}
	out.close();

	Plot(filea, "W.pgm", false, true);
	system("W.pgm");

	system("pause");
	return 0;
}

float f(float x)
{
	float a, b, c;
	//a = 3.0; b = -2.0; c = 5.0;
	//float y = a*x*x + b*x + c;
	
	//float y = 3*log10(x+6);
	//float y = 3*pow(x,4) - 100*pow(x,2) - 30.0*pow(x,1) + 3.0;
	
	float y = pow(x,4)/4. - 36*pow(x,2)/2. + 5;
	return y;
}
