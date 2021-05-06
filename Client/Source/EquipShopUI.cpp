#include "stdafx.h"
#include "EquipShopUI.h"
#include "LiurensShopItemsData.h"
EquipShopUI::EquipShopUI(Scene * pScene, std::wstring name) 
	: ShopUI(pScene, name)
{
	m_pItemsData = ENGINE->GetScriptableData(L"LiurensShopItemsData");
	assert(m_pItemsData);
}

EquipShopUI::~EquipShopUI()
{
}

std::wstring EquipShopUI::GetShopTitle()
{
	return L"장비 상점";
}

EquipShopUI * EquipShopUI::Create(Scene * pScene, std::wstring name)
{
	EquipShopUI * obj = new EquipShopUI(pScene, name);
	obj->Initialize();
	return obj;
}

std::vector<ItemInfo> EquipShopUI::GetItemInfos()
{
	LiurensShopItemsData * pData = static_cast<LiurensShopItemsData*>(m_pItemsData);

	return pData->GetItemInfos();
}
