#include "stdafx.h"
#include "InventoryUI.h"
#include "Button.h"
#include "ProgressBar.h"
#include "PathManager.h"
#include "ItemInfoUI.h"
#include "InventoryData.h"
#include "Client_Events.h"
#include "PlayerMoneyData.h"
#include "GameScene.h"
#include "PlayerEquipData.h"
#include "QuickSlotData.h"
#include "SoundManager.h"

InventoryUI::InventoryUI(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{
	EventDispatcher::AddEventListener(GameEvent::AddItemToInventory, std::to_string(GetInstanceID()).c_str(),
		std::bind(&InventoryUI::OnAddItemToInventory, this, placeholders::_1));
	EventDispatcher::AddEventListener(GameEvent::RemoveItemToInventory, std::to_string(GetInstanceID()).c_str(),
		std::bind(&InventoryUI::OnRemoveItemToInventory, this, placeholders::_1));
}

InventoryUI::~InventoryUI()
{
	EventDispatcher::RemoveEventListener(GameEvent::AddItemToInventory, std::to_string(GetInstanceID()).c_str());
	EventDispatcher::RemoveEventListener(GameEvent::RemoveItemToInventory, std::to_string(GetInstanceID()).c_str());
}

void InventoryUI::Initialize()
{
	m_pBackground = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUISkillBook_I5_0.png",
		D3DXVECTOR3(174.4, 18.4, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(460, 494, 1),
		L"Inventory_Background");
	m_pBackground->SetRenderQueue(3500);


	m_itemSlots.reserve(m_maxSlotCount);
	int slotIndex = 0;
	for (int i = 0; i < m_maxSlotVertical; i++)
	{
		for (int j = 0; j < m_maxSlotHorizontal; j++)
		{
			auto itemSlot = Button::Create(GetScene(),
				L"ItemSlot" + std::to_wstring(slotIndex),
				PATH->AssetsPathW() + L"UI/BLUIOpener_I3_0.png",
				D3DXVECTOR3(9 + j * m_slotOffset,99 - i * m_slotOffset, 0),
				D3DXVECTOR3(0, 0, 0),
				D3DXVECTOR3(50, 50, 1)
			);


			auto itemIcon = UIPanel::Create(GetScene(),
				L"",
				D3DXVECTOR3(9 + j * m_slotOffset, 99 - i * m_slotOffset, 0),
				D3DXVECTOR3(0, 0, 0),
				D3DXVECTOR3(50, 50, 1),
				L"Item_Icon");
			itemIcon->SetRenderQueue(3300);
			itemIcon->SetActive(false);

			m_itemIcons.push_back(itemIcon);


			itemSlot->SetButtonEvent(EButtonEvent::ButtonCollisionStay, [=]() 
			{
				// 마우스 얹었을 때 이벤트
				if (slotIndex >= m_pInventoryData->GetCount())
					return;

				m_pItemSelectPanel->SetActive(true);
				m_pItemInfoUI->Show(itemSlot->m_pTransform->m_position.operator D3DXVECTOR3(), m_pInventoryData->GetItem(slotIndex));

				m_pItemSelectPanel->m_pTransform->SetPosition(itemSlot->m_pTransform->m_position);
			});
			itemSlot->SetButtonEvent(EButtonEvent::ButtonCollisionExit, [=]() 
			{
				// 마우스가 해당 슬롯 밖으로 벗어났을 때
				if (slotIndex >= m_pInventoryData->GetCount())
					return;

				m_pItemSelectPanel->SetActive(false);
				m_pItemInfoUI->Hide();
			});
			itemSlot->SetButtonEvent(EButtonEvent::RightButtonUp, [=]() 
			{
				// 마우스 클릭할 때 이벤트

				if (slotIndex >= m_pInventoryData->GetCount())
					return;
				m_pItemSelectPanel->SetActive(false);
				m_pItemInfoUI->Hide();
				ItemInfo itemInfo;
				bool isSucceeded = m_pInventoryData->TryGetItem(slotIndex, &itemInfo);
				assert(isSucceeded);

				GameScene* pScene = static_cast<GameScene*>(SCENE);
				switch (itemInfo.itemType)
				{
				case EItemType::CollectItem :
					break;
				case EItemType::QuestItem : 
					break; 
				case EItemType::SkillBook :
					EventDispatcher::TriggerEvent(GameEvent::UseSkillBook, (void*)&itemInfo);
					m_pInventoryData->RemoveItem(itemInfo);
					break;
				case EItemType::Item : 
					//EventDispatcher::TriggerEvent(GameEvent::UseItem, (void*)&itemInfo);
					//m_pInventoryData->RemoveItem(itemInfo);
					if(m_pQuickSlotData->ExistItem(itemInfo) == false)
						m_pQuickSlotData->PushItem(itemInfo);
					break;
				case EItemType::Belt : 
					EventDispatcher::TriggerEvent(GameEvent::WearItem, (void*)&itemInfo);
					if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Belt))
					{
						if (pScene->GetPlayerEquipData()->CompareEquipment(EEquipSlot::Belt, itemInfo))
						{
							break;
						}
						else
						{
							pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Belt, itemInfo);
							//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
							m_pInventoryData->RemoveItem(itemInfo);
						}
					}
					else
					{
						pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Belt, itemInfo);
						//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
						m_pInventoryData->RemoveItem(itemInfo);
					}
					break;
				case EItemType::Boots :
					EventDispatcher::TriggerEvent(GameEvent::WearItem, (void*)&itemInfo);
					if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Boots))
					{
						if (pScene->GetPlayerEquipData()->CompareEquipment(EEquipSlot::Boots, itemInfo))
						{
							break;
						}
						else
						{
							pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Boots, itemInfo);
							//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
							m_pInventoryData->RemoveItem(itemInfo);
						}
					}
					else
					{
						pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Boots, itemInfo);
						//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
						m_pInventoryData->RemoveItem(itemInfo);
					}
					break;
				case EItemType::Glove :
					EventDispatcher::TriggerEvent(GameEvent::WearItem, (void*)&itemInfo);
					if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Glove))
					{
						if (pScene->GetPlayerEquipData()->CompareEquipment(EEquipSlot::Glove, itemInfo))
						{
							break;
						}
						else
						{
							pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Glove, itemInfo);
							//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
							m_pInventoryData->RemoveItem(itemInfo);
						}
					}
					else
					{
						pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Glove, itemInfo);
						//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
						m_pInventoryData->RemoveItem(itemInfo);
					}
					break;
				case EItemType::Helmet :
					EventDispatcher::TriggerEvent(GameEvent::WearItem, (void*)&itemInfo);
					if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Helmet))
					{
						if (pScene->GetPlayerEquipData()->CompareEquipment(EEquipSlot::Helmet, itemInfo))
						{
							break;
						}
						else
						{
							pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Helmet, itemInfo);
							//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
							m_pInventoryData->RemoveItem(itemInfo);
						}
					}
					else
					{
						pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Helmet, itemInfo);
						//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
						m_pInventoryData->RemoveItem(itemInfo);
					}
					break;
				case EItemType::Lower :
					EventDispatcher::TriggerEvent(GameEvent::WearItem, (void*)&itemInfo);
					if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Lower))
					{
						if (pScene->GetPlayerEquipData()->CompareEquipment(EEquipSlot::Lower, itemInfo))
						{
							break;
						}
						else
						{
							pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Lower, itemInfo);
							//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
							m_pInventoryData->RemoveItem(itemInfo);
						}
					}
					else
					{
						pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Lower, itemInfo);
						//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
						m_pInventoryData->RemoveItem(itemInfo);
					}
					break;
				case EItemType::Shoulder :
					EventDispatcher::TriggerEvent(GameEvent::WearItem, (void*)&itemInfo);
					if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Shoulder))
					{
						if (pScene->GetPlayerEquipData()->CompareEquipment(EEquipSlot::Shoulder, itemInfo))
						{
							break;
						}
						else
						{
							pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Shoulder, itemInfo);
							//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
							m_pInventoryData->RemoveItem(itemInfo);
						}
					}
					else
					{
						pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Shoulder, itemInfo);
						//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
						m_pInventoryData->RemoveItem(itemInfo);
					}
					break;
				case EItemType::Upper:
					EventDispatcher::TriggerEvent(GameEvent::WearItem, (void*)&itemInfo);
					if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Upper))
					{
						if (pScene->GetPlayerEquipData()->CompareEquipment(EEquipSlot::Upper, itemInfo))
						{
							break;
						}
						else
						{
							pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Upper, itemInfo);
							//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
							m_pInventoryData->RemoveItem(itemInfo);
						}
					}
					else
					{
						pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Upper, itemInfo);
						//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
						m_pInventoryData->RemoveItem(itemInfo);
					}
					break;
				case EItemType::Weapon:
					EventDispatcher::TriggerEvent(GameEvent::WearItem, (void*)&itemInfo);
					if (pScene->GetPlayerEquipData()->IsExistEquipment(EEquipSlot::Weapon))
					{
						if (pScene->GetPlayerEquipData()->CompareEquipment(EEquipSlot::Weapon, itemInfo))
						{
							break;
						}
						else
						{
							pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Weapon, itemInfo);
							//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
							m_pInventoryData->RemoveItem(itemInfo);
						}
					}
					else
					{
						pScene->GetPlayerEquipData()->ChangeEquipment(EEquipSlot::Weapon, itemInfo);
						//EventDispatcher::TriggerEvent(GameEvent::EquipmentChange, (void*)&itemInfo);
						m_pInventoryData->RemoveItem(itemInfo);
					}
					break;
				default: 
					break;

				}

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
		// 버튼 눌렀을 때 
	});

	m_pCoin = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/BLUILooting_I4_3.png",
		D3DXVECTOR3(365.6, -138, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(20, 20, 1),
		L"InventoryCoin");

	m_pItemInfoUI = ItemInfoUI::Create(GetScene(), L"ItemInfoUI");
	m_pItemInfoUI->Hide();


	m_pInventoryData = static_cast<InventoryData*>(ENGINE->GetScriptableData(L"InventoryData"));
	m_pQuickSlotData = static_cast<QuickSlotData*>(ENGINE->GetScriptableData(L"QuickSlotData"));
}

