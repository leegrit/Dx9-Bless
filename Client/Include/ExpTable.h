#pragma once
#include "ScriptableData.h"

class ExpTable : public ScriptableData
{
public :
	int expTable[MAX_LEVEL]
	{
		100, // level 1
		300, // level 2
		600,
		1000,
		1500,
		2000,
		2500,
		3000,
		3500,
		4000
	};
};

