#include "stdafx.h"
#include "SampleScene.h"
#include "SampleCamera.h"
#include "Skybox.h"
#include "PathManager.h"
#include "Light.h"
#include "DynamicMesh.h"
#include "DynamicCamera.h"
#include "GroupMapObject.h"
#include "NavMesh.h"
#include "Pawn.h"
#include "ObjectContainer.h"
#include "LightObject.h"
#include "Terrain.h"
#include "Gui.h"
#include "Player.h"
#include "PlayerCamera.h"
#include "UIPanel.h"
#include "Equipment.h"
#include "Skeletone.h"

using namespace HyEngine;

void SampleScene::Update()
{
	//m_pEquip->SetBoneName(temp);
// 	if(KEYBOARD->Press('B'))
// 	{
// 		m_pPawn->m_pTransform->Translate(m_pPawn->m_pTransform->Forward() * 10 * TIMER->getDeltaTime());
// 	}
// 	if (KEYBOARD->Press('V'))
// 	{
// 		m_pPawn->m_pTransform->Translate(-m_pPawn->m_pTransform->Forward() * 10 * TIMER->getDeltaTime());
// 	}
}

void SampleScene::Load()
{
	/* �ӽ�! */
	strcpy_s(temp, 256, "");

	EventDispatcher::AddEventListener(EngineEvent::ModeChanged, "SampleScene", std::bind(&SampleScene::OnModeChanged, this, placeholders::_1));

	m_pEditCam = DynamicCamera::Create(this, nullptr, L"SampleCamera");
	//AddCamera(L"SampleCamera", camera);



	
	NavMesh* navMesh=	NavMesh::Create(this, nullptr, PATH->DatasPathW() + L"NavMeshData/FirstNavMesh.json");
	
	m_pPlayer = Player::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Lups.json");
	SetPlayer(m_pPlayer);

	m_pGameCam = PlayerCamera::Create(this, m_pPlayer, L"PlayerCamera");
	SelectCamera(L"PlayerCamera");
	Skybox* skybox = new Skybox(m_pGameCam, PATH->ResourcesPathW() + L"Assets/SkyBox/SkyBox_0.dds");
	skybox->Initialize();
	SetSkybox(skybox);
	GroupMapObject::Create(this, nullptr, L"Group", PATH->DatasPathW() + L"MapData/FirstChunkMap.json");

	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/FirstTerrain.json");

	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/FirstDirLight.json");

	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/FirstPointLight.json");


	m_pEquip =	Equipment::Create(this, m_pPlayer, PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW/OSW_00.x", L"Bip01-R-Finger21", L"Sword");
	
	/* For Enemy */
	auto enemy1 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone.json");
	auto enemy2 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone.json");
	enemy2->m_pTransform->SetPosition(0, 0, 0);
	auto enemy3 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone.json");


	/* For UI */
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/ClassMark_0.png", D3DXVECTOR3(0, -300, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 100, 1), L"ClassMark");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_0.png", D3DXVECTOR3(-270, -280, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(400, 20, 1), L"HPBack");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_0.png", D3DXVECTOR3(270, -280, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(400, 20, 1), L"MPBack");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_1.png", D3DXVECTOR3(-270 ,- 280, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(325, 10, 1), L"HPFill");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_2.png", D3DXVECTOR3(270, -280, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(325, 10, 1), L"MPFill");
	
}

void SampleScene::Unload()
{
}

void SampleScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}

void SampleScene::RenderGUI()
{
#ifdef _DEBUG
	Gui::Get()->ShowFPS();
	Gui::Get()->ShowGameMode();

	//Gui::Get()->BeginUI();

//	Gui::Get()->EndUI();
	Gui::Get()->ShowTextInput(temp, 256, 200, 200);

#endif

	/* Test */
// 	static bool bOpen = true;
// 	ImGui::SetNextWindowPos({ WinMaxWidth - 100, 15 });
// 	ImGui::SetNextWindowSize(ImVec2(200, 15));
// 	ImGui::Begin
// 	(
// 		"FPS",
// 		&bOpen,
// 		ImGuiWindowFlags_NoBackground |
// 		ImGuiWindowFlags_NoTitleBar |
// 		ImGuiWindowFlags_NoResize |
// 		ImGuiWindowFlags_NoMove
// 	);
// 	{
// 		string frame = "FPS : " + to_string((int)ImGui::GetIO().Framerate);
// 		ImGui::Text(frame.c_str());
// 	}
// 	ImGui::End();
	
}

void SampleScene::OnModeChanged(void*)
{
	if (ENGINE->GetGameMode() == EGameMode::EDIT_MODE)
	{
		SelectCamera(L"SampleCamera");

	}
	else if (ENGINE->GetGameMode() == EGameMode::GAME_MODE)
	{
		SelectCamera(L"PlayerCamera");
	}
}

char SampleScene::temp[256];