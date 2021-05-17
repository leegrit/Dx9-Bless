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
#include "Goblin.h"
#include "Leoni.h"
#include "Guido.h"
#include "TalkableGoblin.h"
#include "CollectObject.h"
#include "HGoblin.h"

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
	m_pPlayer = Player::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Player.json");
	SetPlayer(m_pPlayer);

	//player->m_pTransform->SetScale(0.5f, 0.5f, 0.5f);

	//////////////////////////////////////////////////////////////////////////
	// CAMERA
	//////////////////////////////////////////////////////////////////////////
	m_pEditCam = DynamicCamera::Create(this, nullptr, L"SampleCamera");
	m_pGameCam = PlayerCamera::Create(this, m_pPlayer, L"PlayerCamera");
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
	/*auto equip = Equipment::Create(this, player, PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW/OSW_00.x", L"Bip01-R-Finger21", L"Sword");
	equip->m_pTransform->SetScale(1.5f, 1.5f, 1.5f);*/
	Equipment* pEquip = Equipment::Create(this, m_pPlayer, PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW_9000/OSW_9000.x", L"Bip01-R-Finger22" /*L"Bip01-R-Finger21"*/, L"Sword");
	pEquip->m_pTransform->SetScale(1.5f, 1.5f, 1.5f);
	m_pPlayer->SetWeapon(pEquip);
	pEquip = Equipment::Create(this, m_pPlayer, PATH->ResourcesPathW() + L"Assets/Mesh/Item/SLD_9000/SLD_9000.x", L"Bip01-L-Hand", L"SLD");
	m_pPlayer->SetShield(pEquip);

	//////////////////////////////////////////////////////////////////////////
	// ENEMY
	//////////////////////////////////////////////////////////////////////////
	auto enemy1 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_1.json");
	auto enemy2 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_2.json");
	auto enemy3 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_3.json");
	auto enemy4 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_4.json");
	auto enemy5 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_5.json");
	auto enemy6 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_6.json");
	auto enemy7 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_7.json");
	auto enemy8 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_8.json");
	auto enemy9 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_9.json");
	auto enemy10 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_10.json");
	auto enemy11 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_11.json");
	auto enemy12 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_12.json");
	auto enemy13 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin01_13.json");
	auto enemy14 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin02_1.json");
	auto enemy15 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin02_2.json");
	auto enemy16 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin02_3.json");
	auto enemy17 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin02_4.json");
	auto enemy18 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin02_5.json");
	auto enemy19 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin02_6.json");
	auto enemy20 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin02_7.json");
	auto enemy21 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin02_8.json");
	auto enemy22 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin03_1.json");
	auto enemy23 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin03_2.json");
	auto enemy24 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin03_3.json");
	auto enemy25 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin03_4.json");
	auto enemy26 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin03_5.json");
	auto enemy27 = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin03_6.json");
	
	
	//////////////////////////////////////////////////////////////////////////
	// NAMED
	//////////////////////////////////////////////////////////////////////////
	auto named = HGoblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/HGoblin.json");

	//////////////////////////////////////////////////////////////////////////
	// NONE PLAYER
	//////////////////////////////////////////////////////////////////////////
	Leoni::Create(this, PATH->DatasPathW() + L"HierarchyData/Leoni.json");
	Guido::Create(this, PATH->DatasPathW() + L"HierarchyData/Guido.json");
	TalkableGoblin::Create(this, PATH->DatasPathW() + L"HierarchyData/GoblinNPC.json");


	//////////////////////////////////////////////////////////////////////////
	// WARP POINT
	//////////////////////////////////////////////////////////////////////////
	auto warpPoint = WarpPoint::Create(this, 3, L"ToAncientTower");
	warpPoint->m_pTransform->SetPosition(-41, 0, 1137);

	//////////////////////////////////////////////////////////////////////////
	// COLLECT OBJECT
	//////////////////////////////////////////////////////////////////////////
	CollectObject::Create(this, L"Statue01", PATH->DatasPathW() + L"HierarchyData/Statue01.json");
	CollectObject::Create(this, L"Statue02", PATH->DatasPathW() + L"HierarchyData/Statue02.json");


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
