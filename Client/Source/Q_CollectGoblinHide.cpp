#include "stdafx.h"
#include "Q_CollectGoblinHide.h"
#include "Client_Events.h"
#include "ItemInfo.h"
#include "InventoryData.h"
#include "PathManager.h"
Q_CollectGoblinHide::Q_CollectGoblinHide() 
	: Quest()
{
	EventDispatcher::AddEventListener(GameEvent::AddItemToInventory, "Q_CollectGoblinHide",
		std::bind(&Q_CollectGoblinHide::OnCollectItem, this, placeholders::_1));
}

Q_CollectGoblinHide::~Q_CollectGoblinHide()
{
	EventDispatcher::RemoveEventListener(GameEvent::AddItemToInventory, "Q_CollectGoblinHide");
}

void Q_CollectGoblinHide::OnCollectItem(void * item)
{
	ItemInfo* pItem = static_cast<ItemInfo*>(item);
	if (pItem->itemName.compare(L"��� ����") == 0)
	{
		m_curCnt++;
	}
}

float Q_CollectGoblinHide::GetCurProgress()
{
	return (float)m_curCnt / (float)m_goalCnt;
}

bool Q_CollectGoblinHide::IsFinish()
{
	return m_curCnt >= m_goalCnt;
}

std::vector<GameObject*> Q_CollectGoblinHide::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_CollectGoblinHide::Initialize()
{
	Quest::Initialize
	(
		L"��� ����",
		L"��� ���� 10���� ���� �� \nġŸŸ���� �����϶�",
		{
			L"��� ������ ����ָ� ���� ����� �˷�����"
		},
		{
			L"���� �̰� ��ų���̾�."
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

		ItemInfo item;
		item.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/SkillBook.jpg";
		item.itemName = L"�ֵθ��� ��ų��";
		item.itemType = EItemType::SkillBook;
		item.typeText = L"��ų��";
		item.itemValue = 1; // skill index
		item.effectText = L"������ �ֵθ��� ��ų�� \nȹ���� �� �ֽ��ϴ�.";
		item.itemDescription = L"������ �ֵθ��� ��ų�� ȹ���� �� �ֽ��ϴ�.";
		item.salePrice = 500;



		InventoryData* pInventoryData = static_cast<InventoryData*>(ENGINE->GetScriptableData(L"InventoryData"));
		if (pInventoryData->IsFull())
		{
			EventDispatcher::TriggerEvent(GameEvent::InventoryFull);
			return;
		}

		pInventoryData->PushItem(item);


		EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&item);

		float exp = 500;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Jungle_Chitata",
		L"Jungle_Chitata"
		);
}
