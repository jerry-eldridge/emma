#include "core/common.h"
#include "core/colorimage.h"
#include "io/ppm.h"

#include <iostream>
using namespace std;

void Read_Color_JPG_File(char *filename, int &MAXVAL, int &N1, int &N2, color *&image)
{
	char tmpfile[1024];
	char command[1024];
	static char path[1024] = "C:\\_Program Files\\GnuWin32\\bin\\";
	static char prog[1024] = "djpeg.exe"; //jpg to pgm, and other file formats
	static char switches[1024] = "";
	sprintf(tmpfile, "%s-TMPASsdDFDASasf001.ppm", filename);
	//sprintf(command, "\"%s%s\" %s -outfile .\\%s .\\%s", path, prog, switches, tmpfile, filename);
	sprintf(command, "\"%s%s\" %s -outfile %s %s", path, prog, switches, tmpfile, filename);

	system(command);
	Read_PPM_File(tmpfile, MAXVAL, N1, N2, image);
	remove(tmpfile);	// delete tmpfile
}


// Obtain djpeg and cjpeg at http://gnuwin32.sourceforge.net/packages/jpeg.htm
void JPG_From_Image(char *filename, int *image, int N1, int N2)
{
	char tmpfile[1024];
	char command[1024];
	static char path[1024] = "C:\\_Program Files\\GnuWin32\\bin\\";
	static char prog[1024] = "cjpeg.exe"; // pgm to jpg, and other file formats
	static char switches[1024] = "-quality 95 -optimize";
	sprintf(tmpfile, "TEMPFILE-TMPASasdHSLDJHSALDhasf001.pgm", filename);
	PGM_P5_From_Image(tmpfile, image, N1, N2);
	sprintf(command, "\"%s%s\" %s -outfile %s %s", path, prog, switches, filename, tmpfile);
	system(command);
	remove(tmpfile);	// delete tmpfile
}

void JPG_From_ColorImage(char *filename, color *image, int N1, int N2)
{
	char tmpfile[1024];
	char command[1024];
	static char path[1024] = "C:\\_Program Files\\GnuWin32\\bin\\";
	static char prog[1024] = "cjpeg.exe"; // pgm to jpg, and other file formats
	static char switches[1024] = "-quality 95 -optimize";
	sprintf(tmpfile, "%s-TMPASasdHSLDJHSALDhasf001.ppm", filename);
	PPM_P6_From_ColorImage(tmpfile, image, N1, N2);
	sprintf(command, "\"%s%s\" %s -outfile .\\%s .\\%s", path, prog, switches, filename, tmpfile);
	system(command);
	remove(tmpfile);	// delete tmpfile
}

// Obtain djpeg and cjpeg at http://gnuwin32.sourceforge.net/packages/jpeg.htm
void Read_JPG_File(char *filename, int &MAXVAL, int &N1, int &N2, int *&image)
{
	char tmpfile[1024];
	char command[1024];
	static char path[1024] = "C:\\_Program Files\\GnuWin32\\bin\\";
	static char prog[1024] = "djpeg.exe"; //jpg to pgm, and other file formats
	static char switches[1024] = "-grayscale";
	sprintf(tmpfile, "TEMPFILE-JPG-TMPASsdDFDASasf001.pgm", filename);
	sprintf(command, "\"%s%s\" %s -outfile %s %s", path, prog, switches, tmpfile, filename);
	system(command);
	Read_PGM_File(tmpfile, MAXVAL, N1, N2, image);
	remove(tmpfile);	// delete tmpfile
}

void Save_JPG_P6(ColorImage *img, char *imagefile)
{
	int i,j;
	int w = img->N1, h = img->N2;
	color *cimg = new color[w*h];
	for (j=0; j<h; j++) { for (i=0; i<w; i++) {
		cimg[i+w*j].r = img->r[j+h*i];
		cimg[i+w*j].g = img->g[j+h*i];
		cimg[i+w*j].b = img->b[j+h*i];
	}}
	JPG_From_ColorImage(imagefile, cimg, w, h);
	delete []cimg;
}