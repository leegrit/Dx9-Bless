#include "stdafx.h"
#include "QuestTable.h"
#include "TestQuest.h"



void QuestTable::Initialize()
{
	/* ���⼭ ����Ʈ �߰� ���� �ѹ��� */
	TestQuest * testQuest = new TestQuest();
	testQuest->Initialize();
	m_quests.push_back(testQuest);



}

void QuestTable::LinkQuests()
{
	/* ���� ����ɶ� �ٽ� ���� �°� �� ������Ʈ ��������ش�. */
	for (auto quest : m_quests)
	{
		quest->LinkObject();
	}
}
