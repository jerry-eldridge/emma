#include <iostream>
using namespace std;

#include <string>

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"


int main(int argc, char *argv[])
{
	if (argc != 3) {
		cout << "Usage: draw_graph <graph>.txt <image>.pgm" << endl;
		return 0;
	}
	string s;
	if (argc == 3) {
		s = argv[2];
		int pos = s.find(".pgm",0);
		if (pos == -1) {
			cout << "Usage: draw_graph <graph>.txt <image>.pgm" << endl;
			return 0;
		}
	} 
	DisplayGraphFile(argv[1], argv[2]);

	return 0;
}
