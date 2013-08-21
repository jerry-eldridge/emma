#include <iostream>
using namespace std;

#include <core/core.h>
#include <io/io.h>
#pragma comment(lib, "emma.lib")

#include <math.h>
#include <complex>

#include <fstream>

double f(double *Q, int n);

int main()
{	
	float dQ,Qmin,Qmax;
	double h = 0.0001; 
	int n = 1;
	int k = 0;
	dQ = 0.1;
	Qmin = -10;
	Qmax = 10;
	double *Q = new double[n];

	char filea1[1024] = "W.txt";
	ofstream out1(filea1);
	Q[k] = Qmin;
	while (Q[k] < Qmax) {
		out1 << Q[k] << " " << f(Q,n) << endl;
		Q[k] += dQ;
	}
	out1.close();
	Plot(filea1, "W.pgm", false, true);
	system("W.pgm");

	// Jacobian is J = dQ/df. If f = [f1 f2 f3] call
	// Jacobian(f,Q,n,J,N1,N2,h) instead. Here since f = [f1]
	// only need (partial) derivative Deriv(f,Q,n,k,h) on 
	// Q[k], the kth component of Q.
	char filea2[1024] = "dW.txt"; // the derivative
	ofstream out2(filea2);
	Q[k] = Qmin;
	while (Q[k] < Qmax) {
		out2 << Q[k] << " " << Deriv(f,Q,n,k,h) << endl;
		Q[k] += dQ;
	}
	out2.close();
	Plot(filea2, "dW.pgm", false, true); // the derivative
	system("dW.pgm");

	delete []Q;

	system("pause");
	return 0;
}

double f(double *Q, int n)
{
	float y;
	y = pow(Q[0],4)/4. - 36*pow(Q[0],2)/2. + 5;
	//y = cos(Q[0]);
	//y = pow(Q[0],2.0);
	return y;
}
