#include "stdafx.h"
#include "SolaireHub2.h"


void Bhop::BunnyHops()
{
	//if the player is not in the air, force jump
	if (Player.onAir == 256)
	{
		*(int*)(dwClient + m_dwForceJump) = 4;
	}
	else
	{
		*(int*)(dwClient + m_dwForceJump) = 5;
	}
}