// GDI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "GDI.h"

#define MAX_LOADSTRING 100
#define CMD_BUTTON_ELLIPS 1001

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HDC dc;
HPEN pen;
HWND penSizeS;
HWND elipsS;

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
	LoadStringW(hInstance, IDC_GDI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GDI));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GDI);
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
bool LButtonPressed;
bool RButtonPressed;
COORD prevCord;
int penSize;
int r;
int g;
int b;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_CREATE: {
		srand(time(0));
		LButtonPressed = false;
		RButtonPressed = false;

		penSizeS = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD, 0, 0, 20, 20, hWnd, NULL, hInst, NULL);
		elipsS = CreateWindowW(L"Button", L"elips", WS_VISIBLE | WS_CHILD, 20, 0, 50, 20, hWnd, (HMENU)CMD_BUTTON_ELLIPS, hInst, NULL);


		penSize = rand() % 100;
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;

		pen = CreatePen(PS_SOLID, penSize, RGB(r, g, b));
		dc = GetDC(hWnd);
		break;
	}
	case WM_RBUTTONDOWN: {


		while (1) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(dc, brush);

			Ellipse(dc, rand() % 1000, rand() % 1000, rand() % 2000, rand() % 1000);
			DeleteObject(brush);
		}
		//Ellipse(dc,100,100,200,200);
		break;

	}
	case WM_LBUTTONDOWN:
	{
		LButtonPressed = true;
		prevCord.Y = GET_Y_LPARAM(lParam);
		prevCord.X = GET_X_LPARAM(lParam);
		SetCapture(hWnd);

		break;
	}
	case WM_LBUTTONUP:
	{
		LButtonPressed = false;
		ReleaseCapture();
		break;
	}
	case WM_MOUSEMOVE:
	{

		if (LButtonPressed) {


			HPEN savedPen = (HPEN)SelectObject(dc, pen);
			MoveToEx(dc, prevCord.X, prevCord.Y, NULL);
			LineTo(dc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

			prevCord.Y = GET_Y_LPARAM(lParam);
			prevCord.X = GET_X_LPARAM(lParam);
			SelectObject(dc, savedPen);

		}

		break;
	}
	case WM_MOUSEWHEEL:

		char buff[100];
		if (((int)wParam) > 0) {

			penSize++;
			pen = CreatePen(PS_SOLID, penSize, RGB(r, g, b));
			_itoa_s(penSize, buff, 10);
			SendMessageA(penSizeS, WM_SETTEXT, 0, (LPARAM)buff);
		}
		else if (penSize > 0) {

			penSize--;
			pen = CreatePen(PS_SOLID, penSize, RGB(r, g, b));

			_itoa_s(penSize, buff, 10);
			SendMessageA(penSizeS, WM_SETTEXT, 0, (LPARAM)buff);
		}

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

		ReleaseDC(hWnd, dc);
		DeleteObject(pen);


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
