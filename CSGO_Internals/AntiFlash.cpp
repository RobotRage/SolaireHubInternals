#include "stdafx.h"
#include "SolaireHub2.h"

void AntiFlash::antiFlash()
{
	*(float*)(Player.CBase + m_flFlashMaxAlpha) = 0.0f;
}