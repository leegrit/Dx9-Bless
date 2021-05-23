#include "stdafx.h"
#include "PlayerEquipData.h"
#include "EquipmentUI.h"
#include "Client_Enumerators.h"
#include "Client_Events.h"
#include "SoundManager.h"
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

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->PlaySound("ChangeEquip", L"Wear.wav", desc);
	EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&item);
}

void PlayerEquipData::RemoveEquipment(EEquipSlot slot)
{
	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->PlaySound("RemoveEquipSound", L"EquiFree.wav", desc);
	equipmentInfos[(int)slot] = ItemInfo();
}

ItemInfo PlayerEquipData::GetEquipment(EEquipSlot slot)
{
	return equipmentInfos[(int)slot];
}
