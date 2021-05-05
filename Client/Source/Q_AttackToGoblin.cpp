#include "stdafx.h"
#include "Q_AttackToGoblin.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "QuestManager.h"

Q_AttackToGoblin::Q_AttackToGoblin()
	: CombatQuest()
{
}

Q_AttackToGoblin::~Q_AttackToGoblin()
{
}

void Q_AttackToGoblin::Initialize()
{
	CombatQuest::Initialize
	(
		L"고블린 퇴치",
		L"고블린 10마리 퇴치",
		{
			L"이곳 고블린은 상당히 호전적이군 \n 병사들을 많이 잃었어\n미안하지만 자네도 같이 싸워줘야겠어",
			L"할 수 있겠나?",
			L"좋아 지금 장비로는 싸우기 힘들테니 장비를 지원해주지"
		},
		{
			L"수고했어 솜씨가 좋군"
		},
		{
			L"알겠습니다"
		},
		{
			L"알겠습닌다"
		},
		EQuestImportance::Main,
		[&]() ->bool
	{
		GameScene *pScene = static_cast<GameScene*>(SCENE);
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"유물 수집");
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
		10,
		L"Goblin"
		);
}
