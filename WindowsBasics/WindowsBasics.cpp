// WindowsBasics.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsBasics.h"
#include <string>
#include "Controls.h"
#include "Pizza.h"

#define MAX_LOADSTRING 100
#define CMD_BUTTON_PRESS_ME 1001
#define CMD_BUTTON_PLUS 1002
#define CMD_BUTTON_MINUS 1003
#define CMD_BUTTON_PLUSTEN 1004
#define CMD_BUTTON_MINUSTEN 1005
#define CMD_BUTTON_RESET 1006
#define CMD_BUTTON_PIZZA 1007

// Global Variables:
//HINSTANCE hInst;                                // current instance
HWND hStatic1;
HWND inc;
HWND incTen;
HWND dec;
HWND decTen;
HWND reset;
HWND pressME;
HWND mainWindow;
HWND Pizza;

//BOOL isControlsReg;

WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
//WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


void createEX();
void processEX(int);
void processEXReset();
//void showWindowControls();



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	isControlsReg = FALSE;
	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadStringW(hInstance, IDC_WINDOWSBASICS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);

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
	//https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexw

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); //size of the structure

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; // function that process messages sent to window https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms633573(v=vs.85)
	wcex.cbClsExtra = 0; //the number of extra bytes
	wcex.cbWndExtra = 0; //the number of extra bytes
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSBASICS)); // handle to an icon resource if NULL=> default icon
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // handle to a cursor resource
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2); //handle to the class background brush
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSBASICS);
	wcex.lpszClassName = L"BasicsWindow";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); //handle to a small icon

	return RegisterClassExW(&wcex);
}

/*COLOR_ACTIVEBORDER
COLOR_ACTIVECAPTION
COLOR_APPWORKSPACE
COLOR_BACKGROUND
COLOR_BTNFACE
COLOR_BTNSHADOW
COLOR_BTNTEXT
COLOR_CAPTIONTEXT
COLOR_GRAYTEXT
COLOR_HIGHLIGHT
COLOR_HIGHLIGHTTEXT
COLOR_INACTIVEBORDER
COLOR_INACTIVECAPTION
COLOR_MENU
COLOR_MENUTEXT
COLOR_SCROLLBAR
COLOR_WINDOW
COLOR_WINDOWFRAME
COLOR_WINDOWTEXT*/


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

	//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowa
	HWND hWnd = CreateWindowW( // hWnd = new WinWlass
		L"BasicsWindow", //
		L"I've changed this title",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,//window position x
		0,//window position y
		640,// window width
		480,// window height
		nullptr, //parent or owner window
		nullptr, // ID of command
		hInstance,
		nullptr);

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

	mainWindow = hWnd;
	switch (message)
	{
	case WM_CREATE:

		createEX();

		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case CMD_BUTTON_PRESS_ME:


			showWindowControls(hInst,mainWindow);


			break;
		case CMD_BUTTON_PIZZA:
			showWindowPizza(hInst, mainWindow);
			break;

		case CMD_BUTTON_PLUS:

			processEX(1);

			break;
		case CMD_BUTTON_MINUS:

			processEX(-1);

			break;
		case CMD_BUTTON_PLUSTEN:

			processEX(10);
			break;
		case CMD_BUTTON_MINUSTEN:

			processEX(-10);
			break;
		case CMD_BUTTON_RESET:
			processEXReset();
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


void createEX() {
	//hStatic2

	hStatic1 = CreateWindowW(
		L"Static",//class name
		L"0", //title
		WS_VISIBLE | WS_CHILD | DT_CENTER,//style
		(640 / 2) - 75 / 2, (480 / 2) - 23 / 2, //x y
		75, 23,
		mainWindow,//parent window
		0,//menu command - no
		hInst,//instanse handle
		NULL);//extra params struct

	inc = CreateWindowW(L"Button", L"++", WS_VISIBLE | WS_CHILD | BS_PUSHLIKE, (640 / 2) - 75 / 2 + 100, (480 / 2) - 23 / 2, 75, 23, mainWindow, (HMENU)CMD_BUTTON_PLUS, hInst, NULL);
	incTen = CreateWindowW(L"Button", L"+10", WS_VISIBLE | WS_CHILD, (640 / 2) - 75 / 2 + 200, (480 / 2) - 23 / 2, 75, 23, mainWindow, (HMENU)CMD_BUTTON_PLUSTEN, hInst, NULL);
	dec = CreateWindowW(L"Button", L"--", WS_VISIBLE | WS_CHILD, (640 / 2) - 75 / 2 - 100, (480 / 2) - 23 / 2, 75, 23, mainWindow, (HMENU)CMD_BUTTON_MINUS, hInst, NULL);
	decTen = CreateWindowW(L"Button", L"-10", WS_VISIBLE | WS_CHILD, (640 / 2) - 75 / 2 - 200, (480 / 2) - 23 / 2, 75, 23, mainWindow, (HMENU)CMD_BUTTON_MINUSTEN, hInst, NULL);
	reset = CreateWindowW(L"Button", L"Reset", WS_VISIBLE | WS_CHILD, (640 / 2) - 75 / 2, 300, 75, 23, mainWindow, (HMENU)CMD_BUTTON_RESET, hInst, NULL);
	pressME = CreateWindowW(L"Button", L"Press me", WS_VISIBLE | WS_CHILD, (640 / 2) - 75 / 2, 265, 75, 23, mainWindow, (HMENU)CMD_BUTTON_PRESS_ME, hInst, NULL);
	Pizza = CreateWindowW(L"Button", L"Pizza", WS_VISIBLE | WS_CHILD, 320-75/2,100 , 75, 23, mainWindow, (HMENU)CMD_BUTTON_PIZZA, hInst, NULL);
}

void processEX(int num) {

	WCHAR  str[MAX_LOADSTRING];
	SendMessageW(hStatic1, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)str);

	int n = _wtoi(str);

	n += num;
	_itow_s(n, str, MAX_LOADSTRING, 10);

	SendMessageW(hStatic1, WM_SETTEXT, 0, (LPARAM)str);

}

