#include "stdafx.h"
#include "ItemQuickSlotUI.h"
#include "Button.h"
#include "Client_Events.h"
#include "QuickSlotData.h"
#include "GameScene.h"
#include "PathManager.h"
#include "UIPanel.h"
#include "InventoryData.h"
#include "SkillProgressUI.h"


ItemQuickSlotUI::ItemQuickSlotUI(Scene * pScene)
	: GameObject(ERenderType::None,pScene, nullptr, L"ItemQuickSlotUI")
{
	EventDispatcher::AddEventListener(GameEvent::SetQuickSlot, std::to_string(GetInstanceID()).c_str(),
		std::bind(&ItemQuickSlotUI::OnSetQuickSlot, this, placeholders::_1));
	EventDispatcher::AddEventListener(GameEvent::RemoveQuickSlot, std::to_string(GetInstanceID()).c_str(),
		std::bind(&ItemQuickSlotUI::OnRemoveQuickSlot, this, placeholders::_1));
}

ItemQuickSlotUI::~ItemQuickSlotUI()
{
	EventDispatcher::RemoveEventListener(GameEvent::SetQuickSlot, std::to_string(GetInstanceID()).c_str());
	EventDispatcher::RemoveEventListener(GameEvent::RemoveQuickSlot, std::to_string(GetInstanceID()).c_str());
}

void ItemQuickSlotUI::Initialize()
{
	m_pQuickSlotData = static_cast<QuickSlotData*>( ENGINE->GetScriptableData(L"QuickSlotData"));
	assert(m_pQuickSlotData);
	m_pInventoryData = static_cast<InventoryData*>(ENGINE->GetScriptableData(L"InventoryData"));


	for (int i = 0; i < m_maxSlotHorizontal; i++)
	{
		int slotIndex = i;
		auto slotButton = Button::Create(GetScene(),
			L"slotButton" + std::to_wstring(i),
			L"",
			D3DXVECTOR3(m_slotXPoses[i], m_slotYPos, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(30, 30, 1));
		
		auto itemIcon = UIPanel::Create(GetScene(),
			L"",
			D3DXVECTOR3(m_slotXPoses[i], m_slotYPos, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(30, 30, 1), 
			L"QuickSlot_ItemIcon");

		auto progress = SkillProgressUI::Create(GetScene(),
			PATH->ResourcesPathW() + L"Assets/UI/black.png",
			D3DXVECTOR3(m_slotXPoses[i], m_slotYPos, 0),
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(30, 30, 1),
			L"QuickSlotProgressUI");

		itemIcon->SetActive(false);

		m_slotButtons.push_back(slotButton);
		m_itemIcons.push_back(itemIcon);
		m_progressUI.push_back(progress);

		slotButton->SetButtonEvent(EButtonEvent::RightButtonUp, [=]()
		{
			if (slotIndex >= m_pQuickSlotData->GetCount())
				return;

			ItemInfo itemInfo;
			bool isSucceeded = m_pQuickSlotData->TryGetItem(slotIndex, &itemInfo);
			assert(isSucceeded);

			//GameScene* pScene = static_cast<GameScene*>(SCENE);
			m_pQuickSlotData->RemoveItem(itemInfo);
		});


	}

}

void ItemQuickSlotUI::Update()
{

	//if (KEYBOARD->Down(VK_F1))
	//{
	//	bool isExist = m_pQuickSlotData->ExitItem(0);
	//	if (isExist)
	//	{
	//		if (m_pQuickSlotData->GetItem(0).curCoolTime >= m_pQuickSlotData->GetItem(0).coolTime)
	//		{
	//			m_pQuickSlotData->ResetCoolTime(0);
	//			m_pInventoryData->RemoveItem(m_pQuickSlotData->GetItem(0));
	//			ItemInfo itemInfo;
	//			// 아직 아이템이 남아있는지 확인
	//			bool bOk = m_pInventoryData->TryGetItem(m_pQuickSlotData->GetItem(0).itemName, &itemInfo);
	//			if (bOk == false) // 잔량이 0개일 경우 퀵슬롯에서 제외
	//			{
	//				m_pQuickSlotData->RemoveItem(m_pQuickSlotData->GetItem(0));
	//			}
	//		}
	//		
	//	}
	//}

	for (int i = 0; i < m_pQuickSlotData->GetCount(); i++)
	{
		
		float amount = m_pQuickSlotData->GetItem(i).curCoolTime / m_pQuickSlotData->GetItem(i).coolTime;
		m_progressUI[i]->SetAmount(amount);
	}

}

void ItemQuickSlotUI::Render()
{
}

void ItemQuickSlotUI::OnSetQuickSlot(void * pItemInfo)
{
	assert(m_bShow);

	for (int i = 0; i < m_pQuickSlotData->GetCount(); i++)
	{
		ItemInfo itemInfo;
		bool bOK = m_pQuickSlotData->TryGetItem(i, &itemInfo);
		assert(bOK);

		m_itemIcons[i]->SetTexture(itemInfo.imagePath);
		m_itemIcons[i]->SetActive(true);
		m_progressUI[i]->SetActive(true);
	}
	for (int i = m_pQuickSlotData->GetCount(); i < m_itemIcons.size(); i++)
	{
		m_itemIcons[i]->SetActive(false);
		m_progressUI[i]->SetActive(false);
	}
}

void ItemQuickSlotUI::OnRemoveQuickSlot(void *pItemInfo)
{
	assert(m_bShow);

	for (int i = 0; i < m_pQuickSlotData->GetCount(); i++)
	{
		ItemInfo itemInfo;
		bool bOK = m_pQuickSlotData->TryGetItem(i, &itemInfo);
		assert(bOK);

		m_itemIcons[i]->SetTexture(itemInfo.imagePath);
		m_itemIcons[i]->SetActive(true);
		m_progressUI[i]->SetActive(true);
	}
	for (int i = m_pQuickSlotData->GetCount(); i < m_itemIcons.size(); i++)
	{
		m_itemIcons[i]->SetActive(false);
		m_itemIcons[i]->SetActive(false);
	}
}

void ItemQuickSlotUI::Show()
{
	for (int i = 0; i < m_pQuickSlotData->GetCount(); i++)
	{
		ItemInfo itemInfo;
		bool bOK = m_pQuickSlotData->TryGetItem(i, &itemInfo);
		assert(bOK);
		m_itemIcons[i]->SetTexture(itemInfo.imagePath);
		m_itemIcons[i]->SetActive(true);
		m_progressUI[i]->SetActive(true);
	}
	
	// 버튼 비활성화
	for (int i = 0; i < m_slotButtons.size(); i++)
	{
		m_slotButtons[i]->SetActive(false);
		m_progressUI[i]->SetActive(false);
	}

	m_bShow = true;
}

void ItemQuickSlotUI::Hide()
{
	for (int i = 0; i < m_itemIcons.size(); i++)
	{
		m_itemIcons[i]->SetActive(false);
		m_progressUI[i]->SetActive(false);
	}

	// 버튼 활성화
	for (int i = 0; i < m_slotButtons.size(); i++)
	{
		m_slotButtons[i]->SetActive(true);
	}

	m_bShow = false;
}

bool ItemQuickSlotUI::IsShow()
{
	return m_bShow;
}

ItemQuickSlotUI * ItemQuickSlotUI::Create(Scene * pScene)
{
	ItemQuickSlotUI * ui = new ItemQuickSlotUI(pScene);
	ui->Initialize();
	return ui;
}
