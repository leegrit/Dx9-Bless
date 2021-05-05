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

void GameScene::Update()
{
	m_pGameManager->Update();
	m_pUIManager->Update();
	m_pNPCInteractManager->Update();
	m_pQuestManager->Update();
	m_pBattleManager->Update();

}

void GameScene::Load()
{
	EventDispatcher::AddEventListener(EngineEvent::ModeChanged, "GameScene", std::bind(&GameScene::OnModeChanged, this, placeholders::_1));
	m_pGameManager = new GameManager(this);
	m_pUIManager = new UIManager(this);
	m_pNPCInteractManager = new NPCInteractManager(this);
	m_pQuestManager = new QuestManager(this);
	m_pBattleManager = new BattleManager(this);


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
}

void GameScene::LateLoadScene()
{
	m_pGameManager->Initialize();
	m_pUIManager->Initialize();
	m_pNPCInteractManager->Initialize();
	m_pQuestManager->Initialize();
	m_pBattleManager->Initialize();

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

