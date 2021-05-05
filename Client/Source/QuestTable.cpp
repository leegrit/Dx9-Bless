#include "stdafx.h"
#include "QuestTable.h"
#include "TestQuest.h"
#include "Q_AttackToGoblin.h"
#include "Q_CollectKey.h"
#include "Q_CollectRelics.h"
#include "Q_FirstMission.h"
#include "Q_TalkableGoblin.h"


void QuestTable::Initialize()
{
	/* 여기서 퀘스트 추가 최초 한번만 */
	TestQuest * testQuest = new TestQuest();
	testQuest->Initialize();
	m_quests.push_back(testQuest);


	Q_AttackToGoblin * pAttackToGoblin = new Q_AttackToGoblin();
	pAttackToGoblin->Initialize();
	m_quests.push_back(pAttackToGoblin);

	Q_CollectKey * pCollectKey = new Q_CollectKey();
	pCollectKey->Initialize();
	m_quests.push_back(pCollectKey);

	Q_FirstMission * pFirstMission = new Q_FirstMission();
	pFirstMission->Initialize();
	m_quests.push_back(pFirstMission);

	Q_TalkableGoblin * pTalkableGoblin = new Q_TalkableGoblin();
	pTalkableGoblin->Initialize();
	m_quests.push_back(pTalkableGoblin);

	Q_CollectRelics * pCollectRelics = new Q_CollectRelics();
	pCollectRelics->Initialize();
	m_quests.push_back(pCollectRelics);


}

void QuestTable::LinkQuests()
{
	/* 씬이 변경될때 다시 씬에 맞게 각 오브젝트 연결시켜준다. */
	for (auto quest : m_quests)
	{
		quest->LinkObject();
	}
}
