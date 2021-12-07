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

#define CMD_SAVE 1007

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
HWND save;

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

void CreateBMPFile(LPTSTR pszFile, HBITMAP hBMP);
PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);


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
		CreateWindowW(L"Button", L"Save", WS_VISIBLE | WS_CHILD, 10, 190, 75, 23, hWnd, (HMENU)CMD_SAVE, hInst, NULL);



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

		case CMD_SAVE:

			CreateBMPFile((LPTSTR)L"mouseActivity.bmp", memoryPicture);
			CreateBMPFile((LPTSTR)L"mouseActivityTrace.bmp", memoryPictureTrace);

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
			if (lclk) {
				DeletePen(msPen);
				msPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
				SelectObject(dc, msPen);
				LineTo(dc, mouseInfo.pt.x / 5, mouseInfo.pt.y / 5);
				SelectObject(msDc, savedPenTrace);
				savedPenTrace = (HPEN)SelectObject(memoryDC, msPen);
				LineTo(memoryDC, mouseInfo.pt.x / 5, mouseInfo.pt.y / 5);
				msPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			}
			else {

				SelectObject(dc, msPen);
				LineTo(dc, mouseInfo.pt.x / 5, mouseInfo.pt.y / 5);
				SelectObject(msDc, savedPenTrace);
				savedPenTrace = (HPEN)SelectObject(memoryDC, msPen);
				LineTo(memoryDC, mouseInfo.pt.x / 5, mouseInfo.pt.y / 5);

			}

			
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


PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp)
{
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;

	// Retrieve the bitmap color format, width, and height.  
	assert(GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp));

	// Convert the color format to a count of bits.  
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;

	// Allocate memory for the BITMAPINFO structure. (This structure  
	// contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
	// data structures.)  

	if (cClrBits < 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * (1 << cClrBits));

	// There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 

	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER));

	// Initialize the fields in the BITMAPINFO structure.  

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);

	// If the bitmap is not compressed, set the BI_RGB flag.  
	pbmi->bmiHeader.biCompression = BI_RGB;

	// Compute the number of bytes in the array of color  
	// indices and store the result in biSizeImage.  
	// The width must be DWORD aligned unless the bitmap is RLE 
	// compressed. 
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;
	// Set biClrImportant to 0, indicating that all of the  
	// device colors are important.  
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}

void CreateBMPFile(LPTSTR pszFile, HBITMAP hBMP)
{
	HANDLE hf;                 // file handle  
	BITMAPFILEHEADER hdr;       // bitmap file-header  
	PBITMAPINFOHEADER pbih;     // bitmap info-header  
	LPBYTE lpBits;              // memory pointer  
	DWORD dwTotal;              // total count of bytes  
	DWORD cb;                   // incremental count of bytes  
	BYTE* hp;                   // byte pointer  
	DWORD dwTmp;
	PBITMAPINFO pbi;
	HDC hDC;

	hDC = CreateCompatibleDC(GetWindowDC(GetDesktopWindow()));
	SelectObject(hDC, hBMP);

	pbi = CreateBitmapInfoStruct(hBMP);

	pbih = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	assert(lpBits);

	// Retrieve the color table (RGBQUAD array) and the bits  
	// (array of palette indices) from the DIB.  
	assert(GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi,
		DIB_RGB_COLORS));

	// Create the .BMP file.  
	hf = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	assert(hf != INVALID_HANDLE_VALUE);

	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
	// Compute the size of the entire file.  
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	// Compute the offset to the array of color indices.  
	hdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file.  
	assert(WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL));

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
	assert(WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)));

	// Copy the array of color indices into the .BMP file.  
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	assert(WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL));

	// Close the .BMP file.  
	assert(CloseHandle(hf));

	// Free memory.  
	GlobalFree((HGLOBAL)lpBits);
}




