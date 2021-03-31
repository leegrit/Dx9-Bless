#include "stdafx.h"
#include "SampleScene.h"
#include "SampleCamera.h"
#include "Skybox.h"
#include "PathManager.h"
#include "Light.h"
#include "DynamicMesh.h"
#include "DynamicCamera.h"
#include "GroupMapObject.h"

void SampleScene::Update()
{
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

	DynamicMesh::Create(this, nullptr, L"Elf", PATH->DatasPathW() + L"HierarchyData/Elf.json");
	GroupMapObject::Create(this, nullptr, L"Group", PATH->DatasPathW() + L"MapData/ChunkMap_0.json");
}

void SampleScene::Unload()
{
}

void SampleScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}
