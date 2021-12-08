// System Metrics.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "System Metrics.h"

#define MAX_LOADSTRING 100
#define CMD_LISTBOX 1000


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

DWORD CALLBACK CreateControls(LPVOID);
DWORD CALLBACK ChangeMetricsInfo(LPVOID);
HWND Listbox;
HWND indexConst;
HWND mDesc;


struct Metrics {

	int nIndex;
	WCHAR indexConst[32];
	WCHAR description[1024];

};


Metrics metrics[] = {

	{56,L"SM_ARRANGE",L"The flags that specify how the system arranged minimized windows"},
	{67,L"SM_CLEANBOOT",L"The value that specifies how the system is started"},
	{80,L"SM_CMONITORS",L"The number of display monitors on a desktop."}

};

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


		if (notificationCode = CBN_SELCHANGE) {

			CreateThread(NULL, 0, ChangeMetricsInfo, NULL, 0, NULL);
			break;
		}

		// Parse the menu selections:
		switch (wmId)
		{
		case CMD_LISTBOX: {

			break;
		}
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
DWORD CALLBACK CreateControls(LPVOID params) {

	HWND hWnd = *((HWND*)params);

	char buff[100];

	Listbox = CreateWindowEx(0, L"Combobox", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_DROPDOWNLIST, 10, 10, 150, 300, hWnd, (HMENU)CMD_LISTBOX, hInst, NULL);
	mDesc = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 40, 150, 200, hWnd, (HMENU)NULL, hInst, NULL);
	indexConst = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 10, 150, 30, hWnd, (HMENU)NULL, hInst, NULL);

	for (int i = 0; i < 3; i++) {

		SendMessageW(Listbox, CB_ADDSTRING, 0, (LPARAM)metrics[i].indexConst);
	}

	return 0;
}


DWORD CALLBACK ChangeMetricsInfo(LPVOID params) {


	int selectedIndex = SendMessageA(Listbox, CB_GETCURSEL, 0, 0);
	SendMessageW(mDesc, WM_SETTEXT, 0, (LPARAM)metrics[selectedIndex].description);

	char buff[100];
	_itoa_s(GetSystemMetrics(metrics[selectedIndex].nIndex),buff,10);

	SendMessageA(indexConst, WM_SETTEXT, 0, (LPARAM)buff);

	return 0;
}
