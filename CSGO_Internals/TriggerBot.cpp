
#include "stdafx.h"
#include "SolaireHub2.h"

	CommonMethods commonMethods;

	void Trigger::toggleTriggerOff()
	{
		//force block attack 1
		*(int*)(dwClient + dwForceAttack) = 4;
	}

	void Trigger::triggerBot()
	{
		//if there is an object in the crosshair
		//and is the player active
		if (Player.crossHair > 0 && Player.CBase > 0)
		{
			//some local vars for object checks
			DWORD target;
			int targetTeam;

			//get the object in the crosshair
			target = *(DWORD*)(dwClient + dwEntityList + ((Player.crossHair - 1) * 0x10));

			//check if the target is valid
			if (target)
			{
				//check the target's team
				targetTeam = *(int*)(target + m_iTeamNum);

				//check the local player team
				

				//if you are aiming at an enemy
				if ((targetTeam != Player.localTeam) && targetTeam > 1 && targetTeam < 4)
				{
					commonMethods.shoot();
				}

				//if you are aiming at your team, dont shoot
				if (targetTeam == Player.localTeam)
				{
					toggleTriggerOff();
				}
			}
		}
	}


