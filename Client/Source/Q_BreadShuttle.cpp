#include "stdafx.h"
#include "Q_BreadShuttle.h"
#include "Client_Events.h"

Q_BreadShuttle::Q_BreadShuttle()
	: Quest()
{
}

Q_BreadShuttle::~Q_BreadShuttle()
{
}

float Q_BreadShuttle::GetCurProgress()
{
	return 1;
}

bool Q_BreadShuttle::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_BreadShuttle::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_BreadShuttle::Initialize()
{
	Quest::Initialize
	(
		L"빵 셔틀",
		L"빵을 구매 후 삼손에게 전달하라",
		{
			L"못보던 얼굴인데 신참인가?",
			L"좋아 심부름 좀 해주면 포션을 나눠주지"
		},
		{
			L"고마워 여기 포션, 위급할 때 도움이 될거야"
		},
		{
			L"알겠습니다."
		},
		{
			L"알겠습니다."
		},
		EQuestImportance::Sub,
		[]() {return true; }, // 첨부터 오픈
		[]()
	{
		float exp = 200;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // 보상 없음 
		L"Samson",
		L"Samson"
		);
}
