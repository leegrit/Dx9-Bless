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

	assert(false);
	//CombatQuest::Initialize
	//(
	//	L"TestQuest",
	//	L"스켈레톤을 3마리 처치",
	//	{
	//		L"메시지 1",
	//		L"메시지 2",
	//		L"메시지 3"
	//	},
	//	{
	//		L"완료 메시지 1",
	//		L"완료 메시지 2",
	//		L"완료 메시지 3"
	//	},
	//	{
	//		L"알겠슴"
	//	},
	//	{
	//		L"알겠슴2"
	//	},
	//	EQuestImportance::Main,
	//	[]() {return true; }, // 첨부터 오픈
	//	[]() {}, // 보상 없음 
	//	pSender,
	//	pSender, // 보상도 같은 애한테 받야아함
	//	3,
	//	L"Skeletone"
	//);

}

void TestQuest::Initialize()
{
	CombatQuest::Initialize
	(
		L"TestQuest",
		L"스켈레톤을 3마리 처치",
		{
			L"메시지 1",
			L"메시지 2",
			L"메시지 3"
		},
		{
			L"완료 메시지 1",
			L"완료 메시지 2",
			L"완료 메시지 3"
		},
		{
			L"알겠슴"
		},
		{
			L"알겠슴2"
		},
		EQuestImportance::Main,
		[]() {return true; }, // 첨부터 오픈
		[]() {}, // 보상 없음 
		L"Sire",
		L"Sire",
		3,
		L"Skeletone"
	);
}
