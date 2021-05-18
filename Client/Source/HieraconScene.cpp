#include "stdafx.h"
#include "HieraconScene.h"
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
#include "Bran.h"
#include "Hieracon_Cora.h"
#include "Samson.h"
#include "Elroy.h"
#include "Elaine.h"
#include "Liurens.h"
#include "Renderer.h"


using namespace HyEngine;

void HieraconScene::Update()
{
	GameScene::Update();
	std::cout << ENGINE->GetFPS() << std::endl;
	/*if (GetFloatA() == 0)
	{
		RENDERER->SetLutFilter(lutFilters.at(0));
	}
	if (GetFloatA() == 1)
	{
		RENDERER->SetLutFilter(lutFilters.at(1));
	}
	if (GetFloatA() == 2)
	{
		RENDERER->SetLutFilter(lutFilters.at(2));
	}
	if (GetFloatA() == 3)
	{
		RENDERER->SetLutFilter(lutFilters.at(3));
	}
	if (GetFloatA() == 4)
	{
		RENDERER->SetLutFilter(lutFilters.at(4));
	}
	if (GetFloatA() == 5)
	{
		RENDERER->SetLutFilter(lutFilters.at(5));
	}*/

	
}

void HieraconScene::Load()
{
	GameScene::Load();

	//////////////////////////////////////////////////////////////////////////
	// RENDER OPTION
	//////////////////////////////////////////////////////////////////////////
	ENGINE->SetRenderOption(RenderOptions::RenderCollider, false);
	ENGINE->SetRenderOption(RenderOptions::RenderLight, true);
	ENGINE->SetRenderOption(RenderOptions::RenderNavMesh, false);
	ENGINE->SetRenderOption(RenderOptions::RenderShadow, true);
	ENGINE->SetRenderOption(RenderOptions::RenderUI, false);
	ENGINE->SetRenderOption(RenderOptions::RenderPostEffect, true);

	//////////////////////////////////////////////////////////////////////////
	// NAVMESH
	//////////////////////////////////////////////////////////////////////////
	NavMesh* navMesh = NavMesh::Create(this, nullptr, PATH->DatasPathW() + L"NavMeshData/Hieracon_NavMesh.json");
	
	//////////////////////////////////////////////////////////////////////////
	// PLAYER
	//////////////////////////////////////////////////////////////////////////
	m_pPlayer = Player::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Hieracon_Player.json");
	SetPlayer(m_pPlayer);
	//m_pPlayer->m_pTransform->SetScale(0.5f, 0.5f, 0.5f);

	//////////////////////////////////////////////////////////////////////////
	// CAMERA
	//////////////////////////////////////////////////////////////////////////
	m_pEditCam =  DynamicCamera::Create(this, nullptr, L"SampleCamera");
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
	GroupMapObject::Create(this, nullptr, L"Group", PATH->DatasPathW() + L"MapData/Hierarcon.json");

	//////////////////////////////////////////////////////////////////////////
	// TERRAIN
	//////////////////////////////////////////////////////////////////////////
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_Terrain0.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_Terrain1.json");
	Terrain::Create(this, nullptr, PATH->DatasPathW() + L"TerrainData/Hieracon_Terrain2.json");


	//////////////////////////////////////////////////////////////////////////
	// LIGHT
	//////////////////////////////////////////////////////////////////////////
	/* Directional Light */
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/DirectionalLight.json");

	/* Point Light */
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight0.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight1.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight2.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight3.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight4.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight5.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight6.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight7.json");

	/*LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight0.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight1.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight2.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight3.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight4.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight5.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight6.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Hieracon_PointLight7.json");
*/
	//////////////////////////////////////////////////////////////////////////
	// EQUIPMENT
	//////////////////////////////////////////////////////////////////////////
	m_pEquip =	Equipment::Create(this, m_pPlayer, PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW_9000/OSW_9000.x", L"Bip01-R-Finger22" /*L"Bip01-R-Finger21"*/, L"Sword");
	m_pEquip->m_pTransform->SetScale(1.5f, 1.5f, 1.5f);
	m_pPlayer->SetWeapon(m_pEquip);
	auto equip = Equipment::Create(this, m_pPlayer, PATH->ResourcesPathW() + L"Assets/Mesh/Item/SLD_9000/SLD_9000.x", L"Bip01-L-Hand", L"SLD");
	m_pPlayer->SetShield(equip);
	//auto equip = Equipment::Create(this, m_pPlayer, PATH->ResourcesPathW() + L"Assets/Mesh/Item/SLD_9000/SLD_9000.x", L"Bip01-L-Finger31", L"SLD");
	//equip->m_pTransform->SetScale(1.5f, 1.5f, 1.5f);

	//////////////////////////////////////////////////////////////////////////
	// ENEMY
	//////////////////////////////////////////////////////////////////////////
	auto enemy1 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone0.json");
	auto enemy2 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone1.json");
	auto enemy3 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone2.json");

	//////////////////////////////////////////////////////////////////////////
	// NONE PLAYER
	//////////////////////////////////////////////////////////////////////////
	//m_nonePlayers.emplace_back(SampleNPC::Create(this, PATH->DatasPathW() + L"HierarchyData/Sire.json"));
	Hieracon_Cora::Create(this, PATH->DatasPathW() + L"HierarchyData/Hieracon_Leoni.json");
	Bran::Create(this, PATH->DatasPathW() + L"HierarchyData/Hieracon_BailanBollwerk.json");
	Samson::Create(this, PATH->DatasPathW() + L"HierarchyData/Hieracon_Chitata.json");
	Elroy::Create(this, PATH->DatasPathW() + L"HierarchyData/Hieracon_Deliah.json");
	Liurens::Create(this, PATH->DatasPathW() + L"HierarchyData/Hieracon_Mathias.json");
	Elaine::Create(this, PATH->DatasPathW() + L"HierarchyData/Hieracon_Gagato.json");

	//////////////////////////////////////////////////////////////////////////
	// NAMED
	//////////////////////////////////////////////////////////////////////////
	//auto dummyBoss = DummyBoss::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/GhostSoldier.json");

	//////////////////////////////////////////////////////////////////////////
	// WARP POINT
	//////////////////////////////////////////////////////////////////////////
	auto warpPoint = WarpPoint::Create(this, 2, L"ToJungle");
	warpPoint->m_pTransform->SetPosition(0, 0, -111);


	//////////////////////////////////////////////////////////////////////////
	// UI
	//////////////////////////////////////////////////////////////////////////
	/*UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/ClassMark_0.png", D3DXVECTOR3(0, -276, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(120, 120, 1), L"1");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/PortraitCircle/PortraitCircle_0.png", D3DXVECTOR3(0, -291, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(160, 160, 1), L"2");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_4.png", D3DXVECTOR3(-368, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"3");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_0.png", D3DXVECTOR3(-295.2, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"4");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_1.png", D3DXVECTOR3(-222 ,-325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"5");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_2.png", D3DXVECTOR3(-150.4, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"6");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_3.png", D3DXVECTOR3(150.4, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"7");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_5.png", D3DXVECTOR3(222, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"8");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_6.png", D3DXVECTOR3(295.2, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"9");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_7.png", D3DXVECTOR3(368, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"11");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_0.png", D3DXVECTOR3(-276, -266, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(400, 20, 1), L"22");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_0.png", D3DXVECTOR3(276, -266, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(400, 20, 1), L"33");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_1.png", D3DXVECTOR3(-276, -265, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(325, 10, 1), L"44");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_2.png", D3DXVECTOR3(276, -265, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(325, 10, 1), L"55");
	*/


	//////////////////////////////////////////////////////////////////////////
	// FOR FILTER
	//////////////////////////////////////////////////////////////////////////
	IDirect3DTexture9* pLutFilterTex = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->AssetsPathW() + L"LUT/TX_FX_PPC_LUT_Betty_NEW.tga");
	//RENDERER->SetLutFilter(pLutFilterTex);

	lutFilters.push_back(pLutFilterTex);
	auto pLutFilterTex1 = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->AssetsPathW() + L"LUT/TX_FX_PPC_LUT_Damon_NEW.tga");
	lutFilters.push_back(pLutFilterTex1);
	auto pLutFilterTex2 = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->AssetsPathW() + L"LUT/TX_FX_PPC_LUT_David1st_NEW.tga");
	lutFilters.push_back(pLutFilterTex2);
	auto pLutFilterTex3 = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->AssetsPathW() + L"LUT/TX_FX_PPC_LUT_David2nd_NEW.tga");
	lutFilters.push_back(pLutFilterTex3);
	auto pLutFilterTex4 = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->AssetsPathW() + L"LUT/TX_FX_PPC_LUT_David2ndBoss_NEW.tga");
	lutFilters.push_back(pLutFilterTex4);
	auto pLutFilterTex5 = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->AssetsPathW() + L"LUT/TX_FX_PPC_LUT_David2ndPhase3_NEW.tga");
	lutFilters.push_back(pLutFilterTex5);
	auto pLutFilterTex6 = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->AssetsPathW() + L"LUT/TX_FX_PPC_LUT_Default.tga");
	lutFilters.push_back(pLutFilterTex6);
}

void HieraconScene::LateLoadScene()
{
	GameScene::LateLoadScene();
	/* For Quest */
	for (auto& npc : m_nonePlayers)
	{
		npc->QuestInitialize();
	}
}

void HieraconScene::Unload()
{
	GameScene::Unload();
}

void HieraconScene::LoadAsync(std::function<void(int, int)> onProgress)
{
	GameScene::LoadAsync(onProgress);
}

void HieraconScene::RenderGUI()
{
	GameScene::RenderGUI();
	
}


Camera * HieraconScene::GetEditCam()
{
	return m_pEditCam;
}

Camera * HieraconScene::GetGameCam()
{
	return m_pGameCam;
}


char HieraconScene::temp[256];