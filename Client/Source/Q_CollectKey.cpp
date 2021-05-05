#include "stdafx.h"
#include "Q_CollectKey.h"
#include "GameScene.h"
#include "QuestManager.h"
#include "Client_Events.h"

Q_CollectKey::Q_CollectKey()
	: CollectQuest()
{
}

Q_CollectKey::~Q_CollectKey()
{
}

void Q_CollectKey::Initialize()
{
	std::vector<int> collectCount={ 1, 1, 1 };
	std::vector<std::wstring > collectNames = { L"TEMP01", L"TEMP02", L"TEMP03" };
	CollectQuest::Initialize
	(
		L"유적 입장",
		L"유적 입장에 필요한 키를 모아라",
		{
			L"유적에 들어가는 방법을 알아냈다고?",
			L"... 그렇군 빨리 키를 모아오도록"
		},
		{
			L"수고했다 \n바로 들어갈테니 준비가 끝나면 따라오도록"
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
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"말하는 고블린");
		if (pQuest->IsCompletelyFinished() == true)
			return true;
		else
			return false;
	},
		[]()
	{
		float exp = 900;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // 보상 없음 
		L"Leoni",
		L"Leoni",
		ECollectType::Multiple,
		collectCount,
		collectNames
		);
}
