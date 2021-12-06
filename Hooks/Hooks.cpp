// Hooks.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Hooks.h"

#define MAX_LOADSTRING 100
#define CMD_KB_HOOK_START 1001
#define CMD_KB_HOOK_STOP 1002
#define CMD_KB_LL_START 1003
#define CMD_KB_LL_STOP 1004


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND listbox;
HHOOK kbHOOK;
HHOOK kbLL;

wchar_t str[MAX_LOADSTRING];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

DWORD   CALLBACK    StartKbHook(LPVOID);
DWORD   CALLBACK    StopKbHook(LPVOID);
LRESULT CALLBACK    KbHookProc(int, WPARAM, LPARAM);


DWORD   CALLBACK    StartKbHookLL(LPVOID);
DWORD   CALLBACK    StopKbHookLL(LPVOID);
LRESULT CALLBACK    KbHookProcLL(int, WPARAM, LPARAM);




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
	LoadStringW(hInstance, IDC_HOOKS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOOKS));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOOKS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_HOOKS);
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

		listbox = CreateWindowW(L"Listbox", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, 100, 10, 500, 500, hWnd, NULL, hInst, NULL);
		CreateWindowW(L"Button", L"Start", WS_VISIBLE | WS_CHILD, 10, 10, 75, 23, hWnd, (HMENU)CMD_KB_HOOK_START, hInst, NULL);
		CreateWindowW(L"Button", L"Stop", WS_VISIBLE | WS_CHILD, 10, 40, 75, 23, hWnd, (HMENU)CMD_KB_HOOK_STOP, hInst, NULL);

		CreateWindowW(L"Button", L"Start LL", WS_VISIBLE | WS_CHILD, 10, 70, 75, 23, hWnd, (HMENU)CMD_KB_LL_START, hInst, NULL);
		CreateWindowW(L"Button", L"Stop LL", WS_VISIBLE | WS_CHILD, 10, 100, 75, 23, hWnd, (HMENU)CMD_KB_LL_STOP, hInst, NULL);

		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case CMD_KB_HOOK_START:
			StartKbHook(NULL);
			break;

		case CMD_KB_HOOK_STOP:
			StopKbHook(NULL);

			break;

		case CMD_KB_LL_START:
			StartKbHookLL(NULL);
			break;
		case CMD_KB_LL_STOP:
			StopKbHookLL(NULL);
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




DWORD   CALLBACK    StartKbHook(LPVOID params) {


	kbHOOK = SetWindowsHookExW(WH_KEYBOARD, KbHookProc, (HINSTANCE)NULL, GetCurrentThreadId());

	if (kbHOOK) {

		_snwprintf_s(str, MAX_LOADSTRING, L"hook started");

	}
	else {

		_snwprintf_s(str, MAX_LOADSTRING, L"hook start failed");


	}
	SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);


	return 0;
}

DWORD   CALLBACK    StopKbHook(LPVOID params) {


	if (kbHOOK) {

		UnhookWindowsHookEx(kbHOOK);
		_snwprintf_s(str, MAX_LOADSTRING, L"hook stopped");
		kbHOOK = NULL;
	}
	else {

		_snwprintf_s(str, MAX_LOADSTRING, L"hook stop failed");

	}

	SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);



	return 0;
}

LRESULT CALLBACK    KbHookProc(int nCode, WPARAM wParam, LPARAM lParam) {

	_snwprintf_s(str, MAX_LOADSTRING, L"%d %d", wParam, lParam);

	SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);


	return CallNextHookEx(kbHOOK, nCode, wParam, lParam);

}



DWORD   CALLBACK    StartKbHookLL(LPVOID params) {

	kbLL = SetWindowsHookExW(WH_KEYBOARD_LL, KbHookProcLL, GetModuleHandle(NULL), 0);

	if (kbLL) {

		_snwprintf_s(str, MAX_LOADSTRING, L"LL hook started");

	}
	else {

		_snwprintf_s(str, MAX_LOADSTRING, L"LL hook start failed");


	}
	SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);

	return 0;
}

DWORD   CALLBACK    StopKbHookLL(LPVOID params) {

	if (kbLL) {

		UnhookWindowsHookEx(kbLL);
		_snwprintf_s(str, MAX_LOADSTRING, L"LL hook stopped");
		kbLL = NULL;
	}
	else {

		_snwprintf_s(str, MAX_LOADSTRING, L"LL hook stop failed");

	}

	SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);



	return 0;
}

LRESULT CALLBACK    KbHookProcLL(int nCode, WPARAM wParam, LPARAM lParam) {

	if (nCode == HC_ACTION) {

		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {

			KBDLLHOOKSTRUCT keyInfo = *((KBDLLHOOKSTRUCT*)lParam);

			_snwprintf_s(str, MAX_LOADSTRING, L"%d %d", keyInfo.vkCode, keyInfo.scanCode);
			SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);

		}

	}

	//_snwprintf_s(str, MAX_LOADSTRING, L"%d %d", wParam, lParam);
	//SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);


	return CallNextHookEx(kbLL, nCode, wParam, lParam);
}









