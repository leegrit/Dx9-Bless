#pragma once
#include "Quest.h"

class Q_FirstMission : public Quest
{
public :
	Q_FirstMission();
	virtual ~Q_FirstMission();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual float GetCurProgress() override;
	virtual bool IsFinish() override;
	virtual std::vector<GameObject*> GetTargets() override;
	
public :
	void Initialize();
	
};

