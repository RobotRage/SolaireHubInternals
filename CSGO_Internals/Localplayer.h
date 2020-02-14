#pragma once

float aimbotSnap = 1;

class Vector3;
class LocalPlayer
{

private:

	LocalPlayer();
	

public:

	static LocalPlayer* Get();

	Vector3* GetOrigin();
	Vector3* GetViewOffset();
	int* GetHealth();
	int* GetTeam();
	void AimAt(Vector3* target);
	float GetDistance(Vector3*);
	void calcPitchYaw(Vector3* target);
};
