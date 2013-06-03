#include "sequence.h"

Sequence::Sequence(int *img, int n1, int n2) {
	n0 = 0;
	len = n1*n2; 
	x = new Complex[len];
	int n; 
	for (n=0; n<len; n++) {
		x[n] = Complex(img[n],0);
	}
}
void Sequence::Set(int i, Complex z) { 
	if ((i>=n0)&&(i<n0+len)) {
		x[i-n0] = z;
	} else {
		// expand sequence. to do.
	}
}
Complex Sequence::Get(int i) {
	if ((i>=n0)&&(i<n0+len)) {
		return x[i-n0];
	} else {
		return Complex(0,0);
	}
}