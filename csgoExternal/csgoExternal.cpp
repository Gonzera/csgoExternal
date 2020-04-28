#include "includes.h"
#include "memory.h"
#include "Offsets.h"

/*struct OffsetsStruc
{
    std::vector<DWORD> ammo = { 0x374, 0x14, 0x0 };
}Offsets;*/

struct variables
{
    DWORD localPlayer;
    DWORD moduleBase;

}var;

void triggerBot()
{
    DWORD crosshairId;
    int attackFlag;
    int team;
    int health;
    int myTeam;
    uintptr_t ForceAttchPtr = var.moduleBase + Offsets.dwForceAttack;
    crosshairId = readMem(var.localPlayer + Offsets.m_iCrosshairId);
  

    if (crosshairId > 0 && crosshairId < 64) {
        DWORD entity = readMem(var.moduleBase + Offsets.dwEntityList + ((crosshairId - 1) * 0x10));
        int team = readMem(entity + Offsets.m_iTeamNum);
        int health = readMem(entity + Offsets.m_iHealth);
        int myTeam = readMem(var.localPlayer + Offsets.m_iTeamNum);
        if (team != myTeam) {
            writeMem(ForceAttchPtr, 6);
        }
        
    }
   

}

int main()
{
    DWORD procId = 0;
    procId = getProcId(L"csgo.exe");

    var.moduleBase = GetModuleBaseAdress(procId, L"client_panorama.dll");
    uintptr_t localPlayerAddrPtr = var.moduleBase + Offsets.dwLocalPlayer;
    if(var.localPlayer == NULL)
        var.localPlayer = readMem(var.moduleBase + Offsets.dwLocalPlayer);

    std::cout << "F1 - GLOW\n";
    std::cout << "HOLD ALT - TRIGGER\n";
    


    while (true) {
        if (GetAsyncKeyState(VK_MENU)) 
            triggerBot();


      
            
        
    }

   
   
}




