README.txt -- Build emma.lib

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