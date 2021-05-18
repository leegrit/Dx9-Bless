#pragma once
#include "Client_Enumerators.h"

enum class EItemBuffType
{
	HPHeal,
	MPHeal,
	PowerUp,
	SpeedUp,
	DefenceUp,
	CoolTimeReset,
};


class ItemInfo
{
public :
	ItemInfo();

	int uid;
	std::wstring imagePath;
	std::wstring itemName;
	EItemType itemType;
	EItemBuffType buffType;
	std::wstring typeText;
	std::wstring effectText;
	// 레벨제한
	int wearableLevel;
	int atk;
	int physicalDef;
	int magicalDef;
	int salePrice;
	// 소모품 효과 값
	int itemValue;
	// 소모품 지속시간
	int itemDuration;
	// 소모품 효과에 대한 설명
	std::wstring itemDescription; 

	float coolTime;
	float curCoolTime;

	bool availableForSale;
	bool availableForDestruction;

public :
	// 소모품, 잡동사니같은 경우 중첩 가능
	void AddItem(ItemInfo itemInfo);
	ItemInfo GetItem(int index);
	int GetOverlapCount();

private:
	int m_itemCount = 1;
public:
	std::vector<ItemInfo> m_overlapItems;

};

