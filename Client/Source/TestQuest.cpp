#include "stdafx.h"
#include "TestQuest.h"
#include "Client_Events.h"


TestQuest::TestQuest()
	: CombatQuest()
{
	
}


TestQuest::~TestQuest()
{
}

void TestQuest::Initialize(GameObject * pSender)
{

	assert(false);
	//CombatQuest::Initialize
	//(
	//	L"TestQuest",
	//	L"���̷����� 3���� óġ",
	//	{
	//		L"�޽��� 1",
	//		L"�޽��� 2",
	//		L"�޽��� 3"
	//	},
	//	{
	//		L"�Ϸ� �޽��� 1",
	//		L"�Ϸ� �޽��� 2",
	//		L"�Ϸ� �޽��� 3"
	//	},
	//	{
	//		L"�˰ڽ�"
	//	},
	//	{
	//		L"�˰ڽ�2"
	//	},
	//	EQuestImportance::Main,
	//	[]() {return true; }, // ÷���� ����
	//	[]() {}, // ���� ���� 
	//	pSender,
	//	pSender, // ���� ���� ������ �޾߾���
	//	3,
	//	L"Skeletone"
	//);

}

void TestQuest::Initialize()
{
	CombatQuest::Initialize
	(
		L"TestQuest",
		L"���̷����� 3���� óġ",
		{
			L"���̷��� 3���� óġ ��Ź 1",
			L"���̷��� 3���� óġ ��Ź 2",
			L"���̷��� 3���� óġ ��Ź 3",
			L"���̷��� 3���� óġ ��Ź 4",
			L"���̷��� 3���� óġ ��Ź 5"
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
		[]() 
	{
		float exp = 200;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Sire",
		L"Sire",
		3,
		L"Skeletone"
	);
}
