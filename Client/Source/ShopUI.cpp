#include "stdafx.h"
#include "ShopUI.h"
#include "Button.h"
#include "PathManager.h"
#include "ItemInfoUI.h"
#include "Client_Events.h"
#include "PlayerMoneyData.h"
#include "InventoryData.h"



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
	m_pBackground->SetRenderQueue(3500);

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
			D3DXVECTOR3(-391, 134 - i * m_slotOffset, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(50, 50, 1));
		m_itemSlots[i]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [=]() 
		{
			if (i >= m_items.size())
				return;
			m_pItemSelectPanel->SetActive(true);
			m_pItemSelectPanel->m_pTransform->SetPosition(m_itemSlots[i]->m_pTransform->m_position);
			m_pItemInfoUI->ShowForShop(D3DXVECTOR3(281, 39, 0), m_items[i]); //m_itemSlots[i]->m_pTransform->m_position.operator D3DXVECTOR3(), false);
		});
		m_itemSlots[i]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [=]() 
		{
			if (i >= m_items.size())
				return;
			m_pItemSelectPanel->SetActive(false);
			m_pItemInfoUI->Hide();
		});
		m_itemSlots[i]->SetButtonEvent(EButtonEvent::RightButtonUp, [=]() 
		{
			// 아이템 구매

			if (i >= m_items.size()) return;
			
			PlayerMoneyData* pData = static_cast<PlayerMoneyData*>(ENGINE->GetScriptableData(L"PlayerMoneyData"));
			
			if (m_items[i].salePrice > pData->money)
			{
				EventDispatcher::TriggerEvent(GameEvent::NotEnoughMoney);
				return;
			}

			InventoryData* pInventoryData = static_cast<InventoryData*>(ENGINE->GetScriptableData(L"InventoryData"));
			if (pInventoryData->IsFull())
			{
				EventDispatcher::TriggerEvent(GameEvent::InventoryFull);
				return;
			}

			//구매 성공
			pData->money -= m_items[i].salePrice;
			pInventoryData->PushItem(m_items[i]);
			EventDispatcher::TriggerEvent(GameEvent::BuyItem, (void*)&m_items[i]);
			EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&m_items[i]);

		});

		m_itemSlotBacks[i] = UIPanel::Create(GetScene(),
			PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_20.png",
			D3DXVECTOR3(-283, 134 - i * m_slotOffset, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(290, 60, 1),
			L"ShopUI_ItemSlotBack");
		m_itemSlotBacks[i]->SetRenderQueue(3400);

		m_itemSlotPrices[i] = UIPanel::Create(GetScene(),
			PATH->AssetsPathW() + L"UI/BLUILooting_I4_3.png",
			D3DXVECTOR3(-158, 120 - i * m_slotOffset, 0),
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
			D3DXVECTOR3(-98.4, 134 - (i - 4) * m_slotOffset, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(50, 50, 1));
		m_itemSlots[i]->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [=]()
		{
			if (i >= m_items.size())
				return;
			m_pItemSelectPanel->SetActive(true);
			m_pItemSelectPanel->m_pTransform->SetPosition(m_itemSlots[i]->m_pTransform->m_position);
			m_pItemInfoUI->ShowForShop(D3DXVECTOR3(281, 39, 0), m_items[i]);
		});
		m_itemSlots[i]->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [=]()
		{
			if (i >= m_items.size())
				return;
			m_pItemSelectPanel->SetActive(false);
			m_pItemInfoUI->Hide();
		});
		m_itemSlots[i]->SetButtonEvent(EButtonEvent::RightButtonUp, [=]()
		{
			// 아이템 구매

			if (i >= m_items.size()) return;

			PlayerMoneyData* pData = static_cast<PlayerMoneyData*>(ENGINE->GetScriptableData(L"PlayerMoneyData"));

			if (m_items[i].salePrice > pData->money)
			{
				EventDispatcher::TriggerEvent(GameEvent::NotEnoughMoney);
				return;
			}

			InventoryData* pInventoryData = static_cast<InventoryData*>(ENGINE->GetScriptableData(L"InventoryData"));
			if (pInventoryData->IsFull())
			{
				EventDispatcher::TriggerEvent(GameEvent::InventoryFull);
				return;
			}

			//구매 성공
			pData->money -= m_items[i].salePrice;
			pInventoryData->PushItem(m_items[i]);
			EventDispatcher::TriggerEvent(GameEvent::BuyItem, (void*)&m_items[i]);
			EventDispatcher::TriggerEvent(GameEvent::AddItemToInventory, (void*)&m_items[i]);

		});

		m_itemSlotBacks[i] = UIPanel::Create(GetScene(),
			PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_20.png",
			D3DXVECTOR3(9.6, 134 - (i - 4) * m_slotOffset, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(290, 60, 1),
			L"ShopUI_ItemSlotBack");
		m_itemSlotBacks[i]->SetRenderQueue(3400);

		m_itemSlotPrices[i] = UIPanel::Create(GetScene(),
			PATH->AssetsPathW() + L"UI/BLUILooting_I4_3.png",
			D3DXVECTOR3(135, 120 - (i - 4) * m_slotOffset, 0),
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

	m_items = GetItemInfos();
	
	for (int i = 0; i < m_items.size(); i++)
	{
		auto iconImage = UIPanel::Create(GetScene(),
			m_items[i].imagePath,
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(50, 50, 1),
			L"ItemIcon"
		);
		iconImage->SetRenderQueue(3300);
		iconImage->m_pTransform->SetPosition(m_itemSlots[i]->m_pTransform->m_position);
		m_itemIcons.push_back(iconImage);
	}
	assert(m_items.size() == m_itemIcons.size());


}

void ShopUI::Update()
{
	if (m_bShow)
	{
		/* Title */
		ENGINE->DrawText(GetShopTitle().c_str(), D3DXVECTOR3(179, 148, 0), D3DXVECTOR3(1.3, 1.3, 1.3), D3DXCOLOR(1, 1, 1, 1));

		PlayerMoneyData * pData = static_cast<PlayerMoneyData*>(ENGINE->GetScriptableData(L"PlayerMoneyData"));

		/* 소유한 금액 */
		ENGINE->DrawText(std::to_wstring(pData->money).c_str(), D3DXVECTOR3(566, 589, 0), D3DXVECTOR3(1.2, 1.2, 1.2), D3DXCOLOR(1, 1, 1, 1));

		/* Slot Left */
		for (int i = 0; i < 4; i++)
		{
			if (m_items.size() <= i)
				break;
			ENGINE->DrawText(m_items[i].itemName.c_str(), D3DXVECTOR3(160, 228 + i * m_slotOffset, 0), D3DXVECTOR3(1,1, 1), D3DXCOLOR(1, 1, 1, 1));
			ENGINE->DrawText(m_items[i].typeText.c_str() , D3DXVECTOR3(160, 252 + i * m_slotOffset, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
			ENGINE->DrawText(std::to_wstring( m_items[i].salePrice).c_str(), D3DXVECTOR3(307, 250 + i * m_slotOffset, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		}

		/* Slot Right */
		for (int i = 4; i < 8; i++)
		{
			if (m_items.size() <= i)
				break;
			ENGINE->DrawText(m_items[i].itemName.c_str(), D3DXVECTOR3(452, 228 + (i - 4) * m_slotOffset, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
			ENGINE->DrawText(m_items[i].typeText.c_str(), D3DXVECTOR3(452, 252 + (i - 4) * m_slotOffset, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
			ENGINE->DrawText(std::to_wstring(m_items[i].salePrice).c_str(), D3DXVECTOR3(607, 250 + (i - 4) * m_slotOffset, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
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
	for (int i = 0; i < m_itemIcons.size(); i++)
	{
		m_itemIcons[i]->SetActive(true);
	}
	m_pCenterLine->SetActive(true);
	m_pUnderLine->SetActive(true);
	m_pUnderPanel->SetActive(true);
	m_pCoinIcon->SetActive(true);
	m_pItemSelectPanel->SetActive(false);

	m_bShow = true;
	EventDispatcher::TriggerEvent(UIEvent::ShopUIOpen);
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
	for (int i = 0; i < m_itemIcons.size(); i++)
	{
		m_itemIcons[i]->SetActive(false);
	}
	m_pCenterLine->SetActive(false);
	m_pUnderLine->SetActive(false);
	m_pUnderPanel->SetActive(false);
	m_pCoinIcon->SetActive(false);
	m_pItemSelectPanel->SetActive(false);
	m_pItemInfoUI->Hide();
	m_bShow = false;
	EventDispatcher::TriggerEvent(UIEvent::ShopUIClose);
}

bool ShopUI::IsShow()
{
	return m_bShow;
}
