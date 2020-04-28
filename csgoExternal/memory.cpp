#include "includes.h"

HANDLE hProc = NULL;

DWORD readMem(DWORD addr)
{
	DWORD x;
	ReadProcessMemory(hProc, (BYTE*)addr, &x, sizeof(x), nullptr);
	return x;
}




DWORD writeMem(uintptr_t addr, DWORD x)
{
	WriteProcessMemory(hProc, (BYTE*)addr, &x, sizeof(x), nullptr);
	return 0;
}


DWORD getProcId(const wchar_t* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, procId);

	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					hProc = OpenProcess(PROCESS_ALL_ACCESS, false, procId);
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
		CloseHandle(hSnap);
		return procId;
	}
}

uintptr_t GetModuleBaseAdress(DWORD procId, const wchar_t* modName) {
	uintptr_t ModBaseAdress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					ModBaseAdress = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
		CloseHandle(hSnap);
		return ModBaseAdress;
	}

}

DWORD getAddres(HANDLE hProc, DWORD addr, std::vector<DWORD> vect)
{
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += vect[i];
	}
	return addr;
}
