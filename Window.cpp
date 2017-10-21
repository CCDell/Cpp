
#include "stdafx.h"
#include "windows.h"
#include "Resources.h"
#include <iostream>

#define MAX_LOADSTRING 100

HINSTANCE hInst; // Handle to the window that stuff is going down in.
				 // 16bit unicode character
WCHAR szWindowTitle[MAX_LOADSTRING] = L"SteamPunkGame"; //Title Bar text 
WCHAR szWindowClass[MAX_LOADSTRING] = L"SteamPunkGame"; //Window Class Name

//Function declarations
ATOM MyRegisterClass(HINSTANCE); // Registers the class for windows
//Declares all of the stuff it needs to understand about the window.
BOOL InitInstance(HINSTANCE, int);//
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPreviousInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	std::cout << "Lmao";

	LoadStringW(hInstance, IDS_APP_TITLE, szWindowTitle, 50);


	hInst = hInstance;



	return 1;
}

/*
*Function: MyRegisterClass(HINSTANCE hInstance);
*Purpose: Registers the window class.
*/

ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}

/*
*Function: InitInstance(HINSTANCE,int)
*Purpose: Saves the instance handle and creates the main window
*Comments: In this function, we save the instance handle in a global 
*		   variable and create and display the main program window.
*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	hInst = hInstance;
	//Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szWindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if(!hWnd){return FALSE; }
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

/*
*Function: WndProc(HWND,UINT,WPARAM,LPARAM)
*Purpose: Processes messages for the main window.
*WM_COMMAND -process the application menu
*WM_PAINT - Paint the main window
*WM_DESTROY - post a quit message and return
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
						WPARAM wParam, LPARAM lParam) {
	switch (message) {

		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);

			switch (wmId) {
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			//Draw anything that uses hdc ici

			EndPaint(hWnd, &ps);
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		}
	return 0;
}

//Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return(INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}


