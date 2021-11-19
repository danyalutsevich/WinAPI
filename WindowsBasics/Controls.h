#pragma once


#include "framework.h"


LRESULT CALLBACK    WndProcControls(HWND, UINT, WPARAM, LPARAM);

void createControls(HWND);
void showWindowControls(HINSTANCE hInstance, HWND mainWindow);
//////////////////////

#define CMD_CHECKBOX 2001
#define CMD_PUSHLIKE 2002
#define CMD_RADIOBUTTON1 2003
#define CMD_RADIOBUTTON2 2004
#define CMD_RADIOBUTTON3 2005
#define CMD_RADIOBUTTON4 2006
#define CMD_COMBOBOX 2007
#define CMD_COMBOBOX 2008

//////////////////////

HWND hwndCHECKBOX;
HWND hwndPUSHLIKE;
HWND hwndRADIO1;
HWND hwndRADIO2;
HWND hwndRADIO3;
HWND hwndRADIO4;
HWND hwndCOMBOBOX;
HWND hwndLISTBOX;
HINSTANCE hInst;
BOOL isControlsReg;

void showWindowControls(HINSTANCE hInstance, HWND mainWindow) {

	//Register class;
	//WndProc
	//CreateWindow

	hInst = hInstance;

	srand(time(0));
	if (!isControlsReg) {
	
		WNDCLASSEXW wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.lpfnWndProc = WndProcControls;
		wcex.hInstance = hInst;
		wcex.hbrBackground = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))/*((HBRUSH)(COLOR_WINDOW + 1))*/;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.lpszClassName = L"ControlsWindow";

		if (!RegisterClassExW(&wcex)) {
			MessageBoxW(mainWindow, L"Register class error!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		isControlsReg = TRUE;
	}

	//3
	HWND controlsWindow = CreateWindowW(L"ControlsWindow", L"Controls", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, mainWindow, NULL, hInst, 0);

	ShowWindow(controlsWindow, SW_NORMAL);

}

