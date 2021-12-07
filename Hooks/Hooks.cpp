// Hooks.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Hooks.h"

#define MAX_LOADSTRING 100
#define CMD_KB_HOOK_START 1001
#define CMD_KB_HOOK_STOP 1002
#define CMD_KB_LL_START 1003
#define CMD_KB_LL_STOP 1004

#define CMD_MS_LL_START 1005
#define CMD_MS_LL_STOP 1006

#define MS_OFFSET_X 5
#define MS_OFFSET_Y 5

#define MS_SCALE_X 5
#define MS_SCALE_Y 5




// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND listbox;

HHOOK kbHOOK;
HHOOK kbLL;
HHOOK msLL;

HDC dc;
HDC memoryDC;

HBITMAP memoryPictureTrace;



HDC msDc;
HDC MSmemoryDC; //DC for memory copy of picture

HBITMAP memoryPicture;


HWND msTrace;

HPEN msPen;

FILE* f;


int buffCount = 0;


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

DWORD   CALLBACK    StartMsHookLL(LPVOID);
DWORD   CALLBACK    StopMsHookLL(LPVOID);
LRESULT CALLBACK    MsHookProcLL(int, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	buffCount = 0;
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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
		CW_USEDEFAULT, 0, 1300, 600, nullptr, nullptr, hInstance, nullptr);

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

	case WM_CREATE:{

		msPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

		listbox = CreateWindowW(L"Listbox", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, 100, 10, 500, 500, hWnd, NULL, hInst, NULL);
		CreateWindowW(L"Button", L"Start", WS_VISIBLE | WS_CHILD, 10, 10, 75, 23, hWnd, (HMENU)CMD_KB_HOOK_START, hInst, NULL);
		CreateWindowW(L"Button", L"Stop", WS_VISIBLE | WS_CHILD, 10, 40, 75, 23, hWnd, (HMENU)CMD_KB_HOOK_STOP, hInst, NULL);

		CreateWindowW(L"Button", L"Start KB LL", WS_VISIBLE | WS_CHILD, 10, 70, 75, 23, hWnd, (HMENU)CMD_KB_LL_START, hInst, NULL);
		CreateWindowW(L"Button", L"Stop KB LL", WS_VISIBLE | WS_CHILD, 10, 100, 75, 23, hWnd, (HMENU)CMD_KB_LL_STOP, hInst, NULL);

		CreateWindowW(L"Button", L"Start MS LL", WS_VISIBLE | WS_CHILD, 10, 130, 75, 23, hWnd, (HMENU)CMD_MS_LL_START, hInst, NULL);
		CreateWindowW(L"Button", L"Stop MS LL", WS_VISIBLE | WS_CHILD, 10, 160, 75, 23, hWnd, (HMENU)CMD_MS_LL_STOP, hInst, NULL);



		msTrace = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | SS_ETCHEDFRAME, 800, 250, 192 * 2, 108 * 2, hWnd, NULL, hInst, NULL);


		dc = GetDC(msTrace);
		memoryDC = CreateCompatibleDC(dc);

		RECT traceRect;
		GetClientRect(msTrace, &traceRect);

		memoryPictureTrace= CreateCompatibleBitmap(memoryDC, traceRect.right - traceRect.left, traceRect.bottom - traceRect.top);
		SelectObject(memoryDC, memoryPictureTrace);

		HBRUSH bgTrace = CreateSolidBrush(GetBkColor(dc));
		FillRect(memoryDC, &traceRect, bgTrace);


		msDc = GetDC(hWnd);
		MSmemoryDC = CreateCompatibleDC(msDc);
		RECT rect;
		GetClientRect(hWnd, &rect);
		
		memoryPicture = CreateCompatibleBitmap(MSmemoryDC, rect.right - rect.left, rect.bottom - rect.top);


		SelectObject(MSmemoryDC, memoryPicture);

		HBRUSH bg = CreateSolidBrush(GetBkColor(msDc));
		FillRect(MSmemoryDC, &rect, bg);


		break;

	}
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

		case CMD_MS_LL_START:
			StartMsHookLL(NULL);
			break;
		case CMD_MS_LL_STOP:
			StopMsHookLL(NULL);
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

		RECT r;
		GetClientRect(hWnd, &r);
		BitBlt(
			hdc,                // destination DC
			0, 0,            // start point
			r.right - r.left,  // width
			r.bottom - r.top,  // height
			MSmemoryDC,          // source DC
			0, 0,              // start point (in source)
			SRCCOPY            // copy mode
		);


		PAINTSTRUCT tracePs;
		HDC tracehdc = BeginPaint(msTrace,&tracePs);
		RECT traceR;
		GetClientRect(msTrace, &traceR);

		BitBlt(tracehdc,0, 0, traceR.right - traceR.left, traceR.bottom - traceR.top, memoryDC,0, 0,SRCCOPY );

		EndPaint(msTrace, &tracePs);
		EndPaint(hWnd, &ps);

	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		ReleaseDC(hWnd, dc);
		ReleaseDC(hWnd, msDc);
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


	if (kbLL) {

		_snwprintf_s(str, MAX_LOADSTRING, L"LL hook works");

	}
	else {
		kbLL = SetWindowsHookExW(WH_KEYBOARD_LL, KbHookProcLL, GetModuleHandle(NULL), 0);

		_snwprintf_s(str, MAX_LOADSTRING, L"LL hook started");


	}
	SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);

	return 0;
}

