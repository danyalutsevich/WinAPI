// SysDialogs.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SysDialogs.h"

#include <string>
#include <iostream>
#include <fstream>

#define MAX_LOADSTRING 100
#define CMD_BUTTON_OPEN_FILE 1001
#define CMD_SAVE_AS 1002
#define CMD_SRC 1003
#define CMD_DEST 1004
#define CMD_CIPH 1005
#define CMD_STOPCIPH 1006
#define CMD_DECIPH 1007


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND fNameS;
HWND editor;
HWND encoding;

HWND hProgres;
HWND hPassword;

HWND src;
HWND dest;

HANDLE mutex;


FILE* f;

bool isStopped = false;
bool ciphering = false;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

DWORD CALLBACK OpenFileClick(LPVOID);
DWORD CALLBACK SRCFileClick(LPVOID);
DWORD CALLBACK CiphFileClick(LPVOID);
DWORD CALLBACK DESTFileClick(LPVOID);
DWORD CALLBACK SaveFileClick(LPVOID);
DWORD CALLBACK stopFlag(LPVOID);


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
	LoadStringW(hInstance, IDC_SYSDIALOGS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SYSDIALOGS));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SYSDIALOGS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SYSDIALOGS);
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

		fNameS = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 10, 10, 280, 75, hWnd, NULL, hInst, NULL);
		CreateWindowW(L"Button", L"...", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 10, 30, 23, hWnd, (HMENU)CMD_BUTTON_OPEN_FILE, hInst, NULL);

		editor = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 10, 150, 280, 300, hWnd, NULL, hInst, NULL);

		CreateWindowW(L"Button", L"Save as", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 300, 300, 75, 23, hWnd, (HMENU)CMD_SAVE_AS, hInst, NULL);
		encoding = CreateWindowW(L"Edit", L"encoding", WS_VISIBLE | WS_CHILD | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL, 10, 100, 75, 23, hWnd, NULL, hInst, NULL);




		src = CreateWindowW(L"Edit", L"source file", WS_VISIBLE | WS_CHILD | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL, 600, 100, 290, 23, hWnd, NULL, hInst, NULL);
		CreateWindowW(L"Button", L"...", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 900, 100, 30, 23, hWnd, (HMENU)CMD_SRC, hInst, NULL);


		dest = CreateWindowW(L"Edit", L"destination file", WS_VISIBLE | WS_CHILD | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL, 600, 130, 290, 23, hWnd, NULL, hInst, NULL);
		CreateWindowW(L"Button", L"...", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 900, 130, 30, 23, hWnd, (HMENU)CMD_DEST, hInst, NULL);

		CreateWindowW(L"Button", L"cipher", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 855, 160, 75, 23, hWnd, (HMENU)CMD_CIPH, hInst, NULL);
		CreateWindowW(L"Button", L"decipher", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 855 - 85, 160, 75, 23, hWnd, (HMENU)CMD_DECIPH, hInst, NULL);
		CreateWindowW(L"Button", L"stop", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 855 - 85 * 2, 160, 75, 23, hWnd, (HMENU)CMD_STOPCIPH, hInst, NULL);

		hProgres = CreateWindowW(PROGRESS_CLASSW, L"", WS_CHILD | WS_VISIBLE | PBS_MARQUEE | PBS_SMOOTH, 600, 190, 330, 23, hWnd, 0, hInst, NULL);

		hPassword = CreateWindowW(L"Edit", L"password", WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_PASSWORD, 600, 70, 290, 23, hWnd, NULL, hInst, NULL);

		mutex = CreateMutex(NULL, FALSE, NULL);


		break;

	case WM_COMMAND:
	{

		int notifID = HIWORD(wParam);

		switch (notifID) {



		}


		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case CMD_BUTTON_OPEN_FILE:

			OpenFileClick(&hWnd);

			break;
		case CMD_CIPH:

			ciphering = true;
			CreateThread(0, 0, CiphFileClick, &hWnd, 0, 0);
			//CiphFileClick(&hWnd);
			break;
		case CMD_DEST:

			DESTFileClick(&hWnd);

			break;
		case CMD_SRC:

			SRCFileClick(&hWnd);
			break;

		case CMD_SAVE_AS:

			SaveFileClick(&hWnd);
			break;
		case ID_FILE_SAVEAS:

			SaveFileClick(&hWnd);
			break;
		case CMD_DECIPH:

			CreateThread(0, 0, CiphFileClick, &hWnd, 0, 0);

			break;
		case CMD_STOPCIPH:

			CreateThread(0, 0, stopFlag, 0, 0, 0);


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

DWORD CALLBACK stopFlag(LPVOID param) {
	if (WaitForSingleObject(mutex, INFINITE) == WAIT_OBJECT_0 && ciphering == true) {

		isStopped = true;
		ReleaseMutex(mutex);
	}

	return 0;

}

DWORD CALLBACK OpenFileClick(LPVOID params) {

	HWND hWnd = *((HWND*)params);
	WCHAR fName[512] = L"0";



	OPENFILENAMEW ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = hInst;
	ofn.lpstrFile = fName;
	ofn.nMaxFile = 512;

	if (GetOpenFileNameW(&ofn)) {

		unsigned char utf16LE[] = { 0xFF, 0xFE };
		unsigned char utf16BE[] = { 0xFE, 0xFF };
		unsigned char utf8[] = { 0xEF, 0xBB };



		SendMessageW(fNameS, WM_SETTEXT, 0, (LPARAM)fName);
		WCHAR correctName[512];

		HANDLE hFile = CreateFileW(fName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == 0) {

			SendMessageW(fNameS, WM_SETTEXT, 0, (LPARAM)L"File open error");

		}
		else {
			DWORD fSize;

			fSize = GetFileSize(hFile, NULL);


			if (fSize > 0) {


				wchar_t* content = new wchar_t[fSize / sizeof(wchar_t) + 1];
				BYTE* mark = new BYTE[2];
				DWORD read;

				if (ReadFile(hFile, content, fSize, &read, NULL)) {

					CloseHandle(hFile);
					hFile = CreateFileW(fName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

					content[fSize / sizeof(wchar_t)] = '\0';
					ReadFile(hFile, mark, 2, &read, NULL);

					if (mark[0] == utf16LE[0] && mark[1] == utf16LE[1]) {

						SendMessageW(editor, WM_SETTEXT, 0, (LPARAM)content);
						SendMessageW(encoding, WM_SETTEXT, 0, (LPARAM)L"utf16LE");
					}
					else if (mark[0] == utf16BE[0] && mark[1] == utf16BE[1]) {

						SendMessageW(editor, WM_SETTEXT, 0, (LPARAM)content);
						SendMessageW(encoding, WM_SETTEXT, 0, (LPARAM)L"utf16BE");
					}
					else if (mark[0] == utf8[0] && mark[1] == utf8[1]) {
						SendMessageW(editor, WM_SETTEXT, 0, (LPARAM)content);
						SendMessageW(encoding, WM_SETTEXT, 0, (LPARAM)L"utf8 with bom");
					}
					else {

						SendMessageA(editor, WM_SETTEXT, 0, (LPARAM)content);
						SendMessageW(encoding, WM_SETTEXT, 0, (LPARAM)L"undefined");
					}

					delete[] content;
				}
				else {

					SendMessageA(editor, WM_SETTEXT, 0, (LPARAM)L"File read error");

				}

			}
			else {


				SendMessageW(editor, WM_SETTEXT, 0, (LPARAM)L"File is empty");

			}

		}
		CloseHandle(hFile);

	}
	else {

		SendMessageW(fNameS, WM_SETTEXT, 0, (LPARAM)L"Selection canceled");

	}

	return 0;
}


DWORD CALLBACK SaveFileClick(LPVOID param) {

	HWND hWnd = *((HWND*)param);



	OPENFILENAMEW ofn;

	wchar_t fileName[512] = L"Hello.txt\0";

	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = hInst;
	ofn.lpstrFile = fileName;
	//ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 512;

	ofn.lpstrFilter = L"All Files\0*.*\0Text files\0*.txt\0C/C++ code files\0*.cpp;*.c\0\0";
	ofn.nFilterIndex = 1;


	if (!GetSaveFileNameW(&ofn)) {

		MessageBoxA(NULL, "Invalid file name", "Invalid file name", MB_ICONERROR);
	}
	else {


		HANDLE hFile = CreateFileW(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile) {

			char content[1024];
			SendMessageA(editor, WM_GETTEXT, 1024, (LPARAM)content);

			DWORD write;
			//WriteFile(hFile, content, strnlen_s(content, 1024), &write, NULL);

			if (!WriteFile(hFile, content, strnlen_s(content, 1024), &write, NULL)) {

				MessageBoxA(hWnd, "write error", "write error", MB_OK | MB_ICONWARNING);
				if (write != strnlen_s(content, 1024)) {

					MessageBoxA(hWnd, "write error", "write error", MB_OK | MB_ICONWARNING);


				}

			}



		}



		CloseHandle(hFile);

	}

	return 0;
}

char srcName[512] = "0";
char destName[512] = "0";

DWORD CALLBACK SRCFileClick(LPVOID param) {

	HWND hWnd = *((HWND*)param);



	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = hInst;
	ofn.lpstrFile = srcName;
	ofn.nMaxFile = 512;

	if (GetOpenFileNameA(&ofn)) {


		SendMessageA(src, WM_SETTEXT, 0, (LPARAM)srcName);
	}
	else {

		SendMessageA(fNameS, WM_SETTEXT, 0, (LPARAM)L"File open error");

	}


	return 0;

}

DWORD CALLBACK DESTFileClick(LPVOID param) {

	HWND hWnd = *((HWND*)param);



	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = hInst;
	ofn.lpstrFile = destName;
	ofn.nMaxFile = 512;

	if (GetOpenFileNameA(&ofn)) {

		SendMessageA(dest, WM_SETTEXT, 0, (LPARAM)destName);

	}
	else {

		SendMessageA(dest, WM_SETTEXT, 0, (LPARAM)L"File open error");

	}


	return 0;

}



DWORD CALLBACK CiphFileClick(LPVOID param) {

	HWND hWnd = *((HWND*)param);


	if (GetWindowTextLengthA(hPassword) > 16) {

		MessageBoxA(NULL, "Password should be less than 16 characters", "Password is too big", MB_ICONERROR | MB_OK);
	}
	else {
		FILE* fsrc;
		fsrc = fopen(srcName, "rb");

		FILE* fdest;
		fdest = fopen(destName, "wb");

		if (fsrc) {

			MessageBoxA(NULL, "Source file already exists it will be overwritten", "Source file already exists", MB_ICONWARNING | MB_OK);
		}

		if (fdest) {

			MessageBoxA(NULL, "Destination file already exists it will be overwritten", "Destination file already exists", MB_ICONWARNING | MB_OK);
		}

		char pass[16];
		SendMessageA(hPassword, WM_GETTEXT, 0, (LPARAM)pass);


		int readed = 0;
		char buff[1];

		int currSymbol = 0;

		int fileSize = 0;
		fseek(fsrc, 0, SEEK_END);
		fileSize = ftell(fsrc);
		std::cout << fileSize;
		fseek(fsrc, 0, SEEK_SET);

		SendMessageW(hProgres, PBM_SETRANGE, 0, MAKELPARAM(0, fileSize));
		SendMessageW(hProgres, PBM_SETBARCOLOR, 0, RGB(0, 255, 0));

		HMODULE dll = LoadLibraryW(L"..\\Debug\\ciphDLL.dll");

		if (dll == NULL) {

			if (MessageBoxW(NULL, L"Would you like to find DLL?", L"DLL not found", MB_YESNO | MB_ICONERROR) == IDYES) {

				char dllPath[512] = "\0";

				OPENFILENAMEA ofn;
				ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
				ofn.lStructSize = sizeof(OPENFILENAMEA);
				ofn.hwndOwner = hWnd;
				ofn.hInstance = hInst;
				ofn.lpstrFile = dllPath;
				ofn.nMaxFile = 512;

				if (GetOpenFileNameA(&ofn)) {

					dll = LoadLibraryA(dllPath);

				}
				else {

					SendMessageA(dest, WM_SETTEXT, 0, (LPARAM)L"DLL open error");

				}

			}
		}

		char(*ciph)(char, char);

		ciph = (char(*)(char, char))GetProcAddress(dll, "Cipher");
		SendMessageW(hProgres, PBM_DELTAPOS, 1, 0);
		DWORD result;

		while (fread(buff, sizeof(char), 1, fsrc) == 1) {

			if (isStopped == false) {

				readed += 1;
				SendMessageW(hProgres, PBM_DELTAPOS, 1, 0);
				//std::cout << *buff;

				//buff[0] = buff[0] ^ pass[readed % strlen(pass)];
				buff[0] = ciph(buff[0], pass[readed % strlen(pass)]);

				//Sleep(1);

				fwrite(buff, sizeof(char), 1, fdest);
			}
			else {

				break;
			}
		}

		fclose(fsrc);
		fclose(fdest);

		if (isStopped == false) {

			MessageBoxW(NULL, L"Done", L"Done", MB_OK | MB_ICONINFORMATION);
		}
		else {

			MessageBoxW(NULL, L"Process was stopped", L"Process was stopped", MB_OK | MB_ICONINFORMATION);

		}

		isStopped = false;
		ciphering = false;
		SendMessageW(hProgres, PBM_DELTAPOS, -fileSize, 0);
	}

	return 0;

}