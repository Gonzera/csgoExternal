#pragma once
#include "includes.h"


struct Offsets
{
    DWORD dwLocalPlayer = 0xD2FB84;
    DWORD dwForceAttack = 0x3175088;
    DWORD dwEntityList = 0x4D43AB4;
    DWORD dwForceJump = 0x51ED750;
    DWORD dwGlowObjectManager = 0x528B880;
    DWORD m_iHealth = 0x100;
    DWORD m_iTeamNum = 0xF4;
    DWORD m_iCrosshairId = 0xB3D4;
    DWORD m_fFlags = 0x104;
    DWORD m_bSpotted = 0x93D;
    DWORD m_iGlowIndex = 0xA428;

}Offsets;