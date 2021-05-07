#include "stdafx.h"
#include "GameScene.h"
#include "DynamicCamera.h"
#include "ObjectContainer.h"
#include "Gui.h"
#include "Player.h"
#include "PlayerCamera.h"
#include "GameManager.h"
#include "UIManager.h"
#include "NPCInteractManager.h"
#include "QuestManager.h"
#include "QuestTable.h"
#include "ExpTable.h"
#include "PlayerInfo.h"
#include "BattleManager.h"
#include "InteractManager.h"
#include "ShopItemsTable.h"
#include "PlayerMoneyData.h"
#include "PlayerStatusData.h"
#include "PlayerEquipData.h"
#include "InventoryData.h"

void GameScene::Update()
{
	m_pGameManager->Update();
	m_pUIManager->Update();
	m_pNPCInteractManager->Update();
	m_pQuestManager->Update();
	m_pBattleManager->Update();
	m_pInteractManager->Update();
}

void GameScene::Load()
{
	EventDispatcher::AddEventListener(EngineEvent::ModeChanged, "GameScene", std::bind(&GameScene::OnModeChanged, this, placeholders::_1));
	m_pGameManager = new GameManager(this);
	m_pUIManager = new UIManager(this);
	m_pNPCInteractManager = new NPCInteractManager(this);
	m_pQuestManager = new QuestManager(this);
	m_pBattleManager = new BattleManager(this);
	m_pInteractManager = new InteractManager(this);


	ExpTable * pExpTable = static_cast<ExpTable*>(ENGINE->GetScriptableData(L"ExpTable"));
	if (pExpTable == nullptr)
	{
		pExpTable = new ExpTable();
		ENGINE->AddScriptableData(L"ExpTable", pExpTable);
	}
	m_pExpTable = pExpTable;

	PlayerInfo* pPlayerInfo = static_cast<PlayerInfo*>(ENGINE->GetScriptableData(L"PlayerInfo"));
	if (pPlayerInfo == nullptr)
	{
		pPlayerInfo = new PlayerInfo();
		ENGINE->AddScriptableData(L"PlayerInfo", pPlayerInfo);
	}
	m_pPlayerInfo = pPlayerInfo;

	ShopItemsTable * pShopItemsTable = static_cast<ShopItemsTable*>(ENGINE->GetScriptableData(L"ShopItemsTable"));
	if (pShopItemsTable == nullptr)
	{
		pShopItemsTable = new ShopItemsTable();
		ENGINE->AddScriptableData(L"ShopItemsTable", pShopItemsTable);
	}

	m_pPlayerMoneyData = static_cast<PlayerMoneyData*>(ENGINE->GetScriptableData(L"PlayerMoneyData"));
	if (m_pPlayerMoneyData == nullptr)
	{
		m_pPlayerMoneyData = new PlayerMoneyData();
		ENGINE->AddScriptableData(L"PlayerMoneyData", m_pPlayerMoneyData);
	}

	m_pPlayerStatusData = static_cast<PlayerStatusData*>(ENGINE->GetScriptableData(L"PlayerStatusData"));
	if (m_pPlayerStatusData == nullptr)
	{
		m_pPlayerStatusData = new PlayerStatusData();
		ENGINE->AddScriptableData(L"PlayerStatusData", m_pPlayerStatusData);
	}

	m_pPlayerEquipData = static_cast<PlayerEquipData*>(ENGINE->GetScriptableData(L"PlayerEquipData"));
	if (m_pPlayerEquipData == nullptr)
	{
		m_pPlayerEquipData = new PlayerEquipData();
		ENGINE->AddScriptableData(L"PlayerEquipData", m_pPlayerEquipData);
	}

	m_pInventoryData = static_cast<InventoryData*>(ENGINE->GetScriptableData(L"InventoryData"));
	if (m_pInventoryData == nullptr)
	{
		m_pInventoryData = new InventoryData();
		ENGINE->AddScriptableData(L"InventoryData", m_pInventoryData);
	}

}

