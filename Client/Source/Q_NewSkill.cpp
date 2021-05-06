#include "stdafx.h"
#include "Q_NewSkill.h"
#include "Client_Events.h"

Q_NewSkill::Q_NewSkill()
	: Quest()
{
}

Q_NewSkill::~Q_NewSkill()
{
}

float Q_NewSkill::GetCurProgress()
{
	return 1;
}

bool Q_NewSkill::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_NewSkill::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_NewSkill::Initialize()
{
	Quest::Initialize
	(
		L"새로운 전투 기술",
		L"기술 교본을 읽어라",
		{
			L"전투 기술을 배우고 싶나? \n난 기술교관 엘로이라고 한다. ",
			L"새 전투 기술을 배우고 싶나 보군. \n그렇다면 기술 교본을 통해 배우는 것이 좋아",
			L"그러고보니 너도 기술 교본을 하나 받았을텐데?",
			L"좋아, 그럼 그 기술 교본을 읽고 새 전투 기술을 익히도록 해 \n소질이 있다면 기술은 금방 몸에 익을거야"
		},
		{
			L"싸울 때 적절히 기술을 활용하면 더욱 빠른 전투가 가능하지"
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
		L"Elroy",
		L"Elroy"
		);
}
