#pragma once
#include "Adresses.h"
#include "Windows.h"
//#include "Hack.h"
#include "Localplayer.h"

//struct of all active cheats

//get the dll
DWORD dwClient = (DWORD)GetModuleHandle("client_panorama.dll");

//offsets
DWORD m_dwLocalPlayer = hazedumper::signatures::dwLocalPlayer;
DWORD m_dwForceJump = hazedumper::signatures::dwForceJump;
DWORD dwForceAttack = hazedumper::signatures::dwForceAttack;
DWORD dwEntityList = hazedumper::signatures::dwEntityList;
DWORD dwGlowObjectManager = hazedumper::signatures::dwGlowObjectManager; 

DWORD m_onAir = hazedumper::netvars::m_fFlags;
DWORD m_iCrosshairId = hazedumper::netvars::m_iCrosshairId;
DWORD m_iHealth = hazedumper::netvars::m_iHealth;
DWORD m_bSpotted = hazedumper::netvars::m_bSpotted;
DWORD m_flFlashMaxAlpha = hazedumper::netvars::m_flFlashMaxAlpha;
DWORD m_iTeamNum = hazedumper::netvars::m_iTeamNum;
DWORD m_iGlowIndex = hazedumper::netvars::m_iGlowIndex;

struct ActiveCheats
{
	public:
		bool Bhop;
		bool togBhop;
		bool Trigger;
		bool glowEsp;
		bool radar;
		bool antiFlash;
		bool chams;
		bool aimBot; //todo: make

}Active;

struct MyPlayer
{
	public:
		DWORD CBase;
		int onAir;
		int crossHair;
		int localTeam;
}Player;

class Aimbot
{
public:
	void aimbot();
};

class Trigger
{
	void toggleTriggerOff();
public:
	void triggerBot();
};

class Bhop
{
public:
	void BunnyHops();
};

class GlowEsp
{
public:
	void ESP(DWORD Entity);
};

class Radar
{
public:	
	void radarSpotted(DWORD radarEntity);
};

class AntiFlash
{
public:
	void antiFlash();
};

class Chams
{
public:
	void chams(DWORD chamsEntList,int team, int hp);
};

class CommonMethods
{
private:
	DWORD EntityList;
	DWORD EntityGlow;
public:
	void shoot();
	void entityListLoop();
};