void GameScene::LateLoadScene()
{
	m_pGameManager->Initialize();
	m_pUIManager->Initialize();
	m_pNPCInteractManager->Initialize();
	m_pQuestManager->Initialize();
	m_pBattleManager->Initialize();
	m_pInteractManager->Initialize();

	ScriptableData * data = ENGINE->GetScriptableData(L"QuestTable");
	if (data == nullptr)
	{
		QuestTable* table = new QuestTable();
		table->Initialize();
		ENGINE->AddScriptableData(L"QuestTable", table);
	}
	else
	{
		QuestTable* table = static_cast<QuestTable*>(data);
		table->LinkQuests();
	}
}

void GameScene::Unload()
{
	EventDispatcher::RemoveEventListener(EngineEvent::ModeChanged, "GameScene");

	SAFE_DELETE(m_pGameManager);
	SAFE_DELETE(m_pUIManager);
	SAFE_DELETE(m_pNPCInteractManager);
	SAFE_DELETE(m_pQuestManager);
	SAFE_DELETE(m_pBattleManager);
}

void GameScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}

void GameScene::RenderGUI()
{
#ifdef _DEBUG
	Gui::Get()->ShowFPS();
	Gui::Get()->ShowGameMode();

	//Gui::Get()->BeginUI();

	//	Gui::Get()->EndUI();
	//Gui::Get()->ShowTextInput(temp, 256, 200, 200);

	if (ENGINE->GetGameMode() == EGameMode::EDIT_MODE)
	{
		Gui::Get()->ShowEditRenderOption();

		//Gui::Get()->BeginEditGUI();
		
		/*Gui::Get()->InputInt("FontPosX", &fontPosX);
		Gui::Get()->InputInt("FontPosY", &fontPosY);
		Gui::Get()->InputInt("FontPosZ", &fontPosZ);
		Gui::Get()->InputInt("FontScaleX", &fontScaleX);
		Gui::Get()->InputInt("FontScaleY", &fontScaleY);*/

		/*char test[256];
		Gui::Get()->InputText("InputText", test, 256);
		int testInt;
		Gui::Get()->InputInt("InputInt", &testInt);
		float testFloat;
		Gui::Get()->InputFloat("InputFloat", &testFloat);*/
		//Gui::Get()->EndEditGUI();
	}
	//Gui::Get()->InputText("InputText", )

#endif
}

void GameScene::OnModeChanged(void *)
{
	if (ENGINE->GetGameMode() == EGameMode::EDIT_MODE)
	{
		Camera* pSelectedCam = SCENE->GetSelectedCamera();
		D3DXVECTOR3 pos = pSelectedCam->m_pTransform->m_position;
		SelectCamera(GetEditCam()->GetName());
		pSelectedCam = SCENE->GetSelectedCamera();
		pSelectedCam->m_pTransform->m_position = pos;

	}
	else if (ENGINE->GetGameMode() == EGameMode::GAME_MODE)
	{
		SelectCamera(GetGameCam()->GetName());
	}
}

PlayerInfo * GameScene::GetPlayerInfo()
{
	return m_pPlayerInfo;
}

ExpTable * GameScene::GetExpTable()
{
	return m_pExpTable;
}

PlayerMoneyData * GameScene::GetPlayerMoneyData()
{
	return m_pPlayerMoneyData;
}

InventoryData * GameScene::GetInventoryData()
{
	return m_pInventoryData;
}

PlayerEquipData * GameScene::GetPlayerEquipData()
{
	return m_pPlayerEquipData;
}

PlayerStatusData * GameScene::GetPlayerStatusData()
{
	return m_pPlayerStatusData;
}

GameManager * GameScene::GetGameManager()
{
	return m_pGameManager;
}

UIManager * GameScene::GetUIManager()
{
	return m_pUIManager;
}

QuestManager * GameScene::GetQuestManager()
{
	return m_pQuestManager;
}

NPCInteractManager * GameScene::GetNPCInteractManager()
{
	return m_pNPCInteractManager;
}

BattleManager * GameScene::GetBattleManager()
{
	return m_pBattleManager;
}

