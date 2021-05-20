#include "stdafx.h"
#include "SpoilsUI.h"
#include "PathManager.h"


SpoilsUI::SpoilsUI(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{
}

SpoilsUI::~SpoilsUI()
{
}

void SpoilsUI::Initialize()
{
	m_pBackground = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUILooting_I4_0.png",
		D3DXVECTOR3(0, 102, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(300, 100, 1),
		L"Looting_Background");
	m_pBackground->SetActive(false);

	m_pItemSlotBack = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
		D3DXVECTOR3(-109, 97, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(45, 45, 1),
		L"Looting_ItemSlot");
	m_pItemSlotBack->SetActive(false);

	m_pItemSlotIcon = UIPanel::Create(GetScene(),
		L"",
		D3DXVECTOR3(-109, 97, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(45, 45, 1),
		L"Looting_ItemSlot");
	m_pItemSlotIcon->SetActive(false);

	m_pGainBtn = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUITokenExchange_IB_0.png",
		D3DXVECTOR3(0, 54, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(100, 20, 1),
		L"Looting_GainBtn");
	m_pGainBtn->SetActive(false);

	m_pCancleBtn = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUITalk_I15_1.png",
		D3DXVECTOR3(134, 133, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(10, 10, 1),
		L"Looting_CancleBtn");
	m_pCancleBtn->SetActive(false);



}

void SpoilsUI::Update()
{
	if (m_bShow)
	{
		ENGINE->DrawText(m_itemName.c_str(),
			D3DXVECTOR3(441, 266, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1), -1);
		ENGINE->DrawText(m_gainFont.c_str(),
			D3DXVECTOR3(500, 323, 0), D3DXVECTOR3(0.7, 0.7, 0.7), D3DXCOLOR(1, 1, 1, 1), -1);

	}
}

void SpoilsUI::Render()
{
}

void SpoilsUI::Show(ItemInfo itemInfo)
{
	m_bShow = true;
	m_pBackground->SetActive(true);
	m_pItemSlotBack->SetActive(true);
	m_pItemSlotIcon->SetActive(true);
	m_pItemSlotIcon->SetTexture(itemInfo.imagePath);
	m_pGainBtn->SetActive(true);
	m_pCancleBtn->SetActive(true);
	m_itemName = itemInfo.itemName;
}

void SpoilsUI::Hide()
{
	m_bShow = false;

	m_pBackground->SetActive(false);
	m_pItemSlotBack->SetActive(false);
	m_pItemSlotIcon->SetActive(false);
	m_pGainBtn->SetActive(false);
	m_pCancleBtn->SetActive(false);
}

bool SpoilsUI::IsShow()
{
	return m_bShow;
}

SpoilsUI * SpoilsUI::Create(Scene * pSceme, std::wstring name)
{
	SpoilsUI* obj = new SpoilsUI(pSceme, name);
	obj->Initialize();
	return obj;
}
