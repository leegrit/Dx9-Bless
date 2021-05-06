#include "stdafx.h"
#include "ElainShopItemsData.h"
#include "PathManager.h"
ElainShopItemsData::ElainShopItemsData()
{
	ItemInfo itemInfo;
	itemInfo.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/WoodIcon.jpg";
	itemInfo.itemName = L"평범한 목재";
	itemInfo.itemType = EItemType::QuestItem;
	itemInfo.itemDescription = L"평범한 목재이다";
	itemInfo.salePrice = 20;
	
	m_items.push_back(itemInfo);
}

ElainShopItemsData::~ElainShopItemsData()
{
}

bool ElainShopItemsData::TryGetItemInfo(int index, ItemInfo * pItemInfo)
{
	if (index >= m_maxItemCount)
		return false;

	if (index >= m_items.size())
		return false;

	*pItemInfo = m_items[index];
	return true;
}

std::vector<ItemInfo> ElainShopItemsData::GetItemInfos()
{
	return m_items;
}