void InventoryUI::Update()
{
	if (m_bShow)
	{
		PlayerMoneyData* pData = static_cast<PlayerMoneyData*>(ENGINE->GetScriptableData(L"PlayerMoneyData"));

		int slotIndex = 0;
		for (int i = 0; i < m_maxSlotVertical; i++)
		{
			for (int j = 0; j < m_maxSlotHorizontal; j++)
			{

				ItemInfo itemInfo;
				bool bOk = m_pInventoryData->TryGetItem(slotIndex, &itemInfo);
				if (bOk == false)
					continue;
				if (itemInfo.itemType == EItemType::Item ||
					itemInfo.itemType == EItemType::Spoils)
				{
					int count = m_pInventoryData->GetOverlapCount(slotIndex);
					ENGINE->DrawText(std::to_wstring(count).c_str(), D3DXVECTOR3(20+ 512 + 9 + j * m_slotOffset,10+ 384 - (99 - i * m_slotOffset), 0), D3DXVECTOR3(0.7f, 0.7f, 0.7f), D3DXCOLOR(1, 1, 1, 1));

				}



				slotIndex++;
			}
		}


		ENGINE->DrawText(L"소지품", D3DXVECTOR3(556, 140, 0), D3DXVECTOR3(1.3, 1.3, 1.3), D3DXCOLOR(1, 1, 1, 1));
		ENGINE->DrawText(std::to_wstring(pData->money).c_str(), D3DXVECTOR3(812, 509, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
		ENGINE->DrawText(L"잡동사니 모두 팔기", D3DXVECTOR3(643, 597, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

	}
}

void InventoryUI::Render()
{
	assert(false);
}

void InventoryUI::OnAddItemToInventory(void* arg)
{
	if (m_bShow == true)
	{
		for (int i = 0; i < m_pInventoryData->GetCount(); i++)
		{
			ItemInfo itemInfo;
			bool bOk = m_pInventoryData->TryGetItem(i, &itemInfo);
			assert(bOk);

			m_itemIcons[i]->SetTexture(itemInfo.imagePath);
			m_itemIcons[i]->SetActive(true);
		}
		for (int j = m_pInventoryData->GetCount(); j < m_itemIcons.size(); j++)
		{
			m_itemIcons[j]->SetActive(false);
		}
	}
}

void InventoryUI::OnRemoveItemToInventory(void* arg)
{
	if (m_bShow == true)
	{
		for (int i = 0; i < m_pInventoryData->GetCount(); i++)
		{
			ItemInfo itemInfo;
			bool bOk = m_pInventoryData->TryGetItem(i, &itemInfo);
			assert(bOk);

			m_itemIcons[i]->SetTexture(itemInfo.imagePath);
			m_itemIcons[i]->SetActive(true);
		}
		for (int j = m_pInventoryData->GetCount(); j < m_itemIcons.size(); j++)
		{
			m_itemIcons[j]->SetActive(false);
		}
	}
}

void InventoryUI::Show()
{
	m_pBackground->SetActive(true);
	for (auto& itemSlot : m_itemSlots)
	{
		itemSlot->SetActive(true);
	}
	for (int i = 0; i < m_pInventoryData->GetCount(); i++)
	{
		ItemInfo itemInfo;
		bool bOk = m_pInventoryData->TryGetItem(i, &itemInfo);
		assert(bOk);

		m_itemIcons[i]->SetTexture(itemInfo.imagePath);
		m_itemIcons[i]->SetActive(true);
	}

	// 이건 기본적으로 false
	// 슬롯에 마우스를 올리면 활성화된다
	m_pItemSelectPanel->SetActive(false);
	m_pUpLine->SetActive(true);
	m_pUnderLine->SetActive(true);
	m_pTokenExchangeButton->SetActive(true);
	m_pCoin->SetActive(true);

	m_bShow = true;
	EventDispatcher::TriggerEvent(UIEvent::InventoryUIOpen);

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->PlaySound("Inven_Open", L"Inven_Open.wav", desc);


}

void InventoryUI::Hide()
{
	m_pBackground->SetActive(false);
	for (auto& itemSlot : m_itemSlots)
	{
		itemSlot->SetActive(false);
	}
	// Show할 땐 현재 존재하는 아이템만 출력하고
	// hide할 때 모두 hid
	for (int i = 0; i < m_itemIcons.size(); i++)
	{
		m_itemIcons[i]->SetActive(false);
	}
	m_pItemSelectPanel->SetActive(false);
	m_pUpLine->SetActive(false);
	m_pUnderLine->SetActive(false);
	m_pTokenExchangeButton->SetActive(false);
	m_pCoin->SetActive(false);
	m_pItemInfoUI->Hide();
	m_bShow = false;
	EventDispatcher::TriggerEvent(UIEvent::InventoryUIClose);

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->PlaySound("Inven_Close", L"Inven_Close.wav", desc);
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
