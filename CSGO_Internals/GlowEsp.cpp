#include "stdafx.h"

#include "SolaireHub2.h"

DWORD GlowObj;

DWORD CID;

int targetTeam;
int hp = 50;

struct GlowStruct
{
	float red = 0.f;
	float green = 1.f;
	float blue = 1.f;
	float alpha = 1.f;
	BYTE Padd[8];
	float buffer3 = 1.f;
	int buffer4 = 0;
	bool on = true;
};
GlowStruct EntGlow;

void GlowEsp::ESP(DWORD Entity)
{
	EntGlow.red = 1.f; EntGlow.green = 1.0f; EntGlow.blue = 0.0f; EntGlow.alpha = 1.f;

	GlowObj = *(DWORD*)(dwClient + dwGlowObjectManager);

		
	if (Entity != NULL)
	{
		hp = *(int*)(Entity + m_iHealth);
		DWORD GlowIndex = *(DWORD*)(Entity + m_iGlowIndex);

		//int dormant = *(int*)(Entity + 0xED);
		/*
		CID = *(DWORD*)(Entity + 0x8);
		CID = *(DWORD*)(CID + 0x8);
		CID = *(DWORD*)(CID + 0x1);
		CID = *(DWORD*)(CID + 0x14);
		*/
		//if (CID == 40)
		//{
				

		if (hp > 0)
		{
			targetTeam = *(int*)(Entity + m_iTeamNum);

			EntGlow.green = (255.0f * (hp/ 100.0f));
			EntGlow.red = (255.0f - EntGlow.green);

			EntGlow.green = EntGlow.green / 255.0f;
			EntGlow.red = EntGlow.red / 255.0f;

			EntGlow.blue = 0;

			if (targetTeam != Player.localTeam)
			{
				*(GlowStruct*)(GlowObj + 0x38 * GlowIndex + 0x4) = EntGlow;
			}
		}
		//}
	}
	
}

