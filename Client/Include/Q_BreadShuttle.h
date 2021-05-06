#pragma once
#include "Quest.h"

class Q_BreadShuttle : public Quest
{
public :
	Q_BreadShuttle();
	virtual ~Q_BreadShuttle();


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

