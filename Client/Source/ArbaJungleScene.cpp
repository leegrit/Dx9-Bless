#include "stdafx.h"
#include "ArbaJungleScene.h"
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
#include "WarpPoint.h"

void ArbaJungleScene::Update()
{
	GameScene::Update();
}

void ArbaJungleScene::Load()
{
	GameScene::Load();

	//////////////////////////////////////////////////////////////////////////
	// RENDER OPTION
	//////////////////////////////////////////////////////////////////////////
	ENGINE->SetRenderOption(RenderOptions::RenderCollider, false);
	ENGINE->SetRenderOption(RenderOptions::RenderLight, false);
	ENGINE->SetRenderOption(RenderOptions::RenderNavMesh, false);
	ENGINE->SetRenderOption(RenderOptions::RenderShadow, true);
	ENGINE->SetRenderOption(RenderOptions::RenderUI, false);

	//////////////////////////////////////////////////////////////////////////
	// NAVMESH
	//////////////////////////////////////////////////////////////////////////
	NavMesh* navMesh = NavMesh::Create(this, nullptr, PATH->DatasPathW() + L"NavMeshData/JungleNavMesh.json");

	//////////////////////////////////////////////////////////////////////////
	// PLAYER
	//////////////////////////////////////////////////////////////////////////
	auto player = Player::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Lups.json");
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
	GroupMapObject::Create(this, nullptr, L"Group", PATH->DatasPathW() + L"MapData/ArbaJungle.json");

	//////////////////////////////////////////////////////////////////////////
	// TERRAIN
	//////////////////////////////////////////////////////////////////////////
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Jungle_Terrain.json");

	//////////////////////////////////////////////////////////////////////////
	// LIGHT
	//////////////////////////////////////////////////////////////////////////
	/* Directional Light */
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_DirectionalLight.json");

	//////////////////////////////////////////////////////////////////////////
	// EQUIPMENT
	//////////////////////////////////////////////////////////////////////////
	auto equip = Equipment::Create(this, player, PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW/OSW_00.x", L"Bip01-R-Finger21", L"Sword");
	equip->m_pTransform->SetScale(1.5f, 1.5f, 1.5f);

	//////////////////////////////////////////////////////////////////////////
	// WARP POINT
	//////////////////////////////////////////////////////////////////////////
	auto warpPoint = WarpPoint::Create(this, 3, L"ToAncientTower");
	warpPoint->m_pTransform->SetPosition(-41, 0, 1137);


}

void ArbaJungleScene::LateLoadScene()
{
	GameScene::LateLoadScene();

}

void ArbaJungleScene::Unload()
{
	GameScene::Unload();

}

void ArbaJungleScene::LoadAsync(std::function<void(int, int)> onProgress)
{
	GameScene::LoadAsync(onProgress);

}

void ArbaJungleScene::RenderGUI()
{
	GameScene::RenderGUI();
}

Camera * ArbaJungleScene::GetEditCam()
{
	return m_pEditCam;
}

Camera * ArbaJungleScene::GetGameCam()
{
	return m_pGameCam;
}
