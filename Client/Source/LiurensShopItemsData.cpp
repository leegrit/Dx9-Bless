#include "stdafx.h"
#include "LiurensShopItemsData.h"
#include "PathManager.h"
LiurensShopItemsData::LiurensShopItemsData()
{
	ItemInfo itemInfo;
	itemInfo.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/Sword3.png";
	itemInfo.itemName = L"평범한 검";
	itemInfo.itemType = EItemType::Weapon;
	itemInfo.typeText = L"무기";
	itemInfo.effectText = L"물리 공격력 15";
	itemInfo.atk = 15;
	itemInfo.salePrice = 100;
	itemInfo.wearableLevel = 1;
	itemInfo.itemDescription = L"평범한 검이다.";

	m_items.push_back(itemInfo);

	ItemInfo sword2;
	sword2.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/Sword2.png";
	sword2.itemName = L"장식용 검";
	sword2.itemType = EItemType::Weapon;
	sword2.typeText = L"무기";
	sword2.effectText = L"물리 공격력 7";
	sword2.atk = 7;
	sword2.salePrice = 70;
	sword2.wearableLevel = 1;
	sword2.itemDescription = L"장식용 검이다.";

	m_items.push_back(sword2);

	ItemInfo leaderHelmet;
	leaderHelmet.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeaderHelmet.png";
	leaderHelmet.itemName = L"가죽 모자";
	leaderHelmet.itemType = EItemType::Helmet;
	leaderHelmet.typeText = L"모자";
	leaderHelmet.effectText = L"물리 방어력 10\n마법 방어력 5";
	leaderHelmet.physicalDef = 10;
	leaderHelmet.magicalDef = 5;
	leaderHelmet.salePrice = 300;
	leaderHelmet.wearableLevel = 1;
	leaderHelmet.itemDescription = L"평범한 가죽모자다.";
	m_items.push_back(leaderHelmet);

	ItemInfo leaderGlove;
	leaderGlove.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeaderGlove.png";
	leaderGlove.itemName = L"가죽 장갑";
	leaderGlove.itemType = EItemType::Glove;
	leaderGlove.typeText = L"장갑";
	leaderGlove.effectText = L"물리 방어력 5";
	leaderGlove.physicalDef = 5;
	leaderGlove.salePrice = 100;
	leaderGlove.wearableLevel = 1;
	leaderGlove.itemDescription = L"평범한 가죽장갑이다.";
	m_items.push_back(leaderGlove);


	ItemInfo leaderUpper;
	leaderUpper.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeatherUpper.png";
	leaderUpper.itemName = L"가죽 옷";
	leaderUpper.itemType = EItemType::Upper;
	leaderUpper.typeText = L"옷";
	leaderUpper.effectText = L"물리 방어력 15\n마법 방어력 15";
	leaderUpper.physicalDef = 15;
	leaderUpper.magicalDef = 15;
	leaderUpper.salePrice = 500;
	leaderUpper.wearableLevel = 1;
	leaderUpper.itemDescription = L"평범한 가죽옷이다.";
	m_items.push_back(leaderUpper);

	ItemInfo leaderLower;
	leaderLower.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeaderLower.png";
	leaderLower.itemName = L"가죽 바지";
	leaderLower.itemType = EItemType::Lower;
	leaderLower.typeText = L"바지";
	leaderLower.effectText = L"물리 방어력 20";
	leaderLower.physicalDef = 20;
	leaderLower.salePrice = 300;
	leaderLower.wearableLevel = 1;
	leaderLower.itemDescription = L"평범한 가죽바지다.";
	m_items.push_back(leaderLower);

	ItemInfo leaderBoots;
	leaderBoots.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeatherBoots.png";
	leaderBoots.itemName = L"가죽 신발";
	leaderBoots.itemType = EItemType::Boots;
	leaderBoots.typeText = L"신발";
	leaderBoots.effectText = L"물리 방어력 5";
	leaderBoots.physicalDef = 5;
	leaderBoots.salePrice = 50;
	leaderBoots.wearableLevel = 1;
	leaderBoots.itemDescription = L"평범한 가죽신발이다.";
	m_items.push_back(leaderBoots);

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

