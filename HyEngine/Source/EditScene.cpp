#include "StandardEngineFramework.h"
#include "EditScene.h"
#include "EditCamera.h"
#include "Light.h"
#include "Ring.h" // �׽�Ʈ
#include "TestMesh.h"
#include "EditMesh.h"
#include "NavMesh.h"
#include "EditDynamicMesh.h"
#include "Terrain.h"
#include "ObjectContainer.h"
#include "LightObject.h"
#include "MeshEffect.h"
#include "StaticMesh.h"
#include "DynamicMesh.h"
#include "UIPanel.h"

using namespace HyEngine;

void HyEngine::EditScene::Update()
{

}

void HyEngine::EditScene::Load()
{
	m_pEditCamera = EditCamera::Create(this, nullptr);
	Camera * camera = m_pEditCamera;
	//AddCamera(camera->GetName(), camera);
	SelectCamera(camera->GetName());

	//Light* light = Light::CreateDirectionalLight();
	//light->Specular() = D3DXVECTOR4(1, 1, 1, 1);
	//light->Ambient() = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1);
	//SetGlobalLight(light);
}

void HyEngine::EditScene::Unload()
{
	Object::Destroy(m_pEditCamera);
}

void HyEngine::EditScene::LoadAsync(std::function<void(int, int)> onProgress)
{
}

void HyEngine::EditScene::LateLoadScene()
{
}

void HyEngine::EditScene::AddMeshObject(int editIndex)
{
	//Ring::Create(this, nullptr);
	StaticMesh::Create(this, nullptr, editIndex);
	
	//EditMesh::Create(this, nullptr);
}

void HyEngine::EditScene::AddPawn(int editIndex)
{
	DynamicMesh::Create(this, nullptr, editIndex);
}

void HyEngine::EditScene::AddNavMesh(int editIndex)
{
	NavMesh::Create(this, nullptr, editIndex);
}

void HyEngine::EditScene::AddTerrain(int editIndex)
{
	Terrain::Create(this, nullptr, editIndex);
}

void HyEngine::EditScene::AddLight(int editIndex)
{
	LightObject::Create(this, nullptr, editIndex);
}

void HyEngine::EditScene::AddMeshEffect(int editIndex)
{
	MeshEffect::Create(this, editIndex);
}

void HyEngine::EditScene::AddTextureEffect(int editIndex)
{
	// TODO
	assert(false);
}

void HyEngine::EditScene::AddUIPanel(int editIndex)
{
	UIPanel::Create(this, nullptr, editIndex);
}


GameObject * HyEngine::EditScene::GetGameObject(int editIndex)
{
	for (auto& obj : GetObjectContainer()->GetGameObjectAll())
	{
		if (obj->GetEditID() == editIndex)
			return obj;
	}
	// TODO 
	/*for (auto& obj : this->GetTextureObjectAll())
	{

	}*/
}

Camera * HyEngine::EditScene::GetEditCamera()
{
	return m_pEditCamera;
}

//void HyEngine::EditScene::PickNavMesh(float xMousePos, float yMousePos)
//{
//	for (auto& obj : GetMeshObjectAll())
//	{
//		EditMesh* editObj = dynamic_cast<EditMesh*>(obj);
//		assert(editObj);
//		if (editObj->GetStaticType() == EStaticType::Navigation)
//		{
//			ID3DXMesh* mesh = editObj->GetDxMesh();
//			if (mesh == nullptr) return;
//			// navmesh picking�� xfile�� ����
//
//			D3DXVECTOR3 origin;
//			D3DXVECTOR3 direction;
//			GetEditCamera()->UnProjection(&origin, &direction, D3DXVECTOR3(xMousePos, yMousePos, 0));
//			BOOL isHit = false;
//			DWORD faceIndex;
//			FLOAT u;
//			FLOAT v;
//			FLOAT dist;
//			LPD3DXBUFFER allHits;
//			DWORD countOfHits;
//			D3DXVECTOR3 resultPos;
//
//			/*D3DXMATRIX worldInverse;
//			D3DXMatrixInverse(&worldInverse, nullptr, &editObj->m_pTransform->GetWorldMatrix());
//			D3DXVec3TransformCoord(&origin, &origin, &worldInverse);
//			D3DXVec3TransformNormal(&direction, &direction, &worldInverse);*/
//
//			D3DXIntersect(mesh, &origin, &direction, &isHit, &faceIndex, &u, &v, &dist, &allHits, &countOfHits);
//			if (isHit)
//			{
//				GameObject* selectedObject = EDIT_ENGINE->GetSelectedObject();
//				assert(selectedObject);
//				NavMesh* navMesh = dynamic_cast<NavMesh*>(selectedObject);
//				//// �ش� �Լ��� navMesh�� ���õ� ���¿��� ���;��Ѵ�.
//				assert(navMesh);
//
//				resultPos = origin + direction * dist;
//
//				// celloption�� ���� �߰�����
//				navMesh->PickingCell(resultPos, ECellOption::NORMAL);
//			}
//
//		}
//	}
//}

