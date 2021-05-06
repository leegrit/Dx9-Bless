#include "stdafx.h"
#include "ShopItemsTable.h"
#include "LiurensShopItemsData.h"
#include "ElainShopItemsData.h"


ShopItemsTable::ShopItemsTable()
{
	LiurensShopItemsData * pLiurensShopItemsData = static_cast<LiurensShopItemsData*>(ENGINE->GetScriptableData(L"LiurensShopItemsData"));
	if (pLiurensShopItemsData == nullptr)
	{
		pLiurensShopItemsData = new LiurensShopItemsData();
		ENGINE->AddScriptableData(L"LiurensShopItemsData", pLiurensShopItemsData);
	}

	ElainShopItemsData * pElainShopItemsData = static_cast<ElainShopItemsData*>(ENGINE->GetScriptableData(L"ElainShopItemsData"));
	if (pElainShopItemsData == nullptr)
	{
		pElainShopItemsData = new ElainShopItemsData();
		ENGINE->AddScriptableData(L"ElainShopItemsData", pElainShopItemsData);
	}
}

ShopItemsTable::~ShopItemsTable()
{
}
