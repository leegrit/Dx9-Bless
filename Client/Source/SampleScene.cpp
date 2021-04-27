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
	/* юс╫ц! */
	strcpy_s(temp, 256, "");

	EventDispatcher::AddEventListener(EngineEvent::ModeChanged, "SampleScene", std::bind(&SampleScene::OnModeChanged, this, placeholders::_1));

	m_pEditCam = DynamicCamera::Create(this, nullptr, L"SampleCamera");
	//AddCamera(L"SampleCamera", camera);

	int a = (UINT)-1;
	int b = D3DX_DEFAULT;

	//////////////////////////////////////////////////////////////////////////
	// NAVMESH
	//////////////////////////////////////////////////////////////////////////
	//NavMesh* navMesh=	NavMesh::Create(this, nullptr, PATH->DatasPathW() + L"NavMeshData/Hieracon_NavMesh.json");
	NavMesh* navMesh = NavMesh::Create(this, nullptr, PATH->DatasPathW() + L"NavMeshData/Hieracon_NavMesh.json");
	//////////////////////////////////////////////////////////////////////////
	// PLAYER
	//////////////////////////////////////////////////////////////////////////
	m_pPlayer = Player::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Lups.json");
	SetPlayer(m_pPlayer);
	//m_pPlayer->m_pTransform->SetScale(0.1f, 0.1f, 0.1f);

	m_pGameCam = PlayerCamera::Create(this, m_pPlayer, L"PlayerCamera");
	SelectCamera(L"PlayerCamera");
	Skybox* skybox = new Skybox(m_pGameCam, PATH->ResourcesPathW() + L"Assets/SkyBox/SkyBox_0.dds");
	skybox->Initialize();
	SetSkybox(skybox);

	//////////////////////////////////////////////////////////////////////////
	// MAP
	//////////////////////////////////////////////////////////////////////////
	GroupMapObject::Create(this, nullptr, L"Group", PATH->DatasPathW() + L"MapData/Hierarcon_Map.json");
	/*for (int i = 0; i < 500; i++)
	{
		GroupMapObject::Create(this, nullptr, L"Group", PATH->DatasPathW() + L"MapData/ChunkMap_Small.json");
	}*/
	//////////////////////////////////////////////////////////////////////////
	// TERRAIN
	//////////////////////////////////////////////////////////////////////////
	//Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Terrain_Small.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_1.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_2.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_3.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_4.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_5.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_6.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_7.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_8.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_9.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_10.json");


	//////////////////////////////////////////////////////////////////////////
	// LIGHT
	//////////////////////////////////////////////////////////////////////////
	/* Directional Light */
	//LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/DirectionalLight.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Light_Small.json");

	/* Point Light */
	/*LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_1.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_2.json");*/
	/*LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_3.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_4.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_5.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_6.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_7.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_8.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_9.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_10.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_11.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_12.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_13.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_14.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_15.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_16.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_17.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_18.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_19.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/PointLight_20.json");*/

	//////////////////////////////////////////////////////////////////////////
	// EQUIPMENT
	//////////////////////////////////////////////////////////////////////////
	m_pEquip =	Equipment::Create(this, m_pPlayer, PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW/OSW_00.x", L"Bip01-R-Finger21", L"Sword");
	//m_pEquip->m_pTransform->SetScale(0.1f, 0.1f, 0.1f);

	//////////////////////////////////////////////////////////////////////////
	// ENEMY
	//////////////////////////////////////////////////////////////////////////
	/*auto enemy1 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone.json");
	enemy1->m_pTransform->m_position += D3DXVECTOR3(50, 0, 0);
	auto enemy2 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone.json");
	enemy2->m_pTransform->m_position += D3DXVECTOR3(0, 0, 0);
	auto enemy3 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone.json");
	enemy3->m_pTransform->m_position += D3DXVECTOR3(0, 0, 50);*/


	//////////////////////////////////////////////////////////////////////////
	// UI
	//////////////////////////////////////////////////////////////////////////
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