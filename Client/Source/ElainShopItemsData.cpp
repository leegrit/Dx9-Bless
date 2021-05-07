#include "stdafx.h"
#include "ElainShopItemsData.h"
#include "PathManager.h"
ElainShopItemsData::ElainShopItemsData()
{
	ItemInfo itemInfo;
	itemInfo.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/WoodIcon.jpg";
	itemInfo.itemName = L"����� ����";
	itemInfo.itemType = EItemType::QuestItem;
	itemInfo.typeText = L"���";
	itemInfo.effectText = L"����� �����̴�";
	itemInfo.itemDescription = L"����� �����̴�";
	itemInfo.salePrice = 20;
	m_items.push_back(itemInfo);

	ItemInfo leaderPiece;
	leaderPiece.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeaderPiece.jpg";
	leaderPiece.itemName = L"���ײ�";
	leaderPiece.itemType = EItemType::QuestItem;
	leaderPiece.typeText = L"���";
	leaderPiece.effectText = L"����� ���ײ��̴�";
	leaderPiece.itemDescription = L"����� ���ײ��̴�";
	leaderPiece.salePrice = 10;
	m_items.push_back(leaderPiece);

	ItemInfo bread;
	bread.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/Bread.jpg";
	bread.itemName = L"���ָӴ�";
	bread.itemType = EItemType::QuestItem;
	bread.typeText = L"����Ʈ ������";
	bread.effectText = L"���� ��� �ָӴϴ�";
	bread.itemDescription = L"���� ��� �ָӴϴ�";
	bread.salePrice = 10;
	m_items.push_back(bread);


	ItemInfo hpPotion;
	hpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/HPPotionIcon.jpg";
	hpPotion.itemName = L"ü�� ����";
	hpPotion.itemType = EItemType::Item;
	hpPotion.typeText = L"����";
	hpPotion.itemValue = 60;
	hpPotion.effectText = L"���ø� ü���� ȸ���� �� �ִ�.";
	hpPotion.itemDescription = L"���ø� ü���� ȸ���� �� �ִ�.";
	hpPotion.salePrice = 100;
	m_items.push_back(hpPotion);

	ItemInfo mpPotion;
	mpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/ManaPotion.jpg";
	mpPotion.itemName = L"���� ����";
	mpPotion.itemType = EItemType::Item;
	mpPotion.typeText = L"����";
	mpPotion.itemValue = 60;
	mpPotion.effectText = L"���ø� ������ ȸ���� �� �ִ�.";
	mpPotion.itemDescription = L"���ø� ������ ȸ���� �� �ִ�.";
	mpPotion.salePrice = 100;
	m_items.push_back(mpPotion);

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