DWORD   CALLBACK    StopKbHookLL(LPVOID params) {
	PROCESS_INFORMATION pInfo;
	STARTUPINFO sInfo;


	ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&sInfo, sizeof(STARTUPINFO));

	if (kbLL) {

		UnhookWindowsHookEx(kbLL);
		kbLL = NULL;
		_snwprintf_s(str, MAX_LOADSTRING, L"LL hook stopped");
		CreateProcessW(L"C:\\Windows\\notepad.exe", (LPWSTR)L"\\W C:\\Users\\luche\\source\\repos\\hooks\\Hooks\\file.txt", NULL, NULL, TRUE, 0, NULL, NULL, &sInfo, &pInfo);
	}
	else {

		_snwprintf_s(str, MAX_LOADSTRING, L"LL hook stop failed");

	}

	SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);



	return 0;
}

void saveToFile(char* buff) {


	f = fopen("file.txt", "at");
	fputs(buff, f);
	fclose(f);


}

char text[100];

LRESULT CALLBACK    KbHookProcLL(int nCode, WPARAM wParam, LPARAM lParam) {

	if (nCode == HC_ACTION) {

		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {

			KBDLLHOOKSTRUCT keyInfo = *((KBDLLHOOKSTRUCT*)lParam);

			_snwprintf_s(str, MAX_LOADSTRING, L"%c %d %d", (char)keyInfo.vkCode, keyInfo.vkCode, buffCount);
			SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);

			text[buffCount] = (char)keyInfo.vkCode;
			buffCount++;


			if (buffCount >= 100) {
				saveToFile(text);
				strcpy(text, "");
				buffCount = 0;
			}



		}

	}

	return CallNextHookEx(kbLL, nCode, wParam, lParam);
}



DWORD   CALLBACK    StartMsHookLL(LPVOID param) {


	if (msLL) {

		_snwprintf_s(str, MAX_LOADSTRING, L"msLL hook works");

	}
	else {
		msLL = SetWindowsHookExW(WH_MOUSE_LL, MsHookProcLL, GetModuleHandle(NULL), 0);

		_snwprintf_s(str, MAX_LOADSTRING, L"msLL hook started");


	}
	SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);

	return 0;
}

DWORD   CALLBACK    StopMsHookLL(LPVOID param) {


	PROCESS_INFORMATION pInfo;
	STARTUPINFO sInfo;


	ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&sInfo, sizeof(STARTUPINFO));

	if (msLL) {

		UnhookWindowsHookEx(msLL);
		_snwprintf_s(str, MAX_LOADSTRING, L"msLL hook stopped");
		//CreateProcessW(L"C:\\Windows\\notepad.exe", (LPWSTR)L"\\W C:\\Users\\luce_dp7x\\source\\repos\\Hooks\\\Hooks\\file.txt", NULL, NULL, TRUE, 0, NULL, NULL, &sInfo, &pInfo);
		msLL = NULL;
	}
	else {

		_snwprintf_s(str, MAX_LOADSTRING, L"msll hook stop failed");

	}

	SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);




	return 0;
}

bool posInit = false;

bool lclk = false;

