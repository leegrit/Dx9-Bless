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

	if (itemInfo.itemType == EItemType::Item || itemInfo.itemType == EItemType::Spoils)
	{
		for (int i = 0; i < m_items.size(); i++)
		{
			if (m_items[i].itemName.compare(itemInfo.itemName) == 0)
			{
				m_items[i].AddItem(itemInfo);

				EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&itemInfo);
				return true; 
			}

		}

	}

	if (itemInfo.itemType == EItemType::Spoils ||
		itemInfo.itemType == EItemType::Item)
	{
		itemInfo.AddItem(itemInfo);
	}
	m_items.push_back(itemInfo);
	

	EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&itemInfo);
	return true;
}

void InventoryData::RemoveItem(ItemInfo itemInfo)
{
	for (int i = 0; i < m_items.size(); i++)
	{
		if (m_items[i].itemType == EItemType::Spoils ||
			m_items[i].itemType == EItemType::Item)
		{
			bool isRemove = false;
			for (int j = 0; m_items[i].GetOverlapCount(); j++)
			{
				if (m_items[i].m_overlapItems[j].uid == itemInfo.uid)
				{
					m_items[i].m_overlapItems.erase(m_items[i].m_overlapItems.begin() + j);
					if (m_items[i].m_overlapItems.size() != 0)
					{
						EventDispatcher::TriggerEvent(GameEvent::RemoveItemToInventory, (void*)&itemInfo);
					}
					isRemove = true;
					break;
				}
			}
			if (isRemove == true)
				break;
		}
		else
		{
			if (m_items[i].uid == itemInfo.uid)
			{
				m_items.erase(m_items.begin() + i);
				EventDispatcher::TriggerEvent(GameEvent::RemoveItemToInventory, (void*)&itemInfo);
				break;;
			}
		}
	}
	for (int i = 0; i < m_items.size(); i++)
	{
		if (m_items[i].itemType == EItemType::Spoils ||
			m_items[i].itemType == EItemType::Item)
		{
			// 중첩 가능 아이템의 경우 중첩된게 0개가 되면 삭제한다.
			if (m_items[i].GetOverlapCount() == 0)
			{
				m_items.erase(m_items.begin() + i);
				EventDispatcher::TriggerEvent(GameEvent::RemoveItemToInventory, (void*)&itemInfo);
				break;;
			}
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
		if (m_items[index].itemType == EItemType::Item)
		{
			*pItemInfo = m_items[index].m_overlapItems[0];
		}
		else
		{
			*pItemInfo = m_items[index];
		}
		return true;
	}
	else
		return false;
}

bool InventoryData::TryGetItem(std::wstring name, ItemInfo * pItemInfo)
{
	for (int i = 0; i < m_items.size(); i++)
	{
		if (m_items[i].itemName.compare(name) == 0)
		{
			if (m_items[i].itemType == EItemType::Item)
			{
				*pItemInfo = m_items[i].m_overlapItems[0];
			}
			else
			{
				*pItemInfo = m_items[i];
			}
			return true;
		}
	}
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

int InventoryData::GetOverlapCount(int index)
{
	return m_items.at(index).m_overlapItems.size();
}
