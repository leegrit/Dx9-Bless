#include "stdafx.h"
#include "ItemManager.h"
#include "QuickSlotData.h"
#include "InventoryData.h"
#include "Client_Events.h"
#include "SoundManager.h"
#include "PlayerSkillInfo.h"

ItemManager::ItemManager(GameScene * pScene)
{
	EventDispatcher::AddEventListener(GameEvent::UseSkillBook, "ItemManager",
		std::bind(&ItemManager::OnUseSkillBook, this, placeholders::_1));
}

ItemManager::~ItemManager()
{
	EventDispatcher::RemoveEventListener(GameEvent::UseSkillBook, "ItemManager");
}

void ItemManager::OnUseSkillBook(void * pItemInfo)
{
	ItemInfo itemInfo = *static_cast<ItemInfo*>(pItemInfo);
	EventDispatcher::TriggerEvent(GameEvent::GainSkill, &itemInfo.itemValue);
	m_pPlayerSkillInfo->isLock[itemInfo.itemValue] = false;
}

void ItemManager::Initialize()
{
	m_pQuickSlotData = static_cast<QuickSlotData*>(ENGINE->GetScriptableData(L"QuickSlotData"));
	m_pInventoryData = static_cast<InventoryData*>(ENGINE->GetScriptableData(L"InventoryData"));
	m_pPlayerSkillInfo = static_cast<PlayerSkillInfo*>(ENGINE->GetScriptableData(L"PlayerSkillInfo"));
}

