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

void InventoryData::RemoveItem(ItemInfo itemInfo)
{
	for (int i = 0; i < m_items.size(); i++)
	{
		if (m_items[i].uid == itemInfo.uid)
		{
			m_items.erase(m_items.begin() + i);
			EventDispatcher::TriggerEvent(GameEvent::RemoveItemToInventory, (void*)&itemInfo);
			return;
		}
	}
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
		return true;
	}
	else
		return false;
}

ItemInfo InventoryData::GetItem(int index)
{
	return m_items.at(index);
}

bool InventoryData::IsFull()
{
	return m_items.size() >= m_inventoryMaxCount;
}

int InventoryData::GetCount()
{
	return m_items.size();
}
