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
 	//Light* light = Light::CreateDirectionalLight();
 //	SetGlobalLight(light);

	auto camera = DynamicCamera::Create(this, nullptr, L"SampleCamera");
	//AddCamera(L"SampleCamera", camera);
	SelectCamera(L"SampleCamera");


	Skybox* skybox = new Skybox(camera, PATH->ResourcesPathW() + L"Assets/SkyBox/SkyBox_0.dds");
	skybox->Initialize();
	//SetSkybox(skybox);
	NavMesh* navMesh=	NavMesh::Create(this, nullptr, PATH->DatasPathW() + L"NavMeshData/Sample_NavMesh.json");
	
	m_pPawn = Pawn::Create(this, nullptr, navMesh, PATH->DatasPathW() + L"HierarchyData/Sample_Elf.json");
	GroupMapObject::Create(this, nullptr, L"Group", PATH->DatasPathW() + L"MapData/ChunkMap_6.json");

	Light * light = new Light();
	light->Type() = ELightType::POINT;
	light->Diffuse() = D3DXCOLOR(3.0f, 3.0f, 3.0f, 3.0f);
	light->Position() = D3DXVECTOR4( m_pPawn->m_pTransform->m_position.operator D3DXVECTOR3(), 1);
	light->Range() = 10;
	light->Constant() = 0.0f;
	light->Linear() = 0.2f;
	light->Exp() = 0.0f;


	
	GetObjectContainer()->AddLight(light);
}

void SampleScene::Unload()
{
}

void SampleScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}
