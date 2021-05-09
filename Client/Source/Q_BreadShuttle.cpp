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
	if (pItem->itemName.compare(L"ü�� ����") == 0)
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
		L"������ ����",
		L"������ ���� �� ��տ��� �����϶�",
		{
			L"����, Ȥ�� ������ ������ ���� �˰��ֳ�?",
			L"��ȭ������ ������ �����ؿ��� ������ ���� �˷�����"
		},
		{
			L"���� ���� ����, ������ �� ������ �ɰž�"
		},
		{
			L"�˰ڽ��ϴ�."
		},
		{
			L"�˰ڽ��ϴ�."
		},
		EQuestImportance::Sub,
		[]() {return true; }, // ÷���� ����
		[]()
	{
		float exp = 200;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Hieracon_Chitata",
		L"Hieracon_Chitata"
		);
}
