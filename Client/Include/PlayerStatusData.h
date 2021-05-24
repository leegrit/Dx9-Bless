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
	int physicalDef;
	int magicalDef;
	float critical;
	float defense; // �ڵ� ���Ȯ��
};

