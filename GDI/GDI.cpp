// GDI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "GDI.h"

#define MAX_LOADSTRING 100
#define CMD_BUTTON_ELLIPS 1001
#define CMD_BUTTON_PEN 1002
#define CMD_BUTTON_RECTANGLE 1003
#define CMD_BUTTON_POLYGON 1004
#define CMD_BUTTON_ROUNDRECT 1005

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


HDC dc;
HDC memoryDC; //DC for memory copy of picture
HBITMAP memoryPicture;


HWND sPenHeight;
HWND sPenWidth;
HWND sEllipse;
HWND sPen;
HWND sRectangle;
HWND sPolygon;
HWND sRoundRect;


HPEN pen;
HPEN bPen;

HBRUSH brush;

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
int vertex;
POINT *polygon;
COORD prevCord;
int penWidth;
int penHeight;
int r; //for pen
int g;
int b;
int rb; //b for brush
int gb;
int bb;
int currentPen;

bool widthHeight;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_CREATE: {


		const WCHAR fontName[] = L"Comic Sans";
		const long nFontSize = 10;

		HFONT s_hFont;
		HDC hdc = GetDC(hWnd);
		LOGFONT logFont = { 0 };
		logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		logFont.lfWeight = FW_BOLD;
		wcscpy_s(logFont.lfFaceName, fontName);
		s_hFont = CreateFontIndirect(&logFont);


		srand(time(0));
		widthHeight = true;
		LButtonPressed = false;
		RButtonPressed = false;
		currentPen = CMD_BUTTON_PEN;


		sPenWidth = CreateWindowW(L"Static", L"10", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 20, 20, 20, hWnd, NULL, hInst, NULL);
		sPenHeight = CreateWindowW(L"Static", L"10", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 20, 20, hWnd, NULL, hInst, NULL);

		sPen = CreateWindowW(L"Button", L"✒", WS_VISIBLE | WS_CHILD | SS_CENTER, 20, 0, 20, 20, hWnd, (HMENU)CMD_BUTTON_PEN, hInst, NULL);
		sEllipse = CreateWindowW(L"Button", L"⬯", WS_VISIBLE | WS_CHILD | SS_CENTER, 40, 0, 20, 20, hWnd, (HMENU)CMD_BUTTON_ELLIPS, hInst, NULL);
		sRectangle = CreateWindowW(L"Button", L"▭", WS_VISIBLE | WS_CHILD | SS_CENTER, 60, 0, 20, 20, hWnd, (HMENU)CMD_BUTTON_RECTANGLE, hInst, NULL);
		sRoundRect = CreateWindowW(L"Button", L"▢", WS_VISIBLE | WS_CHILD | SS_CENTER, 80, 0, 20, 20, hWnd, (HMENU)CMD_BUTTON_ROUNDRECT, hInst, NULL);
		sPolygon = CreateWindowW(L"Button", L"⎔", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 0, 20, 20, hWnd, (HMENU)CMD_BUTTON_POLYGON, hInst, NULL);


		SendMessage(sPenWidth, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(sPenHeight, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(sPen, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(sEllipse, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(sRectangle, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));


		dc = GetDC(hWnd);
		memoryDC = CreateCompatibleDC(dc);
		RECT rect;
		GetClientRect(hWnd,&rect);

		memoryPicture = CreateCompatibleBitmap(memoryDC, rect.right - rect.left, rect.bottom - rect.top);


		vertex = 3;
		polygon = new POINT[vertex];

		penHeight = 10;
		penWidth = 10;
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
		rb = rand() % 255;
		gb = rand() % 255;
		bb = rand() % 255;

		pen = CreatePen(PS_SOLID, penHeight, RGB(r, g, b));
		bPen = CreatePen(PS_SOLID, 1, RGB(r, g, b));


		brush = CreateSolidBrush(RGB(rb, gb, bb));

	}
				  break;


	case WM_RBUTTONDOWN: {

		widthHeight ? widthHeight = false : widthHeight = true;
		break;

	}
	case WM_LBUTTONDOWN: {
		LButtonPressed = true;
		prevCord.Y = GET_Y_LPARAM(lParam);
		prevCord.X = GET_X_LPARAM(lParam);
		SetCapture(hWnd);

		break;
	}
	case WM_LBUTTONUP: {
		LButtonPressed = false;
		ReleaseCapture();
		break;
	}
	case WM_MBUTTONDOWN: {

		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
		rb = rand() % 255;
		gb = rand() % 255;
		bb = rand() % 255;

		DeleteObject(pen);
		DeleteObject(bPen);
		DeleteObject(brush);

		pen = CreatePen(PS_SOLID, penHeight, RGB(r, g, b));
		bPen = CreatePen(PS_SOLID, 1, RGB(r, g, b));

		brush = CreateSolidBrush(RGB(rb, gb, bb));


	}
	case WM_MOUSEMOVE:
	{

		if (LButtonPressed) {

			if (currentPen == CMD_BUTTON_PEN) {

				HPEN savedPen = (HPEN)SelectObject(dc, pen);
				MoveToEx(dc, prevCord.X, prevCord.Y, NULL);
				LineTo(dc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				prevCord.Y = GET_Y_LPARAM(lParam);
				prevCord.X = GET_X_LPARAM(lParam);
				SelectObject(dc, savedPen);
			}
			else if (currentPen == CMD_BUTTON_ELLIPS) {


				SelectObject(dc, brush);
				SelectObject(dc, bPen);

				Ellipse(dc, GET_X_LPARAM(lParam) - (penWidth / 2), GET_Y_LPARAM(lParam) - (penHeight / 2), GET_X_LPARAM(lParam) + (penWidth / 2), GET_Y_LPARAM(lParam) + (penHeight / 2));

			}
			else if (currentPen == CMD_BUTTON_RECTANGLE) {

				SelectObject(dc, brush);
				SelectObject(dc, bPen);
				Rectangle(dc, GET_X_LPARAM(lParam) - (penWidth / 2), GET_Y_LPARAM(lParam) - (penHeight / 2), GET_X_LPARAM(lParam) + (penWidth / 2), GET_Y_LPARAM(lParam) + (penHeight / 2));

			}
			else if (currentPen == CMD_BUTTON_ROUNDRECT)
			{


				SelectObject(dc, brush);
				SelectObject(dc, bPen);
				RoundRect(dc, GET_X_LPARAM(lParam) - (penWidth / 2), GET_Y_LPARAM(lParam) - (penHeight / 2), GET_X_LPARAM(lParam) + (penWidth / 2), GET_Y_LPARAM(lParam) + (penHeight / 2),penWidth/2,penHeight/2);
			}
			else if (currentPen == CMD_BUTTON_POLYGON) {

				SelectObject(dc, brush);
				SelectObject(dc, bPen);

				//POINT vert[3] = { penWidth + GET_X_LPARAM(lParam),penHeight + GET_Y_LPARAM(lParam),penWidth -GET_X_LPARAM(lParam),penHeight - GET_Y_LPARAM(lParam),penWidth + GET_X_LPARAM(lParam),penHeight - GET_Y_LPARAM(lParam) };
				//Polygon(dc,vert,3);
				for(int i=0;i<100000;i++)
				SetPixel(dc, rand()%1920, rand()%1080, RGB(rand()%255, rand() % 255, rand() % 255));

			}

		}

		break;
	}
	case WM_MOUSEWHEEL:

		char buff[100];
		if (widthHeight) {

			if (((int)wParam) > 0) {

				penHeight++;
				DeleteObject(pen);
				pen = CreatePen(PS_SOLID, penHeight, RGB(r, g, b));
				_itoa_s(penHeight, buff, 10);
				SendMessageA(sPenHeight, WM_SETTEXT, 0, (LPARAM)buff);
			}
			else if (penHeight > 0) {

				penHeight--;
				DeleteObject(pen);
				pen = CreatePen(PS_SOLID, penHeight, RGB(r, g, b));

				_itoa_s(penHeight, buff, 10);
				SendMessageA(sPenHeight, WM_SETTEXT, 0, (LPARAM)buff);
			}
		}
		else {

			if (((int)wParam) > 0) {

				penWidth++;
				_itoa_s(penWidth, buff, 10);
				SendMessageA(sPenWidth, WM_SETTEXT, 0, (LPARAM)buff);
			}
			else if (penWidth > 0) {

				penWidth--;
				_itoa_s(penWidth, buff, 10);
				SendMessageA(sPenWidth, WM_SETTEXT, 0, (LPARAM)buff);
			}

		}

		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case CMD_BUTTON_PEN:

			currentPen = CMD_BUTTON_PEN;
			break;
		case CMD_BUTTON_ELLIPS:

			currentPen = CMD_BUTTON_ELLIPS;
			break;
		case CMD_BUTTON_RECTANGLE:

			currentPen = CMD_BUTTON_RECTANGLE;
			break;
		case CMD_BUTTON_ROUNDRECT:

			currentPen = CMD_BUTTON_ROUNDRECT;
			break;
		case CMD_BUTTON_POLYGON:

			currentPen = CMD_BUTTON_POLYGON;
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

		ReleaseDC(hWnd, dc);
		DeleteObject(pen);

		DeleteObject(bPen);
		DeleteObject(brush);
		
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
