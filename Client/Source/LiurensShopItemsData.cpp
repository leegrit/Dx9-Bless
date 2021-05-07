#include "stdafx.h"
#include "LiurensShopItemsData.h"
#include "PathManager.h"
LiurensShopItemsData::LiurensShopItemsData()
{
	ItemInfo itemInfo;
	itemInfo.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/Sword3.png";
	itemInfo.itemName = L"����� ��";
	itemInfo.itemType = EItemType::Weapon;
	itemInfo.typeText = L"����";
	itemInfo.effectText = L"���� ���ݷ� 15";
	itemInfo.atk = 15;
	itemInfo.salePrice = 100;
	itemInfo.wearableLevel = 1;
	itemInfo.itemDescription = L"����� ���̴�.";

	m_items.push_back(itemInfo);

	ItemInfo sword2;
	sword2.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/Sword2.png";
	sword2.itemName = L"��Ŀ� ��";
	sword2.itemType = EItemType::Weapon;
	sword2.typeText = L"����";
	sword2.effectText = L"���� ���ݷ� 7";
	sword2.atk = 7;
	sword2.salePrice = 70;
	sword2.wearableLevel = 1;
	sword2.itemDescription = L"��Ŀ� ���̴�.";

	m_items.push_back(sword2);

	ItemInfo leaderHelmet;
	leaderHelmet.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeaderHelmet.png";
	leaderHelmet.itemName = L"���� ����";
	leaderHelmet.itemType = EItemType::Helmet;
	leaderHelmet.typeText = L"����";
	leaderHelmet.effectText = L"���� ���� 10\n���� ���� 5";
	leaderHelmet.physicalDef = 10;
	leaderHelmet.magicalDef = 5;
	leaderHelmet.salePrice = 300;
	leaderHelmet.wearableLevel = 1;
	leaderHelmet.itemDescription = L"����� ���׸��ڴ�.";
	m_items.push_back(leaderHelmet);

	ItemInfo leaderGlove;
	leaderGlove.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeaderGlove.png";
	leaderGlove.itemName = L"���� �尩";
	leaderGlove.itemType = EItemType::Glove;
	leaderGlove.typeText = L"�尩";
	leaderGlove.effectText = L"���� ���� 5";
	leaderGlove.physicalDef = 5;
	leaderGlove.salePrice = 100;
	leaderGlove.wearableLevel = 1;
	leaderGlove.itemDescription = L"����� �����尩�̴�.";
	m_items.push_back(leaderGlove);


	ItemInfo leaderUpper;
	leaderUpper.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeatherUpper.png";
	leaderUpper.itemName = L"���� ��";
	leaderUpper.itemType = EItemType::Upper;
	leaderUpper.typeText = L"��";
	leaderUpper.effectText = L"���� ���� 15\n���� ���� 15";
	leaderUpper.physicalDef = 15;
	leaderUpper.magicalDef = 15;
	leaderUpper.salePrice = 500;
	leaderUpper.wearableLevel = 1;
	leaderUpper.itemDescription = L"����� ���׿��̴�.";
	m_items.push_back(leaderUpper);

	ItemInfo leaderLower;
	leaderLower.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeaderLower.png";
	leaderLower.itemName = L"���� ����";
	leaderLower.itemType = EItemType::Lower;
	leaderLower.typeText = L"����";
	leaderLower.effectText = L"���� ���� 20";
	leaderLower.physicalDef = 20;
	leaderLower.salePrice = 300;
	leaderLower.wearableLevel = 1;
	leaderLower.itemDescription = L"����� ���׹�����.";
	m_items.push_back(leaderLower);

	ItemInfo leaderBoots;
	leaderBoots.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeatherBoots.png";
	leaderBoots.itemName = L"���� �Ź�";
	leaderBoots.itemType = EItemType::Boots;
	leaderBoots.typeText = L"�Ź�";
	leaderBoots.effectText = L"���� ���� 5";
	leaderBoots.physicalDef = 5;
	leaderBoots.salePrice = 50;
	leaderBoots.wearableLevel = 1;
	leaderBoots.itemDescription = L"����� ���׽Ź��̴�.";
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

