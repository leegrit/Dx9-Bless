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
	item.itemName = L"���� ��ų��";
	item.itemType = EItemType::SkillBook;
	item.typeText = L"��ų��";
	item.itemValue = 0; // skill index
	item.effectText = L"������ ���� ��ų�� \nȹ���� �� �ֽ��ϴ�.";
	item.itemDescription = L"������ ���� ��ų�� ȹ���� �� �ֽ��ϴ�.";
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
		L"���ο� ���� ���",
		L"��� ������ �о��",
		{
			L"���� ����� ���� �ͳ�? \n�� ������� �����̶�� �Ѵ�. ",
			L"�� ���� ����� ���� �ͳ� ����. \n�׷��ٸ� ��� ������ ���� ���� ���� ����",
			L"�׷����� �ʵ� ��� ������ �ϳ� �޾����ٵ�?",
			L"����, �׷� �� ��� ������ �а� �� ���� ����� �������� �� \n������ �ִٸ� ����� �ݹ� ���� �����ž�"
		},
		{
			L"�ο� �� ������ ����� Ȱ���ϸ� ���� ���� ������ ��������"
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
		L"Hieracon_Deliah",
		L"Hieracon_Deliah"
		);
}
