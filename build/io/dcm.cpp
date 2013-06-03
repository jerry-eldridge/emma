#include "core/common.h"
#include "io/ppm.h"

#include <iostream>
using namespace std;

// Obtain dcm2pnm at http://dicom.offis.de/dcmtk.php.en
void Read_DCM_File(char *filename, int &MAXVAL, int &N1, int &N2, int *&image)
{
	char tmpfile[1024];
	char command[1024];
	static char path[1024] = "C:\\_Program Files\\dcmtk-3.5.4-win32-i386\\bin\\";
	static char prog[1024] = "dcm2pnm.exe"; //jpg to pgm, and other file formats
	//static char switches[1024] = "+op"; // saves as 8bit signed values
	static char switches[1024] = "+opw";	// saves as 16bit signed values
	sprintf(tmpfile, "TEMPFILE-DCM-TMPASsdDFDASasf001.pgm");
	sprintf(command, "\"%s%s\" %s %s %s", path, prog, switches, filename, tmpfile);
	system(command);
	Read_PGM_File(tmpfile, MAXVAL, N1, N2, image);
	remove(tmpfile);	// delete tmpfile
}

void Read_DCM_File_Info(char *filename)
{
	char command[1024];
	static char path[1024] = "C:\\_Program Files\\dcmtk-3.5.4-win32-i386\\bin\\";
	static char prog[1024] = "dcm2pnm.exe"; //jpg to pgm, and other file formats
	static char switches[1024] = "-im -o"; // display info no output
	sprintf(command, "\"%s%s\" %s %s %s", path, prog, switches, filename);
	system(command);
	system("PAUSE");
}

// Obtain dcm2pnm at http://dicom.offis.de/dcmtk.php.en
void Read_DCM_Options_File(char *filename, char *options, int &MAXVAL, int &N1, int &N2, int *&image)
{
	char tmpfile[1024];
	char command[1024];
	static char path[1024] = "C:\\_Program Files\\dcmtk-3.5.4-win32-i386\\bin\\";
	static char prog[1024] = "dcm2pnm.exe"; //jpg to pgm, and other file formats
	//static char switches[1024] = "+op"; // saves as 8bit signed values
	//static char switches[1024]; = "+opw";	// saves as 16bit signed values
	static char switches[1024];
	strcpy(switches, options);
	sprintf(tmpfile, "TEMPFILE-DCM-TMPASsdDFDASasf001.pgm");
	sprintf(command, "\"%s%s\" %s %s %s", path, prog, switches, filename, tmpfile);
	system(command);
	Read_PGM_File(tmpfile, MAXVAL, N1, N2, image);
	remove(tmpfile);	// delete tmpfile
}
