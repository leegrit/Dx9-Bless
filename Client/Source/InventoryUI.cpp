#include "stdafx.h"
#include "InventoryUI.h"
#include "Button.h"
#include "ProgressBar.h"
#include "PathManager.h"
#include "ItemInfoUI.h"

InventoryUI::InventoryUI(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{

}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Initialize()
{
	m_pBackground = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUISkillBook_I5_0.png",
		D3DXVECTOR3(174.4, 18.4, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(460, 494, 1),
		L"Inventory_Background");

	m_itemSlots.reserve(m_maxSlotCount);
	int slotIndex = 0;
	for (int i = 0; i < m_maxSlotHorizontal; i++)
	{
		for (int j = 0; j < m_maxSlotVertical; j++)
		{
			auto itemSlot = Button::Create(GetScene(),
				L"ItemSlot" + std::to_wstring(slotIndex),
				PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
				D3DXVECTOR3(9 + i * m_slotOffset,99 - j * m_slotOffset, 0),
				D3DXVECTOR3(0, 0, 0),
				D3DXVECTOR3(50, 50, 1)
			);
			itemSlot->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [=]() 
			{
				// ���콺 ����� �� �̺�Ʈ
				m_pItemSelectPanel->SetActive(true);
				m_pItemInfoUI->Show(itemSlot->m_pTransform->m_position.operator D3DXVECTOR3());

				m_pItemSelectPanel->m_pTransform->SetPosition(itemSlot->m_pTransform->m_position);
			});
			itemSlot->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [=]() 
			{
				// ���콺�� �ش� ���� ������ ����� ��
				m_pItemSelectPanel->SetActive(false);
				m_pItemInfoUI->Hide();
			});
			itemSlot->SetButtonEvent(EButtonEvent::ButtonUp, [=]() 
			{
				// ���콺 Ŭ���� �� �̺�Ʈ

			});
			m_itemSlots.push_back(itemSlot);

			slotIndex++;
		}
	}

	m_pItemSelectPanel = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUILooting_I4_1.png",
		D3DXVECTOR3(9, 99, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(50, 50, 1),
		L"ItemSelectPanel");

	m_pUpLine = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIPartyMatching_I11_2.png",
		D3DXVECTOR3(170, 136, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(468, 1, 1),
		L"UpLine");

	m_pUnderLine = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUIPartyMatching_I11_2.png",
		D3DXVECTOR3(170, -103, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(468, 1, 1),
		L"UnderLine");

	m_pTokenExchangeButton = Button::Create(GetScene(),
		L"TokenExchangeButton",
		PATH->AssetsPathW() + L"UI/BLUITokenExchange_IB_0.png",
		D3DXVECTOR3(168 , -223.2, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(250, 35, 1)
	);
	m_pTokenExchangeButton->SetButtonEvent(EButtonEvent::ButtonUp, []() 
	{
		// ��ư ������ �� 
	});

	m_pCoin = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUILooting_I4_3.png",
		D3DXVECTOR3(365.6, -138, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(20, 20, 1),
		L"InventoryCoin");

	m_pItemInfoUI = ItemInfoUI::Create(GetScene(), L"ItemInfoUI");
	m_pItemInfoUI->Hide();
}

void InventoryUI::Update()
{

}

void InventoryUI::Render()
{
	assert(false);
}

void InventoryUI::Show()
{
	m_pBackground->SetActive(true);
	for (auto& itemSlot : m_itemSlots)
	{
		itemSlot->SetActive(true);
	}
	// �̰� �⺻������ false
	// ���Կ� ���콺�� �ø��� Ȱ��ȭ�ȴ�
	m_pItemSelectPanel->SetActive(false);
	m_pUpLine->SetActive(true);
	m_pUnderLine->SetActive(true);
	m_pTokenExchangeButton->SetActive(true);
	m_pCoin->SetActive(true);

	m_bShow = true;
}

void InventoryUI::Hide()
{
	m_pBackground->SetActive(false);
	for (auto& itemSlot : m_itemSlots)
	{
		itemSlot->SetActive(false);
	}
	m_pItemSelectPanel->SetActive(false);
	m_pUpLine->SetActive(false);
	m_pUnderLine->SetActive(false);
	m_pTokenExchangeButton->SetActive(false);
	m_pCoin->SetActive(false);

	m_bShow = false;
}

bool InventoryUI::IsShow()
{
	return m_bShow;
}

InventoryUI * InventoryUI::Create(Scene * pScene, std::wstring name)
{
	InventoryUI * ui = new InventoryUI(pScene, name);
	ui->Initialize();
	return ui;
}
