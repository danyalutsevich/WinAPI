// Processes.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Processes.h"

#define MAX_LOADSTRING 100

#define CMD_BUTTON_1 1000
#define CMD_BUTTON_2 1001

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND Button1;
HWND listbox;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void button1Click();
void chrome();

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
	LoadStringW(hInstance, IDC_PROCESSES, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROCESSES));

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

	srand(time(0));

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROCESSES));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))/*(HBRUSH)(COLOR_WINDOW+1)*/;
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROCESSES);
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
		listbox = CreateWindowW(L"Listbox", L"", WS_CHILD | WS_VISIBLE, 100, 10, 300, 400, hWnd, NULL, hInst, NULL);
		Button1 = CreateWindowW(L"Button", L"Process", WS_CHILD | WS_VISIBLE, 10, 10, 75, 23, hWnd, (HMENU)CMD_BUTTON_1, hInst, NULL);

		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case CMD_BUTTON_1:
			//button1Click();
			chrome();
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



PROCESS_INFORMATION pInfo;
STARTUPINFO sInfo;



DWORD WINAPI NewProcess(LPVOID param) {

	//SendMessageW(listbox,LB_ADDSTRING,100,(LPARAM)L"works");


	WaitForSingleObject(pInfo.hProcess, 100);
	TerminateProcess(pInfo.hProcess, 2000);

	CloseHandle(pInfo.hThread);
	CloseHandle(pInfo.hProcess);
	SendMessageW(listbox, LB_ADDSTRING, 100, (LPARAM)L"stopped");
	return 0;
}

void button1Click() {

	ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&sInfo, sizeof(STARTUPINFO));


	if (CreateProcessW(L"C:\\Windows\\notepad.exe", (LPWSTR)L"\\W C:\\Users\\luce_dp7x\\Desktop\\xtx.txt", NULL, NULL, TRUE, 0, NULL, NULL, &sInfo, &pInfo)) {

		//CreateThread(NULL,0,NewProcess,NULL,0,NULL);

		SendMessageW(listbox, LB_ADDSTRING, 100, (LPARAM)L"works");



	}
	else {

		SendMessageW(listbox, LB_ADDSTRING, 100, (LPARAM)L"error");

	}


}

void chrome() {

	ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&sInfo, sizeof(STARTUPINFO));


	if (CreateProcessW(L"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe", (LPWSTR)L"\\W https://github.com/danyalutsevich/WinAPI/blob/threads/Threads/Threads.cpp", NULL, NULL, TRUE, 0, NULL, NULL, &sInfo, &pInfo)) {

		//CreateThread(NULL,0,NewProcess,NULL,0,NULL);

		SendMessageW(listbox, LB_ADDSTRING, 100, (LPARAM)L"works");



	}
	else {

		SendMessageW(listbox, LB_ADDSTRING, 100, (LPARAM)L"error");

	}
}