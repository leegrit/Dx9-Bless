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
	bool TryGetItem(int slotIndex, _Out_ ItemInfo* pItemInfo);
	ItemInfo GetItem(int slotIndex);
	bool IsFull();
	int GetCount();

private :
	std::vector<ItemInfo> m_items;
	const int m_slotCount = 7;

};

