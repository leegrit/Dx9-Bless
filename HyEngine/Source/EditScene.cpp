#include "StandardEngineFramework.h"
#include "EditScene.h"
#include "EditCamera.h"
#include "Light.h"
#include "Ring.h" // Å×½ºÆ®
#include "TestMesh.h"
#include "EditMesh.h"

using namespace Editor;

void Editor::EditScene::Update()
{

}

void Editor::EditScene::Load()
{
	m_pEditCamera = EditCamera::Create(this, nullptr);
	Camera * camera = m_pEditCamera;
	AddCamera(camera->GetName(), camera);
	SelectCamera(camera->GetName());

	Light* light = Light::CreateDirectionalLight();
	light->Specular() = D3DXVECTOR4(1, 1, 1, 1);
	light->Ambient() = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1);
	SetGlobalLight(light);
}

void Editor::EditScene::Unload()
{
	Object::Destroy(m_pEditCamera);
}

void Editor::EditScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}

void Editor::EditScene::LateLoadScene()
{
}

void Editor::EditScene::AddMeshObject(int index)
{
	//Ring::Create(this, nullptr);
	EditMesh::Create(this, nullptr, index);
	//EditMesh::Create(this, nullptr);
}

GameObject * Editor::EditScene::GetMeshObject(int index)
{
	for (auto& obj : GetMeshObjectAll())
	{
		EditObject* editObj = dynamic_cast<EditObject*>(obj);
		assert(editObj);
		if (editObj->GetEditID() == index)
			return obj;
	}
}

Camera * Editor::EditScene::GetEditCamera()
{
	return m_pEditCamera;
}


