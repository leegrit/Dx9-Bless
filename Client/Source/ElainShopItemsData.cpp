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
	hpPotion.buffType = EItemBuffType::HPHeal;
	hpPotion.typeText = L"포션";
	hpPotion.itemValue = 200;
	hpPotion.effectText = L"마시면 체력을 회복할 수 있다.";
	hpPotion.itemDescription = L"마시면 체력을 회복할 수 있다.";
	hpPotion.salePrice = 100;
	hpPotion.coolTime = 2.0f;
	hpPotion.curCoolTime = 2.0;
	m_items.push_back(hpPotion);

	ItemInfo mpPotion;
	mpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/ManaPotion.jpg";
	mpPotion.itemName = L"마나 포션";
	mpPotion.itemType = EItemType::Item;
	mpPotion.buffType = EItemBuffType::MPHeal;
	mpPotion.typeText = L"포션";
	mpPotion.itemValue = 60;
	mpPotion.effectText = L"마시면 마나를 회복할 수 있다.";
	mpPotion.itemDescription = L"마시면 마나를 회복할 수 있다.";
	mpPotion.salePrice = 100;
	mpPotion.coolTime = 2.0f;
	mpPotion.curCoolTime = 2.0;
	m_items.push_back(mpPotion);

	ItemInfo powerUpPotion;
	powerUpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/PowerPotion.png";
	powerUpPotion.itemName = L"힘 강화 포션";
	powerUpPotion.itemType = EItemType::Item;
	powerUpPotion.buffType = EItemBuffType::PowerUp;
	powerUpPotion.typeText = L"포션";
	powerUpPotion.itemValue = 10;
	powerUpPotion.effectText = L"마시면 힘이 강해진다.";
	powerUpPotion.itemDescription = L"마시면 힘이 강해진다.";
	powerUpPotion.salePrice = 100;
	powerUpPotion.coolTime = 2.0f;
	powerUpPotion.curCoolTime = 2.0;
	powerUpPotion.itemDuration = 30;
	m_items.push_back(powerUpPotion);

	ItemInfo speedUpPotion;
	speedUpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/SpeedPotion.png";
	speedUpPotion.itemName = L"속도 강화 포션";
	speedUpPotion.itemType = EItemType::Item;
	speedUpPotion.buffType = EItemBuffType::SpeedUp;
	speedUpPotion.typeText = L"포션";
	speedUpPotion.itemValue = 10;
	speedUpPotion.effectText = L"마시면 이동속도가 빨라진다..";
	speedUpPotion.itemDescription = L"마시면이동속도가 빨라진다.";
	speedUpPotion.salePrice = 100;
	speedUpPotion.coolTime = 2.0f;
	speedUpPotion.curCoolTime = 2.0;
	speedUpPotion.itemDuration = 30;
	m_items.push_back(speedUpPotion);

	ItemInfo defenceUpPotion;
	defenceUpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/DefPotion.png";
	defenceUpPotion.itemName = L"방어력 강화 포션";
	defenceUpPotion.itemType = EItemType::Item;
	defenceUpPotion.buffType = EItemBuffType::DefenceUp;
	defenceUpPotion.typeText = L"포션";
	defenceUpPotion.itemValue = 10;
	defenceUpPotion.effectText = L"마시면 방어력이 올라간다. ";
	defenceUpPotion.itemDescription = L"마시면 방어력이 올라간다.";
	defenceUpPotion.salePrice = 100;
	defenceUpPotion.coolTime = 2.0f;
	defenceUpPotion.curCoolTime = 2.0;
	defenceUpPotion.itemDuration = 30;
	m_items.push_back(defenceUpPotion);

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
