
#include "stdafx.h"
#include "Adresses.h"

#include "LocalPlayer.h"
#include "Player.h"
#include "Vector3.h"

#include <Windows.h>
#include <cstdint>

#include <math.h>

Player* Player::GetPlayer(int index)
{
	static uint32_t moduleBase = (uint32_t)GetModuleHandle("client_panorama.dll");
	static uint32_t entityList = moduleBase + hazedumper::signatures::dwEntityList;

	return (Player*)(entityList + index * 0x10);
}

int* Player::GetMaxPlayer()
{
	static uint32_t moduleBase = (uintptr_t)GetModuleHandle("engine.dll");
	return (int*)(*(uint32_t*)(moduleBase + hazedumper::signatures::dwClientState) + hazedumper::signatures::dwClientState_MaxPlayer);
}

Vector3* Player::GetOrigin()
{
	return (Vector3*)(*(uintptr_t*)this + hazedumper::netvars::m_vecOrigin);
}

Vector3* Player::GetViewOffset()
{
	return (Vector3*)(*(uintptr_t*)this + hazedumper::netvars::m_vecViewOffset);
}

Vector3* Player::GetBonePos(int boneID)
{
	uint32_t boneMatrix = *(uint32_t*)(*(uint32_t*)this + hazedumper::netvars::m_dwBoneMatrix);
	static Vector3 bonePos;
	bonePos.x = *(float*)(boneMatrix + 0x30 * boneID + 0x0C);
	bonePos.y = *(float*)(boneMatrix + 0x30 * boneID + 0x1C);
	bonePos.z = *(float*)(boneMatrix + 0x30 * boneID + 0x2C);
	return &bonePos;
}

int* Player::GetHealth()
{
	return (int*)(*(uint32_t*)this + hazedumper::netvars::m_iHealth);
}

int* Player::GetTeam()
{
	return (int*)(*(uint32_t*)this + hazedumper::netvars::m_iTeamNum);
}

int* Player::mbspotted()
{
	return (int*)(*(uint32_t*)this + hazedumper::netvars::m_bSpottedByMask);
}

double PI = 3.14159265358;

float pitch;
float yaw;
void LocalPlayer::calcPitchYaw(Vector3* target)
{
	static uint32_t engineModule = (uint32_t)GetModuleHandle("engine.dll");
	static Vector3* viewAngles = (Vector3*)(*(uint32_t*)(engineModule + hazedumper::signatures::dwClientState) + hazedumper::signatures::dwClientState_ViewAngles);

	Vector3 origin = *GetOrigin();
	Vector3 viewOffset = *GetViewOffset();
	Vector3* myPos = &(origin + viewOffset);

	Vector3 deltaVec = { target->x - myPos->x, target->y - myPos->y, target->z - myPos->z };
	float deltaVecLength = sqrt(deltaVec.x * deltaVec.x + deltaVec.y * deltaVec.y + deltaVec.z * deltaVec.z);

	pitch = -asin(deltaVec.z / deltaVecLength) * (180 / PI);
	yaw = atan2(deltaVec.y, deltaVec.x) * (180 / PI);

	yaw = yaw - viewAngles->y;
}

float absolute(float i)
{
	if (i < 0)
	{
		i = i * -1;
	}
	return i;
}

Player* GetClosestEnemy()
{

	LocalPlayer* localPlayer = LocalPlayer::Get();

	float closestDitance = 1000000;
	int closesDistanceIndex = -1;


	float lowestPitch = 99999;
	float lowestYaw = 99999;





	for (int i = 1; i < *Player::GetMaxPlayer(); i++)
	{
		Player* currentPlayer = Player::GetPlayer(i);


		if (!currentPlayer || !(*(uint32_t*)currentPlayer) || (uint32_t)currentPlayer == (uint32_t)localPlayer)
		{
			continue;
		}

		if (*currentPlayer->GetTeam() == *localPlayer->GetTeam())
		{
			continue;
		}

		if (*currentPlayer->GetHealth() < 1 || *localPlayer->GetHealth() < 1)
		{
			continue;
		}
		if (!*currentPlayer->mbspotted())
		{
			continue;
		}
		float currentDistance = localPlayer->GetDistance(currentPlayer->GetOrigin());
		/*
		if (currentDistance < closestDitance)
		{
			closestDitance = currentDistance;
			//closesDistanceIndex = i;
		}
		*/
		LocalPlayer::Get()->calcPitchYaw(currentPlayer->GetBonePos(8));
		if (pitch < lowestPitch)
		{
			lowestPitch = pitch;
		}

		if (absolute(yaw) < absolute(lowestYaw))
		{
			lowestYaw = absolute(yaw);
			closesDistanceIndex = i;
		}
	}

	if (closesDistanceIndex == -1)
	{
		return NULL;
	}
	return Player::GetPlayer(closesDistanceIndex);
}

void Run()
{

	Player* closestEnemy = GetClosestEnemy();

	if (closestEnemy)
	{
		LocalPlayer::Get()->AimAt(closestEnemy->GetBonePos(8));
	}
}