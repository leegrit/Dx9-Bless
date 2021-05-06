#include "stdafx.h"
#include "GeneralStoreUI.h"
#include "ElainShopItemsData.h"

GeneralStoreUI::GeneralStoreUI(Scene * pScene, std::wstring name)
	: ShopUI(pScene, name)
{
	m_pItemsData= ENGINE->GetScriptableData(L"ElainShopItemsData");
	assert(m_pItemsData);
}

GeneralStoreUI::~GeneralStoreUI()
{
}

std::wstring GeneralStoreUI::GetShopTitle()
{
	return L"잡화 상점";
}

std::vector<ItemInfo> GeneralStoreUI::GetItemInfos()
{
	ElainShopItemsData * pData = static_cast<ElainShopItemsData*>(m_pItemsData);

	return pData->GetItemInfos();
}

GeneralStoreUI * GeneralStoreUI::Create(Scene * pScene, std::wstring name)
{
	GeneralStoreUI* obj = new GeneralStoreUI(pScene, name);
	obj->Initialize();
	return obj;
}
