#pragma once

#include "CombatQuest.h"
class Q_AttackToGoblin : public CombatQuest
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
public :
	Q_AttackToGoblin();
	virtual ~Q_AttackToGoblin();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void OnAccept() override;


public :
	void Initialize();
};

