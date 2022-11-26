#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <TlHelp32.h>

using mLoadLibraryA		 = HINSTANCE(WINAPI*)(const char* lpLibFilename);
using f_GetProcAddress = UINT_PTR	(WINAPI*)(HINSTANCE hModule ,const char* lpLibFilename);
using f_DLL_ENTRY_POINT = BOOL		(WINAPI*)(void* hModule, DWORD dwReason, void* pReserrved);

struct MANUAL_MAPPING_DATA {
	mLoadLibraryA    pLoadLibraryA;
	f_GetProcAddress  pGetProcAddress;
	HINSTANCE		 hMod;
};

BOOL ManualMap(HANDLE hProc, const char* szDllFile);