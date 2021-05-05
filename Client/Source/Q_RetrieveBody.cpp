#include "stdafx.h"
#include "Q_RetrieveBody.h"
#include "GameScene.h"
#include "QuestManager.h"
#include "Client_Events.h"

Q_RetrieveBody::Q_RetrieveBody()
	: CollectQuest()
{
}


Q_RetrieveBody::~Q_RetrieveBody()
{
}

void Q_RetrieveBody::Initialize()
{
	std::vector<int> collectCount = { 5 };
	std::vector<std::wstring> collectNames = {L"Dead_Soldier"};
	CollectQuest::Initialize
	(
		L"시체 회수",
		L"아직 회수되지 못한 병사의 시체를 회수하라",
		{
			L"이번 임무에서 생각보다 피해가 컸군",
			L"아직 회수되지 못한 시체를 회수해주게"
		},
		{
			L"고맙군"
		},
		{
			L"알겠습니다."
		},
		{
			L"알겠습니다."
		},
		EQuestImportance::Main,
		[&]() ->bool
	{
		GameScene *pScene = static_cast<GameScene*>(SCENE);
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"고블린 퇴치");
		if (pQuest->IsCompletelyFinished() == true)
			return true;
		else
			return false;
	},
		[]()
	{
		float exp = 400;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // 보상 없음 
		L"Leoni",
		L"Leoni",
		ECollectType::Single,
		collectCount,
		collectNames
		);
}
