#include "stdafx.h"
#include "ItemInfo.h"

ItemInfo::ItemInfo()
{
	imagePath = L"";
	itemName = L"";
	itemType = EItemType::None;
	atk = 0;
	physicalDef = 0;
	magicalDef = 0;
	int salePrice = 0;
	itemValue = 0;
	itemDuration = 0;
	itemDescription = L"";
	availableForSale = true;
	availableForDestruction = true;
}
