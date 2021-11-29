// dllS.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include <string>
#include "dllS.h"

#define MAX_LOADSTRING 100
#define CMD_BUTTON_SQR 1001
#define CMD_BUTTON_CUBE 1002
#define CMD_BUTTON_PLUS 1003
#define CMD_BUTTON_DECTOSIX 1004

typedef long (*sqr_type)(long); // sqr_type ~~ long (*)(long)
typedef long (*sqr_type2)(long,long); // sqr_type ~~ long (*)(long)
typedef long (*sqr_type3)(wchar_t); // sqr_type ~~ long (*)(long)
sqr_type sqr_fun; // sqr_type sqr_fun == long (*sqr_fun)(long)
sqr_type cube_fun;
sqr_type2 plus_fun;
sqr_type3 dectosix_fun;


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND sqrB;
HWND cubeB;
HWND plusB;
HWND dectosixB;
HWND edit;
HWND listbox;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void buttonSqr();
void buttonCube();
void buttonPlus();
void dectosix();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DLLS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DLLS));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DLLS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DLLS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:

		sqrB = CreateWindowW(L"Button", L"sqr", WS_CHILD | WS_VISIBLE, 10, 10, 75, 23, hWnd, (HMENU)CMD_BUTTON_SQR, hInst, NULL);
		cubeB = CreateWindowW(L"Button", L"cube", WS_CHILD | WS_VISIBLE, 10, 40, 75, 23, hWnd, (HMENU)CMD_BUTTON_CUBE, hInst, NULL);
		plusB = CreateWindowW(L"Button", L"plus", WS_CHILD | WS_VISIBLE, 10, 70, 75, 23, hWnd, (HMENU)CMD_BUTTON_PLUS, hInst, NULL);
		dectosixB = CreateWindowW(L"Button", L"dectosix", WS_CHILD | WS_VISIBLE, 10, 100, 75, 23, hWnd, (HMENU)CMD_BUTTON_DECTOSIX, hInst, NULL);
		listbox = CreateWindowW(L"Listbox", L"", WS_CHILD | WS_VISIBLE, 100, 10, 300, 400, hWnd, NULL, hInst, NULL);
		edit = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE, 10, 130, 75, 23, hWnd, NULL, hInst, NULL);

		break;
	case WM_COMMAND:
	{

		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{

		case CMD_BUTTON_SQR:
			buttonSqr();
			break;
		case CMD_BUTTON_PLUS:
			buttonPlus();
			break;
		case CMD_BUTTON_CUBE:
			buttonCube();
			break;
		case CMD_BUTTON_DECTOSIX:

			dectosix();
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


void buttonSqr() {

	HMODULE dll = LoadLibraryW(L"..\\Debug\\dll create.dll");
	if (dll == NULL) {

		MessageBoxW(NULL, L"error", L"dll", MB_OK | MB_ICONERROR);
	}
	else {
		sqr_fun = (sqr_type)GetProcAddress(dll, "sqr");

		if (sqr_fun) {




			wchar_t buff[100];
			SendMessageW(edit, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)buff);
			long param = _wtoi(buff);
			_snwprintf_s(buff, 100, L"%d^3 = %d", param, sqr_fun(param));
			SendMessageW(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)buff);


			//MessageBoxW(NULL, buff, L"OK", MB_OK | MB_ICONINFORMATION);

		}
		else {

			MessageBoxW(NULL, L"error", L"sqr", MB_OK | MB_ICONERROR);
		}
		
	}




}
void buttonCube() {



	HMODULE dll = LoadLibraryW(L"..\\Debug\\dll create.dll");
	if (dll == NULL) {

		MessageBoxW(NULL, L"error", L"dll", MB_OK | MB_ICONERROR);
	}
	else {
		cube_fun = (sqr_type)GetProcAddress(dll, "cube");
		if (cube_fun) {
			wchar_t buff[100];
			SendMessageW(edit,WM_GETTEXT, MAX_LOADSTRING, (LPARAM)buff);
			long param = _wtoi(buff);
			_snwprintf_s(buff, 100, L"%d^3 = %d", param, cube_fun(param));
			SendMessageW(listbox,LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)buff);


			//MessageBoxW(NULL, buff, L"OK", MB_OK | MB_ICONINFORMATION);
		}
		else {

			MessageBoxW(NULL, L"error", L"cube", MB_OK | MB_ICONERROR);


		}

	}
}


int parts;
std::string* splitString(std::string str, char sym) {

	size_t pos = 0;
	parts = 1;

	while ((pos = str.find(sym, pos + 1)) != std::string::npos) {
		parts++;
	}

	std::string* res = new std::string[parts];
	pos = 0;
	size_t pos2;

	for (int i = 0; i < parts - 1; i++) {

		pos2 = str.find(sym, pos + 1);
		res[i] = str.substr(pos, pos2 - pos);
		pos = pos2;


	}

	res[parts - 1] = str.substr(pos + 1);



	return res;
}




void buttonPlus() {
	try {

	HMODULE dll = LoadLibraryW(L"..\\Debug\\dll create.dll");
	if (dll == NULL) {

		MessageBoxW(NULL, L"error", L"dll", MB_OK | MB_ICONERROR);
	}
	else {
		plus_fun = (sqr_type2)GetProcAddress(dll, "plus");
		if (plus_fun) {

			std::string* params;
			wchar_t buff[100];
			SendMessageW(edit, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)buff);
			params=splitString(std::to_string((char)buff), '+');

			long a = std::atoi(params[0].c_str());
			SendMessageW(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)L"A");
			SendMessageA(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)params[0].c_str());
			long b = std::atoi(params[1].c_str());
			SendMessageW(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)L"B");
			SendMessageA(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)params[1].c_str());
			_snwprintf_s(buff, 100, L"%d + %d = %d", a,b, plus_fun(1,1));
			SendMessageW(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)buff);



			//MessageBoxW(NULL, buff, L"OK", MB_OK | MB_ICONINFORMATION);
		}
		else {

			MessageBoxW(NULL, L"error", L"cube", MB_OK | MB_ICONERROR);


		}


	}

	}
	catch (std::exception& ex) {

		SendMessageA(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)ex.what());
	}

}


void dectosix() {
	try{
	HMODULE dll = LoadLibraryW(L"..\\Debug\\dll create.dll");
	if (dll == NULL) {

		MessageBoxW(NULL, L"error", L"dll", MB_OK | MB_ICONERROR);
	}
	else {
		dectosix_fun = (sqr_type3)GetProcAddress(dll, "dectosix");
		if (dectosix_fun) {
			wchar_t buff[100];
			SendMessageW(edit, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)buff);
			long param = _wtoi(buff);
			_snwprintf_s(buff, 100, L"%d to hex = %d", param, dectosix_fun(param));
			SendMessageW(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)buff);


			//MessageBoxW(NULL, buff, L"OK", MB_OK | MB_ICONINFORMATION);
		}
		else {

			MessageBoxW(NULL, L"error", L"cube", MB_OK | MB_ICONERROR);


		}

	}

}
catch (std::exception& ex) {

	SendMessageA(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)ex.what());
}

}