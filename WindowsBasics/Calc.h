#pragma once

#include "framework.h"

LRESULT CALLBACK    WndProcCalc(HWND, UINT, WPARAM, LPARAM);

void createCalc(HWND);
void showWindowCalc(HINSTANCE hInstance, HWND mainWindow);
void animation();

HINSTANCE hInstC;
BOOL isCalcReg = FALSE;

////////////////////////
const int const  CMD_BUTTONS[10] = { 4000,4001,4002,4003,4004,4005,4006,4007,4008,4009 };

#define CMD_BUTTON_0 4000
#define CMD_BUTTON_1 4001
#define CMD_BUTTON_2 4002
#define CMD_BUTTON_3 4003
#define CMD_BUTTON_4 4004
#define CMD_BUTTON_5 4005
#define CMD_BUTTON_6 4006
#define CMD_BUTTON_7 4007
#define CMD_BUTTON_8 4008
#define CMD_BUTTON_9 4009




#define CMD_BUTTON_PLUS 4010
#define CMD_BUTTON_MINUS 4011
#define CMD_BUTTON_MULTIPLY 4012
#define CMD_BUTTON_DEVIDE 4013
#define CMD_BUTTON_CLEAN 4014




///////////////////
HWND hwndSTATIC;
HWND hwndEDIT;
HWND hwndPLUS;
HWND hwndMINUS;
HWND hwndMULTIPLY;
HWND hwndDEVIDE;
HWND hwndCLEAN;
HWND hwndBUTTONS[10];



void showWindowCalc(HINSTANCE hInstance, HWND mainWindow) {

	//Register class;
	//WndProc
	//CreateWindow

	hInstC = hInstance;

	srand(time(0));
	if (!isCalcReg) {

		WNDCLASSEXW wcexC;
		ZeroMemory(&wcexC, sizeof(WNDCLASSEXW));
		wcexC.cbSize = sizeof(WNDCLASSEX);
		wcexC.lpfnWndProc = WndProcCalc;
		wcexC.hInstance = hInstC;
		wcexC.hbrBackground = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))/*((HBRUSH)(COLOR_WINDOW + 1))*/;
		wcexC.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcexC.lpszClassName = L"CalcWindow";

		if (!RegisterClassExW(&wcexC)) {
			MessageBoxW(mainWindow, L"Register class error!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		isCalcReg = TRUE;
	}

	//3
	HWND controlsWindow = CreateWindowW(L"CalcWindow", L"Calculator", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 400, 600, mainWindow, NULL, hInstC, 0);

	ShowWindow(controlsWindow, SW_NORMAL);

}


LRESULT CALLBACK    WndProcCalc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message)
	{
	case WM_CREATE:
		createCalc(hWnd);
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		switch (wmId)
		{

		case CMD_BUTTON_0:

			WCHAR str[11];

			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)str);
			str[wcslen(str) + 1] = L'\0';
			std::wstring strbuff = str;

			strbuff+=L"0";

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)strbuff.c_str());

			break;

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



void createCalc(HWND hWnd) {


	const WCHAR fontName[] = L"Courier";
	const long nFontSize = 20;

	HFONT s_hFont;
	HDC hdc = GetDC(hWnd);
	LOGFONT logFont = { 0 };
	logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	logFont.lfWeight = FW_BOLD;
	wcscpy_s(logFont.lfFaceName, fontName);
	s_hFont = CreateFontIndirect(&logFont);



	hwndSTATIC = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD, 20, 30, 125, 23, hWnd, 0, hInstC, 0);
	hwndEDIT = CreateWindowW(L"Edit", L"0", WS_VISIBLE | WS_CHILD | ES_RIGHT, 20, 60, 125, 23, hWnd, 0, hInstC, 0);
	SendMessage(hwndEDIT, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

	//CreateWindowW(L"Static", L"Your name:", WS_VISIBLE | WS_CHILD, 20, 30, 125, 23, hWnd, NULL, hInstP, NULL);
	//CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE, 20, 60, 125, 23, hWnd, (HMENU)CMD_COMBOBOX, hInst, 0);




	WCHAR  buff[2];

	COORD pos;
	pos.X = 0;
	pos.Y = 0;

	for (int i = 1; i < 10; i++) {

		_itow_s(i, buff, 2, 10);
		hwndBUTTONS[i] = CreateWindowW(L"Button", buff, WS_CHILD | WS_VISIBLE, pos.X * 67 + 100, pos.Y * 67 + 100, 65, 65, hWnd, (HMENU)(4000 + i), hInstC, 0);
		SendMessage(hwndBUTTONS[i], WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		pos.X++;
		if (pos.X == 3) {
			pos.X = 0;
			pos.Y++;

		}
	}

	hwndBUTTONS[0] = CreateWindowW(L"Button", L"0", WS_CHILD | WS_VISIBLE, (pos.X + 1) * 67 + 100, (pos.Y) * 67 + 100, 65, 65, hWnd, (HMENU)4000, hInstC, 0);
	SendMessage(hwndBUTTONS[0], WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));



	hwndMULTIPLY = CreateWindowW(L"Button", L"*", WS_CHILD | WS_VISIBLE, (pos.X) * 67 + 100, (pos.Y) * 67 + 100, 65, 65, hWnd, (HMENU)CMD_BUTTON_MULTIPLY, hInstC, 0);
	SendMessage(hwndMULTIPLY, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

	hwndDEVIDE = CreateWindowW(L"Button", L"/", WS_CHILD | WS_VISIBLE, (pos.X) * 67 + 100, (pos.Y + 1) * 67 + 100, 65, 65, hWnd, (HMENU)CMD_BUTTON_DEVIDE, hInstC, 0);
	SendMessage(hwndDEVIDE, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));


	hwndPLUS = CreateWindowW(L"Button", L"+", WS_CHILD | WS_VISIBLE, (pos.X + 2) * 67 + 100, (pos.Y + 1) * 67 + 100, 65, 65, hWnd, (HMENU)CMD_BUTTON_PLUS, hInstC, 0);
	SendMessage(hwndPLUS, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

	hwndMINUS = CreateWindowW(L"Button", L"-", WS_CHILD | WS_VISIBLE, (pos.X + 2) * 67 + 100, (pos.Y) * 67 + 100, 65, 65, hWnd, (HMENU)CMD_BUTTON_MINUS, hInstC, 0);
	SendMessage(hwndMINUS, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));


	hwndCLEAN = CreateWindowW(L"Button", L"C", WS_CHILD | WS_VISIBLE, (pos.X + 1) * 67 + 100, (pos.Y + 1) * 67 + 100, 65, 65, hWnd, (HMENU)CMD_BUTTON_CLEAN, hInstC, 0);
	SendMessage(hwndCLEAN, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));




}