void processEXReset() {

	SendMessageW(hStatic1, WM_SETTEXT, 0, (LPARAM)"0");
}
//
//LRESULT CALLBACK    WndProcControls(HWND, UINT, WPARAM, LPARAM);
//
//void createControls(HWND);
//
////////////////////////
//#define CMD_CHECKBOX 2001
//#define CMD_PUSHLIKE 2002
//#define CMD_RADIOBUTTON1 2003
//#define CMD_RADIOBUTTON2 2004
//#define CMD_RADIOBUTTON3 2005
//#define CMD_RADIOBUTTON4 2006
//#define CMD_COMBOBOX 2007
//#define CMD_COMBOBOX 2008
//
////////////////////////
//
//HWND hwndCHECKBOX;
//HWND hwndPUSHLIKE;
//HWND hwndRADIO1;
//HWND hwndRADIO2;
//HWND hwndRADIO3;
//HWND hwndRADIO4;
//HWND hwndCOMBOBOX;
//HWND hwndLISTBOX;
//
//
//
//void showWindowControls() {
//
//	//Register class;
//	//WndProc
//	//CreateWindow
//	srand(time(0));
//	if (!isControlsReg) {
//
//		WNDCLASSEXW wcex;
//		ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
//		wcex.cbSize = sizeof(WNDCLASSEX);
//		wcex.lpfnWndProc = WndProcControls;
//		wcex.hInstance = hInst;
//		wcex.hbrBackground = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))/*((HBRUSH)(COLOR_WINDOW + 1))*/;
//		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//		wcex.lpszClassName = L"ControlsWindow";
//
//		if (!RegisterClassExW(&wcex)) {
//			MessageBoxW(mainWindow, L"Register class error!", L"Error", MB_OK | MB_ICONERROR);
//			return;
//		}
//		isControlsReg = TRUE;
//	}
//
//	//3
//	HWND controlsWindow = CreateWindowW(L"ControlsWindow", L"Controls", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, mainWindow, NULL, hInst, 0);
//
//	ShowWindow(controlsWindow, SW_NORMAL);
//
//}
//
//LRESULT CALLBACK    WndProcControls(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//
//	switch (message)
//	{
//	case WM_CREATE:
//		createControls(hWnd);
//		break;
//
//	case WM_COMMAND:
//	{
//		int wmId = LOWORD(wParam);
//
//		switch (wmId)
//		{
//		case CMD_CHECKBOX: {
//
//			LRESULT state = SendMessageW(hwndCHECKBOX, BM_GETCHECK, 0, 0);
//			if (state == BST_CHECKED) {
//
//				SendMessageW(hwndCHECKBOX, BM_SETCHECK, BST_UNCHECKED, 0);
//				SendMessageW(hwndCHECKBOX, WM_KILLFOCUS, 0, 0);
//				SendMessageW(hwndCHECKBOX, WM_SETTEXT, 0, (LPARAM)L"unchecked");
//			}
//			else {
//
//				SendMessageW(hwndCHECKBOX, BM_SETCHECK, BST_CHECKED, 0);
//				SendMessageW(hwndCHECKBOX, WM_KILLFOCUS, 0, 0);
//				SendMessageW(hwndCHECKBOX, WM_SETTEXT, 0, (LPARAM)L"checked");
//
//			}
//		}
//						 break;
//		case CMD_PUSHLIKE: {
//
//			LRESULT state = SendMessageW(hwndPUSHLIKE, BM_GETCHECK, 0, 0);
//			if (state == BST_CHECKED) {
//
//				SendMessageW(hwndPUSHLIKE, BM_SETCHECK, BST_UNCHECKED, 0);
//				SendMessageW(hwndPUSHLIKE, WM_KILLFOCUS, 0, 0);
//				SendMessageW(hwndPUSHLIKE, WM_SETTEXT, 0, (LPARAM)L"unchecked");
//			}
//			else {
//
//				SendMessageW(hwndPUSHLIKE, BM_SETCHECK, BST_CHECKED, 0);
//				SendMessageW(hwndPUSHLIKE, WM_KILLFOCUS, 0, 0);
//				SendMessageW(hwndPUSHLIKE, WM_SETTEXT, 0, (LPARAM)L"checked");
//
//			}
//
//		}
//
//						 break;
//
//		case CMD_RADIOBUTTON1:
//
//
//			SendMessageW(hwndRADIO1, BM_SETCHECK, BST_CHECKED, 0);
//			SendMessageW(hwndRADIO2, BM_SETCHECK, BST_UNCHECKED, 0);
//			SendMessageW(hwndRADIO3, BM_SETCHECK, BST_UNCHECKED, 0);
//			SendMessageW(hwndRADIO4, BM_SETCHECK, BST_UNCHECKED, 0);
//
//
//			break;
//
//		case CMD_RADIOBUTTON2:
//
//			SendMessageW(hwndRADIO1, BM_SETCHECK, BST_UNCHECKED, 0);
//			SendMessageW(hwndRADIO2, BM_SETCHECK, BST_CHECKED, 0);
//			SendMessageW(hwndRADIO3, BM_SETCHECK, BST_UNCHECKED, 0);
//			SendMessageW(hwndRADIO4, BM_SETCHECK, BST_UNCHECKED, 0);
//
//			break;
//		case CMD_RADIOBUTTON3:
//			SendMessageW(hwndRADIO1, BM_SETCHECK, BST_UNCHECKED, 0);
//			SendMessageW(hwndRADIO2, BM_SETCHECK, BST_UNCHECKED, 0);
//			SendMessageW(hwndRADIO3, BM_SETCHECK, BST_CHECKED, 0);
//			SendMessageW(hwndRADIO4, BM_SETCHECK, BST_UNCHECKED, 0);
//			break;
//		case CMD_RADIOBUTTON4:
//			SendMessageW(hwndRADIO1, BM_SETCHECK, BST_UNCHECKED, 0);
//			SendMessageW(hwndRADIO2, BM_SETCHECK, BST_UNCHECKED, 0);
//			SendMessageW(hwndRADIO3, BM_SETCHECK, BST_UNCHECKED, 0);
//			SendMessageW(hwndRADIO4, BM_SETCHECK, BST_CHECKED, 0);
//			break;
//		}
//		break;
//	}
//	case WM_DESTROY:
//		//PostQuitMessage(0);
//		break;
//
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}
//
//void createControls(HWND hWnd) {
//
//
//	CreateWindowW(L"Button", L"Buttons", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 380, 220, hWnd, NULL, hInst, 0);
//	CreateWindowW(L"Button", L"Push", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 25, 35, 75, 23, hWnd, NULL, hInst, 0);
//	CreateWindowW(L"Button", L"Def", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP, 25, 65, 75, 23, hWnd, NULL, hInst, 0);
//	CreateWindowW(L"Button", L"PushLike", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE, 25, 95, 75, 23, hWnd, NULL, hInst, 0);
//	hwndCHECKBOX = CreateWindowW(L"Button", L"unchecked", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 25, 125, 75, 23, hWnd, (HMENU)CMD_CHECKBOX, hInst, 0);
//	hwndPUSHLIKE = CreateWindowW(L"Button", L"unchecked", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_PUSHLIKE, 25, 155, 75, 23, hWnd, (HMENU)CMD_PUSHLIKE, hInst, 0);
//	CreateWindowW(L"Button", L"Right", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_RIGHTBUTTON, 25, 185, 75, 23, hWnd, NULL, hInst, 0);
//
//	hwndRADIO1 = CreateWindowW(L"Button", L"Radio1", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 130, 35, 75, 23, hWnd, (HMENU)CMD_RADIOBUTTON1, hInst, 0);
//	hwndRADIO2 = CreateWindowW(L"Button", L"Radio2", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 130, 65, 75, 23, hWnd, (HMENU)CMD_RADIOBUTTON2, hInst, 0);
//	hwndRADIO3 = CreateWindowW(L"Button", L"Radio3", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 130, 95, 75, 23, hWnd, (HMENU)CMD_RADIOBUTTON3, hInst, 0);
//	hwndRADIO4 = CreateWindowW(L"Button", L"Radio4", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 130, 125, 75, 23, hWnd, (HMENU)CMD_RADIOBUTTON4, hInst, 0);
//
//	hwndCOMBOBOX = CreateWindowW(L"Combobox", L"Combox", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST , 130, 155, 75, 75, hWnd, (HMENU)CMD_COMBOBOX, hInst, 0);
//	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"a");
//	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"b");
//	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"c");
//
//	hwndLISTBOX = CreateWindowW(L"Listbox", L"Combox", WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | WS_HSCROLL | WS_VSCROLL, 230, 35, 75, 75, hWnd, (HMENU)CMD_COMBOBOX, hInst, 0);
//	SendMessageW(hwndLISTBOX, LB_ADDSTRING, 0, (LPARAM)L"a");
//	SendMessageW(hwndLISTBOX, LB_ADDSTRING, 0, (LPARAM)L"b");
//	SendMessageW(hwndLISTBOX, LB_ADDSTRING, 0, (LPARAM)L"c");
//
//	CreateWindowW(L"Edit", L"Combox", WS_CHILD | WS_VISIBLE , 130, 185, 75, 23, hWnd, (HMENU)CMD_COMBOBOX, hInst, 0);
//
//
//
//	CreateWindowW(L"Button", L"Pizza", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 500, 10, 380, 220, hWnd, NULL, hInst, 0);
//
//	//CreateWindowW(L"Static", L"Choose pizza", WS_VISIBLE | WS_CHILD | BS_PUSHLIKE, , (480 / 2) - 23 / 2, 75, 23, hWnd, (HMENU)CMD_BUTTON_PLUS, hInst, NULL);
//
//
//
//
//}
//