void ItemManager::Update()
{
	if (KEYBOARD->Down(VK_F1))
	{
		bool isExist = m_pQuickSlotData->ExitItem(0);
		if (isExist)
		{
			if (m_pQuickSlotData->GetItem(0).curCoolTime >= m_pQuickSlotData->GetItem(0).coolTime)
			{

				ItemInfo useItemInfo = m_pQuickSlotData->GetItem(0);
				UseItem(useItemInfo);
				m_pQuickSlotData->ResetCoolTime(0);
				m_pInventoryData->RemoveItem(m_pQuickSlotData->GetItem(0));
				ItemInfo itemInfo;
				// 아직 아이템이 남아있는지 확인
				bool bOk = m_pInventoryData->TryGetItem(m_pQuickSlotData->GetItem(0).itemName, &itemInfo);
				if (bOk == false) // 잔량이 0개일 경우 퀵슬롯에서 제외
				{
					m_pQuickSlotData->RemoveItem(m_pQuickSlotData->GetItem(0));
				}
			}
		}
	}
	if (KEYBOARD->Down(VK_F2))
	{
		bool isExist = m_pQuickSlotData->ExitItem(1);
		if (isExist)
		{
			if (m_pQuickSlotData->GetItem(1).curCoolTime >= m_pQuickSlotData->GetItem(1).coolTime)
			{
				ItemInfo useItemInfo = m_pQuickSlotData->GetItem(1);
				UseItem(useItemInfo);
				m_pQuickSlotData->ResetCoolTime(1);
				m_pInventoryData->RemoveItem(m_pQuickSlotData->GetItem(1));
				ItemInfo itemInfo;
				// 아직 아이템이 남아있는지 확인
				bool bOk = m_pInventoryData->TryGetItem(m_pQuickSlotData->GetItem(1).itemName, &itemInfo);
				if (bOk == false) // 잔량이 0개일 경우 퀵슬롯에서 제외
				{
					m_pQuickSlotData->RemoveItem(m_pQuickSlotData->GetItem(1));
				}
			}
		}
	}
	if (KEYBOARD->Down(VK_F3))
	{
		bool isExist = m_pQuickSlotData->ExitItem(2);
		if (isExist)
		{
			if (m_pQuickSlotData->GetItem(2).curCoolTime >= m_pQuickSlotData->GetItem(2).coolTime)
			{
				ItemInfo useItemInfo = m_pQuickSlotData->GetItem(2);
				UseItem(useItemInfo);
				m_pQuickSlotData->ResetCoolTime(2);
				m_pInventoryData->RemoveItem(m_pQuickSlotData->GetItem(2));
				ItemInfo itemInfo;
				// 아직 아이템이 남아있는지 확인
				bool bOk = m_pInventoryData->TryGetItem(m_pQuickSlotData->GetItem(2).itemName, &itemInfo);
				if (bOk == false) // 잔량이 0개일 경우 퀵슬롯에서 제외
				{
					m_pQuickSlotData->RemoveItem(m_pQuickSlotData->GetItem(2));
				}
			}
		}
	}
	if(KEYBOARD->Down(VK_F4))
	{
		bool isExist = m_pQuickSlotData->ExitItem(3);
		if (isExist)
		{
			if (m_pQuickSlotData->GetItem(3).curCoolTime >= m_pQuickSlotData->GetItem(2).coolTime)
			{
				ItemInfo useItemInfo = m_pQuickSlotData->GetItem(3);
				UseItem(useItemInfo);
				m_pQuickSlotData->ResetCoolTime(3);
				m_pInventoryData->RemoveItem(m_pQuickSlotData->GetItem(3));
				ItemInfo itemInfo;
				// 아직 아이템이 남아있는지 확인
				bool bOk = m_pInventoryData->TryGetItem(m_pQuickSlotData->GetItem(3).itemName, &itemInfo);
				if (bOk == false) // 잔량이 0개일 경우 퀵슬롯에서 제외
				{
					m_pQuickSlotData->RemoveItem(m_pQuickSlotData->GetItem(3));
				}
			}
		}
	}
	if (KEYBOARD->Down(VK_F5))
	{
		bool isExist = m_pQuickSlotData->ExitItem(4);
		if (isExist)
		{
			if (m_pQuickSlotData->GetItem(4).curCoolTime >= m_pQuickSlotData->GetItem(4).coolTime)
			{
				ItemInfo useItemInfo = m_pQuickSlotData->GetItem(4);
				UseItem(useItemInfo);
				m_pQuickSlotData->ResetCoolTime(4);
				m_pInventoryData->RemoveItem(m_pQuickSlotData->GetItem(4));
				ItemInfo itemInfo;
				// 아직 아이템이 남아있는지 확인
				bool bOk = m_pInventoryData->TryGetItem(m_pQuickSlotData->GetItem(4).itemName, &itemInfo);
				if (bOk == false) // 잔량이 0개일 경우 퀵슬롯에서 제외
				{
					m_pQuickSlotData->RemoveItem(m_pQuickSlotData->GetItem(4));
				}
			}
		}
	}
	if (KEYBOARD->Down(VK_F6))
	{
		bool isExist = m_pQuickSlotData->ExitItem(5);
		if (isExist)
		{
			if (m_pQuickSlotData->GetItem(5).curCoolTime >= m_pQuickSlotData->GetItem(5).coolTime)
			{
				ItemInfo useItemInfo = m_pQuickSlotData->GetItem(5);
				UseItem(useItemInfo);
				m_pQuickSlotData->ResetCoolTime(5);
				m_pInventoryData->RemoveItem(m_pQuickSlotData->GetItem(5));
				ItemInfo itemInfo;
				// 아직 아이템이 남아있는지 확인
				bool bOk = m_pInventoryData->TryGetItem(m_pQuickSlotData->GetItem(5).itemName, &itemInfo);
				if (bOk == false) // 잔량이 0개일 경우 퀵슬롯에서 제외
				{
					m_pQuickSlotData->RemoveItem(m_pQuickSlotData->GetItem(5));
				}
			}
		}
	}
	if (KEYBOARD->Down(VK_F7))
	{
		bool isExist = m_pQuickSlotData->ExitItem(6);
		if (isExist)
		{
			if (m_pQuickSlotData->GetItem(6).curCoolTime >= m_pQuickSlotData->GetItem(6).coolTime)
			{
				ItemInfo useItemInfo = m_pQuickSlotData->GetItem(6);
				UseItem(useItemInfo);
				m_pQuickSlotData->ResetCoolTime(6);
				m_pInventoryData->RemoveItem(m_pQuickSlotData->GetItem(6));
				ItemInfo itemInfo;
				// 아직 아이템이 남아있는지 확인
				bool bOk = m_pInventoryData->TryGetItem(m_pQuickSlotData->GetItem(6).itemName, &itemInfo);
				if (bOk == false) // 잔량이 0개일 경우 퀵슬롯에서 제외
				{
					m_pQuickSlotData->RemoveItem(m_pQuickSlotData->GetItem(6));
				}
			}
		}
	}

	for (int i = 0; i < m_pQuickSlotData->GetCount(); i++)
	{
		m_pQuickSlotData->IncreaseCoolTime(i);
	}
}

void ItemManager::UseItem(ItemInfo info)
{
	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->PlaySound("UsePotionSound", L"PotionSound.ogg", desc);
	EventDispatcher::TriggerEvent(GameEvent::UseItem, (void*)&info);
	switch (info.buffType)
	{
	case EItemBuffType::HPHeal:
		break;
	case EItemBuffType::MPHeal:
		break;
	case EItemBuffType::PowerUp:
		break;
	case EItemBuffType::SpeedUp :
		break;
	case EItemBuffType::DefenceUp:
		break;
	case EItemBuffType::CoolTimeReset:
		break;
	default:
		assert(false);
		break;
	}
}
