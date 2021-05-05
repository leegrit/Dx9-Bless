#include "stdafx.h"
#include "CombatQuest.h"
#include "ObjectContainer.h"
#include "Client_Events.h"

CombatQuest::CombatQuest()
	:Quest()
{
	EventDispatcher::AddEventListener(BattleEvent::CharacterDie, "CombatQuest",
		std::bind(&CombatQuest::OnKillEnemy, this, placeholders::_1));
}

CombatQuest::~CombatQuest()
{
	EventDispatcher::RemoveEventListener(BattleEvent::CharacterDie, "CombatQuest");
}

void CombatQuest::Initialize(std::wstring questName, std::wstring questContent, std::vector<std::wstring> acceptDialogs, std::vector<std::wstring> finishDialogs, std::wstring playerAcceptDialog, std::wstring playerFinishDialog, EQuestImportance questImportance, std::function<bool()> openCondition, std::function<void()> onFinished,std::wstring senderName,
	std::wstring rewardProviderName, int killCount, std::wstring targetName)
{
	Quest::Initialize
	(
		questName,
		questContent,
		acceptDialogs,
		finishDialogs,
		playerAcceptDialog,
		playerFinishDialog,
		questImportance,
		openCondition,
		onFinished,
		senderName,
		rewardProviderName
	);
	m_killCount = killCount;
	m_killedCount = 0;
	m_enemyName = targetName;

	
}

float CombatQuest::GetCurProgress()
{
	return m_killedCount / m_killCount;
}

bool CombatQuest::IsFinish()
{
	return m_killedCount >= m_killCount;
}

std::vector<GameObject*> CombatQuest::GetTargets()
{
	return m_targets;
}

void CombatQuest::LinkObject()
{
	Quest::LinkObject();
	SCENE->GetObjectContainer()->TryGetDynamicMeshObjects(m_enemyName, &m_targets);
}

void CombatQuest::OnKillEnemy(void * arg)
{
	GameObject * obj = static_cast<GameObject*>(arg);
	if (m_enemyName.compare(obj->GetName()) == 0)
	{
		m_killedCount++;
	}
}
