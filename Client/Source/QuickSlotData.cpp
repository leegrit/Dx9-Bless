#include "stdafx.h"
#include "QuickSlotData.h"
#include "Client_Events.h"


QuickSlotData::QuickSlotData()
{
	m_items.reserve(m_slotCount);
}

bool QuickSlotData::PushItem(ItemInfo itemInfo)
{
	if (m_items.size() >= m_slotCount)
		return false;

	m_items.push_back(itemInfo);
	EventDispatcher::TriggerEvent(GameEvent::SetQuickSlot, (void*)&itemInfo);
	return true;
}

void QuickSlotData::RemoveItem(ItemInfo itemInfo)
{
	for (int i = 0; i < m_items.size(); i++)
	{
		if (m_items[i].uid == itemInfo.uid)
		{
			m_items.erase(m_items.begin() + i);
			EventDispatcher::TriggerEvent(GameEvent::RemoveQuickSlot, (void*)&itemInfo);
			return;
		}
	}
}

bool QuickSlotData::ExitItem(int slotIndex)
{
	if (m_items.size() <= slotIndex)
		return false;
	return true;
}

bool QuickSlotData::ExistItem(ItemInfo itemInfo)
{
	for (int i = 0; i < m_items.size(); i++)
	{
		if (m_items[i].itemName.compare(itemInfo.itemName) == 0)
			return true;
	}
	return false;
}

bool QuickSlotData::TryGetItem(int slotIndex, ItemInfo * pItemInfo)
{
	if (ExitItem(slotIndex))
	{
		*pItemInfo = m_items[slotIndex];
		return true;
	}
	else
		return false;
}

ItemInfo QuickSlotData::GetItem(int slotIndex)
{
	return m_items.at(slotIndex);
}

bool QuickSlotData::IsFull()
{
	return m_items.size() >= m_slotCount;
}

int QuickSlotData::GetCount()
{
	return m_items.size();
}



void QuickSlotData::IncreaseCoolTime(int slotIndex)
{
	m_items[slotIndex].curCoolTime += TIMER->getDeltaTime();
}

void QuickSlotData::ResetCoolTime(int slotIndex)
{
	m_items[slotIndex].curCoolTime = 0;
}
