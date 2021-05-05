#include "stdafx.h"
#include "Q_FirstMission.h"
#include "Client_Events.h"

Q_FirstMission::Q_FirstMission()
	:Quest()
{
}

Q_FirstMission::~Q_FirstMission()
{
}

void Q_FirstMission::Initialize()
{
	Quest::Initialize
	(
		L"첫 미션",
		L"코라에게 말을 걸어라",
		{
			L"우리의 임무는 주변 유물, 유적을 모두 탐색하는 것이다.",
			L"일손이 모자르니 당분간 여기서 도와줘야겠다.",
			L"일할 준비가 되면 다시 말하도록"
		},
		{
			L"좋아, 우선 유물을 조사중인 고아르에게 가서 돕도록"
		},
		{
			L"알겠습니다."
		},
		{
			L"아직 준비가 덜되었습니다."
		},
		EQuestImportance::Main,
		[]() {return true; }, // 첨부터 오픈
		[]()
	{
		float exp = 200;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // 보상 없음 
		L"Leoni",
		L"Leoni"
		);
}

float Q_FirstMission::GetCurProgress()
{
	return 1;
}

bool Q_FirstMission::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_FirstMission::GetTargets()
{
	return std::vector<GameObject*>();
}

