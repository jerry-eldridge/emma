README.txt

Compile example1.cpp using the "emma.lib" file created in 
the emma\build\ directory.

Alternatively, you could move all .cpp file to a single
directory containing also example1.cpp. And compile
to example1.exe. Run. It creates an image and displays
with the Operating System's default method of displaying
a PGM file.

The program assumes the .h files are in include\.
So far this has include\core\ and include\io\. 

For example, if the emma project is in c:\emma\
You specify c:\emma\include as an Include directory
in Visual C++ 2008 or later. And c:\emma\lib as an
Library directory.

Visual Studio 2008 > Tools > Options > Projects and Solutions >
VC++ Directories > Show directories for Library and Include.

By Right Clicking on example1 in a Visual Studio 2008
sln project, you can:
Solution 'example1' > example1 (right click) > Properties >
Output directory: "..\bin\"
if you want example1.exe to be output to c:\emma\bin\.


