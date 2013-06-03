README.txt

Emma is a Graphics library that works with int *img and double *dimg
images. You can save to PGM and PPM formats as well as optionally
compress to JPG with the gnuwin JPG library mentioned below. 

It will create graphics in a int *img = new int[w*h] array for example
such as setting values, drawing lines, ellipses, graphs, etc.

PGM,PPM,JPG image files can be viewed with Irfanview image editor.
Alternatively, you could use the freeglut (GLUT) pgm and ppm opengl
program. I prefer Irfanview editor. There might be other PGM/PPM
image viewers on web, search www.google.com for such.

Emma was created by Jerry Eldridge.

README-INCLUDE.txt
Set

#define FONT_DIR "c:\\emma\\fonts" in emma\include\core\font.h

to specify where emma\fonts folder is located at.

README-BUILD.txt -- Build emma.lib

Create a Static Library called "emma.lib" and put into
"..\lib\".

For example, using Visual Studio 2008 Express from Microsoft,
you can create a static library, and Release version.
Options are Console Application, Windows Application, DLL,
and Static Library in Visual Studio 2008 (and later).

The program assumes the .h files are in include\.
So far this has include\core\ and include\io\. 

For example, if the emma project is in c:\emma\
You specify c:\emma\include as an Include directory
in Visual C++ 2008 or later. And c:\emma\lib as an
Library directory.

Visual Studio 2008 > Tools > Options > Projects and Solutions >
VC++ Directories > Show directories for Library and Include.

README-JPG.txt

To compress to JPG, install the GnuWin32 JPG library
containing "djpeg.exe" and "cjpeg.exe" in the directory

"C:\\_Program Files\\GnuWin32\\bin\\"

else change emma\io\jpg.cpp to use a different location.

Obtain djpeg and cjpeg at 
http://gnuwin32.sourceforge.net/packages/jpeg.htm
