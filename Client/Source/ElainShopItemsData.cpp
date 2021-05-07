#include "stdafx.h"
#include "ElainShopItemsData.h"
#include "PathManager.h"
ElainShopItemsData::ElainShopItemsData()
{
	ItemInfo itemInfo;
	itemInfo.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/WoodIcon.jpg";
	itemInfo.itemName = L"평범한 목재";
	itemInfo.itemType = EItemType::QuestItem;
	itemInfo.typeText = L"재료";
	itemInfo.effectText = L"평범한 목재이다";
	itemInfo.itemDescription = L"평범한 목재이다";
	itemInfo.salePrice = 20;
	m_items.push_back(itemInfo);

	ItemInfo leaderPiece;
	leaderPiece.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/LeaderPiece.jpg";
	leaderPiece.itemName = L"가죽끈";
	leaderPiece.itemType = EItemType::QuestItem;
	leaderPiece.typeText = L"재료";
	leaderPiece.effectText = L"평범한 가죽끈이다";
	leaderPiece.itemDescription = L"평범한 가죽끈이다";
	leaderPiece.salePrice = 10;
	m_items.push_back(leaderPiece);

	ItemInfo bread;
	bread.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/Bread.jpg";
	bread.itemName = L"빵주머니";
	bread.itemType = EItemType::QuestItem;
	bread.typeText = L"퀘스트 아이템";
	bread.effectText = L"빵이 담긴 주머니다";
	bread.itemDescription = L"빵이 담긴 주머니다";
	bread.salePrice = 10;
	m_items.push_back(bread);


	ItemInfo hpPotion;
	hpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/HPPotionIcon.jpg";
	hpPotion.itemName = L"체력 포션";
	hpPotion.itemType = EItemType::Item;
	hpPotion.typeText = L"포션";
	hpPotion.itemValue = 60;
	hpPotion.effectText = L"마시면 체력을 회복할 수 있다.";
	hpPotion.itemDescription = L"마시면 체력을 회복할 수 있다.";
	hpPotion.salePrice = 100;
	m_items.push_back(hpPotion);

	ItemInfo mpPotion;
	mpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/ManaPotion.jpg";
	mpPotion.itemName = L"마나 포션";
	mpPotion.itemType = EItemType::Item;
	mpPotion.typeText = L"포션";
	mpPotion.itemValue = 60;
	mpPotion.effectText = L"마시면 마나를 회복할 수 있다.";
	mpPotion.itemDescription = L"마시면 마나를 회복할 수 있다.";
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
