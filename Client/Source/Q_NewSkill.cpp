#include "stdafx.h"
#include "Q_NewSkill.h"
#include "Client_Events.h"
#include "SoundManager.h"
#include "InventoryData.h"
#include "PathManager.h"

Q_NewSkill::Q_NewSkill()
	: Quest()
{
}

Q_NewSkill::~Q_NewSkill()
{
}

float Q_NewSkill::GetCurProgress()
{
	return -1;
}

bool Q_NewSkill::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_NewSkill::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_NewSkill::OnAccept()
{

	ItemInfo item;
	item.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/SkillBook.jpg";
	item.itemName = L"가드 스킬북";
	item.itemType = EItemType::SkillBook;
	item.typeText = L"스킬북";
	item.itemValue = 0; // skill index
	item.effectText = L"읽으면 가드 스킬을 \n획득할 수 있습니다.";
	item.itemDescription = L"읽으면 가드 스킬을 획득할 수 있습니다.";
	item.salePrice = 500;
	


	InventoryData* pInventoryData = static_cast<InventoryData*>(ENGINE->GetScriptableData(L"InventoryData"));
	if (pInventoryData->IsFull())
	{
		EventDispatcher::TriggerEvent(GameEvent::InventoryFull);
		return;
	}

	pInventoryData->PushItem(item);


	EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&item);
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
		L"Hieracon_Deliah",
		L"Hieracon_Deliah"
		);
}
