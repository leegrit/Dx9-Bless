#include "stdafx.h"
#include "ItemInfoUI.h"
#include "PathManager.h"
#include "ItemInfo.h"

ItemInfoUI::ItemInfoUI(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{

}

ItemInfoUI::~ItemInfoUI()
{
}

void ItemInfoUI::Initialize()
{
	m_pBackground = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUILetterInfo_I1_0.png",
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(250, 300, 1),
		L"ItemInfoBackground");
	m_pBackground->SetRenderQueue(3000);
	m_backGroundOriginPos = m_pBackground->m_pTransform->m_position.operator D3DXVECTOR3();

	m_pCoinIcon = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUILooting_I4_3.png",
		D3DXVECTOR3(103, -111, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(15, 15, 1),
		L"ItemInfo_CoinIcon");
	m_pCoinIcon->SetRenderQueue(2800);
	m_coinIconOriginPos = m_pCoinIcon->m_pTransform->m_position.operator D3DXVECTOR3();

	


}

void ItemInfoUI::Update()
{
	if (m_bShow)
	{
		if (m_showItemInfo.itemType == EItemType::None)
			return;

		ENGINE->DrawText(m_showItemInfo.itemName.c_str(), m_titlePosition, D3DXVECTOR3(1.4, 1.4, 1.4), D3DXCOLOR(1, 1, 1, 1));
	
		ENGINE->DrawText(m_showItemInfo.typeText.c_str(), m_typePosition, D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

		ENGINE->DrawText(m_showItemInfo.effectText.c_str(), m_effectPosition, D3DXVECTOR3(1, 1, 1), D3DXCOLOR(0, 0.55, 0.38, 1));

		std::wstring saleText;
		std::wstring dstrText;
		if (m_showItemInfo.availableForSale == true)
		{
			saleText = L"판매 가능";
			ENGINE->DrawText(saleText.c_str(), m_salePosition, D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		}
		else
		{
			saleText = L"판매 불가능";
			ENGINE->DrawText(saleText.c_str(), m_salePosition, D3DXVECTOR3(1, 1, 1), D3DXCOLOR(0, 0.7, 0, 1));
		}
		if (m_showItemInfo.availableForDestruction == true)
		{
			dstrText = L"파괴 가능";
			ENGINE->DrawText(dstrText.c_str(), m_dstrPosition, D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		}
		else
		{
			dstrText = L"파괴 불가능";
			ENGINE->DrawText(dstrText.c_str(), m_dstrPosition, D3DXVECTOR3(1, 1, 1), D3DXCOLOR(0, 0.7, 0, 1));
		}

		ENGINE->DrawText(std::to_wstring(m_showItemInfo.salePrice).c_str(), m_pricePosition, D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

		
		
	}
}

void ItemInfoUI::Render()
{
	assert(false);
}

void ItemInfoUI::Show(D3DXVECTOR3 itemSlotPosition, ItemInfo itemInfo,  bool bInventory)
{
	m_showItemInfo = itemInfo;
	m_itemSlotPosition = itemSlotPosition;
	if (bInventory)
	{
		m_pTransform->m_position = m_itemSlotPosition + m_posOffset;
	}
	else
	{
		m_pTransform->m_position = m_itemSlotPosition + m_equipUIOffset;
	}
	m_pBackground->m_pTransform->m_position = m_backGroundOriginPos + m_pTransform->m_position.operator D3DXVECTOR3();
	m_pBackground->SetActive(true);
	m_pCoinIcon->m_pTransform->m_position = m_coinIconOriginPos + m_pTransform->m_position.operator D3DXVECTOR3();
	m_pCoinIcon->SetActive(true);
	//m_pCoinIcon->SetRenderQueue(2900);
	

	m_titlePosition.x = m_titleOriginPos.x + m_pTransform->m_position.operator D3DXVECTOR3().x;
	m_titlePosition.y = m_titleOriginPos.y - m_pTransform->m_position.operator D3DXVECTOR3().y;
	m_titlePosition.z = 0;

	m_typePosition.x = m_typeOriginPos.x + m_pTransform->m_position.operator D3DXVECTOR3().x;
	m_typePosition.y = m_typeOriginPos.y - m_pTransform->m_position.operator D3DXVECTOR3().y;
	m_typePosition.z = 0;

	m_effectPosition.x = m_effectOriginPos.x + m_pTransform->m_position.operator D3DXVECTOR3().x;
	m_effectPosition.y = m_effectOriginPos.y - m_pTransform->m_position.operator D3DXVECTOR3().y;
	m_effectPosition.z = 0;

	m_salePosition.x = m_saleOriginPos.x + m_pTransform->m_position.operator D3DXVECTOR3().x;
	m_salePosition.y = m_saleOriginPos.y - m_pTransform->m_position.operator D3DXVECTOR3().y;
	m_salePosition.z = 0;

	m_dstrPosition.x = m_dstrOriginPos.x + m_pTransform->m_position.operator D3DXVECTOR3().x;
	m_dstrPosition.y = m_dstrOriginPos.y - m_pTransform->m_position.operator D3DXVECTOR3().y;
	m_dstrPosition.z = 0;

	m_pricePosition.x = m_priceOriginPos.x + m_pTransform->m_position.operator D3DXVECTOR3().x;
	m_pricePosition.y = m_priceOriginPos.y - m_pTransform->m_position.operator D3DXVECTOR3().y;
	m_pricePosition.z = 0;


	m_bShow = true;
}

void ItemInfoUI::ShowForShop(D3DXVECTOR3 position, ItemInfo itemInfo )
{
	m_showItemInfo = itemInfo;
	m_pBackground->m_pTransform->m_position = m_backGroundOriginPos + position;
	m_pBackground->SetActive(true);
	m_pCoinIcon->m_pTransform->m_position = m_coinIconOriginPos + position;
	m_pCoinIcon->SetActive(true);
	//m_pCoinIcon->SetRenderQueue(2900);

	m_titlePosition.x = m_titleOriginPos.x + position.x;
	m_titlePosition.y = m_titleOriginPos.y - position.y;
	m_titlePosition.z = 0;

	m_typePosition.x = m_typeOriginPos.x + position.x;
	m_typePosition.y = m_typeOriginPos.y - position.y;
	m_typePosition.z = 0;

	m_effectPosition.x = m_effectOriginPos.x + position.x;
	m_effectPosition.y = m_effectOriginPos.y - position.y;
	m_effectPosition.z = 0;

	m_salePosition.x = m_saleOriginPos.x + position.x;
	m_salePosition.y = m_saleOriginPos.y - position.y;
	m_salePosition.z = 0;

	m_dstrPosition.x = m_dstrOriginPos.x + position.x;
	m_dstrPosition.y = m_dstrOriginPos.y - position.y;
	m_dstrPosition.z = 0;

	m_pricePosition.x = m_priceOriginPos.x + position.x;
	m_pricePosition.y = m_priceOriginPos.y - position.y;
	m_pricePosition.z = 0;
	
	m_bShow = true;
}

void ItemInfoUI::Hide()
{
	m_pBackground->SetActive(false);
	m_pCoinIcon->SetActive(false);

	m_bShow = false;
}

ItemInfoUI * ItemInfoUI::Create(Scene * pScene, std::wstring name)
{
	ItemInfoUI* ui = new ItemInfoUI(pScene, name);
	ui->Initialize();
	return ui;
}
