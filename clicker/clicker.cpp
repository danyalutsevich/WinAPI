// Practice.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "clicker.h"

#define MAX_LOADSTRING 100
#define CMD_BUTTON_CLICKER 1000
#define CMD_CPS 1001
#define CMD_REDUCE_PROGRESS 1002
#define CMD_TIMER 1003
#define CMD_BUTTON_EASY 1004
#define CMD_BUTTON_HARD 1005
#define CMD_HARD 1006
#define CMD_EASY 1007



// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND clicker;
HWND scoreS;
HWND CPS;
HWND CPSmaxS;
HWND Level1;
HWND Level2;
HWND hProgres;
HWND hEdit;
HWND hTimer;
COLORREF color;


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
	srand(time(0));
	color = RGB(rand() % 255, rand() % 255, rand() % 255);
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CLICKER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLICKER));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_CLICKER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(color);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLICKER);
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
		CW_USEDEFAULT, 0, 1080 / 2, 1920 / 2, nullptr, nullptr, hInstance, nullptr);

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
//F
//

int score = 0;
int clicksPerSec = 0;
int CPSmax = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_CREATE: {


		const WCHAR fontName[] = L"Cascadia Mono";
		const long nFontSize = 50;

		HFONT s_hFont;
		HDC hdc = GetDC(hWnd);
		LOGFONT logFont = { 0 };
		logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		logFont.lfWeight = FW_BOLD;
		wcscpy_s(logFont.lfFaceName, fontName);
		s_hFont = CreateFontIndirect(&logFont);


		const long nFontSize2 = 12;

		HFONT s_hFont2;
		HDC hdc2 = GetDC(hWnd);
		LOGFONT logFont2 = { 0 };
		logFont2.lfHeight = -MulDiv(nFontSize2, GetDeviceCaps(hdc2, LOGPIXELSY), 72);
		logFont2.lfWeight = FW_BOLD;
		wcscpy_s(logFont2.lfFaceName, fontName);
		s_hFont2 = CreateFontIndirect(&logFont2);


		clicker = CreateWindowW(L"Button", L"", WS_CHILD | WS_VISIBLE, 10, 300, 505, 505, hWnd, (HMENU)CMD_BUTTON_CLICKER, hInst, NULL);
		scoreS = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER, 0, 0, 525, 100, hWnd, NULL, hInst, NULL);
		CPS = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER, 520 / 2 - 50, 130, 100, 25, hWnd, NULL, hInst, NULL);
		CPSmaxS = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER, 520 / 2 - 50, 154, 100, 25, hWnd, NULL, hInst, NULL);
		hTimer = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER, 520 / 2 - 50, 178, 100, 25, hWnd, NULL, hInst, NULL);
		hEdit = CreateWindowW(L"Edit", L"Set time", WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER, 520 / 2 - 50, 202, 100, 25, hWnd, NULL, hInst, NULL);
		Level1 = CreateWindowW(L"Button", L"Easy", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 520 / 2 - 50, 226, 100, 25, hWnd, (HMENU)CMD_BUTTON_EASY, hInst, NULL);
		Level2 = CreateWindowW(L"Button", L"Hard", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 520 / 2 - 50, 250, 100, 25, hWnd, (HMENU)CMD_BUTTON_HARD, hInst, NULL);
		hProgres = CreateWindowW(PROGRESS_CLASSW, L"", WS_CHILD | WS_VISIBLE | PBS_MARQUEE | PBS_SMOOTH, 0, 100, 524, 15, hWnd, 0, hInst, NULL);

		SendMessageW(hProgres, PBM_SETRANGE, -5, MAKELPARAM(0, 100));
		SendMessageW(hProgres, PBM_SETBARCOLOR, 0, color);
		SendMessageW(Level1, BM_SETCHECK, BST_CHECKED, 0);

		SetTimer(hWnd, CMD_CPS, 1000, NULL);
		SetTimer(hWnd, CMD_REDUCE_PROGRESS, 1000, NULL);
		SetTimer(hWnd, CMD_TIMER, 1, NULL);

		SendMessage(scoreS, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(CPS, WM_SETFONT, (WPARAM)s_hFont2, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(CPSmaxS, WM_SETFONT, (WPARAM)s_hFont2, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(hTimer, WM_SETFONT, (WPARAM)s_hFont2, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(Level1, WM_SETFONT, (WPARAM)s_hFont2, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(Level2, WM_SETFONT, (WPARAM)s_hFont2, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(hEdit, WM_SETFONT, (WPARAM)s_hFont2, (LPARAM)MAKELONG(TRUE, 0));




		break;
	}

	case WM_TIMER:
		if (wParam == CMD_CPS) {


			char buff[100];
			_itoa_s(clicksPerSec, buff, 10);
			SendMessageA(CPS, WM_SETTEXT, 0, (LPARAM)buff);
			clicksPerSec = 0;

		}
		if (wParam == CMD_REDUCE_PROGRESS) {

			SendMessageW(hProgres, PBM_DELTAPOS, -5, 0);

		}
		if (wParam == CMD_TIMER) {

			char buff[100];

			_snprintf_s(buff, 100, 100, "%d:%d:%d:%d", (clock() / 3600000) % 24, (clock() / 60000) % 60, (clock() / 1000) % 60, clock() % 1000);
			SendMessageA(hTimer, WM_SETTEXT, 0, (LPARAM)buff);

			if (SendMessageW(Level1, BM_GETCHECK, 0, 0)) {

				if (SendMessageW(hProgres, PBM_GETPOS, 0, 0) == 100) {
					int res;
					res = MessageBoxA(hWnd, "Want to play again?", "You won", MB_YESNO);

					if (res == IDYES) {

						CPSmax = 0;
						score = 0;
						SendMessageW(hProgres, PBM_SETPOS, 0, 0);

					}

				}
			}
			

		}
		/*if (wParam == CMD_HARD) {

			char buff[100];
			SendMessageA(hEdit, WM_GETTEXT, 0, (LPARAM)buff);

			
			if (atoi(buff)) {


				MessageBoxA(hWnd, "L", "You lose", MB_ICONSTOP | MB_OK);

				CPSmax = 0;
				score = 0;
				SendMessageW(hProgres, PBM_SETPOS, 0, 0);

			}
			else {
				
				MessageBoxA(hWnd, "Set time", "Please", MB_ICONSTOP | MB_OK);

			}


			

		}*/
		/*if (wParam == CMD_EASY) {

			if (SendMessageW(hProgres, PBM_GETPOS, 0, 0) == 100) {
				int res;
				res = MessageBoxA(hWnd, "Want to play again?", "You won", MB_YESNO);

				if (res == IDYES) {

					CPSmax = 0;
					score = 0;
					SendMessageW(hProgres, PBM_SETPOS, 0, 0);

				}

			}

		}*/
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case CMD_BUTTON_CLICKER: {


			score += SendMessageW(hProgres, PBM_DELTAPOS, 1, 0) + 1;
			char buff[100];
			_itoa_s(score, buff, 10);
			SendMessageA(scoreS, WM_SETTEXT, 0, (LPARAM)buff);

			clicksPerSec++;
			if (clicksPerSec > CPSmax) {
				CPSmax = clicksPerSec;

				_snprintf_s(buff, 100, 100, "max: %d", CPSmax);
				SendMessageA(CPSmaxS, WM_SETTEXT, 0, (LPARAM)buff);
			}
			
			

		}

							   break;

	/*	case CMD_BUTTON_EASY:

			SendMessageW(Level1, BM_SETCHECK, BST_CHECKED, 0);
			SendMessageW(Level2, BM_SETCHECK, BST_UNCHECKED, 0);
			break;*/

	/*	case CMD_BUTTON_HARD:

			char buff[100];
			SendMessageA(hEdit, WM_GETTEXT, 0, (LPARAM)buff);

			SetTimer(hWnd,CMD_HARD,atoi(buff),NULL);
			SendMessageW(Level1, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(Level2, BM_SETCHECK, BST_CHECKED, 0);


			break;*/
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
