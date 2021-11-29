// dllS.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include <string>
#include "dllS.h"

#define MAX_LOADSTRING 100
#define CMD_BUTTON_SQR 1001
#define CMD_BUTTON_CUBE 1002
#define CMD_BUTTON_PLUS 1003
#define CMD_BUTTON_DEC2HEX 1005
#define CMD_BUTTON_HEX2DEC 1006

typedef long (*sqr_type)(long); // sqr_type ~~ long (*)(long)
typedef long (*sqr_type2)(long, long); // sqr_type ~~ long (*)(long)
typedef long (*sqr_type3)(wchar_t); // sqr_type ~~ long (*)(long)
sqr_type sqr_fun; // sqr_type sqr_fun == long (*sqr_fun)(long)
sqr_type cube_fun;
sqr_type2 plus_fun;
//sqr_type3 dec2hex_fun;


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND sqrB;
HWND cubeB;
HWND plusB;
HWND dec2hexB;
HWND hex2decB;
HWND edit;
HWND listbox;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void buttonSqr();
void buttonCube();
void buttonPlus();
void dec2hex();
void hex2dec();

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
		dec2hexB = CreateWindowW(L"Button", L"dec2hex", WS_CHILD | WS_VISIBLE, 10, 100, 75, 23, hWnd, (HMENU)CMD_BUTTON_DEC2HEX, hInst, NULL);
		hex2decB = CreateWindowW(L"Button", L"hex2dec", WS_CHILD | WS_VISIBLE, 10, 130, 75, 23, hWnd, (HMENU)CMD_BUTTON_HEX2DEC, hInst, NULL);
		listbox = CreateWindowW(L"Listbox", L"", WS_CHILD | WS_VISIBLE, 100, 10, 300, 400, hWnd, NULL, hInst, NULL);
		edit = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE, 10, 160, 75, 23, hWnd, NULL, hInst, NULL);

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
		case CMD_BUTTON_DEC2HEX:

			dec2hex();
			break;
		case CMD_BUTTON_HEX2DEC:
			
			hex2dec();
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
			SendMessageW(edit, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)buff);
			long param = _wtoi(buff);
			_snwprintf_s(buff, 100, L"%d^3 = %d", param, cube_fun(param));
			SendMessageW(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)buff);


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
	


	HMODULE dll = LoadLibraryW(L"..\\Debug\\dll create.dll");
	long (*plus)(long,long);
	plus = (long (*)(long, long))GetProcAddress(dll, "plus");

	if (plus) {
		char buff[100];
		SendMessageA(edit, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)buff);
		
		std::string* res=splitString(buff,'+');
		int a = atoi(res[0].c_str());
		int b = atoi(res[1].c_str());



		_snprintf_s(buff, 100, 100, "%d + %d  = %d", a,b, plus(a,b));
		SendMessageA(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)buff);

	}
	else {

		MessageBoxW(NULL, L"error", L"plus", MB_OK | MB_ICONERROR);


	}

}

void dec2hex() {

	HMODULE dll = LoadLibraryW(L"..\\Debug\\dll create.dll");
	char* (*dec2hex)(int);
	dec2hex = (char*(*)(int))GetProcAddress(dll, "dec2hex");

	if (dec2hex) {
		char buff[100];
		SendMessageA(edit, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)buff);
		int param = atoi(buff);
		char* res = dec2hex(param);
		_snprintf_s(buff,100, 100, "%d to hex = %s", param, res);
	

		SendMessageA(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)buff);
		delete res;
	}
	else {

		MessageBoxW(NULL, L"error", L"dec2hex", MB_OK | MB_ICONERROR);


	}
}

void hex2dec() {

	HMODULE dll = LoadLibraryW(L"..\\Debug\\dll create.dll");

	int (*hex2dec)(const char*);
	hex2dec = (int (*)(const char *))GetProcAddress(dll, "hex2dec");

	if (hex2dec) {
		char buff[100];
		SendMessageA(edit, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)buff);


		_snprintf_s(buff, 100, 100, "%s to dec = %d", buff, hex2dec(buff));


		SendMessageA(listbox, LB_ADDSTRING, MAX_LOADSTRING, (LPARAM)buff);

	}
	else {

		MessageBoxW(NULL, L"error", L"hex2dec", MB_OK | MB_ICONERROR);


	}
}

