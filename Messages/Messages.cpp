// Messages.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Messages.h"

#define MAX_LOADSTRING 100
#define CMD_TIMER_MOVEWINDOW 2000
#define CMD_TIMER_ANTICLICK 2001

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hStatic1;
HWND hStatic2;
HWND hStatic3;
HWND hProgres;

HWND listbox;
WCHAR str[100];


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
	LoadStringW(hInstance, IDC_MESSAGES, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MESSAGES));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MESSAGES));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MESSAGES);
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
		CW_USEDEFAULT, 0, 800, 800, nullptr, nullptr, hInstance, nullptr);

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
int count = 0;
int x = 0;
int y = 0;
bool xFlag = false;
bool yFlag = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:

		hStatic1 = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 10, 100, 15, hWnd, 0, hInst, NULL);
		hStatic2 = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER, 120, 10, 100, 15, hWnd, 0, hInst, NULL);
		hStatic3 = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER, 230, 10, 100, 15, hWnd, 0, hInst, NULL);
		listbox = CreateWindowW(L"Listbox", L"", WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 30, 400, 300, hWnd, 0, hInst, NULL);
		hProgres = CreateWindowW(PROGRESS_CLASSW, L"", WS_CHILD | WS_VISIBLE | PBS_MARQUEE | PBS_SMOOTH, 10, 350, 100, 15, hWnd, 0, hInst, NULL);
		SetTimer(hWnd, CMD_TIMER_ANTICLICK, 1000, NULL);
		SetTimer(hWnd, CMD_TIMER_MOVEWINDOW, 10, NULL);
		//SendMessageW(hProgres,PBM_SETSTEP,10,0);

		break;

	case WM_TIMER:
		if (wParam == CMD_TIMER_ANTICLICK) {


			SendMessageW(hProgres, PBM_DELTAPOS, -4, 0);


		}
		if (wParam == CMD_TIMER_MOVEWINDOW) {


			MoveWindow(hWnd, x, y, 800, 800, 1);

			if (xFlag) {
				x -= 6;

			}
			else {
				x += 6;
			}
			if (yFlag) {
				y -= 6;

			}
			else {
				y += 6;
			}

			if (x > 1920 - 800) {
				xFlag = true;

			}

			if (x < 0) {
				xFlag = false;

			}

			if (y > 1080 - 800) {
				yFlag = true;

			}

			if (y < 0) {
				yFlag = false;

			}

		}

		break;
	case WM_KEYDOWN:
	{

		_snwprintf_s(str, 100, L"%d %u", wParam, (lParam >> 16) & 0xff);
		//(lParam >> 16) & 0x11111111;
		SendMessageW(hStatic1, WM_SETTEXT, 100, (LPARAM)str);
		SendMessageW(listbox, LB_ADDSTRING, 100, (LPARAM)str);
	}

	break;
	case WM_MBUTTONDOWN:

		KillTimer(hWnd,CMD_TIMER_ANTICLICK);
		break;
	case WM_MOUSEMOVE:

		_snwprintf_s(str, 100, L"%d %d", GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		SendMessageW(hStatic2, WM_SETTEXT, 100, (LPARAM)str);
		SendMessageW(listbox, LB_ADDSTRING, 100, (LPARAM)str);


		break;
	case WM_LBUTTONDOWN:

		_snwprintf_s(str, 100, L"%d", count);
		SendMessageW(hStatic3, WM_SETTEXT, 100, (LPARAM)str);

		count++;


		break;
	case WM_RBUTTONUP:
		SendMessageW(hProgres, PBM_DELTAPOS, 4, 0);
		SendMessageW(hProgres, PBM_SETBARCOLOR, 0, RGB(rand() % 255, rand() % 255, rand() % 255));

		break;
	case WM_LBUTTONUP:

		SendMessageW(hProgres, PBM_DELTAPOS, -4, 0);
		SendMessageW(hProgres, PBM_SETBARCOLOR, 0, RGB(rand() % 255, rand() % 255, rand() % 255));



		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
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
