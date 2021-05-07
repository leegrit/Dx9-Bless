#include "stdafx.h"
#include "ItemInfo.h"

ItemInfo::ItemInfo()
{
	uid = UIDGen::Get()->GetUID();
	imagePath = L"";
	itemName = L"";
	typeText = L"";
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
