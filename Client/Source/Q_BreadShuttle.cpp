#include "stdafx.h"
#include "Q_BreadShuttle.h"
#include "Client_Events.h"
#include "ItemInfo.h"
Q_BreadShuttle::Q_BreadShuttle()
	: Quest()
{
	EventDispatcher::AddEventListener(GameEvent::BuyItem, "BreadShuttle",
		std::bind(&Q_BreadShuttle::OnBuyItem, this, placeholders::_1));

}

Q_BreadShuttle::~Q_BreadShuttle()
{
	EventDispatcher::RemoveEventListener(GameEvent::BuyItem, "BreadShuttle");
}

void Q_BreadShuttle::OnBuyItem(void * item)
{
	ItemInfo * pItem = static_cast<ItemInfo*>(item);
	if (pItem->itemName.compare(L"체력 포션") == 0)
	{
		m_isBuy = true;
	}
}

float Q_BreadShuttle::GetCurProgress()
{
	return -1;
}

bool Q_BreadShuttle::IsFinish()
{
	return m_isBuy;
}

std::vector<GameObject*> Q_BreadShuttle::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_BreadShuttle::Initialize()
{
	Quest::Initialize
	(
		L"포션의 사용법",
		L"포션을 구매 후 삼손에게 전달하라",
		{
			L"신참, 혹시 포션의 사용법에 대해 알고있나?",
			L"잡화점에서 포션을 구매해오면 사용법에 대해 알려주지"
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
		L"Hieracon_Chitata",
		L"Hieracon_Chitata"
		);
}