LRESULT CALLBACK    MsHookProcLL(int nCode, WPARAM wParam, LPARAM lParam) {

	if (nCode == HC_ACTION) {

		MOUSEHOOKSTRUCT mouseInfo = *((MOUSEHOOKSTRUCT*)lParam);
			HPEN savedPen = (HPEN)SelectObject(msDc, msPen);
			HPEN savedPenTrace = (HPEN)SelectObject(dc, msPen);

		if (wParam == WM_MOUSEMOVE) {

			//KBDLLHOOKSTRUCT keyInfo = *((KBDLLHOOKSTRUCT*)lParam);

			//_snwprintf_s(str, MAX_LOADSTRING, L"%d %d", pos.X, pos.Y);
			//SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)str);


			

			if (!posInit) {

				MoveToEx(dc, mouseInfo.pt.x / 5, mouseInfo.pt.y / 5, NULL);
				posInit = true;
			}

			SelectObject(dc, msPen);
			LineTo(dc, mouseInfo.pt.x / 5, mouseInfo.pt.y / 5);
			SelectObject(msDc, savedPenTrace);
			savedPenTrace = (HPEN)SelectObject(memoryDC, msPen);
			LineTo(memoryDC, mouseInfo.pt.x / 5, mouseInfo.pt.y / 5);

			
			SetPixel(msDc, (mouseInfo.pt.x / 5) + 800, mouseInfo.pt.y / 5, RGB(255, 0, 0));
			SetPixel(msDc, (mouseInfo.pt.x / 5) + 801, mouseInfo.pt.y / 5, RGB(255, 0, 0));
			SetPixel(msDc, (mouseInfo.pt.x / 5) + 800, mouseInfo.pt.y / 5 + 1, RGB(255, 0, 0));
			SetPixel(msDc, (mouseInfo.pt.x / 5) + 801, mouseInfo.pt.y / 5 + 1, RGB(255, 0, 0));
			SelectObject(msDc, savedPen);

			savedPen = (HPEN)SelectObject(MSmemoryDC, msPen);
			SetPixel(MSmemoryDC, (mouseInfo.pt.x / 5) + 800, mouseInfo.pt.y / 5, RGB(255, 0, 0));
			SetPixel(MSmemoryDC, (mouseInfo.pt.x / 5) + 801, mouseInfo.pt.y / 5, RGB(255, 0, 0));
			SetPixel(MSmemoryDC, (mouseInfo.pt.x / 5) + 800, mouseInfo.pt.y / 5 + 1, RGB(255, 0, 0));
			SetPixel(MSmemoryDC, (mouseInfo.pt.x / 5) + 801, mouseInfo.pt.y / 5 + 1, RGB(255, 0, 0));

		




		}
		if (wParam == WM_LBUTTONDOWN) {

			Ellipse(dc, mouseInfo.pt.x / MS_SCALE_X - 4, mouseInfo.pt.y / MS_SCALE_Y - 2, mouseInfo.pt.x / MS_SCALE_X + 4, mouseInfo.pt.y / 5 + MS_SCALE_Y + 2);
			savedPenTrace = (HPEN)SelectObject(memoryDC, msPen);
			Ellipse(memoryDC, mouseInfo.pt.x / MS_SCALE_X - 4, mouseInfo.pt.y / MS_SCALE_Y - 2, mouseInfo.pt.x / MS_SCALE_X + 4, mouseInfo.pt.y / 5 + MS_SCALE_Y + 2);

			lclk = true;

		}
		if (wParam == WM_LBUTTONUP) {


			lclk = false;


		}
		if (wParam == WM_RBUTTONDOWN) {

			Rectangle(dc, mouseInfo.pt.x / MS_SCALE_X - 4, mouseInfo.pt.y / MS_SCALE_Y - 2, mouseInfo.pt.x / MS_SCALE_X + 4, mouseInfo.pt.y / 5 + MS_SCALE_Y + 2);
			savedPenTrace = (HPEN)SelectObject(memoryDC, msPen);
			Rectangle(memoryDC, mouseInfo.pt.x / MS_SCALE_X - 4, mouseInfo.pt.y / MS_SCALE_Y - 2, mouseInfo.pt.x / MS_SCALE_X + 4, mouseInfo.pt.y / 5 + MS_SCALE_Y + 2);

		}

		if (wParam == WM_MOUSEWHEEL) {


			if (((int)wParam) > 0) {

				AngleArc(dc, mouseInfo.pt.x / MS_SCALE_X, mouseInfo.pt.y / MS_SCALE_Y, 10, 0, 180);
				savedPenTrace = (HPEN)SelectObject(memoryDC, msPen);
				AngleArc(memoryDC, mouseInfo.pt.x / MS_SCALE_X, mouseInfo.pt.y / MS_SCALE_Y, 10, 0, 180);
			}
			else
			{

				AngleArc(dc, mouseInfo.pt.x / MS_SCALE_X, mouseInfo.pt.y / MS_SCALE_Y, 10, 0, -180);
				savedPenTrace = (HPEN)SelectObject(memoryDC, msPen);
				AngleArc(memoryDC, mouseInfo.pt.x / MS_SCALE_X, mouseInfo.pt.y / MS_SCALE_Y, 10, 0, -180);

			}

		}


	}

	return CallNextHookEx(msLL, nCode, wParam, lParam);
}






