#ifndef _SEQUENCE_H
#define _SEQUENCE_H

#include <iostream>
using namespace std;
#include <complex>

typedef complex<double> Complex;

class Sequence {
public:
	Complex *x;
	int len;
	int n0;
	Sequence() {len = 0; x = 0; }
	Sequence(int leni, int n0i) {len = leni; 
		x = new Complex[len]; n0 = n0i;}
	~Sequence() { if (!x) delete []x; }
	Sequence(int *img, int n1, int n2);
	void Set(int i, Complex z);
	Complex Get(int i);
};

#endif
