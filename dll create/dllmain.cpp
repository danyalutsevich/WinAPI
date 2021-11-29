// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define DLLEXPORT __declspec(dllexport)


extern "C" {


	DLLEXPORT long sqr(long x) {

		return x * x;

	}

	DLLEXPORT long cube(long x) {

		return x * x * x;

	}

	DLLEXPORT long plus(long a, long b) {

		return a + b;

	}

	DLLEXPORT wchar_t* dectosix(wchar_t* str) {

		int x=_wtoi(str);

		wchar_t buff[100];

		_itow_s(x,buff,16);

		return buff;
	}


}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

