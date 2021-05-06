#pragma once
#include "Quest.h"

class Q_FirstEquipment : public Quest
{
public :
	Q_FirstEquipment();
	virtual ~Q_FirstEquipment();


	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual float GetCurProgress() override;
	virtual bool IsFinish() override;
	virtual std::vector<GameObject*> GetTargets() override;

public:
	void Initialize();
};

