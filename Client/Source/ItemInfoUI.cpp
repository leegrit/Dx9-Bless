#include "stdafx.h"
#include "ItemInfoUI.h"
#include "PathManager.h"

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
	m_pBackground->SetRenderQueue(2800);
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
}

void ItemInfoUI::Render()
{
	assert(false);
}

void ItemInfoUI::Show(D3DXVECTOR3 itemSlotPosition, bool bInventory)
{
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
}

void ItemInfoUI::Hide()
{
	m_pBackground->SetActive(false);
	m_pCoinIcon->SetActive(false);
}

ItemInfoUI * ItemInfoUI::Create(Scene * pScene, std::wstring name)
{
	ItemInfoUI* ui = new ItemInfoUI(pScene, name);
	ui->Initialize();
	return ui;
}
