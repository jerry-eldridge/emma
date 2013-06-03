#include <iostream>
using namespace std;

#include <string>

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"


int main(int argc, char *argv[])
{
	if (argc != 2) {
		cout << "Usage: draw_graph <graph>.txt <image>.pgm" << endl;
		return 0;
	}
	DisplayGraphFile(argv[1], "worldmap_graph.pgm",700,500);

	return 0;
}
