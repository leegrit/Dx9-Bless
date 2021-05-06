#include "stdafx.h"
#include "ShopUI.h"
#include "Button.h"
#include "PathManager.h"
#include "ItemInfoUI.h"

ShopUI::ShopUI(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{
}

ShopUI::~ShopUI()
{
}

void ShopUI::Initialize()
{
	m_pBackground = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIFlashShop_I5F_0.png",
		D3DXVECTOR3(-139, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(600, 500, 1),
		L"ShopUI_Background");

	m_pCloseButton = Button::Create(GetScene(), L"ShopUI_CloseButton",
		PATH->AssetsPathW() + L"UI/BLUITalk_I15_1.png",
		D3DXVECTOR3(124, 220, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(25, 25, 1));
	m_pCloseButton->SetButtonEvent(EButtonEvent::ButtonUp, [&]() 
	{
		Hide();
	});

	m_pCenterLine = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIEXPBar_I3_5.png",
		D3DXVECTOR3(-136, 28, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0.4, 325, 1),
		L"ShopUI_CenterLine");

	m_pUnderLine = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIEXPBar_I3_5.png",
		D3DXVECTOR3(-136, -135.2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(575, 0.4, 1),
		L"ShopUI_UnderLine");

	m_pUnderPanel = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_2.png",
		D3DXVECTOR3(-136, -136.8, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(100, 60, 1),
		L"ShopUI_UnderPanel");

	m_pCoinIcon = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUILooting_I4_3.png",
		D3DXVECTOR3(120, -218, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(25, 25, 1),
		L"ShopUI_CoinIcon");


	m_itemSlots.resize(8);
	m_itemSlotBacks.resize(8);
	m_itemSlotPrices.resize(8);

	//////////////////////////////////////////////////////////////////////////
	// ITEM SLOT LEFT
	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 4; i++)
	{
		m_itemSlots[i] = Button::Create(GetScene(),
			L"ShopUI_ItemSlot_" + std::to_wstring(i),
			PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
			D3DXVECTOR3(-98.4, 134 - i * m_slotOffset, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(50, 50, 1));
		m_itemSlots[i]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [=]() 
		{
			m_pItemSelectPanel->SetActive(true);
			m_pItemSelectPanel->m_pTransform->SetPosition(m_itemSlots[i]->m_pTransform->m_position);
			m_pItemInfoUI->Show(m_itemSlots[i]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		});
		m_itemSlots[i]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [=]() 
		{
			m_pItemSelectPanel->SetActive(false);
			m_pItemInfoUI->Hide();
		});

		m_itemSlotBacks[i] = UIPanel::Create(GetScene(),
			PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_20.png",
			D3DXVECTOR3(-283, 134 - i * m_slotOffset, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(290, 60, 1),
			L"ShopUI_ItemSlotBack");

		m_itemSlotPrices[i] = UIPanel::Create(GetScene(),
			PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_20.png",
			D3DXVECTOR3(135, 120 - i * m_slotOffset, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(25, 25, 1),
			L"ShopUI_ItemSlotPrice");


	}


	//////////////////////////////////////////////////////////////////////////
	// ITEM SLOT RIGHT
	//////////////////////////////////////////////////////////////////////////
	for (int i = 4; i < 8; i++)
	{
		m_itemSlots[i] = Button::Create(GetScene(),
			L"ShopUI_ItemSlot_" + std::to_wstring(i),
			PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
			D3DXVECTOR3(-391, 134 - (i - 4) * m_slotOffset, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(50, 50, 1));
		m_itemSlots[i]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [=]()
		{
			m_pItemSelectPanel->SetActive(true);
			m_pItemSelectPanel->m_pTransform->SetPosition(m_itemSlots[i]->m_pTransform->m_position);
			m_pItemInfoUI->Show(m_itemSlots[i]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		});
		m_itemSlots[i]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [=]()
		{
			m_pItemSelectPanel->SetActive(false);
			m_pItemInfoUI->Hide();
		});

		m_itemSlotBacks[i] = UIPanel::Create(GetScene(),
			PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_20.png",
			D3DXVECTOR3(9.6, 134 - (i - 4) * m_slotOffset, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(290, 60, 1),
			L"ShopUI_ItemSlotBack");

		m_itemSlotPrices[i] = UIPanel::Create(GetScene(),
			PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_20.png",
			D3DXVECTOR3(-158, 120 - (i - 4) * m_slotOffset, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(25, 25, 1),
			L"ShopUI_ItemSlotPrice");
	}

	m_pItemSelectPanel = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUILooting_I4_1.png",
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"ItemSelectPanel");
	m_pItemSelectPanel->SetActive(false);

	m_pItemInfoUI = ItemInfoUI::Create(GetScene(), L"ItemInfoUI");
	m_pItemInfoUI->Hide();
}

void ShopUI::Update()
{
	if (m_bShow)
	{
		/* Title */
		ENGINE->DrawText(GetShopTitle().c_str(), D3DXVECTOR3(179, 148, 0), D3DXVECTOR3(1.3, 1.3, 1.3), D3DXCOLOR(1, 1, 1, 1));

		/* ������ �ݾ� */
		ENGINE->DrawText(L"100", D3DXVECTOR3(566, 589, 0), D3DXVECTOR3(1.2, 1.2, 1.2), D3DXCOLOR(1, 1, 1, 1));

		/* Slot Left */
		for (int i = 0; i < 4; i++)
		{
			ENGINE->DrawText(L"�̸�", D3DXVECTOR3(160, 228 + i * m_slotOffset, 0), D3DXVECTOR3(1,1, 1), D3DXCOLOR(1, 1, 1, 1));
			ENGINE->DrawText(L"Ÿ��", D3DXVECTOR3(160, 252 + i * m_slotOffset, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
			ENGINE->DrawText(L"200", D3DXVECTOR3(307, 250 + i * m_slotOffset, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		}

		/* Slot Right */
		for (int i = 4; i < 8; i++)
		{
			ENGINE->DrawText(L"�̸�", D3DXVECTOR3(452, 228 + (i - 4) * m_slotOffset, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
			ENGINE->DrawText(L"Ÿ��", D3DXVECTOR3(452, 252 + (i - 4) * m_slotOffset, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
			ENGINE->DrawText(L"200", D3DXVECTOR3(607, 250 + (i - 4) * m_slotOffset, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		}

	}
}

void ShopUI::Render()
{
}

void ShopUI::Show()
{
	m_pBackground->SetActive(true);
	m_pCloseButton->SetActive(true);
	for (int i = 0; i < 8; i++)
	{
		m_itemSlots[i]->SetActive(true);
		m_itemSlotBacks[i]->SetActive(true);
		m_itemSlotPrices[i]->SetActive(true);
	}
	m_pCenterLine->SetActive(true);
	m_pUnderLine->SetActive(true);
	m_pUnderPanel->SetActive(true);
	m_pCoinIcon->SetActive(true);
	m_pItemSelectPanel->SetActive(false);

	m_bShow = true;
}

void ShopUI::Hide()
{
	m_pBackground->SetActive(false);
	m_pCloseButton->SetActive(false);
	for (int i = 0; i < 8; i++)
	{
		m_itemSlots[i]->SetActive(false);
		m_itemSlotBacks[i]->SetActive(false);
		m_itemSlotPrices[i]->SetActive(false);
	}
	m_pCenterLine->SetActive(false);
	m_pUnderLine->SetActive(false);
	m_pUnderPanel->SetActive(false);
	m_pCoinIcon->SetActive(false);
	m_pItemSelectPanel->SetActive(false);

	m_bShow = false;
}

bool ShopUI::IsShow()
{
	return m_bShow;
}
