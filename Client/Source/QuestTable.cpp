#include "stdafx.h"
#include "QuestTable.h"
#include "TestQuest.h"



void QuestTable::Initialize()
{
	/* 여기서 퀘스트 추가 최초 한번만 */
	TestQuest * testQuest = new TestQuest();
	testQuest->Initialize();
	m_quests.push_back(testQuest);



}

void QuestTable::LinkQuests()
{
	/* 씬이 변경될때 다시 씬에 맞게 각 오브젝트 연결시켜준다. */
	for (auto quest : m_quests)
	{
		quest->LinkObject();
	}
}
