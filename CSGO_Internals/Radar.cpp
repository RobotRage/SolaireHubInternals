#include "stdafx.h"
#include "SolaireHub2.h"
CommonMethods cmnMethods;
void Radar::radarSpotted(DWORD radarEntity)
{
	*(DWORD*)(radarEntity + m_bSpotted) = true;	
}