bool HyEngine::EditScene::PickNavMesh(float xMousePos, float yMousePos, ECellOption option,  VectorData * pickedPos)
{
	std::vector<GameObject*>& opaqueContainer =  GetObjectContainer()->GetOpaqueObjectAll();
	/* For Terrain */
	//std::vector<GameObject*>& textureContainer = GetTextureObjectAll();

	//std::vector<GameObject*> container;
	//container.insert(container.end(), meshContainer.begin(), meshContainer.end());
	//container.insert(container.end(), textureContainer.begin(), textureContainer.end());

	for (auto& obj : opaqueContainer)
	{
// 		EditMesh* editObj = dynamic_cast<EditMesh*>(obj);
// 		if (editObj == nullptr) continue;
		//assert(editObj);
		if (obj->GetStaticType() == EStaticType::Navigation)
		{
			StaticMesh* editMesh = dynamic_cast<StaticMesh*>(obj);
			if (editMesh != nullptr)
			{
				ID3DXMesh* mesh = editMesh->GetMesh();
				if (mesh == nullptr) continue;
				// navmesh picking�� xfile�� ����

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

				D3DXMATRIX worldInverse;

				// ��ȯ �� ���� ���� ���� origin, direction�� �����صд�.
				// �̸� �����ϴ� ������ ���߿� world ������ origin�� direction�� ���Ǳ� ����
				D3DXVECTOR3 worldOrigin = origin;
				D3DXVECTOR3 worldDirection = direction;
				D3DXMatrixInverse(&worldInverse, nullptr, &obj->m_pTransform->GetWorldMatrix());
				D3DXVec3TransformCoord(&origin, &origin, &worldInverse);
				D3DXVec3TransformNormal(&direction, &direction, &worldInverse);

				/*D3DXMATRIX worldInverse;
				D3DXMatrixInverse(&worldInverse, nullptr, &editObj->m_pTransform->GetWorldMatrix());
				D3DXVec3TransformCoord(&origin, &origin, &worldInverse);
				D3DXVec3TransformNormal(&direction, &direction, &worldInverse);*/

				D3DXIntersect(mesh, &origin, &direction, &isHit, &faceIndex, &u, &v, &dist, &allHits, &countOfHits);
				if (isHit)
				{
					GameObject* selectedObject = EDIT_ENGINE->GetSelectedObject();
					assert(selectedObject);
					NavMesh* navMesh = dynamic_cast<NavMesh*>(selectedObject);
					//// �ش� �Լ��� navMesh�� ���õ� ���¿��� ���;��Ѵ�.
					assert(navMesh);

					resultPos = worldOrigin + worldDirection * dist;
					pickedPos->x = resultPos.x;
					pickedPos->y = resultPos.y;
					pickedPos->z = resultPos.z;

					navMesh->TryPickingCell(pickedPos, resultPos, option);


					return true;

				}
			}

			Terrain* terrain = dynamic_cast<Terrain*>(obj);
			if (terrain != nullptr)
			{
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

				D3DXMATRIX worldInverse;
				D3DXMatrixInverse(&worldInverse, nullptr, &obj->m_pTransform->GetWorldMatrix());
				D3DXVec3TransformCoord(&origin, &origin, &worldInverse);
				D3DXVec3TransformNormal(&direction, &direction, &worldInverse);

				isHit = terrain->TryPickOnTerrain(origin, direction, &resultPos);
				if (isHit)
				{

					GameObject* selectedObject = EDIT_ENGINE->GetSelectedObject();
					assert(selectedObject);
					NavMesh* navMesh = dynamic_cast<NavMesh*>(selectedObject);
					//// �ش� �Լ��� navMesh�� ���õ� ���¿��� ���;��Ѵ�.
					assert(navMesh);

					pickedPos->x = resultPos.x;
					pickedPos->y = resultPos.y;
					pickedPos->z = resultPos.z;

					navMesh->TryPickingCell(pickedPos, resultPos, option);


					return true;
				}
			}
		}
	}
	return false;
}



