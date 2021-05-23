#pragma once
#include "ScriptableData.h"
using namespace HyEngine;
class PlayerSkillInfo : public ScriptableData
{
public :
	bool isLock[20] = { true, true, true, true, true,  true, true, true, true, true, };
	//bool isFirstLock = true; // shield
	//bool isSecondLock = true; // swing
	//bool isThirdLock = true; // stab
	//bool isFourthLock = true; // tornado
	//bool isFifthLock = true; // buff

};

