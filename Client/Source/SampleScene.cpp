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
#include "QuestNPC.h"
#include "DummyBoss.h"


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

	ENGINE->DrawText(L"TEST FONT", D3DXVECTOR3(fontPosX, fontPosY, fontPosZ), D3DXVECTOR3(fontScaleX, fontScaleY, 1), D3DXCOLOR(1, 0, 0, 1));
}

void SampleScene::Load()
{
	//////////////////////////////////////////////////////////////////////////
	// RENDER OPTION
	//////////////////////////////////////////////////////////////////////////
	ENGINE->SetRenderOption(RenderOptions::RenderCollider, false);
	ENGINE->SetRenderOption(RenderOptions::RenderLight, false);
	ENGINE->SetRenderOption(RenderOptions::RenderNavMesh, false);
	ENGINE->SetRenderOption(RenderOptions::RenderShadow, false);
	ENGINE->SetRenderOption(RenderOptions::RenderUI, false);



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
	m_pPlayer->m_pTransform->SetScale(0.5f, 0.5f, 0.5f);

	//////////////////////////////////////////////////////////////////////////
	// CAMERA
	//////////////////////////////////////////////////////////////////////////
	m_pGameCam = PlayerCamera::Create(this, m_pPlayer, L"PlayerCamera");
	SelectCamera(L"PlayerCamera");

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


	//////////////////////////////////////////////////////////////////////////
	// EQUIPMENT
	//////////////////////////////////////////////////////////////////////////
	m_pEquip =	Equipment::Create(this, m_pPlayer, PATH->ResourcesPathW() + L"Assets/Mesh/Item/OSW/OSW_00.x", L"Bip01-R-Finger21", L"Sword");
	m_pEquip->m_pTransform->SetScale(1.5f, 1.5f, 1.5f);

	//////////////////////////////////////////////////////////////////////////
	// ENEMY
	//////////////////////////////////////////////////////////////////////////
	auto enemy1 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone0.json");
	auto enemy2 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone1.json");
	auto enemy3 = Skeletone::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/Skeletone2.json");

	//////////////////////////////////////////////////////////////////////////
	// NONE PLAYER
	//////////////////////////////////////////////////////////////////////////
	auto nonePlayer = QuestNPC::Create(this, PATH->DatasPathW() + L"HierarchyData/Sire.json");

	//////////////////////////////////////////////////////////////////////////
	// NAMED
	//////////////////////////////////////////////////////////////////////////
	auto dummyBoss = DummyBoss::Create(this, navMesh, PATH->DatasPathW() + L"HierarchyData/GhostSoldier.json");

	//////////////////////////////////////////////////////////////////////////
	// UI
	//////////////////////////////////////////////////////////////////////////
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/ClassMark_0.png", D3DXVECTOR3(0, -276, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(120, 120, 1), L"1");
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
	/*UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/BossGauge_1.png", D3DXVECTOR3(0, 290.4, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(800, 150, 1), L"66");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/BossGauge_0.png", D3DXVECTOR3(0, 291, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(800, 150, 1), L"77");
	UIPanel::Create(this, PATH->ResourcesPathW() + L"Assets/UI/BossGauge_2.png", D3DXVECTOR3(30, 292, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(640, 12, 1), L"88");*/

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
	//Gui::Get()->ShowTextInput(temp, 256, 200, 200);

	if (ENGINE->GetGameMode() == EGameMode::EDIT_MODE)
	{
		Gui::Get()->ShowEditRenderOption();

		//Gui::Get()->BeginEditGUI();
		Gui::Get()->ShowGUI({
			[&]() {Gui::Get()->InputInt("FontPosX", &fontPosX); },
			[&]() {Gui::Get()->InputInt("FontPosY", &fontPosY); },
			[&]() {Gui::Get()->InputInt("FontPosZ", &fontPosZ); },
			[&]() {Gui::Get()->InputInt("FontScaleX", &fontScaleX); },
			[&]() {Gui::Get()->InputInt("FontScaleY", &fontScaleY); }
		});
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
		Camera* pSelectedCam = SCENE->GetSelectedCamera();
		D3DXVECTOR3 pos = pSelectedCam->m_pTransform->m_position;
		SelectCamera(L"SampleCamera");
		pSelectedCam = SCENE->GetSelectedCamera();
		pSelectedCam->m_pTransform->m_position = pos;

	}
	else if (ENGINE->GetGameMode() == EGameMode::GAME_MODE)
	{
		SelectCamera(L"PlayerCamera");
	}
}

char SampleScene::temp[256];