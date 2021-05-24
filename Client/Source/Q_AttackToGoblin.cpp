#include "stdafx.h"
#include "Q_AttackToGoblin.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "QuestManager.h"
#include "PathManager.h"
#include "ItemInfo.h"
#include "InventoryData.h"

Q_AttackToGoblin::Q_AttackToGoblin()
	: CombatQuest()
{
}

Q_AttackToGoblin::~Q_AttackToGoblin()
{
}

void Q_AttackToGoblin::OnAccept()
{
	CombatQuest::OnAccept();

	ItemInfo weapon;
	weapon.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/Sword1.png";
	weapon.itemName = L"강철 검";
	weapon.itemType = EItemType::Weapon;
	weapon.typeText = L"무기";
	weapon.effectText = L"물리 공격력 30";
	weapon.atk = 30;
	weapon.salePrice = 1000;
	weapon.wearableLevel = 1;
	weapon.itemDescription = L"강철로된 검이다.";

	ItemInfo upperInfo;
	upperInfo.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/SteelUpper.png";
	upperInfo.itemName = L"강철 갑옷";
	upperInfo.itemType = EItemType::Upper;
	upperInfo.typeText = L"상의";
	upperInfo.effectText = L"물리 방어력 30";
	upperInfo.physicalDef = 30;
	upperInfo.salePrice = 1300;
	upperInfo.wearableLevel = 1;
	upperInfo.itemDescription = L"강철로된 갑옷이다.";

	ItemInfo lower;
	lower.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/SteelGlove.png";
	lower.itemName = L"강철 글러브";
	lower.itemType = EItemType::Glove;
	lower.typeText = L"글러브";
	lower.effectText = L"물리 방어력 25";
	lower.physicalDef = 25;
	lower.salePrice = 800;
	lower.wearableLevel = 1;
	lower.itemDescription = L"강철로된 글러브다.";

	InventoryData* pInventoryData = static_cast<InventoryData*>(ENGINE->GetScriptableData(L"InventoryData"));
	if (pInventoryData->IsFull())
	{
		EventDispatcher::TriggerEvent(GameEvent::InventoryFull);
		return;
	}
	pInventoryData->PushItem(weapon);
	EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&weapon);
	pInventoryData->PushItem(upperInfo);
	EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&upperInfo);
	pInventoryData->PushItem(lower);
	EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&lower);
}

void Q_AttackToGoblin::Initialize()
{
	CombatQuest::Initialize
	(
		L"고블린 퇴치",
		L"고블린 10마리 퇴치",
		{
			L"이곳 고블린은 상당히 호전적이군 \n 병사들을 많이 잃었어\n미안하지만 자네도 같이 싸워줘야겠어",
			L"할 수 있겠나?",
			L"좋아 지금 장비로는 싸우기 힘들테니 장비를 지원해주지"
		},
		{
			L"수고했어 솜씨가 좋군"
		},
		{
			L"알겠습니다"
		},
		{
			L"알겠습닌다"
		},
		EQuestImportance::Main,
		[&]() ->bool
	{
		GameScene *pScene = static_cast<GameScene*>(SCENE);
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"유물 수집");
		if (pQuest->IsCompletelyFinished() == true)
			return true;
		else
			return false;
	},
		[]()
	{
		float exp = 400;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // 보상 없음 
		L"Leoni",
		L"Leoni",
		20,
		L"Goblin"
		);
}
