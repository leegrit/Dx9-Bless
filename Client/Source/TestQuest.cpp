#include "stdafx.h"
#include "TestQuest.h"



TestQuest::TestQuest()
	: CombatQuest()
{
	
}


TestQuest::~TestQuest()
{
}

void TestQuest::Initialize(GameObject * pSender)
{


	CombatQuest::Initialize
	(
		L"TestQuest",
		L"���̷����� 3���� óġ",
		{
			L"�޽��� 1",
			L"�޽��� 2",
			L"�޽��� 3"
		},
		{
			L"�Ϸ� �޽��� 1",
			L"�Ϸ� �޽��� 2",
			L"�Ϸ� �޽��� 3"
		},
		{
			L"�˰ڽ�"
		},
		{
			L"�˰ڽ�2"
		},
		EQuestImportance::Main,
		[]() {return true; }, // ÷���� ����
		[]() {}, // ���� ���� 
		pSender,
		pSender, // ���� ���� ������ �޾߾���
		3,
		L"Skeletone"
	);

}
