#pragma once
#include "CombatQuest.h"
class Q_TalkableGoblin : public CombatQuest
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
public :
	Q_TalkableGoblin();
	virtual ~Q_TalkableGoblin();

public :
	void Initialize();
};

