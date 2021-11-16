// WindowsBasics.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsBasics.h"
#include <string>

#define MAX_LOADSTRING 100
#define CMD_BUTTON_PRESS_ME 1001
#define CMD_BUTTON_PLUS 1002
#define CMD_BUTTON_MINUS 1003

// Global Variables:
HINSTANCE hInst;                                // current instance
HWND hStatic1;
HWND inc;
HWND dec;
HWND mainWindow;

WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
//WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


void createEX();
//void processEX();
void processEX_PLUS();
void processEX_MINUS();

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
	//LoadStringW(hInstance, IDC_WINDOWSBASICS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	//MessageBoxA(NULL, (char*)((wchar_t*)"Hello World!"), (char*)((wchar_t*)"message"), MB_OK);


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
	static int count = 0;
	std::string charct1er = std::to_string(count);
	mainWindow = hWnd;
	switch (message)
	{
	case WM_CREATE:
		//hStatic1=CreateWindowW(
		//	L"Static",//class name
		//	L"Hello World!", //title
		//	WS_VISIBLE|WS_CHILD,//style
		//	10,10, //x y
		//	200,20,
		//	hWnd,//parent window
		//	0,//menu command - no
		//	hInst,//instanse handle
		//	NULL);//extra params struct
		createEX();

	
		CreateWindowW(L"Button", L"Press me", WS_VISIBLE | WS_CHILD, (640/2)-75/2, (480/2)-23/2, 75, 23, hWnd, (HMENU)CMD_BUTTON_PRESS_ME, hInst, NULL);
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case CMD_BUTTON_PRESS_ME:
		
			/*MessageBeep(MB_OK);
			
			count++;
			SendMessageA(hStatic1,WM_SETTEXT,0,(LPARAM)((wchar_t*)charct1er.c_str()));*/

			//processEX();

			break;
		case CMD_BUTTON_PLUS:

			processEX_PLUS();

			break;
		case CMD_BUTTON_MINUS:

			processEX_MINUS();

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
		L"Hello World!", //title
		WS_VISIBLE | WS_CHILD,//style
		10, 10, //x y
		200, 20,
		mainWindow,//parent window
		0,//menu command - no
		hInst,//instanse handle
		NULL);//extra params struct

	inc= CreateWindowW(L"Button", L"++", WS_VISIBLE | WS_CHILD, (640 / 2) - 75 / 2, (480 / 2) - 100 / 2, 75, 23, mainWindow, (HMENU)CMD_BUTTON_PLUS, hInst, NULL);
	dec= CreateWindowW(L"Button", L"--", WS_VISIBLE | WS_CHILD, (640 / 2) - 75 / 2, (480 / 2) +50, 75, 23, mainWindow, (HMENU)CMD_BUTTON_MINUS, hInst, NULL);
}

void processEX_PLUS() {
	WCHAR  str[MAX_LOADSTRING];
	SendMessageW(hStatic1,WM_GETTEXT,MAX_LOADSTRING,(LPARAM)str);
	int n = _wtoi(str);
	n++;
	_itow_s(n,str,MAX_LOADSTRING,10);

	SendMessageA(hStatic1, WM_SETTEXT, 0, (LPARAM)str);



}

void processEX_MINUS() {
	WCHAR  str[MAX_LOADSTRING];
	SendMessageW(hStatic1, WM_GETTEXT, MAX_LOADSTRING, (LPARAM)str);
	int n = _wtoi(str);
	n--;
	_itow_s(n, str, MAX_LOADSTRING, 10);

	SendMessageA(hStatic1, WM_SETTEXT, 0, (LPARAM)str);



}