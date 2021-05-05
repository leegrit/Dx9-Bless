#include "stdafx.h"
#include "Q_CollectRelics.h"
#include "GameScene.h"
#include "QuestManager.h"
#include "Client_Events.h"
Q_CollectRelics::Q_CollectRelics()
	: CollectQuest()
{
}

Q_CollectRelics::~Q_CollectRelics()
{
}

void Q_CollectRelics::Initialize()
{
	std::vector<int> collectCount = {1, 1};
	std::vector<std::wstring> collectNames = { L"Statue01", L"Statue02" };
	CollectQuest::Initialize
	(
		L"유물 수집",
		L"흩어진 유물을 수집하라",
		{
			L"아 오셨군요 \n 마침 일손이 필요하던 참입니다.",
			L"이 근처 유물들을 수집하여 저에게 갖다주십시오"
		},
		{
			L"감사합니다",
			L"아까 코라가 급하게 찾는거같던데 한번 가보십쇼"
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
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"첫 미션");
		if (pQuest->IsCompletelyFinished() == true)
			return true;
		else
			return false;
	}, 
		[]()
	{
		float exp = 300;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // 보상 없음 
		L"Guido",
		L"Guido",
		ECollectType::Multiple,
		collectCount,
		collectNames
		);
}
