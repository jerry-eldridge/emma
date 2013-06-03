#include <iostream>
using namespace std;

#pragma comment(lib, "emma.lib")

#include "core/core.h"
#include "io/io.h"

ColorImage gdisplay(500,500);

int main() 
{
	gdisplay.Clear(0,0,255);
	char imgfilename[4098] = "eg3.ppm";
	gdisplay.Save_PGM_P6(imgfilename);
	system(imgfilename);

}
