#include "stdafx.h"
#include "Q_TalkableGoblin.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "QuestManager.h"


Q_TalkableGoblin::Q_TalkableGoblin()
	: CombatQuest()
{
}


Q_TalkableGoblin::~Q_TalkableGoblin()
{
}

void Q_TalkableGoblin::Initialize()
{
	CombatQuest::Initialize
	(
		L"말하는 고블린",
		L"고블린 족장을 처치하라",
		{
			L"공... 공격하지 말아주세요 ! ",
			L"휴.. 고마워요 \n원래 우리 부족은 이렇게 호전적이지 않았는데",
			L"어느날 족장이 바뀌면서 다들 이상해졌어요", 
			L"도와줄 수 있으신가요?"
		},
		{
			L"고마워요!",
			L"그러고보니 유적에 들어가는 방법을 찾는거같은데",
			L"이 근처에 유적에 들어갈 수 있는 키가 흩어져있어요"
			L"모든 키를 모아 유적지 입구쪽 유물의 모양을 완성시키면 \n들어갈 수 있을거에요"
		},
		{
			L"알았다"
		},
		{
			L"알았다"
		},
		EQuestImportance::Sub,
		[&]() ->bool
	{
		return true;
		GameScene *pScene = static_cast<GameScene*>(SCENE);
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"유물 수집");
		if (pQuest->IsCompletelyFinished() == true)
			return true;
		else
			return false;
	},
		[]()
	{
		float exp = 800;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // 보상 없음 
		L"GoblinNPC",
		L"GoblinNPC",
		1,
		L"HGoblin"
		);
}
