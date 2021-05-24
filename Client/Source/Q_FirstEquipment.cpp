#include "stdafx.h"
#include "Q_FirstEquipment.h"
#include "Client_Events.h"
#include "ItemInfo.h"


Q_FirstEquipment::Q_FirstEquipment()
	: Quest()
{
	EventDispatcher::AddEventListener(GameEvent::EquipmentChange, "Q_FirstEquipment",
		std::bind(&Q_FirstEquipment::OnChangedEquipment, this, placeholders::_1));
}

Q_FirstEquipment::~Q_FirstEquipment()
{
	EventDispatcher::RemoveEventListener(GameEvent::EquipmentChange, "Q_FirstEquipment");
}

void Q_FirstEquipment::OnChangedEquipment(void * item)
{
	if (item == nullptr) return;
	ItemInfo * pItemInfo = static_cast<ItemInfo*>(item);
	if (pItemInfo->itemType == EItemType::Weapon)
	{
		m_isEquip = true;
	}
}

float Q_FirstEquipment::GetCurProgress()
{
	return -1;
}

bool Q_FirstEquipment::IsFinish()
{
	return m_isEquip;
}

std::vector<GameObject*> Q_FirstEquipment::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_FirstEquipment::Initialize()
{
	Quest::Initialize
	(
		L"ù ���",
		L"���������� ���⸦ ���� �� \n�����϶�",
		{
			L"���� ��� �װ� ����?",
			L"���������� ����� ��������� �ʰھ�"
		},
		{
			L"�׷� �ڰ�� ������ �������"
		},
		{
			L"�˰ڽ��ϴ�."
		},
		{
			L"�˰ڽ��ϴ�"
		},
		EQuestImportance::Sub,
		[]() {return true; }, // ÷���� ����
		[]()
	{
		float exp = 300;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Hieracon_BailanBollwerk",
		L"Hieracon_BailanBollwerk"
		);
}
