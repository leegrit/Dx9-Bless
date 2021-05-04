#include "stdafx.h"
#include "AncientTowerScene.h"
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
#include "QuestNPC.h"
#include "DummyBoss.h"
#include "SampleNPC.h"

void AncientTowerScene::Update()
{
	GameScene::Update();
}

void AncientTowerScene::Load()
{
	GameScene::Load();
	//////////////////////////////////////////////////////////////////////////
	// RENDER OPTION
	//////////////////////////////////////////////////////////////////////////
	ENGINE->SetRenderOption(RenderOptions::RenderCollider, false);
	ENGINE->SetRenderOption(RenderOptions::RenderLight, false);
	ENGINE->SetRenderOption(RenderOptions::RenderNavMesh, false);
	ENGINE->SetRenderOption(RenderOptions::RenderShadow, false);
	ENGINE->SetRenderOption(RenderOptions::RenderUI, false);

	//////////////////////////////////////////////////////////////////////////
	// NAVMESH
	//////////////////////////////////////////////////////////////////////////
	NavMesh* navMesh = NavMesh::Create(this, nullptr, PATH->DatasPathW() + L"NavMeshData/Ancient_NavMesh.json");

	//////////////////////////////////////////////////////////////////////////
	// PLAYER
	//////////////////////////////////////////////////////////////////////////
	auto player = Player::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Ancient_Lups.json");
	SetPlayer(player);
	player->m_pTransform->SetScale(0.5f, 0.5f, 0.5f);

	//////////////////////////////////////////////////////////////////////////
	// CAMERA
	//////////////////////////////////////////////////////////////////////////
	m_pEditCam = DynamicCamera::Create(this, nullptr, L"SampleCamera");
	m_pGameCam = PlayerCamera::Create(this, player, L"PlayerCamera");
	SelectCamera(m_pGameCam->GetName());

	//////////////////////////////////////////////////////////////////////////
	// SKYBOX
	//////////////////////////////////////////////////////////////////////////
	Skybox* skybox = new Skybox(m_pGameCam, PATH->ResourcesPathW() + L"Assets/SkyBox/SkyBox_0.dds");
	skybox->Initialize();
	SetSkybox(skybox);

	//////////////////////////////////////////////////////////////////////////
	// MAP
	//////////////////////////////////////////////////////////////////////////
	GroupMapObject::Create(this, nullptr, L"Group", PATH->DatasPathW() + L"MapData/AncientTower.json");

	//////////////////////////////////////////////////////////////////////////
	// LIGHT
	//////////////////////////////////////////////////////////////////////////
	/* Directional Light */
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Ancient_DirectionalLight.json");

	//////////////////////////////////////////////////////////////////////////
	// EQUIPMENT
	//////////////////////////////////////////////////////////////////////////
	m_pEquip = Equipment::Create(this, player, PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW/OSW_00.x", L"Bip01-R-Finger21", L"Sword");
	m_pEquip->m_pTransform->SetScale(1.5f, 1.5f, 1.5f);

	


}

void AncientTowerScene::LateLoadScene()
{
	GameScene::LateLoadScene();
}

void AncientTowerScene::Unload()
{
	GameScene::Unload();
}

void AncientTowerScene::LoadAsync(std::function<void(int, int)> onProgress)
{
	GameScene::LoadAsync(onProgress);
}

void AncientTowerScene::RenderGUI()
{
	GameScene::RenderGUI();
}

Camera * AncientTowerScene::GetEditCam()
{
	return m_pEditCam;
}

Camera * AncientTowerScene::GetGameCam()
{
	return m_pGameCam;
}
