#include "stdafx.h"
#include "SolaireHub2.h"

void Chams::chams(DWORD chamsEntList, int team, int hp)
{
	struct GlowStruct
	{
		float red = 0.36f;
		float green = 0.63999f;
		float blue = 0.0f;
		float alpha = 1.f;
		BYTE Padd[8];
		float buffer3 = 1.f;
		int buffer4 = 0;
		bool on = true;
	};
	GlowStruct EntGlow;

	BYTE Green[4] = { 255, 0, 0, 255 };
	unsigned char* green = Green;
	if (Player.localTeam != team)
	{
		*(GlowStruct*)(chamsEntList + 0x70) = EntGlow;
	}
	else
	{
		*(unsigned char**)(chamsEntList + 0x70) = green;
	}
}