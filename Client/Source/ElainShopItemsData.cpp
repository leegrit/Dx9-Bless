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
	hpPotion.buffType = EItemBuffType::HPHeal;
	hpPotion.typeText = L"����";
	hpPotion.itemValue = 200;
	hpPotion.effectText = L"���ø� ü���� ȸ���� �� �ִ�.";
	hpPotion.itemDescription = L"���ø� ü���� ȸ���� �� �ִ�.";
	hpPotion.salePrice = 100;
	hpPotion.coolTime = 2.0f;
	hpPotion.curCoolTime = 2.0;
	m_items.push_back(hpPotion);

	ItemInfo mpPotion;
	mpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/ManaPotion.jpg";
	mpPotion.itemName = L"���� ����";
	mpPotion.itemType = EItemType::Item;
	mpPotion.buffType = EItemBuffType::MPHeal;
	mpPotion.typeText = L"����";
	mpPotion.itemValue = 60;
	mpPotion.effectText = L"���ø� ������ ȸ���� �� �ִ�.";
	mpPotion.itemDescription = L"���ø� ������ ȸ���� �� �ִ�.";
	mpPotion.salePrice = 100;
	mpPotion.coolTime = 2.0f;
	mpPotion.curCoolTime = 2.0;
	m_items.push_back(mpPotion);

	ItemInfo powerUpPotion;
	powerUpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/PowerPotion.png";
	powerUpPotion.itemName = L"�� ��ȭ ����";
	powerUpPotion.itemType = EItemType::Item;
	powerUpPotion.buffType = EItemBuffType::PowerUp;
	powerUpPotion.typeText = L"����";
	powerUpPotion.itemValue = 10;
	powerUpPotion.effectText = L"���ø� ���� ��������.";
	powerUpPotion.itemDescription = L"���ø� ���� ��������.";
	powerUpPotion.salePrice = 100;
	powerUpPotion.coolTime = 2.0f;
	powerUpPotion.curCoolTime = 2.0;
	powerUpPotion.itemDuration = 30;
	m_items.push_back(powerUpPotion);

	ItemInfo speedUpPotion;
	speedUpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/SpeedPotion.png";
	speedUpPotion.itemName = L"�ӵ� ��ȭ ����";
	speedUpPotion.itemType = EItemType::Item;
	speedUpPotion.buffType = EItemBuffType::SpeedUp;
	speedUpPotion.typeText = L"����";
	speedUpPotion.itemValue = 10;
	speedUpPotion.effectText = L"���ø� �̵��ӵ��� ��������..";
	speedUpPotion.itemDescription = L"���ø��̵��ӵ��� ��������.";
	speedUpPotion.salePrice = 100;
	speedUpPotion.coolTime = 2.0f;
	speedUpPotion.curCoolTime = 2.0;
	speedUpPotion.itemDuration = 30;
	m_items.push_back(speedUpPotion);

	ItemInfo defenceUpPotion;
	defenceUpPotion.imagePath = PATH->AssetsPathW() + L"UI/ItemIcon/DefPotion.png";
	defenceUpPotion.itemName = L"���� ��ȭ ����";
	defenceUpPotion.itemType = EItemType::Item;
	defenceUpPotion.buffType = EItemBuffType::DefenceUp;
	defenceUpPotion.typeText = L"����";
	defenceUpPotion.itemValue = 10;
	defenceUpPotion.effectText = L"���ø� ������ �ö󰣴�. ";
	defenceUpPotion.itemDescription = L"���ø� ������ �ö󰣴�.";
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
