#include "stdafx.h"
#include "GeneralStoreUI.h"

GeneralStoreUI::GeneralStoreUI(Scene * pScene, std::wstring name)
	: ShopUI(pScene, name)
{
}

GeneralStoreUI::~GeneralStoreUI()
{
}

std::wstring GeneralStoreUI::GetShopTitle()
{
	return L"��ȭ ����";
}

GeneralStoreUI * GeneralStoreUI::Create(Scene * pScene, std::wstring name)
{
	GeneralStoreUI* obj = new GeneralStoreUI(pScene, name);
	obj->Initialize();
	return obj;
}
