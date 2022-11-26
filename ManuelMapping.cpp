// ManuelMapping.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Injector.h"


DWORD getProcessID(const std::wstring& pProcessName) {
	HANDLE hToolHelper = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0x0);
	PROCESSENTRY32 p32ProcessEntry = { 0 };
	p32ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	if (hToolHelper == NULL) {
		return NULL;
	}

	if (!Process32First(hToolHelper, &p32ProcessEntry)) {
		CloseHandle(hToolHelper);
		return NULL;
	}

	do {
		if (!wcscmp(p32ProcessEntry.szExeFile, pProcessName.c_str())) {
			CloseHandle(hToolHelper);
			return p32ProcessEntry.th32ProcessID;
		}
	} while (Process32Next(hToolHelper, &p32ProcessEntry));

	CloseHandle(hToolHelper);
	return NULL;
}

int main()
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, getProcessID(L"chrome.exe"));

	if (!hProc) {
		std::cout << "Can't find process\n";
		return 1;
	}

	if (ManualMap(hProc, "C:\\Users\\otaka\\Desktop\\DSHack\\ManuelMapping\\x64\\Release\\Dll1.dll")) {
		std::cout << "Mapped Correctly\n";
	}
	else {
		std::cout << "Coudln't map\n";
	}

	CloseHandle(hProc);
}
