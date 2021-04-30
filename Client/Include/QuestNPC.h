#pragma once
#include "NonePlayer.h"


class QuestNPC : public NonePlayer
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit QuestNPC(Scene* pScene);
	virtual ~QuestNPC();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath) override;
	virtual void Update() override;
	virtual void OnCollision(Collider * other) override;

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private : /* For Quest */
	int m_questCount;


	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static QuestNPC * Create(Scene* pScene, std::wstring dataPath);

};

