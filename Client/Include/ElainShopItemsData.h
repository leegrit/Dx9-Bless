#pragma once
#include "ScriptableData.h"
#include "ItemInfo.h"

using namespace HyEngine;
class ElainShopItemsData : public ScriptableData
{
public :
	ElainShopItemsData();
	~ElainShopItemsData();

public :
	bool TryGetItemInfo(int index, _Out_ ItemInfo* pItemInfo);
	std::vector<ItemInfo> GetItemInfos();
private :
	std::vector<ItemInfo> m_items;
	const int m_maxItemCount = 8;
};

