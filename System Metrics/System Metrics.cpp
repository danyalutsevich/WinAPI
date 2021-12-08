// System Metrics.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "System Metrics.h"

#define MAX_LOADSTRING 100
#define CMD_LISTBOX 1000
#define CMD_BUTTON_SHOWWINDOW 1001

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD CALLBACK CreateControls(LPVOID);
DWORD CALLBACK ChangeMetricsInfo(LPVOID);

LRESULT CALLBACK    WndProcCentered(HWND, UINT, WPARAM, LPARAM);
void showWindowCentered(HINSTANCE, HWND );
HWND Listbox;
HWND indexConst;
HWND mDesc;

bool isCenteredReg=false;
COORD screenSize;

ATOM centeredWinAtom=0;

struct Metrics {

	int nIndex;
	WCHAR indexConst[32];
	WCHAR description[1024];

};


Metrics metrics[] = {

	{67,L"SM_CLEANBOOT",L"The value that specifies how the system is started"},
	{56,L"SM_ARRANGE",L"The flags that specify how the system arranged minimized windows"},
	{31, L"SM_CYSIZE ", L"The thickness of the sizing border around the perimeter of a window that can be resized, in pixels."},
	{30, L"SM_CXSIZE", L"The width of a button in a window caption or title bar, in pixels."},
	{29, L"SM_CYMIN", L"The minimum height of a window, in pixels."},
	{28, L"SM_CXMIN", L"The minimum width of a window, in pixels."},
	{20, L"SM_CYVSCROLL", L"The height of the arrow bitmap on a vertical scroll bar, in pixels."},
	{17, L"SM_CYFULLSCREEN", L"The height of the client area for a full-screen window on the primary display monitor, in pixels."},
	{16, L"SM_CXFULLSCREEN", L"The width of the client area for a full-screen window on the primary display monitor, in pixels"},
	{6, L"SM_CYBORDER", L"The height of a 3-D border, in pixels. This is the 3-D counterpart of SM_CYBORDER."},
	{5, L"SM_CXBORDER", L"The width of a window border, in pixels. This is equivalent to the SM_CXEDGE value for windows with the 3-D look."},
	{2, L"SM_CXVSCROLL", L"The width of a vertical scroll bar, in pixels."},
	{1, L"SM_CYSCREEN", L"The height of the screen of the primary display monitor, in pixels. "},
	{0, L"SM_CXSCREEN", L"The width of the screen of the primary display monitor, in pixels"},

};


void showWindowCentered(HINSTANCE hInstance, HWND hWnd) {


	hInst = hInstance;

	if (!isCenteredReg) {

		WNDCLASSEXW wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.lpfnWndProc = WndProcCentered;
		wcex.hInstance = hInst;
		wcex.hbrBackground = CreateSolidBrush(COLOR_WINDOW + 1);
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.lpszClassName = L"CenteredWindow";

		if (!RegisterClassExW(&wcex)) {
			MessageBoxW(hWnd, L"Register class error!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		isCenteredReg = TRUE;
	}
	screenSize.Y=GetSystemMetrics(SM_CYSCREEN);
	screenSize.X=GetSystemMetrics(SM_CXSCREEN);
	HWND centeredWindow = CreateWindowW(L"CenteredWindow", L"Centered", WS_OVERLAPPEDWINDOW, screenSize.X/2- (screenSize.X/8), screenSize.Y/2- (screenSize.Y / 8), screenSize.X / 4, screenSize.Y / 4, hWnd, NULL, hInst, 0);

	ShowWindow(centeredWindow, SW_NORMAL);
	UpdateWindow(centeredWindow);
}

LRESULT CALLBACK    WndProcCentered(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message)
	{
	

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		switch (wmId)
		{




		}
	}
	case WM_DESTROY:
		//PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




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
	LoadStringW(hInstance, IDC_SYSTEMMETRICS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SYSTEMMETRICS));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SYSTEMMETRICS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SYSTEMMETRICS);
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
	case WM_CREATE: {

		CreateControls(&hWnd);

		break;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		int notificationCode = HIWORD(wParam);


		if (notificationCode == CBN_SELCHANGE) {

			CreateThread(NULL, 0, ChangeMetricsInfo, NULL, 0, NULL);
			break;
		}

		// Parse the menu selections:
		switch (wmId)
		{
		case CMD_BUTTON_SHOWWINDOW: {
			showWindowCentered(hInst,hWnd);

			break;
		}
		
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

DWORD CALLBACK CreateControls(LPVOID params) {

	HWND hWnd = *((HWND*)params);

	char buff[100];
	
	Listbox = CreateWindowEx(0, L"Combobox", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_DROPDOWNLIST, 10, 10, 150, 300, hWnd, (HMENU)CMD_LISTBOX, hInst, NULL);
	mDesc = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 40, 150, 200, hWnd, (HMENU)NULL, hInst, NULL);
	indexConst = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 10, 150, 30, hWnd, (HMENU)NULL, hInst, NULL);
	
	CreateWindowW(L"Button", L"showWindow", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 150, 75, 23, hWnd, (HMENU)CMD_BUTTON_SHOWWINDOW, hInst, NULL);



	for (int i = 0; i < sizeof(metrics)/sizeof(Metrics); i++) {

		SendMessageW(Listbox, CB_ADDSTRING, 0, (LPARAM)metrics[i].indexConst);
	}

	return 0;
}


DWORD CALLBACK ChangeMetricsInfo(LPVOID params) {


	int selectedIndex = SendMessageA(Listbox, CB_GETCURSEL, 0, 0);
	SendMessageW(mDesc, WM_SETTEXT, 0, (LPARAM)metrics[selectedIndex].description);

	char buff[100];
	_itoa_s(GetSystemMetrics(metrics[selectedIndex].nIndex), buff, 10);

	SendMessageA(indexConst, WM_SETTEXT, 0, (LPARAM)buff);

	return 0;
}
