#include "stdafx.h"
#include "EquipShopUI.h"

EquipShopUI::EquipShopUI(Scene * pScene, std::wstring name) 
	: ShopUI(pScene, name)
{
}

EquipShopUI::~EquipShopUI()
{
}

std::wstring EquipShopUI::GetShopTitle()
{
	return L"��� ����";
}

EquipShopUI * EquipShopUI::Create(Scene * pScene, std::wstring name)
{
	EquipShopUI * obj = new EquipShopUI(pScene, name);
	obj->Initialize();
	return obj;
}
