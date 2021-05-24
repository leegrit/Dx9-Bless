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
	if (pItem->itemName.compare(L"고블린 가죽") == 0)
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
		L"고블린 가죽",
		L"고블린 가죽 10개를 수집 후 \n치타타에게 전달하라",
		{
			L"고블린 가죽을 모아주면 좋은 기술을 알려주지"
		},
		{
			L"고마워 이건 스킬북이야."
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

		ItemInfo item;
		item.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/SkillBook.jpg";
		item.itemName = L"휘두르기 스킬북";
		item.itemType = EItemType::SkillBook;
		item.typeText = L"스킬북";
		item.itemValue = 1; // skill index
		item.effectText = L"읽으면 휘두르기 스킬을 \n획득할 수 있습니다.";
		item.itemDescription = L"읽으면 휘두르기 스킬을 획득할 수 있습니다.";
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
	}, // 보상 없음 
		L"Jungle_Chitata",
		L"Jungle_Chitata"
		);
}
