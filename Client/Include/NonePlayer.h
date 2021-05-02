#pragma once
#include "Character.h"

namespace HyEngine
{
	class Billboard;
};


class NonePlayer abstract : public Character
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR 
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit NonePlayer(Scene* scene);
	virtual ~NonePlayer();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath)override;
	virtual void QuestInitialize();
	virtual void Update() override;
	virtual void OnCollision(Collider * other) override;
	/*virtual void ShowQuestMark(Quest * pQuest) override;
	virtual void RemoveQuestMark(Quest * pQuest) override;
	virtual void ShowQuestFinishMark(Quest * pQuest) override;
	virtual void RemoveQuestFinishMark(Quest * pQuest) override;*/
	
	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void DoInteract();

	//////////////////////////////////////////////////////////////////////////
	// PROTECTED METHOD
	//////////////////////////////////////////////////////////////////////////
protected :
	void AddQuest(class Quest* pQuest);


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private: 
	float m_interDist = 10; // 상호작용 거리
	std::vector<class Quest*> m_quests;
	std::function<void()> m_onInteractEnd;
	/*HyEngine::Billboard* m_pMainQuestMarker = nullptr;
	HyEngine::Billboard* m_pSubQuestMarker = nullptr;
	HyEngine::Billboard* m_pMainQuestFinishMarker = nullptr;
	HyEngine::Billboard* m_pSubQuestFinishMarker = nullptr;*/

};

