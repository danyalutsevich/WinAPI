#pragma once

#include "framework.h"

LRESULT CALLBACK    WndProcPizza(HWND, UINT, WPARAM, LPARAM);

void createPizza(HWND,HDC);
void showWindowPizza(HINSTANCE hInstance, HWND mainWindow);

HINSTANCE hInstP;
BOOL isPizzaReg;

////////////////////////
#define CMD_BUTTON_PIZZA
#define CMD_SIZE50 3000
#define CMD_SIZE40 3001
#define CMD_SIZE30 3002

///////////////////
HWND hwndSIZE50;
HWND hwndSIZE40;
HWND hwndSIZE30;


void showWindowPizza(HINSTANCE hInstance, HWND mainWindow) {

	//Register class;
	//WndProc
	//CreateWindow

	hInstP = hInstance;

	srand(time(0));
	if (!isPizzaReg) {

		WNDCLASSEXW wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.lpfnWndProc = WndProcPizza;
		wcex.hInstance = hInstP;
		wcex.hbrBackground = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))/*((HBRUSH)(COLOR_WINDOW + 1))*/;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.lpszClassName = L"ControlsWindow";

		if (!RegisterClassExW(&wcex)) {
			MessageBoxW(mainWindow, L"Register class error!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		isPizzaReg = TRUE;
	}

	//3
	HWND controlsWindow = CreateWindowW(L"ControlsWindow", L"Pizza", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, mainWindow, NULL, hInst, 0);

	ShowWindow(controlsWindow, SW_NORMAL);

}


LRESULT CALLBACK    WndProcPizza(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message)
	{
	case WM_CREATE:
		createPizza(hWnd,(HDC)wParam);
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		switch (wmId)
		{
		case CMD_SIZE50:

			SendMessageW(hwndSIZE50, BM_SETCHECK, BST_CHECKED, 0);
			SendMessageW(hwndSIZE40, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndSIZE30, BM_SETCHECK, BST_UNCHECKED, 0);


			break;
		case CMD_SIZE40:

			SendMessageW(hwndSIZE50, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndSIZE40, BM_SETCHECK, BST_CHECKED, 0);
			SendMessageW(hwndSIZE30, BM_SETCHECK, BST_UNCHECKED, 0);

			break;
		case CMD_SIZE30:
			
			SendMessageW(hwndSIZE50, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndSIZE40, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessageW(hwndSIZE30, BM_SETCHECK, BST_CHECKED, 0);

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

void createPizza(HWND hWnd,HDC wParam) {



	CreateWindowW(L"Static", L"// \"\"--.._", WS_VISIBLE | WS_CHILD, 520, 30, 110, 23, hWnd, NULL, hInstP, NULL);
	CreateWindowW(L"Static", L"||    (_)  _ \" - ._", WS_VISIBLE | WS_CHILD, 520, 50, 110, 23, hWnd, NULL, hInstP, NULL);
	CreateWindowW(L"Static", L"||      _ (_)       '-.", WS_VISIBLE | WS_CHILD, 520, 70, 110, 23, hWnd, NULL, hInstP, NULL);
	CreateWindowW(L"Static", L"||     (_)     __..-'", WS_VISIBLE | WS_CHILD, 520, 90, 110, 23, hWnd, NULL, hInstP, NULL);
	CreateWindowW(L"Static", L" \\\\__.. --\"\"", WS_VISIBLE | WS_CHILD, 520, 110, 110, 23, hWnd, NULL, hInstP, NULL);

	
	
	CreateWindowW(L"Button", L"Pizza", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 400, 300, hWnd, NULL, hInst, 0);	
	CreateWindowW(L"Static", L"Your name:", WS_VISIBLE | WS_CHILD , 20, 30, 125, 23, hWnd, NULL, hInstP, NULL);
	CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE, 20, 60, 125, 23, hWnd, (HMENU)CMD_COMBOBOX, hInst, 0);

	hwndSIZE50 = CreateWindowW(L"Button", L"50 cm", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 20, 90, 75, 23, hWnd, (HMENU)CMD_SIZE50, hInst, 0);
	hwndSIZE40 = CreateWindowW(L"Button", L"40 cm", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 20, 120, 75, 23, hWnd, (HMENU)CMD_SIZE40, hInst, 0);
	hwndSIZE30 = CreateWindowW(L"Button", L"30 cm", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 20, 150, 75, 23, hWnd, (HMENU)CMD_SIZE30, hInst, 0);



	CreateWindowW(L"Static", L"Choose pizza", WS_VISIBLE | WS_CHILD , 270, 170, 125, 23, hWnd, NULL, hInstP, NULL);
	
	hwndCOMBOBOX = CreateWindowW(L"Combobox", L"Combox", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_HSCROLL | WS_VSCROLL, 270, 200, 125, 150, hWnd, (HMENU)CMD_COMBOBOX, hInstP, 0);
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Neapolitan Pizza");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Chicago Pizza");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Detroit Pizza");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"California Pizza");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Sicilian Pizza");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"St. Louis Pizza");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Greek Pizza");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Hawaii");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Capricciosa");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Calzone");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Balado");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Rendang ");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Satay");
	SendMessageW(hwndCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)L"Uruguay");
	

}


