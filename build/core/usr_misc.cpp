#include "core/usr_misc.h"

#include <iostream>
using namespace std;

#include <math.h>

char *StringToUppercase(char *&str)
{
	char *buffer;
	char c;
	int i, len;
	len = strlen(str);
	buffer = new char[len+1];
	for (i=0; i<len; i++) {
		c = toupper(str[i]);
		buffer[i] = c;
	}
	buffer[len] = 0;
	return buffer;
}

void CorrectSignedByteImage(int *&image, int N1, int N2)
{
	int pos, neg;
	int val;
	int n;
	for (n=0; n<N1*N2; n++) {
		val = image[n];
		pos = 0x7F & val;
		neg = -(0x80&val);
		val = pos+neg+0x80;
		image[n] = val;
	}
}

bool Array_Support(int N1, int N2, int x, int y)
{
	return !((x<0)||(x>=N1)||(y<0)||(y>=N2));
}

void FalseColor(double t, double mid, int &r, int &g, int &b)
{
	if (t<=mid) {
		r = round(P3_MAXVAL*(-1.0/mid*(t-mid)));
		g = round(P3_MAXVAL*(1.0/mid*(t-mid)+1));;
		b = 0;
	} else {
		r = 0;
		g = round(P3_MAXVAL*(-1.0/(1-mid)*(t-1)));
		b = round(P3_MAXVAL*(1.0/(1-mid)*(t-1)+1));
	}
}

// From paper on skin detection by Margaret Fleck
double Fleck_L(double x)
{
	return 105*log10(x+1);
}


int round(double x)
{
	int val = 0;
	val = floor(x + 0.5);
	return val;
}

// Note swap() is defined as a generic function in C or C++. Topic: portability
void swap(double x, double y)
{
	double tmp;
	tmp = x; 
	x = y; 
	y = tmp;
}

double My_atan2(double x, double y)
{
	double theta;
	theta = atan2(y,x);
	if (theta < 0.0) {
		theta += 2*PI;
	}
	return theta;
}

// With x1 -> y1 and x2 -> y2, given x, return y using linear map
double MapTo(double x1, double y1, double x2, double y2, double x)
{
	double m = 1.*(y2-y1)/(x2-x1);
	double y = m*(x-x1)+y1;
	return y;
}