#pragma once

void Run();

class Vector3;
class Player
{

private:
	Player();

public:
	static int* GetMaxPlayer();
	static Player* GetPlayer(int index);

	int* GetHealth();
	int* GetTeam();
	int* mbspotted();
	Vector3* GetOrigin();
	Vector3* GetViewOffset();
	Vector3* GetBonePos(int boneID);
	
};
