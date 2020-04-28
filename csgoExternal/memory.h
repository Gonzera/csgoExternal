#include "includes.h"

DWORD readMem(DWORD addr);
DWORD writeMem(uintptr_t addr, DWORD x);

DWORD getProcId(const wchar_t* procName);
uintptr_t GetModuleBaseAdress(DWORD procId, const wchar_t* modName);
DWORD getAddres(HANDLE hProc, DWORD addr, std::vector<DWORD> vect);
