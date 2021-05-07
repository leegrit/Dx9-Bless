#include "stdafx.h"
#include "PlayerEquipData.h"
#include "EquipmentUI.h"
#include "Client_Enumerators.h"
#include "Client_Events.h"

PlayerEquipData::PlayerEquipData()
{
	equipmentInfos.resize((int)EEquipSlot::MAX);

}

int PlayerEquipData::GetPower()
{
	return equipmentInfos[(int)EEquipSlot::Weapon].atk;
}

int PlayerEquipData::GetPhysicalDef()
{
	float acc = 0;
	for (int i = 0; i < (int)EEquipSlot::MAX; i++)
	{
		acc += equipmentInfos[i].physicalDef;
	}
	return acc;
}

int PlayerEquipData::GetMagicalDef()
{
	float acc = 0;
	for (int i = 0; i < (int)EEquipSlot::MAX; i++)
	{
		acc += equipmentInfos[i].magicalDef;
	}
	return acc;
}

bool PlayerEquipData::IsExistEquipment(EEquipSlot slot)
{
	return equipmentInfos[(int)slot].itemType != EItemType::None;
}

bool PlayerEquipData::CompareEquipment(EEquipSlot slot, ItemInfo item)
{
	if (equipmentInfos[(int)slot].uid == item.uid)
	{
		return true;
	}
	else
		return false;
}

void PlayerEquipData::ChangeEquipment(EEquipSlot slot, ItemInfo item)
{
	equipmentInfos[(int)slot] = item;

	EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, nullptr);
}

void PlayerEquipData::RemoveEquipment(EEquipSlot slot)
{
	equipmentInfos[(int)slot] = ItemInfo();
}

ItemInfo PlayerEquipData::GetEquipment(EEquipSlot slot)
{
	return equipmentInfos[(int)slot];
}
