#include "stdafx.h"
#include "InventoryData.h"
#include "Client_Events.h"

InventoryData::InventoryData()
{
	m_items.reserve(m_inventoryMaxCount);
}

bool InventoryData::PushItem(ItemInfo itemInfo)
{
	if (m_items.size() >= m_inventoryMaxCount)
	{
		return false;
	}

	m_items.push_back(itemInfo);

	EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&itemInfo);
}

bool InventoryData::ExitItem(int index)
{
	if (m_items.size() <= index)
	{
		return false;
	}
	return true;
}

bool InventoryData::TryGetItem(int index, _Out_ ItemInfo* pItemInfo)
{
	if (ExitItem(index))
	{
		*pItemInfo = m_items[index];
	}
	else
		return false;
}
