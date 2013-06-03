#include <iostream>
using namespace std;

#include <core/core.h>
#include <io/io.h>
#pragma comment(lib, "emma.lib")

#include <math.h>
#include <complex>

#include <fstream>

typedef complex<double> Complex;

Complex H(Complex z);

void AmpData(char *filename);
void PhaseData(char *filename);
Complex H(double omega);
Complex H(Complex z);

int main()
{
	char filea[1024] = "oppen-p229-amp.txt";
	char filep[1024] = "oppen-p229-phase.txt";
	char imfilea[1024] = "oppen-p229-amp.pgm";
	char imfilep[1024] = "oppen-p229-phase.pgm";
	AmpData(filea);
	PhaseData(filep);
	Plot(filea, imfilea, true);
	system(imfilea);
	Plot(filep, imfilep, false);
	system(imfilep);

	Plot("humidity-mote2-filtered.txt","humidity.pgm",false);
	system("humidity.pgm");

	system("pause");
	return 0;
}

void AmpData(char *filename)
{
	ofstream out(filename);
	double omega = 0, d_omega = 2*PI/100;
	while (omega < 2*PI) {
		Complex z = H(omega);
		double amp = log(norm(z));
		out << omega << " " << amp << endl;
		omega += d_omega;
	}

	out.close();
}

void PhaseData(char *filename)
{
	ofstream out(filename);
	double omega = 0, d_omega = 2*PI/100;
	while (omega < 2*PI) {
		Complex z = H(omega);
		double phase = arg(z);
		out << omega << " " << phase << endl;
		omega += d_omega;
	}

	out.close();
}


Complex H(double omega)
{
	Complex z(cos(omega),sin(omega));
	return H(z);
}

Complex H(Complex z)
{
	Complex w, z1, z2, one(1,0);
	z1 = pow(z,-1); z2 = pow(z,-2);
	w = 0.05634*(one+z1)*(one-1.0166*z1 + z2)/
		((one-0.683*z1)*(one-1.4461*z1+0.7957*z2));
	return w;

}