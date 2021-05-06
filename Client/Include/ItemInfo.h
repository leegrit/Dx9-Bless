#pragma once
#include "Client_Enumerators.h"
class ItemInfo
{
public :
	ItemInfo();

	std::wstring imagePath;
	std::wstring itemName;
	EItemType itemType;
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

	bool availableForSale;
	bool availableForDestruction;
};

