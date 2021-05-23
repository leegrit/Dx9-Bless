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
#include "Soldier.h"
#include "CinematicManager.h"
#include "HGoblinCinematicTrack.h"
#include "Sprite3D.h"
#include "SoundManager.h"
#include "BattleCinematicTrack.h"
#include "QuestManager.h"
#include "UpdateDispatcher.h"
#include "Quest.h"
#include "Client_Events.h"
#include "Jungle_Chitata.h"
#include "Jungle_Gagato.h"
#include "Jungle_Liurens.h"

void ArbaJungleScene::Update()
{
	GameScene::Update();
}

void ArbaJungleScene::Load()
{
	GameScene::Load();

	//////////////////////////////////////////////////////////////////////////
	// EVENT
	//////////////////////////////////////////////////////////////////////////
	EventDispatcher::AddEventListener(QuestEvent::QuestAccept, "ArbaJungleScene",
		std::bind(&ArbaJungleScene::OnQuestAccept, this, placeholders::_1));

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_NORMAL;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->PlaySound("BGM", L"EastSkarapForest.mp3", desc);

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
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight1.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight2.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight3.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight4.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight5.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight6.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight7.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight8.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight9.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight10.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight11.json");
	LightObject::Create(this, nullptr, PATH->DatasPathW() + L"LightData/Jungle_PointLight12.json");


	//////////////////////////////////////////////////////////////////////////
	// EQUIPMENT
	//////////////////////////////////////////////////////////////////////////
	/*auto equip = Equipment::Create(this, player, PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW/OSW_00.x", L"Bip01-R-Finger21", L"Sword");
	equip->m_pTransform->SetScale(1.5f, 1.5f, 1.5f);*/
	Equipment* pEquip = Equipment::Create(this, m_pPlayer, PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW_9000/OSW_9000.x", L"Bip01-R-Finger22" /*L"Bip01-R-Finger21"*/, L"Sword");
	pEquip->m_pTransform->SetScale(1.5f, 1.5f, 1.5f);
	m_pPlayer->SetWeapon(pEquip);
	pEquip = Equipment::Create(this, m_pPlayer, PATH->ResourcesPathW() + L"Assets/Mesh/Item/SLD_9000/SLD_9000.x", L"Bip01-L-Hand", L"SLD");
	pEquip->m_pTransform->m_rotationEuler = D3DXVECTOR3(0, 0, 180);
	m_pPlayer->SetShield(pEquip);

	//////////////////////////////////////////////////////////////////////////
	// ENVIRONMENT
	//////////////////////////////////////////////////////////////////////////
	auto env1 = Sprite3D::Create(this, L"Env1",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env1->m_pTransform->m_position = D3DXVECTOR3(-12, 30, 137);
	env1->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env1->PlayAnimation();
	auto env2 = Sprite3D::Create(this, L"Env2",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env2->m_pTransform->m_position = D3DXVECTOR3(123, 30, 343);
	env2->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env2->PlayAnimation();
	auto env3 = Sprite3D::Create(this, L"Env3",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env3->m_pTransform->m_position = D3DXVECTOR3(-276, 30, 242);
	env3->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env3->PlayAnimation();
	auto env4 = Sprite3D::Create(this, L"Env4",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env4->m_pTransform->m_position = D3DXVECTOR3(-36, 30, 840);
	env4->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env4->PlayAnimation();
	auto env5 = Sprite3D::Create(this, L"Env5",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env5->m_pTransform->m_position = D3DXVECTOR3(-399, 30, 790);
	env5->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env5->PlayAnimation();
	auto env6 = Sprite3D::Create(this, L"Env6",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env6->m_pTransform->m_position = D3DXVECTOR3(208, 30, 576);
	env6->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env6->PlayAnimation();
	auto env7 = Sprite3D::Create(this, L"Env7",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env7->m_pTransform->m_position = D3DXVECTOR3(390, 30, 582);
	env7->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env7->PlayAnimation();
	auto env8 = Sprite3D::Create(this, L"Env8",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env8->m_pTransform->m_position = D3DXVECTOR3(332, 30, 989);
	env8->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env8->PlayAnimation();
	auto env9 = Sprite3D::Create(this, L"Env9",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env9->m_pTransform->m_position = D3DXVECTOR3(73, 30, 1163);
	env9->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env9->PlayAnimation();
	auto env10 = Sprite3D::Create(this, L"Env10",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env10->m_pTransform->m_position = D3DXVECTOR3(-218, 30, 993);
	env10->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env10->PlayAnimation();
	auto env11 = Sprite3D::Create(this, L"Env11",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env11->m_pTransform->m_position = D3DXVECTOR3(-138, 30, 705);
	env11->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env11->PlayAnimation();
	auto env12 = Sprite3D::Create(this, L"Env12",
		PATH->AssetsPathW() + L"Effect/Texture/FX_GstarFire_005_TEX_KJS", ELoopType::Loop, 64, 20.0f);
	env12->m_pTransform->m_position = D3DXVECTOR3(-35, 30, 430);
	env12->m_pTransform->m_scale = D3DXVECTOR3(35, 35, 35);
	env12->PlayAnimation();


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
	// SOLDIERS
	//////////////////////////////////////////////////////////////////////////
	auto soldier01 = Soldier::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Soldier01.json");
	auto soldier02 = Soldier::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Soldier02.json");
	auto soldier03 = Soldier::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Soldier03.json");
	auto soldier04 = Soldier::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Soldier04.json");
	auto soldier05 = Soldier::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Soldier05.json");
	auto soldier06 = Soldier::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Soldier06.json");


	//////////////////////////////////////////////////////////////////////////
	// NAMED
	//////////////////////////////////////////////////////////////////////////
	auto named = HGoblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/HGoblin.json");


	//////////////////////////////////////////////////////////////////////////
	// CINEMATIC
	//////////////////////////////////////////////////////////////////////////
	//HGoblinCinematicTrack * pHGoblinCineTrack = new HGoblinCinematicTrack(named);
	//GetCinematicManager()->AddCinematic(L"HGoblinCinematic", pHGoblinCineTrack);

	auto goblin01_Cin = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin_Cin01.json");
	auto goblin02_Cin = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin_Cin02.json");
	auto goblin03_Cin = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin_Cin03.json");
	auto goblin04_Cin = Goblin::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Goblin_Cin04.json");

	auto soldier01_Cin = Soldier::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Soldier01_Cin.json");
	auto soldier02_Cin = Soldier::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Soldier02_Cin.json");
	auto soldier03_Cin = Soldier::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Soldier03_Cin.json");
	auto soldier04_Cin = Soldier::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Jungle_Soldier04_Cin.json");
	std::vector<GameObject* > actors = { goblin01_Cin, goblin02_Cin, goblin03_Cin , goblin04_Cin,
	soldier01_Cin, soldier02_Cin, soldier03_Cin, soldier04_Cin};

	for (auto actor : actors)
	{
		actor->SetActive(false);
	}
	//BattleCinematicTrack * pBattleCinTrack = new BattleCinematicTrack(actors);
	//GetCinematicManager()->AddCinematic(L"BattleCinematic", pBattleCinTrack);

	//////////////////////////////////////////////////////////////////////////
	// NONE PLAYER
	//////////////////////////////////////////////////////////////////////////
	Leoni::Create(this, PATH->DatasPathW() + L"HierarchyData/Jungle_Leoni.json");
	Guido::Create(this, PATH->DatasPathW() + L"HierarchyData/Jungle_Guido.json");
	TalkableGoblin::Create(this, PATH->DatasPathW() + L"HierarchyData/GoblinNPC.json");
	Jungle_Gagato::Create(this, PATH->DatasPathW() + L"HierarchyData/Jungle_Gagato.json");
	Jungle_Liurens::Create(this, PATH->DatasPathW() + L"HierarchyData/Jungle_Mathias.json");
	Jungle_Chitata::Create(this, PATH->DatasPathW() + L"HierarchyData/Jungle_Chitata.json");
	// gagato / 잡화 
	// mathi / 무기점
	// chitata /  퀘스트



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
	SOUND->StopAll();

	EventDispatcher::RemoveEventListener(QuestEvent::QuestAccept, "ArbaJungleScene");
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

void ArbaJungleScene::OnQuestAccept(void * pQuestIndex)
{
	int index = *static_cast<int*>(pQuestIndex);
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	Quest * pQuest = pScene->GetQuestManager()->GetQuest(index);
	if (pQuest->GetQuestName().compare(L"고블린 퇴치") == 0)
	{

		UpdateDispatcher::Dispatch([&]()->UpdateDispatcher::UpdateState
		{
			m_elapsed += TIMER->getDeltaTime();
			if (m_elapsed >= m_cinematicDelay)
			{
				GameScene* pScene = static_cast<GameScene*>(SCENE);
				pScene->GetCinematicManager()->PlayCinematic(L"BattleCinematic");
				return UpdateDispatcher::UpdateState::End;
			}
			return UpdateDispatcher::UpdateState::Continue;
		}, []() {});
	}
}
