
#include "stdafx.h"
#include "SolaireHub2.h"

Radar radar;
Chams chams;
GlowEsp glowEsp;

void CommonMethods::shoot()
{
	//force attack
	*(int*)(dwClient + dwForceAttack) = 5;
	Sleep(20);
	*(int*)(dwClient + dwForceAttack) = 4;
}

void CommonMethods::entityListLoop()
{	
	Player.localTeam = *(int*)(Player.CBase + 0xF4);
	for (int i = 0; i < 64; i++)
	{	
		EntityList = *(DWORD*)(dwClient + dwEntityList + ((i - 1) * 16));

		if (EntityList)
		{
			if (Active.radar)
			{
				radar.radarSpotted(EntityList);
			}
			if (Active.chams)
			{
				int team = *(int*)(EntityList + m_iTeamNum);
				int hp = *(int*)(EntityList + m_iHealth);
				chams.chams(EntityList, team, hp);
			}
		}

		EntityGlow = *(DWORD*)(dwClient + dwEntityList + i * 0x10);
		if (EntityGlow)
		{
			if (Active.glowEsp)
			{
				glowEsp.ESP(EntityGlow);
			}
		}
	}
}