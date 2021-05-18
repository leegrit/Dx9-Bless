#include "stdafx.h"
#include "ItemInfo.h"

ItemInfo::ItemInfo()
{
	uid = UIDGen::Get()->GetUID();
	imagePath = L"";
	itemName = L"";
	typeText = L"";
	itemType = EItemType::None;
	atk = 0;
	physicalDef = 0;
	magicalDef = 0;
	int salePrice = 0;
	itemValue = 0;
	itemDuration = 0;
	itemDescription = L"";
	coolTime = 0;
	curCoolTime = 0;
	availableForSale = true;
	availableForDestruction = true;
}

void ItemInfo::AddItem(ItemInfo itemInfo)
{
	m_overlapItems.push_back(itemInfo);
}

ItemInfo ItemInfo::GetItem(int index)
{
	return m_overlapItems[index];
}

int ItemInfo::GetOverlapCount()
{
	return m_overlapItems.size();
}
