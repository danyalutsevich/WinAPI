// Threads.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Threads.h"
#include <time.h>

#define MAX_LOADSTRING 100
#define CMD_BUTTON_1 1001
#define CMD_BUTTON_2 1002
#define CMD_BUTTON_3 1003
#define CMD_BUTTON_4 1004


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND listbox;




HWND hwndBUTTON1;
HWND hwndBUTTON2;
HWND hwndBUTTON3;
HWND hwndBUTTON4;

HANDLE mutex4 = NULL;




// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void StartThread();
void StartThread2();
void StartThread3();
void StartThread4();



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
	LoadStringW(hInstance, IDC_THREADS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_THREADS));

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
	srand(time(0));
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_THREADS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))/*(HBRUSH)(COLOR_WINDOW + 3)*/;
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_THREADS);
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

		hwndBUTTON1 = CreateWindowW(L"Button", L"Push me", WS_CHILD | WS_VISIBLE, 10, 10, 75, 23, hWnd, (HMENU)CMD_BUTTON_1, hInst, 0);
		hwndBUTTON2 = CreateWindowW(L"Button", L"Thread", WS_CHILD | WS_VISIBLE, 10, 50, 75, 23, hWnd, (HMENU)CMD_BUTTON_2, hInst, 0);
		hwndBUTTON3 = CreateWindowW(L"Button", L"percent", WS_CHILD | WS_VISIBLE, 10, 110, 75, 23, hWnd, (HMENU)CMD_BUTTON_3, hInst, 0);
		hwndBUTTON4 = CreateWindowW(L"Button", L"mutex", WS_CHILD | WS_VISIBLE, 10, 170, 75, 23, hWnd, (HMENU)CMD_BUTTON_4, hInst, 0);
		listbox = CreateWindowW(L"Listbox", L"", WS_CHILD | WS_VISIBLE, 90, 90, 350, 223, hWnd, (HMENU)NULL, hInst, 0);
		mutex4 = CreateMutex(NULL, FALSE, NULL);

		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{

		case CMD_BUTTON_1:
			StartThread();


			break;
		case CMD_BUTTON_2:

			StartThread2();


			break;
		case CMD_BUTTON_3:

			StartThread3();

			break;
		case CMD_BUTTON_4:
			

			StartThread4();
			

			break;
		case IDM_ABOUT:
			/*DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);*/
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
		CloseHandle(mutex4);

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





DWORD WINAPI ThreadProc(LPVOID params) {



	MessageBoxW(NULL, L"hell", L"Works", MB_YESNOCANCEL);


	// DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, About);

	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID params) {

	MessageBoxW(NULL, (LPCWSTR)params, L"Works", MB_YESNOCANCEL);

	//MessageBoxW(NULL, (LPCWSTR)params,L"Works",MB_YESNOCANCEL);



	return 0;
}



void StartThread() {

	CreateThread(
		NULL, // attributes for thread
		0,    //Stack limit 0 - system default
		ThreadProc,// Address of thread function
		NULL, // Pointer to parametr(s)
		0,    // Creation flags
		NULL  // Thread Id pointer
	);

}



void StartThread2() {

	CreateThread(
		NULL,
		0,
		ThreadProc2,
		szTitle,
		0,
		NULL
	);

}



struct DepData {

	int month;
	float percent;
	static int count;
	DepData(int month, float percent) :month{ month }, percent{ percent } {

	}
};

int DepData::count = 0;

int activeThreads;
float deposit;
HANDLE hts[12] = {};


DWORD WINAPI finalizer(LPVOID params) {


	for (int i = 0; i < 12; i++) {

		if (hts[i]) {

			CloseHandle(hts[i]);
			hts[i] = NULL;
		}

	}

	wchar_t buff[100];
	_snwprintf_s(buff, 100, L"total %.2f", deposit);
	SendMessage(listbox, LB_ADDSTRING, 100, (LPARAM)buff);


	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID params) {

	wchar_t buff[100];

	DepData* data = (DepData*)params;

	deposit += deposit * (data->percent / 100.0f);


	_snwprintf_s(buff, 100, L"month %d percent %.2f amount %.2f", data->month, data->percent, deposit);
	//SendMessage(listbox, LB_ADDSTRING, 100, (LPARAM)buff);


	delete data;

	activeThreads--;
	if (activeThreads == 0) {
		//launch finalizer

		CreateThread(NULL, 0, finalizer, (LPVOID)NULL, 0, NULL);
	}
	return 0;
}


void StartThread3() {




	int month = 12;
	activeThreads = 0;
	deposit = 100;

	for (int i = 0; i < month; i++) {

		hts[i] = CreateThread(NULL, 0, ThreadProc3, (LPVOID)new DepData(i + 1, 10.f), 0, NULL);

		if (hts[i] != NULL) {
			activeThreads++;
		}
	}



}


HANDLE hts4[12];
int activeThreads4;



DWORD WINAPI finalizer4(LPVOID params) {


	for (int i = 0; i < 12; i++) {

		if (hts4[i]) {

			CloseHandle(hts4[i]);
			hts4[i] = NULL;
		}

	}

	wchar_t buff[100];
	_snwprintf_s(buff, 100, L"total %.2f", deposit);
	SendMessage(listbox, LB_ADDSTRING, 100, (LPARAM)buff);

	return 0;
}

DWORD WINAPI ThreadProc4(LPVOID params) {

	//SendMessage(listbox, LB_RESETCONTENT, 0, (LPARAM)0);
	wchar_t buff[100];

	DepData* data = (DepData*)params;
	DWORD waitResult = WaitForSingleObject(mutex4, INFINITE);

	if (waitResult == WAIT_OBJECT_0) {

		deposit += deposit * (data->percent / 100.0f);

		_snwprintf_s(buff, 100, L"month %d percent %.2f amount %.2f", data->month, data->percent, deposit);
		//SendMessage(listbox, LB_ADDSTRING, 100, (LPARAM)buff);



		activeThreads4++;
		if (activeThreads4 == 12) {
			//launch finalizer

			CreateThread(NULL, 0, finalizer4, (LPVOID)NULL, 0, NULL);
		}
		ReleaseMutex(mutex4);
	}
	else {

		SendMessage(listbox, LB_ADDSTRING, 100, (LPARAM)L"Mutex wait error");


	}

	delete data;
	return 0;
}

void StartThread4() {

	int month = 12;
	activeThreads4 = 0;
	deposit = 100;

	for (int i = 0; i < month; i++) {

		hts4[i] = CreateThread(NULL, 0, ThreadProc4, (LPVOID)new DepData(i + 1, 10.f), 0, NULL);

		
	}


}
