#include "StandardEngineFramework.h"
#include "EditScene.h"
#include "EditCamera.h"
#include "Light.h"
#include "Ring.h" // 테스트
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

void Editor::EditScene::PickNavMesh(float xMousePos, float yMousePos)
{
	for (auto& obj : GetMeshObjectAll())
	{
		EditMesh* editObj = dynamic_cast<EditMesh*>(obj);
		assert(editObj);
		if (editObj->GetStaticType() == EStaticType::Navigation)
		{
			ID3DXMesh* mesh = editObj->GetDxMesh();
			if (mesh == nullptr) return;
			// navmesh picking은 xfile만 가능

			D3DXVECTOR3 origin;
			D3DXVECTOR3 direction;
			GetEditCamera()->UnProjection(&origin, &direction, D3DXVECTOR3(xMousePos, yMousePos, 0));
			BOOL isHit = false;
			DWORD faceIndex;
			FLOAT u;
			FLOAT v;
			FLOAT dist;
			LPD3DXBUFFER allHits;
			DWORD countOfHits;
			D3DXVECTOR3 resultPos;
			D3DXIntersect(mesh, &origin, &direction, &isHit, &faceIndex, &u, &v, &dist, &allHits, &countOfHits);
			if (isHit)
			{
				resultPos = origin + direction * dist;
			}

		}
	}
}


