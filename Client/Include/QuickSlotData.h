#pragma once
#include "ScriptableData.h"
#include "ItemInfo.h"

class QuickSlotData : public ScriptableData
{
public:
	QuickSlotData();

	bool PushItem(ItemInfo itemInfo);
	void RemoveItem(ItemInfo itemInfo);
	bool ExitItem(int slotIndex);
	bool ExistItem(ItemInfo itemInfo);
	bool TryGetItem(int slotIndex, _Out_ ItemInfo* pItemInfo);
	ItemInfo GetItem(int slotIndex);
	bool IsFull();
	int GetCount();

	void IncreaseCoolTime(int slotIndex);
	void ResetCoolTime(int slotIndex);
private :
	std::vector<ItemInfo> m_items;
	const int m_slotCount = 7;

};

