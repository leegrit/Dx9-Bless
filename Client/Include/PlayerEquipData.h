#pragma once
#include "ScriptableData.h"
#include "ItemInfo.h"
#include "Client_Enumerators.h"

class PlayerEquipData : public ScriptableData
{
public: 
	PlayerEquipData();
	int GetPower();
	int GetPhysicalDef();
	int GetMagicalDef();
	bool IsExistEquipment(EEquipSlot slot);
	bool CompareEquipment(EEquipSlot slot, ItemInfo item);
	void ChangeEquipment(EEquipSlot slot, ItemInfo item);
	void RemoveEquipment(EEquipSlot slot);
	ItemInfo GetEquipment(EEquipSlot slot);

private :
	std::vector<ItemInfo> equipmentInfos;
};

