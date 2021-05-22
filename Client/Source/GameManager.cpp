#include "stdafx.h"
#include "GameManager.h"
#include "GameScene.h"
#include "Client_Events.h"
#include "PlayerInfo.h"
#include "ExpTable.h"
#include "UIManager.h"
#include "EquipmentUI.h"
#include "InventoryUI.h"
#include "SoundManager.h"


GameManager::GameManager(GameScene * pScene)
	: m_pScene(pScene)
{
	EventDispatcher::AddEventListener(GameEvent::SendExp, "GameManager",
		std::bind(&GameManager::OnSendExp, this, placeholders::_1));

	EventDispatcher::AddEventListener(UIEvent::InventoryUIOpen, "GameManager",
		std::bind(&GameManager::OnInventoryUIOpen, this, placeholders::_1));
	EventDispatcher::AddEventListener(UIEvent::InventoryUIClose, "GameManager",
		std::bind(&GameManager::OnInventoryUIClose, this, placeholders::_1));
	EventDispatcher::AddEventListener(UIEvent::EquipmentUIOpen, "GameManager",
		std::bind(&GameManager::OnEquipmentUIOpen, this, placeholders::_1));
	EventDispatcher::AddEventListener(UIEvent::EquipmentUIClose, "GameManager",
		std::bind(&GameManager::OnEquipmentUIClose, this, placeholders::_1));
	EventDispatcher::AddEventListener(UIEvent::ShopUIOpen, "GameManager",
		std::bind(&GameManager::OnShopUIOpen, this, placeholders::_1));
	EventDispatcher::AddEventListener(UIEvent::ShopUIClose, "GameManager",
		std::bind(&GameManager::OnShopUIClose, this, placeholders::_1));
}

GameManager::~GameManager()
{
	EventDispatcher::RemoveEventListener(GameEvent::SendExp, "GameManager");

	EventDispatcher::RemoveEventListener(UIEvent::InventoryUIOpen, "GameManager");
	EventDispatcher::RemoveEventListener(UIEvent::InventoryUIClose, "GameManager");
	EventDispatcher::RemoveEventListener(UIEvent::EquipmentUIOpen, "GameManager");
	EventDispatcher::RemoveEventListener(UIEvent::EquipmentUIClose, "GameManager");
	EventDispatcher::RemoveEventListener(UIEvent::ShopUIOpen, "GameManager");
	EventDispatcher::RemoveEventListener(UIEvent::ShopUIClose, "GameManager");

}

void GameManager::OnSendExp(void * value)
{
	float exp = *static_cast<float*>(value);
	PlayerInfo* pPlayerInfo = m_pScene->GetPlayerInfo();
	pPlayerInfo->exp += exp;
	
	ExpTable* pExpTable = m_pScene->GetExpTable();

	// 누적 경험치가 exp 테이블의 해당 레벨보다 많으면 레벨업
	if (pPlayerInfo->exp >= pExpTable->expTable[pPlayerInfo->level - 1])
	{
		pPlayerInfo->level++;
		EventDispatcher::TriggerEvent(GameEvent::LevelUp, (int*)&pPlayerInfo->level);
	}


}

void GameManager::OnInventoryUIOpen(void *)
{
	m_bOccupyUI = true;
}

void GameManager::OnInventoryUIClose(void *)
{
	m_bOccupyUI = false;
}

void GameManager::OnEquipmentUIOpen(void *)
{
	m_bOccupyUI = true;
}

void GameManager::OnEquipmentUIClose(void *)
{
	m_bOccupyUI = false;
}

void GameManager::OnShopUIOpen(void *)
{
	m_bOccupyUI = true;
}

void GameManager::OnShopUIClose(void *)
{
	m_bOccupyUI = false;
}

void GameManager::Initialize()
{
}

void GameManager::Update()
{
	if (m_bOccupyUI == false)
	{
		if (KEYBOARD->Down('I'))
		{
			/* Open Inventory */
			m_pScene->GetUIManager()->GetInventoryUI()->Show();
		}
		else if (KEYBOARD->Down('E'))
		{
			/* Open Equipment */
			m_pScene->GetUIManager()->GetEquipmentUI()->Show();
		}
	}
	else
	{
		if (KEYBOARD->Down('I'))
		{
			if (m_pScene->GetUIManager()->GetInventoryUI()->IsShow())
			{
				m_pScene->GetUIManager()->GetInventoryUI()->Hide();
			}
		}
		else if (KEYBOARD->Down('E'))
		{
			if (m_pScene->GetUIManager()->GetEquipmentUI()->IsShow())
			{
				m_pScene->GetUIManager()->GetEquipmentUI()->Hide();
			}
		}
	}
}

bool GameManager::IsPlayerMovable()
{
	return !m_bOccupyUI;
}

void GameManager::SwitchBGM(TCHAR* soundName)
{
	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_NORMAL;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->StopSound("BGM");
	SOUND->PlaySound("BGM", soundName, desc);
}
