#include <iostream>
using namespace std;
#include <math.h>
#include <fstream>

#include "core/core.h"
#include "io/io.h"
#pragma comment(lib, "emma.lib")

double X(double *Q, int n); // x = X(Q,n)
double Y(double *Q, int n); // y = Y(Q,n)
double Z(double *Q, int n); // z = Z(Q,n)

int main()
{
	int n;
	int N1, N2;
	n = 3;
	const int m = 3;
	N1 = m; N2 = n;
	double (*F[m])(double *,int) = {X,Y,Z}; // define F[m] = [X,Y,Z]
	double h = 0.00001;

	// Create Arrays
	double *J = new double[N1*N2];
	double *Jinv = new double[N1*N2];
	double *A = new double[N1*N2];
	double *Q = new double[n];
	double *P = new double[m];
	double *Q_New= new double[n]; // next state
	double *P_New = new double[n]; // next state
	double *C1 = new double[n]; // temporary matrices Ci
	double *C2 = new double[n];
	double *P_Accuracy = new double[m];

	// Q[0] in (0,infty), Q[1] in [0,PI], Q[2] in [0,2*PI]
	Q[0] = 1; Q[1] = PI/2.; Q[2] = 0;

	cout << "This Computes the inverse f^{-1} of a nonlinear\n" <<
		"transformation f. Note that P = f(Q). Input a P_New close\n" <<
		"to previous P and a linear transformation matrix J, the\n" <<
		"Jacobian, is calculated which is used for approximating\n" <<
		"the inverse Q = f^{-1}(P).\n" << 
		"http://en.wikipedia.org/wiki/Jacobian_matrix_and_determinant\n" <<
		"An initialization of Q is done previous calculating P = f(Q)\n\n" <<
		"Secretly, Q is spherical coordinates, P is cartesian coordinates\n" <<
		"and J and Jinv converts from one to the other. But the method\n" <<
		"works for any function f, not just the transformation from spherical\n" <<
		"to cartesian.\n" <<
		endl;
	int i,j;
	bool start = true;
	for (i=0; i<30; i++) {
		// Compute P = F(Q)
		for (j=0; j<m; j++) 
			P[j] = F[j](Q,n);

		// Copy P to P_New at start
		if (start) {
			start = false;
			Copy(P, P_New, m, 1);
		}

		// Compute Jacobian J
		Jacobian(F,Q,n,J,N1,N2,h);

		//cout << "J = " << endl; PrintMat(J,N1,N2);
		cout << "Q_New = f^{-1}(P) = "; PrintMat(Q,n,1);
		cout << "(Corrected) P = f(Q_New) = "; PrintMat(P,m,1);
		Sub(P_New, P, P_Accuracy, m, 1); // Compare P_New and P
		cout << "error(P) = "; PrintMat(P_Accuracy,m,1);
		//Inv2(J, A, N1, N2); // A = Jinv using 2x2 Inverse
		//cout << "Jinv2 = " << endl; PrintMat(A,N1,N2);
		double det = 0;
		Inv(J, Jinv, N1, det); // Compute Jinv using nxn Inverse
		//cout << "Jinv = " << endl; PrintMat(Jinv,N1,N2);
		//cout << "det(Jinv) = " << det << endl;

		cout << "Input P_New[m]: (" << m << " values) on one line" << endl;
		// Input P_New
		for (j=0; j<m; j++) {
			cout << ">> P_New[" << j << "]: ";
			cin >> P_New[j];
		}

		Sub(P_New, P, C1, n, 1);
		Mult(J, C1, C2, n, n, 1); // Assume N2 = n.
		Add(Q,C2,Q_New,n,1); // Q_New = Q + J*(P_New - P)
		cout << "Using Q_New = Q + J*(P_New - P) = f^{-1}(P_New), J = Jacobian." << endl;
		cout << "You can also use P_New = P + Jinv*(Q_New - Q) = f(Q_New)." << endl;

		//Sub(Q_New, Q, C1, n, 1);
		//Mult(Jinv, C1, C2, n, n, 1); // Assume N2 = n.
		//Add(P,C2,P_New,n,1); // P_New = P + Jinv*(Q_New - Q)
		//cout << "P_New = P + Jinv*(Q_New - Q) = "; PrintMat(P_New,n,1);

		Copy(Q_New,Q,n,1); // Copy Q_New to Q
	}

	// Delete Arrays
	delete []J;
	delete []Jinv;
	delete []A;
	delete []Q;
	delete []P;
	delete []Q_New;
	delete []P_New;
	delete []C1;
	delete []C2;
	delete []P_Accuracy;

	system("pause");
	return 0;
}

double X(double *Q, int n)
{
	return Q[0]*sin(Q[1])*cos(Q[2]);
}

double Y(double *Q, int n)
{
	return Q[0]*sin(Q[1])*sin(Q[2]);
}

double Z(double *Q, int n)
{
	return Q[0]*cos(Q[1]);
}