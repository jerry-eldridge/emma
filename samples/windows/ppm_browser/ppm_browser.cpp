#include <windows.h>
#include <commdlg.h> // file menu

//// Create a compile error and uncomment these to see which warning message is disabled.
//#pragma warning (disable : 4244)
//#pragma warning (disable : 4101)
//#pragma warning (disable : 4305)
//#pragma warning (disable : 4996)

#include <iostream>
#include <string>
using namespace std;

#pragma comment(lib, "emma.lib")
#include "core/core.h"
#include "io/io.h"
//#include "io/jpg.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
TCHAR szAppName[] = TEXT ("Emma Windows") ;

//int gw = 500, gh = 500; // width, height
//int *gimg = new int[gw*gh];

int gw,gh;
ColorImage gimg;

static OPENFILENAME ofn;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	HWND     hwnd ;
	MSG      msg ;
	WNDCLASS wndclass ;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
				  szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	gw = gh = 500;
	hwnd = CreateWindow (szAppName, TEXT ("Emma Windows"),
					  WS_OVERLAPPEDWINDOW,
					  0,0,gw+20,gh+45,
					  NULL, NULL, hInstance, NULL) ;


	if (!strcmp(szCmdLine, "")) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFilter = TEXT("PPM files (*.ppm)\0*.ppm\0\0");
		ofn.nMaxFile = MAX_PATH;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrDefExt = TEXT("ppm");
		ofn.lpstrFile = szCmdLine;

		ofn.Flags = OFN_HIDEREADONLY;
		GetOpenFileName(&ofn);
	}
	if (!strcmp(szCmdLine, "")) {
		return 0;
	}

	//int i, j;
	//for (j=0; j<gh; j++) {
	//	for (i=0; i<gw; i++) {
	//		gimg[i+gw*j] = 100; // else j+h*i
	//	}
	//}

	// if Command Line is null, then Load will crash, need to
	// check for null szCmdLine and exit
	gimg.Load_PPM(szCmdLine);//"mandelbrot.ppm");
	gw = gimg.N1;
	gh = gimg.N2;


	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}

	return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	HDC	hdc ;
	PAINTSTRUCT ps ;
	int i,j, val, RR, GG, BB;

    switch (message) {
     case WM_CREATE:
		cxClient = LOWORD (lParam) ;
		cyClient = HIWORD (lParam) ;
     case WM_SIZE:
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          return 0;
	 case WM_MOUSEMOVE:
		return 0;
	 case WM_LBUTTONDOWN:
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	 case WM_KEYDOWN:
		 switch (wParam) {
			case VK_ESCAPE: // ESC
				PostQuitMessage (WM_DESTROY) ;
				break;
		 }
	 case WM_CHAR:
		 switch (wParam) {
			case 'p': case 'P':
				Beep(1000, 100);
				break;
		 }
		return 0;
     case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;

		for (j=0; j<gh; j++) {
			for (i=0; i<gw; i++) {
				//val = gimg[i+gw*j];
				gimg.GetPixel2(i,j, RR, GG, BB);				
				SetPixel(hdc, i, j, RGB(RR, GG, BB));
			}
		}

		EndPaint (hwnd, &ps) ;
		return 0 ;
     case WM_DESTROY:
		  //delete []gimg;

          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
