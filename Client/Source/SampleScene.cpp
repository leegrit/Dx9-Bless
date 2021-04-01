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

void SampleScene::Update()
{
	if(KEYBOARD->Press('B'))
	{
		m_pPawn->m_pTransform->Translate(m_pPawn->m_pTransform->Forward() * 10 * TIMER->getDeltaTime());
	}
	if (KEYBOARD->Press('V'))
	{
		m_pPawn->m_pTransform->Translate(-m_pPawn->m_pTransform->Forward() * 10 * TIMER->getDeltaTime());
	}
}

void SampleScene::Load()
{
 	Light* light = Light::CreateDirectionalLight();
 	SetGlobalLight(light);

	auto camera = DynamicCamera::Create(this, nullptr, L"SampleCamera");
	AddCamera(L"SampleCamera", camera);
	SelectCamera(L"SampleCamera");


	Skybox* skybox = new Skybox(camera, PATH->ResourcesPathW() + L"Assets/SkyBox/SkyBox_0.dds");
	skybox->Initialize();
	SetSkybox(skybox);
	NavMesh* navMesh=	NavMesh::Create(this, nullptr, PATH->DatasPathW() + L"NavMeshData/Sample_NavMesh.json");
	
	m_pPawn = Pawn::Create(this, nullptr, navMesh, PATH->DatasPathW() + L"HierarchyData/Sample_Elf.json");
	GroupMapObject::Create(this, nullptr, L"Group", PATH->DatasPathW() + L"MapData/ChunkMap_6.json");

	
}

void SampleScene::Unload()
{
}

void SampleScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}
