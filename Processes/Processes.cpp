// Processes.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Processes.h"

#define MAX_LOADSTRING 100

#define CMD_OPEN_NOTEPAD 1000
#define CMD_CLOSE_NOTEPAD 1001
#define CMD_OPEN_CHROME 1002
#define CMD_CLOSE_CHROME 1003
#define CMD_OPEN_CALC 1004
#define CMD_CLOSE_CALC 1005
#define CMD_OPEN_CMD 1006
#define CMD_CLOSE_CMD 1007

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hListbox;
HWND hNotepadO;
HWND hNotepadC;
HWND hChromeO;
HWND hChromeC;
HWND hCalcO;
HWND hCalcC;
HWND hCmdO;
HWND hCmdC;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void notepad();
void closeNotepad();
void chrome();
void closeChrome();
void calc();
void closeCalc();
void cmd();
void closeCmd();



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
		hListbox = CreateWindowW(L"Listbox", L"", WS_CHILD | WS_VISIBLE, 300, 10, 300, 400, hWnd, NULL, hInst, NULL);
		hNotepadO = CreateWindowW(L"Button", L"notepad", WS_CHILD | WS_VISIBLE, 10, 10, 75, 23, hWnd, (HMENU)CMD_OPEN_NOTEPAD, hInst, NULL);
		hNotepadC = CreateWindowW(L"Button", L"close", WS_CHILD | WS_VISIBLE, 100, 10, 75, 23, hWnd, (HMENU)CMD_CLOSE_NOTEPAD, hInst, NULL);
		hChromeO = CreateWindowW(L"Button", L"chrome", WS_CHILD | WS_VISIBLE, 10, 40, 75, 23, hWnd, (HMENU)CMD_OPEN_CHROME, hInst, NULL);
		hChromeC = CreateWindowW(L"Button", L"close", WS_CHILD | WS_VISIBLE, 100, 40, 75, 23, hWnd, (HMENU)CMD_CLOSE_CHROME, hInst, NULL);
		hCalcO = CreateWindowW(L"Button", L"calc", WS_CHILD | WS_VISIBLE, 10, 70, 75, 23, hWnd, (HMENU)CMD_OPEN_CALC, hInst, NULL);
		hCalcC = CreateWindowW(L"Button", L"close", WS_CHILD | WS_VISIBLE, 100, 70, 75, 23, hWnd, (HMENU)CMD_CLOSE_CALC, hInst, NULL);
		hCmdO = CreateWindowW(L"Button", L"cmd", WS_CHILD | WS_VISIBLE, 10, 100, 75, 23, hWnd, (HMENU)CMD_OPEN_CMD, hInst, NULL);
		hCmdC = CreateWindowW(L"Button", L"close", WS_CHILD | WS_VISIBLE, 100, 100, 75, 23, hWnd, (HMENU)CMD_CLOSE_CMD, hInst, NULL);

		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case CMD_OPEN_NOTEPAD:
			notepad();
			break;
		case CMD_CLOSE_NOTEPAD:
			closeNotepad();
			break;
		case CMD_OPEN_CHROME:

			chrome();
			break;
		case CMD_OPEN_CALC:
			calc();
			break;
		case CMD_CLOSE_CALC:
			closeCalc();
			break;

		case CMD_OPEN_CMD:
			cmd();
			break;

		case CMD_CLOSE_CMD:
			closeCmd();
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




struct INFO {

	PROCESS_INFORMATION pInfo;
	STARTUPINFO sInfo;

	INFO() {

		ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
		ZeroMemory(&sInfo, sizeof(STARTUPINFO));

	}

};

DWORD WINAPI NewProcess(LPVOID param) {


	INFO* app = (INFO*)param;
	WaitForSingleObject(app->pInfo.hProcess, 60000);
	TerminateProcess(app->pInfo.hProcess, 0);
	SendMessageW(hListbox,LB_ADDSTRING,100,(LPARAM)L"you've not used this app for 1 minute, so it has been closed");

	CloseHandle(app->pInfo.hThread);
	CloseHandle(app->pInfo.hProcess);
	return 0;
}

INFO iNotepad;
void notepad() {

	if (CreateProcessW(L"C:\\Windows\\notepad.exe", (LPWSTR)L"\\W C:\\Users\\luche\\Desktop\\dz.txt", NULL, NULL, TRUE, 0, NULL, NULL, &iNotepad.sInfo, &iNotepad.pInfo)) {

		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"notepad works");
		CreateThread(NULL,0,NewProcess, &iNotepad,0,NULL);
	}
	else {

		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"notepad error");

	}


}

void closeNotepad() {

	if (TerminateProcess(iNotepad.pInfo.hProcess, 0)) {

		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"notepad stopped");

		CloseHandle(iNotepad.pInfo.hThread);
		CloseHandle(iNotepad.pInfo.hProcess);

	}

}

INFO iChrome;

void chrome() {

	
	if (CreateProcessW(L"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe", 
		(LPWSTR)L"\\ https://itstep.org", NULL, NULL, TRUE, IDLE_PRIORITY_CLASS |CREATE_NEW_PROCESS_GROUP, NULL, NULL, &iChrome.sInfo, &iChrome.pInfo)) {


		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"chrome works");
		CreateThread(NULL, 0, NewProcess, &iChrome, 0, NULL);


	}
	else {

		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"chrome error");

	}
}

void closeChrome() {

	if (TerminateProcess(iChrome.pInfo.hProcess, 0)) {

		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"chrome stopped");

		CloseHandle(iChrome.pInfo.hThread);
		CloseHandle(iChrome.pInfo.hProcess);

	}

}



INFO iCalc;

void calc() {


	if (CreateProcessW(L"C:\\Windows\\SysWOW64\\calc.exe",NULL, NULL, NULL, TRUE, IDLE_PRIORITY_CLASS | CREATE_NEW_PROCESS_GROUP, NULL, NULL, &iCalc.sInfo, &iCalc.pInfo)) {


		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"calc works");
		CreateThread(NULL, 0, NewProcess, &iCalc, 0, NULL);



	}
	else {

		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"calc error");

	}
}

void closeCalc() {

	if (TerminateProcess(iCalc.pInfo.hProcess, 0)) {

		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"calc stopped");

		CloseHandle(iCalc.pInfo.hThread);
		CloseHandle(iCalc.pInfo.hProcess);

	}

}


INFO iCmd;

void cmd() {


	if (CreateProcessW(L"C:\\Windows\\SysWOW64\\cmd.exe", NULL, NULL, NULL, TRUE, IDLE_PRIORITY_CLASS | CREATE_NEW_PROCESS_GROUP, NULL, NULL, &iCmd.sInfo, &iCmd.pInfo)) {


		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"cmd works");
		CreateThread(NULL, 0, NewProcess, &iCmd, 0, NULL);



	}
	else {

		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"cmd error");

	}
}

void closeCmd() {

	if (TerminateProcess(iCmd.pInfo.hProcess, 0)) {

		SendMessageW(hListbox, LB_ADDSTRING, 100, (LPARAM)L"cmd stopped");

		CloseHandle(iCmd.pInfo.hThread);
		CloseHandle(iCmd.pInfo.hProcess);

	}

}