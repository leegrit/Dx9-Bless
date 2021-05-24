#include "stdafx.h"
#include "QuestTable.h"
#include "TestQuest.h"
#include "Q_AttackToGoblin.h"
#include "Q_CollectKey.h"
#include "Q_CollectRelics.h"
#include "Q_FirstMission.h"
#include "Q_TalkableGoblin.h"
#include "Q_BreadShuttle.h"
#include "Q_FirstEquipment.h"
#include "Q_NewSkill.h"
#include "Q_PrepareForMission.h"
#include "Q_CollectGoblinHide.h"


void QuestTable::Initialize()
{
	/* ���⼭ ����Ʈ �߰� ���� �ѹ��� */
	TestQuest * testQuest = new TestQuest();
	testQuest->Initialize();
	m_quests.push_back(testQuest);

	//////////////////////////////////////////////////////////////////////////
	// FOR HIERACON 
	//////////////////////////////////////////////////////////////////////////
	Q_BreadShuttle * pBreadShuttle = new Q_BreadShuttle();
	pBreadShuttle->Initialize();
	m_quests.push_back(pBreadShuttle);

	Q_FirstEquipment * pFirstEquipment = new Q_FirstEquipment();
	pFirstEquipment->Initialize();
	m_quests.push_back(pFirstEquipment);

	Q_NewSkill * pNewSkill = new Q_NewSkill();
	pNewSkill->Initialize();
	m_quests.push_back(pNewSkill);

	Q_PrepareForMission * pPrepareForMission = new Q_PrepareForMission();
	pPrepareForMission->Initialize();
	m_quests.push_back(pPrepareForMission);


	//////////////////////////////////////////////////////////////////////////
	// FOR ArbaJungle
	//////////////////////////////////////////////////////////////////////////
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

	Q_CollectGoblinHide * pCollectGoblinHide = new Q_CollectGoblinHide();
	pCollectGoblinHide->Initialize();
	m_quests.push_back(pCollectGoblinHide);
 
}

void QuestTable::LinkQuests()
{
	/* ���� ����ɶ� �ٽ� ���� �°� �� ������Ʈ ��������ش�. */
	for (auto quest : m_quests)
	{
		quest->LinkObject();
	}
}
