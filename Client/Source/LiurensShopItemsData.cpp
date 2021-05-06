#include "stdafx.h"
#include "LiurensShopItemsData.h"
#include "PathManager.h"
LiurensShopItemsData::LiurensShopItemsData()
{
	ItemInfo itemInfo;
	itemInfo.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/WeaponIcon.png";
	itemInfo.itemName = L"평범한 검";
	itemInfo.itemType = EItemType::Weapon;
	itemInfo.atk = 15;
	itemInfo.salePrice = 100;
	itemInfo.wearableLevel = 1;
	itemInfo.itemDescription = L"평범한 검이다.";

	m_items.push_back(itemInfo);

}

LiurensShopItemsData::~LiurensShopItemsData()
{
}

bool LiurensShopItemsData::TryGetItemInfo(int index, ItemInfo * pItemInfo)
{
	if (index >= m_maxItemCount)
		return false;

	if (index >= m_items.size())
		return false;

	*pItemInfo = m_items[index];
	return true;
}

std::vector<ItemInfo> LiurensShopItemsData::GetItemInfos()
{
	return m_items;
}

