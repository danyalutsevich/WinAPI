#pragma once

#include "framework.h"

LRESULT CALLBACK    WndProcCalc(HWND, UINT, WPARAM, LPARAM);

void createCalc(HWND);
void showWindowCalc(HINSTANCE hInstance, HWND mainWindow);
void animation();
std::wstring* splitString(std::wstring, wchar_t);


HINSTANCE hInstC;
BOOL isCalcReg = FALSE;

////////////////////////


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
#define CMD_BUTTON_EQUALS 4015
#define CMD_BUTTON_DELETE 4016
#define CMD_BUTTON_PLUSMINUS 4017
#define CMD_BUTTON_DOT 4018




///////////////////

HWND hwndSTATIC;
HWND hwndEDIT;

HWND hwndBUTTONS[10];

HWND hwndPLUS;
HWND hwndMINUS;
HWND hwndMULTIPLY;
HWND hwndDEVIDE;
HWND hwndCLEAN;
HWND hwndEQUALS;
HWND hwndDELETE;
HWND hwndPLUSMINUS;
HWND hwndDOT;





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
int n;
wchar_t buff[100] = L"\0";
char* str;

std::wstring* splitString(std::wstring str, wchar_t sym) {

	size_t pos = 0;
	int parts = 1;

	while ((pos = str.find(sym, pos + 1)) != std::string::npos) {
		parts++;
	}

	std::wstring* res = new std::wstring[parts];
	pos = 0;
	size_t pos2;

	for (int i = 0; i < parts - 1; i++) {

		pos2 = str.find(sym, pos + 1);
		res[i] = str.substr(pos, pos2 - pos);
		pos = pos2;


	}

	res[parts - 1] = str.substr(pos + 1);



	return res;
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



			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);

			if (_wtoi(buff) > 0) {

				wcscat_s(buff, L"0");
				SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			}




			break;
		case CMD_BUTTON_1:



			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);


			wcscat_s(buff, L"1");

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			break;
		case CMD_BUTTON_2:


			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);


			wcscat_s(buff, L"2");

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			break;
		case CMD_BUTTON_3:


			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);


			wcscat_s(buff, L"3");

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			break;

		case CMD_BUTTON_4:


			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);


			wcscat_s(buff, L"4");

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			break;

		case CMD_BUTTON_5:


			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);


			wcscat_s(buff, L"5");

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			break;

		case CMD_BUTTON_6:


			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);


			wcscat_s(buff, L"6");

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			break;

		case CMD_BUTTON_7:


			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);


			wcscat_s(buff, L"7");

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			break;


		case CMD_BUTTON_8:


			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);


			wcscat_s(buff, L"8");

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			break;


		case CMD_BUTTON_9:


			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);


			wcscat_s(buff, L"9");

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			break;


		case CMD_BUTTON_CLEAN:

			wcscpy_s(buff, L"");
			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)L"0");


			break;

		case CMD_BUTTON_PLUSMINUS:

			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);

			str = new char[wcslen(buff) + 1];
			str[wcslen(buff) + 1] = '\0';

			for (int i = 0; i < wcslen(buff); i++) {

				str[i] = (char)buff[i];
				
			}

			if (!(std::regex_search(str, std::regex("\\d\\+")))) {

				n = _wtoi(buff);

				if (n != 0) {

					n *= -1;

					_itow_s(n, buff, 10);

					SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);
				}
			}

			break;


		case CMD_BUTTON_PLUS:

			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);

			if (buff[wcslen(buff) - 1] == L"-"[0] || buff[wcslen(buff) - 1] == L"*"[0] || buff[wcslen(buff) - 1] == L"/"[0]) {

				buff[wcslen(buff) - 1] = L"+"[0];
			}
			else if (buff[wcslen(buff) - 1] != L"+"[0]) {

				wcscat_s(buff, L"+");



			}

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);

			break;

		case CMD_BUTTON_MINUS:

			SendMessageW(hwndEDIT, WM_GETTEXT, 0, (LPARAM)buff);
			if (buff[wcslen(buff) - 1] == L"+"[0] || buff[wcslen(buff) - 1] == L"*"[0] || buff[wcslen(buff) - 1] == L"/"[0]) {

				buff[wcslen(buff) - 1] = L"-"[0];
			}
			else if (buff[wcslen(buff) - 1] != L"-"[0]) {

				wcscat_s(buff, L"-");



			}

			SendMessageW(hwndEDIT, WM_SETTEXT, 0, (LPARAM)buff);



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



	hwndSTATIC = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | ES_RIGHT, 20, 30, 360, 23, hWnd, 0, hInstC, 0);
	SendMessage(hwndSTATIC, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));


	hwndEDIT = CreateWindowW(L"Edit", L"0", WS_VISIBLE | WS_CHILD | ES_RIGHT, 20, 60, 360, 23, hWnd, 0, hInstC, 0);
	SendMessage(hwndEDIT, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

	//CreateWindowW(L"Static", L"Your name:", WS_VISIBLE | WS_CHILD, 20, 30, 125, 23, hWnd, NULL, hInstP, NULL);
	//CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE, 20, 60, 125, 23, hWnd, (HMENU)CMD_COMBOBOX, hInst, 0);




	WCHAR  buff[2];

	COORD bPos;
	bPos.X = 50;
	bPos.Y = 200;

	COORD bSize;
	bSize.X = 65;
	bSize.Y = 65;

	COORD bMargin;
	bMargin.X = 2;
	bMargin.Y = 2;

	COORD pos;
	pos.X = 0;
	pos.Y = 0;

	for (int i = 1; i < 10; i++) {

		_itow_s(i, buff, 2, 10);
		hwndBUTTONS[i] = CreateWindowW(L"Button", buff, WS_CHILD | WS_VISIBLE, pos.X * (bSize.X + bMargin.X) + bPos.X, pos.Y * 67 + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)(4000 + i), hInstC, 0);
		SendMessage(hwndBUTTONS[i], WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		pos.X++;
		if (pos.X == 3) {
			pos.X = 0;
			pos.Y++;

		}
	}

	hwndBUTTONS[0] = CreateWindowW(L"Button", L"0", WS_CHILD | WS_VISIBLE, (pos.X + 1) * (bSize.X + bMargin.X) + bPos.X, (pos.Y) * (bSize.Y + bMargin.Y) + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)4000, hInstC, 0);
	SendMessage(hwndBUTTONS[0], WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));



	hwndPLUSMINUS = CreateWindowW(L"Button", L"+/-", WS_CHILD | WS_VISIBLE, (pos.X) * (bSize.X + bMargin.X) + bPos.X, (pos.Y) * (bSize.Y + bMargin.Y) + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)CMD_BUTTON_PLUSMINUS, hInstC, 0);
	SendMessage(hwndPLUSMINUS, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

	hwndDOT = CreateWindowW(L"Button", L".", WS_CHILD | WS_VISIBLE, (pos.X + 2) * (bSize.X + bMargin.X) + bPos.X, (pos.Y) * (bSize.Y + bMargin.Y) + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)CMD_BUTTON_DOT, hInstC, 0);
	SendMessage(hwndDOT, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));



	hwndMULTIPLY = CreateWindowW(L"Button", L"×", WS_CHILD | WS_VISIBLE, (pos.X + 3) * (bSize.X + bMargin.X) + bPos.X, (pos.Y - 3) * (bSize.Y + bMargin.Y) + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)CMD_BUTTON_MULTIPLY, hInstC, 0);
	SendMessage(hwndMULTIPLY, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

	hwndDEVIDE = CreateWindowW(L"Button", L"÷", WS_CHILD | WS_VISIBLE, (pos.X + 3) * (bSize.X + bMargin.X) + bPos.X, (pos.Y - 4) * (bSize.Y + bMargin.Y) + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)CMD_BUTTON_DEVIDE, hInstC, 0);
	SendMessage(hwndDEVIDE, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

	hwndDELETE = CreateWindowW(L"Button", L"DEL", WS_CHILD | WS_VISIBLE, (pos.X + 2) * (bSize.X + bMargin.X) + bPos.X, (pos.Y - 4) * (bSize.Y + bMargin.Y) + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)CMD_BUTTON_DELETE, hInstC, 0);
	SendMessage(hwndDELETE, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

	hwndCLEAN = CreateWindowW(L"Button", L"C", WS_CHILD | WS_VISIBLE, (pos.X + 1) * (bSize.X + bMargin.X) + bPos.X, (pos.Y - 4) * (bSize.Y + bMargin.Y) + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)CMD_BUTTON_CLEAN, hInstC, 0);
	SendMessage(hwndCLEAN, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));


	hwndPLUS = CreateWindowW(L"Button", L"+", WS_CHILD | WS_VISIBLE, (pos.X + 3) * (bSize.X + bMargin.X) + bPos.X, (pos.Y - 1) * (bSize.Y + bMargin.Y) + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)CMD_BUTTON_PLUS, hInstC, 0);
	SendMessage(hwndPLUS, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

	hwndMINUS = CreateWindowW(L"Button", L"-", WS_CHILD | WS_VISIBLE, (pos.X + 3) * (bSize.X + bMargin.X) + bPos.X, (pos.Y - 2) * (bSize.Y + bMargin.Y) + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)CMD_BUTTON_MINUS, hInstC, 0);
	SendMessage(hwndMINUS, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

	hwndEQUALS = CreateWindowW(L"Button", L"=", WS_CHILD | WS_VISIBLE, (pos.X + 3) * (bSize.X + bMargin.X) + bPos.X, (pos.Y) * (bSize.Y + bMargin.Y) + bPos.Y, bSize.X, bSize.Y, hWnd, (HMENU)CMD_BUTTON_EQUALS, hInstC, 0);
	SendMessage(hwndEQUALS, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));




}


