#include <cmath>
#include <stdio.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <iostream>
#include "MemMan.h"
#include "csgo.hpp"


#define KeyDOWN -32768
#define KeyUP 0


using namespace std;

MemMan MemClass;

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;


/*
struct offsets
{
	DWORD localPlayer = 0xD8B2DC; // localPlayer
	DWORD forceLMB = 0x31D446C; // dwForceAttack
	DWORD entityList = 0x4DA2F24; // dwEntityList
	DWORD crosshair = 0xB3E4; // m_iCrosshairId
	DWORD team = 0xF4; // m_iTeamNum
	DWORD health = 0x100; // m_iHealth
	DWORD vectorOrigin = 0x138; // m_vecOrigin
	DWORD itemDefIndex = 0x2FAA; // m_iItemDefinitionIndex
	DWORD activeWeapon = 0x2EF8; // m_hActiveWeapon
	DWORD isScoped = 0x3928; // m_bIsScoped
	} offset; */

//working
struct offsets
{
	DWORD localPlayer = 0xD8B2DC; // 
	DWORD dwForceAttack = 0x31D446C; // 
	DWORD dwEntityList = 0x4DA2F24; // 
	DWORD m_iCrosshairId = 0xB3E4; // 
	DWORD m_iTeamNum = 0xF4; // 
	DWORD m_iHealth = 0x100; // 
	DWORD m_vecOrigin = 0x138; // 
	DWORD m_iItemDefinitionIndex = 0x2FAA; // 
	DWORD m_hActiveWeapon = 0x2EF8; // 
	DWORD m_bIsScoped = 0x3928; // 
} offset;




/*struct offsets
{
	DWORD localPlayer;
	DWORD dwForceAttack;
	DWORD dwEntityList;
	DWORD m_iCrosshairId;
	DWORD m_iTeamNum;
	DWORD m_iHealth;
	DWORD m_vecOrigin;
	DWORD m_iItemDefinitionIndex;
	DWORD m_hActiveWeapon;
	DWORD m_bIsScoped;
} offset;
*/

struct variables
{
	DWORD localPlayer;
	DWORD gameModule;
	int myTeam;
	int tbDelay;
	int myWeaponID;
	} val;

struct vec
{
	float x, y, z;
};

bool checkIfScoped()
{
	return MemClass.readMem<bool>(val.localPlayer + offset.m_bIsScoped);
}

void setTBDelay(float distance)
{
	float delay;
	switch (val.myWeaponID)
	{
	case 262204: delay = 3; break;
	case 7: delay = 3.3; break;
	case 40: delay = 0.15; break;
	case 9: delay = 0.15; break;
	default: delay = 0;
	}
	val.tbDelay = delay * distance;
}

void getMyWeapon()
{
	int weapon = MemClass.readMem<int>(val.localPlayer + offset.m_hActiveWeapon);
	int weaponEntity = MemClass.readMem<int>(val.gameModule + offset.dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);
	if (weaponEntity != NULL)
		val.myWeaponID = MemClass.readMem<int>(weaponEntity + offset.m_iItemDefinitionIndex);
}

float getDistance(DWORD entity)
{
	vec myLocation = MemClass.readMem<vec>(val.localPlayer + offset.m_vecOrigin);
	vec enemyLocation = MemClass.readMem<vec>(entity + offset.m_vecOrigin);

	return sqrt(pow(myLocation.x - enemyLocation.x, 2) + pow(myLocation.y - enemyLocation.y, 2) + pow(myLocation.z - enemyLocation.z, 2)) * 0.0254;
}

void shoot()
{
	Sleep(val.tbDelay);
	MemClass.writeMem<int>(val.gameModule + offset.dwForceAttack, 5);
	Sleep(20);
	MemClass.writeMem<int>(val.gameModule + offset.dwForceAttack, 4);
}

bool canTBot = false, keyHeld = false;

bool checkTBot()
{
	int crosshair = MemClass.readMem<int>(val.localPlayer + offset.m_iCrosshairId);
	if (crosshair != 0 && crosshair < 64)
	{
		DWORD entity = MemClass.readMem<DWORD>(val.gameModule + offset.dwEntityList + ((crosshair - 1) * 0x10));
		int eTeam = MemClass.readMem<int>(entity + offset.m_iTeamNum);
		int eHealth = MemClass.readMem<int>(entity + offset.m_iHealth);
		if (eTeam != val.myTeam && eHealth > 0)
		{
			float distance = getDistance(entity);
			getMyWeapon();
			setTBDelay(distance);
			if (val.myWeaponID == 40 || val.myWeaponID == 9)
				return checkIfScoped();
			else
				return true;
		}
		else
			return false;
	}
	else
		return false;
}

void handleTBot()
{
	if (checkTBot())
		shoot();
}

void triggerBot() {
	val.myTeam = MemClass.readMem<int>(val.localPlayer + offset.m_iTeamNum);
	canTBot = !canTBot;
	std::cout << "Trigger bot activated" << std::endl;
};


int main()
{
	int proc = MemClass.getProcess("csgo.exe");

	val.gameModule = MemClass.getModule(proc, "client.dll");
	val.localPlayer = MemClass.readMem<DWORD>(val.gameModule + offset.localPlayer);

	if (val.localPlayer == NULL)
		while (val.localPlayer == NULL)
			val.localPlayer = MemClass.readMem<DWORD>(val.gameModule + offset.localPlayer);

	while (true)
	{
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			triggerBot();
		}
		
		if (GetAsyncKeyState(VK_XBUTTON1) == KeyDOWN && !keyHeld)
		{
			keyHeld = true;
			canTBot = true;
			// std::cout << "held" << std::endl;
		}

		if (GetAsyncKeyState(VK_XBUTTON1) == KeyUP && keyHeld)
		{
			keyHeld = false;
			canTBot = false;
			//std::cout << "release" << std::endl;
		}

		if (canTBot)
			handleTBot();

		else std::cout << "Trigger bot deactivated" << std::endl;
		Sleep(1);
	}
	return 0;
}