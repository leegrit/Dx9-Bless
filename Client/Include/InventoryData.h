#pragma once
#include "ScriptableData.h"
#include "ItemInfo.h"

class InventoryData  : public ScriptableData
{
public :
	InventoryData();

	bool PushItem(ItemInfo itemInfo);
	void RemoveItem(ItemInfo itemInfo);
	bool ExitItem(int index);
	bool TryGetItem(int index, _Out_ ItemInfo* pItemInfo);
	ItemInfo GetItem(int index);
	bool IsFull();
	int GetCount();
private:

	std::vector<ItemInfo> m_items;
	int m_currentItemSize;
	const int m_inventoryMaxCount = 40;
};

