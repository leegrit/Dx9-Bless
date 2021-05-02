#pragma once
#include "CombatQuest.h"

class TestQuest : public CombatQuest
{
public:
	TestQuest();
	virtual ~TestQuest();

public:
	void Initialize(GameObject* pSender);
	void Initialize();
};

