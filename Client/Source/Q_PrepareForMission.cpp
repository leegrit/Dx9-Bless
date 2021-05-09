#include "stdafx.h"
#include "Q_PrepareForMission.h"
#include "Client_Events.h"
Q_PrepareForMission::Q_PrepareForMission()
	: Quest()
{
}

Q_PrepareForMission::~Q_PrepareForMission()
{
}

float Q_PrepareForMission::GetCurProgress()
{
	return 1;
}

bool Q_PrepareForMission::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_PrepareForMission::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_PrepareForMission::Initialize()
{
	Quest::Initialize
	(
		L"임무를 위한 준비",
		L"레벨3을 달성하시오",
		{
			L"히에라콘에 온걸 환영해 신참",
			L"마침 잘왔어 지금 아르바 정글에서 고전중이라고 하는군",
			L"어서 준비를 마치고 다시 말걸도록"
		},
		{
			L"좋아 출발하지"
		},
		{
			L"알겠습니다."
		},
		{
			L"알겠습니다"
		},
		EQuestImportance::Main,
		[]() {return true; }, // 첨부터 오픈
		[]()
	{
		float exp = 200;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // 보상 없음 
		L"Hieracon_Leoni",
		L"Hieracon_Leoni"
		);
}
