#include "stdafx.h"
#include "Q_FirstEquipment.h"
#include "Client_Events.h"

Q_FirstEquipment::Q_FirstEquipment()
	: Quest()
{
}

Q_FirstEquipment::~Q_FirstEquipment()
{
}

float Q_FirstEquipment::GetCurProgress()
{
	return 1;
}

bool Q_FirstEquipment::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_FirstEquipment::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_FirstEquipment::Initialize()
{
	Quest::Initialize
	(
		L"첫 장비",
		L"무기점에서 무기를 구매 후 착용하라",
		{
			L"신참 장비가 그게 뭐야?",
			L"무기점가서 장비좀 맞춰야하지 않겠어"
		},
		{
			L"그래 자고로 전투는 장비빨이지"
		},
		{
			L"알겠습니다."
		},
		{
			L"알겠습니다"
		},
		EQuestImportance::Sub,
		[]() {return true; }, // 첨부터 오픈
		[]()
	{
		float exp = 300;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // 보상 없음 
		L"Hieracon_BailanBollwerk",
		L"Hieracon_BailanBollwerk"
		);
}
