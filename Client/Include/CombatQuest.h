#pragma once
#include "Quest.h"

class CombatQuest : public Quest
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
public :
	CombatQuest();
	virtual ~CombatQuest();

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC 
	//////////////////////////////////////////////////////////////////////////
public:
	void Initialize
	(
		std::wstring questName,
		std::wstring questContent,
		std::vector<std::wstring> acceptDialogs,
		std::vector<std::wstring> finishDialogs,
		std::wstring playerAcceptDialog,
		std::wstring playerFinishDialog,
		EQuestImportance questImportance,
		std::function<bool()> openCondition,
		std::function<void()> onFinished,
		std::wstring senderName,
		std::wstring rewardProviderName,
		int killCount,
		std::wstring targetName
	);
	
	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual float GetCurProgress() override;
	virtual bool IsFinish() override;
	virtual std::vector<GameObject*> GetTargets() override;
	virtual void LinkObject() override;

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
	void OnKillEnemy(void*);

private :
	// 잡아야하는 몹 개수
	int m_killCount;
	int m_killedCount;
	// 잡아야하는 몹 이름
	std::wstring m_enemyName;

	// target 몹들
	std::vector<GameObject*> m_targets;



};

