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

void bHop() {
   BYTE m_fFlags = readMem(var.localPlayer + Offsets.m_fFlags);
   
   
       if (GetAsyncKeyState(VK_SPACE) && m_fFlags & (1 << 0))
           writeMem(var.moduleBase + Offsets.dwForceJump, 6);
   
}

void radar() {
    for (int i = 0; i < 64; i++) {
        DWORD entity = readMem(var.moduleBase + Offsets.dwEntityList + (i * 0x10));
        if (entity != NULL) {
            writeMem(entity + Offsets.m_bSpotted, TRUE);
        }
    }
}

void glow() {
    float a = 2;
    float b = 0;
    float c = 0;
    float d = 0.5;
    DWORD glowManager = readMem(var.moduleBase + Offsets.dwGlowObjectManager);
    int myTeam = readMem(var.localPlayer + Offsets.m_iTeamNum);
    for (int i = 0; i < 64; i++) {
        DWORD entity = readMem(var.moduleBase + Offsets.dwEntityList + (i * 0x10));
        if (entity != NULL) {
            int entityTeam = readMem(entity + Offsets.m_iTeamNum);
            int glowIndex = readMem(entity + Offsets.m_iGlowIndex);

            if (myTeam != entityTeam) {
                writeMem(glowManager + ((glowIndex * 0x38) + 0x4), a);
                writeMem(glowManager + ((glowIndex * 0x38) + 0x8), b);
                writeMem(glowManager + ((glowIndex * 0x38) + 0xc), c);
                writeMem(glowManager + ((glowIndex * 0x38) + 0x10), d);

                
            }
            writeMem(glowManager + ((glowIndex * 0x38) + 0x24), true);
            writeMem(glowManager + ((glowIndex * 0x38) + 0x25), false);
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
        while(var.localPlayer == NULL)
            var.localPlayer = readMem(var.moduleBase + Offsets.dwLocalPlayer);

    std::cout << "F1 - BUNNYHOP\n";
    std::cout << "F2 - RADAR\n";
    std::cout << "F3 - GLOW\n";
    std::cout << "HOLD ALT - TRIGGER\n";
    
    //bools to toggle shit on and off
    bool doBHop = false;
    bool doRadar = false;
    bool doGlow = false;

    while (true) {
        //toggles shit on and off

        if (GetAsyncKeyState(VK_MENU)) 
            triggerBot();
        if (GetAsyncKeyState(VK_F1)) {
            doBHop = !doBHop;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_F2)) {
            doRadar = !doRadar;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_F3)) {
            doGlow = !doGlow;
            Sleep(100);
        }
        if (doBHop == true)
            bHop();
        if (doRadar)
            radar();
        if (doGlow)
            glow();
    }

   
   
}




