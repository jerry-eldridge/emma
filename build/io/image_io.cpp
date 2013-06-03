#include "io/ppm.h"
#include "io/jpg.h"
#include "io/dcm.h"
#include "core/usr_misc.h"

#include <iostream>
using namespace std;

void Read_Any_File(char *filename, int &MAXVAL, int &N1, int &N2, int *&image)
{
	char c = '.';
	char *pchar;
	char *ext;
	int len;
	pchar = strrchr(filename, c);
	if (!pchar) {
		printf("Filename has no extension. Eg, <filename>. Supported types are JPG, DCM, PGM.\n");
	}
	len = strlen(pchar);
	if (len == 0) {
		printf("Filename has no extension. Eg, <filename.>\n");
	}
	pchar++;
	ext = StringToUppercase(pchar);
	if (!strcmp(ext, "DCM")) {
		Read_DCM_File(filename, MAXVAL, N1, N2, image);
	} else if (!strcmp(ext, "JPG")) {
		Read_JPG_File(filename, MAXVAL, N1, N2, image);
	} else if (!strcmp(ext, "PGM")) {
		Read_PGM_File(filename, MAXVAL, N1, N2, image);
	} else {
		printf("Unsupported File extension.\n");
	}
	delete []ext;
}
