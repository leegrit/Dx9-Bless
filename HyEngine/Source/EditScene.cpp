#include "StandardEngineFramework.h"
#include "EditScene.h"
#include "EditCamera.h"
#include "Light.h"
#include "Ring.h" // ?׽?Ʈ
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
#include "EditFont.h"
#include "TextureEffect.h"
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
	DynamicMesh::Create(this, nullptr, editIndex, ESkinningType::SoftwareSkinning);
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
	//assert(false);
	TextureEffect::Create(this, editIndex);
}

void HyEngine::EditScene::AddUIPanel(int editIndex)
{
	UIPanel::Create(this, nullptr, editIndex);
}

void HyEngine::EditScene::AddFont(int editIndex)
{
	EditFont::Create(this, editIndex);
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
//			// navmesh picking?? xfile?? ????
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
//				//// ?ش? ?Լ??? navMesh?? ???õ? ???¿??? ?????;??Ѵ?.
//				assert(navMesh);
//
//				resultPos = origin + direction * dist;
//
//				// celloption?? ???? ?߰?????
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

	D3DXVECTOR3 resultPosition= D3DXVECTOR3(0, 0, 0);
	float minDist = FLT_MAX;
	bool anyHit = false;
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
				// navmesh picking?? xfile?? ????

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

				// ??ȯ ?? ???? ???? ???? origin, direction?? ?????صд?.
				// ?̸? ?????ϴ? ?????? ???߿? world ?????? origin?? direction?? ?????Ǳ? ????
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
					Camera* cam = GetEditCamera();

					resultPos = worldOrigin + worldDirection * dist;
					float dist = D3DXVec3Length(&(cam->m_pTransform->m_position.operator D3DXVECTOR3() - resultPos));
				

					if (minDist > dist)
					{
						anyHit = true;
						minDist = dist;
						resultPosition = resultPos;
						pickedPos->x = resultPos.x;
						pickedPos->y = resultPos.y;
						pickedPos->z = resultPos.z;
					}
					

					


					//return true;

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
					Camera* cam = GetEditCamera();

					float dist = D3DXVec3Length(&(cam->m_pTransform->m_position.operator D3DXVECTOR3() - resultPos));

					if (minDist > dist)
					{
						anyHit = true;
						minDist = dist;
						resultPosition = resultPos;
						pickedPos->x = resultPos.x;
						pickedPos->y = resultPos.y;
						pickedPos->z = resultPos.z;
					}


					//return true;
				}
			}
		}
	}

	if (anyHit)
	{
		GameObject* selectedObject = EDIT_ENGINE->GetSelectedObject();
		NavMesh* navMesh = dynamic_cast<NavMesh*>(selectedObject);
		//// ?ش? ?Լ??? navMesh?? ???õ? ???¿??? ?????;??Ѵ?.
		assert(navMesh);
		navMesh->TryPickingCell(pickedPos, resultPosition, option);
		return true;
	}
	return false;
}