LRESULT CALLBACK    WndProcControls(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message)
	{
	case WM_CREATE:
		createControls(hWnd);
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		switch (wmId)
		{
		case CMD_CHECKBOX: {

			LRESULT state = SendMessageW(hwndCHECKBOX, BM_GETCHECK, 0, 0);
			if (state == BST_CHECKED) {

				SendMessageW(hwndCHECKBOX, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessageW(hwndCHECKBOX, WM_KILLFOCUS, 0, 0);
				SendMessageW(hwndCHECKBOX, WM_SETTEXT, 0, (LPARAM)L"unchecked");
			}
			else {

				SendMessageW(hwndCHECKBOX, BM_SETCHECK, BST_CHECKED, 0);
				SendMessageW(hwndCHECKBOX, WM_KILLFOCUS, 0, 0);
				SendMessageW(hwndCHECKBOX, WM_SETTEXT, 0, (LPARAM)L"checked");

			}
		}
						 break;
		case CMD_PUSHLIKE: {

			LRESULT state = SendMessageW(hwndPUSHLIKE, BM_GETCHECK, 0, 0);
			if (state == BST_CHECKED) {

				SendMessageW(hwndPUSHLIKE, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessageW(hwndPUSHLIKE, WM_KILLFOCUS, 0, 0);
				SendMessageW(hwndPUSHLIKE, WM_SETTEXT, 0, (LPARAM)L"unchecked");
			}
			else {

				SendMessageW(hwndPUSHLIKE, BM_SETCHECK, BST_CHECKED, 0);
				SendMessageW(hwndPUSHLIKE, WM_KILLFOCUS, 0, 0);
				SendMessageW(hwndPUSHLIKE, WM_SETTEXT, 0, (LPARAM)L"checked");

			}

		}

						 break;

		case CMD_RADIOBUTTON1:


			SendMessageW(hwndRADIO1, BM_SETCHECK, BST_CHECKED, 0);
			SendMessageW(hwndRADIO2, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndRADIO3, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndRADIO4, BM_SETCHECK, BST_UNCHECKED, 0);


			break;

		case CMD_RADIOBUTTON2:

			SendMessageW(hwndRADIO1, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndRADIO2, BM_SETCHECK, BST_CHECKED, 0);
			SendMessageW(hwndRADIO3, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndRADIO4, BM_SETCHECK, BST_UNCHECKED, 0);

			break;
		case CMD_RADIOBUTTON3:
			SendMessageW(hwndRADIO1, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndRADIO2, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndRADIO3, BM_SETCHECK, BST_CHECKED, 0);
			SendMessageW(hwndRADIO4, BM_SETCHECK, BST_UNCHECKED, 0);
			break;
		case CMD_RADIOBUTTON4:
			SendMessageW(hwndRADIO1, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndRADIO2, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndRADIO3, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndRADIO4, BM_SETCHECK, BST_CHECKED, 0);
			break;
		}
		break;
	}
	case WM_DESTROY:
		//PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void createControls(HWND hWnd) {


	CreateWindowW(L"Button", L"Buttons", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 380, 220, hWnd, NULL, hInst, 0);
	CreateWindowW(L"Button", L"Push", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 25, 35, 75, 23, hWnd, NULL, hInst, 0);
	CreateWindowW(L"Button", L"Def", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP, 25, 65, 75, 23, hWnd, NULL, hInst, 0);
	CreateWindowW(L"Button", L"PushLike", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE, 25, 95, 75, 23, hWnd, NULL, hInst, 0);
	hwndCHECKBOX = CreateWindowW(L"Button", L"unchecked", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 25, 125, 75, 23, hWnd, (HMENU)CMD_CHECKBOX, hInst, 0);
	hwndPUSHLIKE = CreateWindowW(L"Button", L"unchecked", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_PUSHLIKE, 25, 155, 75, 23, hWnd, (HMENU)CMD_PUSHLIKE, hInst, 0);
	CreateWindowW(L"Button", L"Right", WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_RIGHTBUTTON, 25, 185, 75, 23, hWnd, NULL, hInst, 0);

	hwndRADIO1 = CreateWindowW(L"Button", L"Radio1", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 130, 35, 75, 23, hWnd, (HMENU)CMD_RADIOBUTTON1, hInst, 0);
	hwndRADIO2 = CreateWindowW(L"Button", L"Radio2", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 130, 65, 75, 23, hWnd, (HMENU)CMD_RADIOBUTTON2, hInst, 0);
	hwndRADIO3 = CreateWindowW(L"Button", L"Radio3", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 130, 95, 75, 23, hWnd, (HMENU)CMD_RADIOBUTTON3, hInst, 0);
	hwndRADIO4 = CreateWindowW(L"Button", L"Radio4", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 130, 125, 75, 23, hWnd, (HMENU)CMD_RADIOBUTTON4, hInst, 0);

	hwndCOMBOBOX = CreateWindowW(L"Combobox", L"Combox", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 130, 155, 75, 75, hWnd, (HMENU)CMD_COMBOBOX, hInst, 0);
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"a");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"b");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"c");

	hwndLISTBOX = CreateWindowW(L"Listbox", L"Combox", WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | WS_HSCROLL | WS_VSCROLL, 230, 35, 75, 75, hWnd, (HMENU)CMD_COMBOBOX, hInst, 0);
	SendMessageW(hwndLISTBOX, LB_ADDSTRING, 0, (LPARAM)L"a");
	SendMessageW(hwndLISTBOX, LB_ADDSTRING, 0, (LPARAM)L"b");
	SendMessageW(hwndLISTBOX, LB_ADDSTRING, 0, (LPARAM)L"c");

	CreateWindowW(L"Edit", L"Combox", WS_CHILD | WS_VISIBLE, 130, 185, 75, 23, hWnd, (HMENU)CMD_COMBOBOX, hInst, 0);



	CreateWindowW(L"Button", L"Pizza", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 500, 10, 380, 220, hWnd, NULL, hInst, 0);

	//CreateWindowW(L"Static", L"Choose pizza", WS_VISIBLE | WS_CHILD | BS_PUSHLIKE, , (480 / 2) - 23 / 2, 75, 23, hWnd, (HMENU)CMD_BUTTON_PLUS, hInst, NULL);




}



