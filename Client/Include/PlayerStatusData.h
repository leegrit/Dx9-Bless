#pragma once
#include "ScriptableData.h"

class PlayerStatusData : public ScriptableData
{
public :
	PlayerStatusData();

	int power;
	int life;
	int intel;
	int dex;
	float critical;
};

