// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#define DLLEXPORT __declspec(dllexport)

extern "C" {

    char DLLEXPORT Cipher(char c, char p) {

        return c ^ p;

    }

    char DLLEXPORT Decipher(char c, char p) {

        return c ^ p;

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
