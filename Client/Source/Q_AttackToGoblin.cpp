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
	weapon.itemName = L"��ö ��";
	weapon.itemType = EItemType::Weapon;
	weapon.typeText = L"����";
	weapon.effectText = L"���� ���ݷ� 30";
	weapon.atk = 30;
	weapon.salePrice = 1000;
	weapon.wearableLevel = 1;
	weapon.itemDescription = L"��ö�ε� ���̴�.";

	ItemInfo upperInfo;
	upperInfo.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/SteelUpper.png";
	upperInfo.itemName = L"��ö ����";
	upperInfo.itemType = EItemType::Upper;
	upperInfo.typeText = L"����";
	upperInfo.effectText = L"���� ���� 30";
	upperInfo.physicalDef = 30;
	upperInfo.salePrice = 1300;
	upperInfo.wearableLevel = 1;
	upperInfo.itemDescription = L"��ö�ε� �����̴�.";

	ItemInfo lower;
	lower.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/SteelGlove.png";
	lower.itemName = L"��ö �۷���";
	lower.itemType = EItemType::Glove;
	lower.typeText = L"�۷���";
	lower.effectText = L"���� ���� 25";
	lower.physicalDef = 25;
	lower.salePrice = 800;
	lower.wearableLevel = 1;
	lower.itemDescription = L"��ö�ε� �۷����.";

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
		L"��� ��ġ",
		L"��� 10���� ��ġ",
		{
			L"�̰� ����� ����� ȣ�����̱� \n ������� ���� �Ҿ���\n�̾������� �ڳ׵� ���� �ο���߰ھ�",
			L"�� �� �ְڳ�?",
			L"���� ���� ���δ� �ο�� �����״� ��� ����������"
		},
		{
			L"�����߾� �ؾ��� ����"
		},
		{
			L"�˰ڽ��ϴ�"
		},
		{
			L"�˰ڽ��Ѵ�"
		},
		EQuestImportance::Main,
		[&]() ->bool
	{
		GameScene *pScene = static_cast<GameScene*>(SCENE);
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"���� ����");
		if (pQuest->IsCompletelyFinished() == true)
			return true;
		else
			return false;
	},
		[]()
	{
		float exp = 400;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Leoni",
		L"Leoni",
		20,
		L"Goblin"
		);
}
