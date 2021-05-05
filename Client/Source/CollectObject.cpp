#include "stdafx.h"
#include "CollectObject.h"
#include "ObjectContainer.h"
#include "Light.h"
#include "MeshData.h"
#include "HierarchyData.h"
#include "GameObjectData.h"
#include "PathManager.h"
#include "Deserializer.h"
#include "UIManager.h"
#include "GameScene.h"
#include "Client_Events.h"

CollectObject::CollectObject(Scene * pScene, std::wstring name)
	: Mesh(ERenderType::RenderOpaque, pScene, nullptr, name)
	, m_pMesh(nullptr)
{

}

CollectObject::~CollectObject()
{
}

void CollectObject::Initialize(std::wstring dataPath)
{
	std::shared_ptr<HierarchyData> data= Deserializer::Deserialize(dataPath);
	InsertGameData(data->gameObjectData);
	InsertMeshData(data->meshData);
}

void CollectObject::Render()
{
	GameObject::Render();

	for (int i = 0; i < m_mtrls.size(); i++)
	{
		if (m_effects[i] == nullptr)
			continue;

		m_effects[i]->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
		m_effects[i]->SetValue("ViewMatrix", &CAMERA->GetViewMatrix(), sizeof(CAMERA->GetViewMatrix()));
		m_effects[i]->SetValue("ProjMatrix", &CAMERA->GetProjectionMatrix(), sizeof(CAMERA->GetProjectionMatrix()));

		/* Set world position */
		m_effects[i]->SetValue("WorldPosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));

		if (m_diffuseMasks[i] == nullptr)
			m_effects[i]->SetTechnique("StaticMesh");
		else
			m_effects[i]->SetTechnique("StaticMaskedMesh");
		m_effects[i]->Begin(0, 0);
		{
			m_effects[i]->BeginPass(0);
			m_pMesh->DrawSubset(i);
			m_effects[i]->EndPass();
		}
		m_effects[i]->End();
	}
}

void CollectObject::Update()
{
	GameObject::Update();
	
}

void CollectObject::DrawPrimitive(ID3DXEffect * pEffect)
{
	GameObject::DrawPrimitive(pEffect);
	pEffect->SetBool("IsSkinnedMesh", false);
	pEffect->CommitChanges();
	for (int i = 0; i < m_mtrls.size(); i++)
	{
		m_pMesh->DrawSubset(i);
	}
}

void CollectObject::UpdatedData(EDataType dataType)
{
	if (dataType != EDataType::MeshData) return;
	MeshData* data = m_pMeshData;
	assert(data);
	std::wstring  meshPath = CString::CharToWstring(data->meshFilePath);
	std::wstring meshPathExt = HyEngine::Path::GetExtension(meshPath);
	std::wstring diffuseTexturePath = CString::CharToWstring(data->diffuseTexturePath);
	std::wstring diffuseTextureExt = HyEngine::Path::GetExtension(diffuseTexturePath);


	// xfile formatÀÎ °æ¿ì
	if (std::wcscmp(meshPathExt.c_str(), L"X") == 0 || std::wcscmp(meshPathExt.c_str(), L"x") == 0)
	{
		if (m_lastLoadedMeshPath != meshPath)
		{
			m_lastLoadedMeshPath = meshPath;
			HRESULT hr = 0;

			ID3DXBuffer * adjBuffer = nullptr;
			ID3DXBuffer* mtrlBuffer = nullptr;
			DWORD numMtrls = 0;


			bool isSucceeded = MeshLoader::TryGetMesh(PATH->ResourcesPathW() + meshPath, &adjBuffer, &mtrlBuffer, &numMtrls, &m_pMesh);
			assert(isSucceeded);

			if (mtrlBuffer != 0 && numMtrls != 0)
			{
				D3DXMATERIAL * mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

				std::wstring dirPath = HyEngine::Path::GetDirectoryName(PATH->ResourcesPathW() + meshPath);
				for (int i = 0; i < numMtrls; i++)
				{
					// the MatD3D property doesn't have an ambient value set
					// when its loaded, so set it now:
					mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
					// save the ith material
					m_mtrls.push_back(mtrls[i]);

					// check if the ith material has an associative texture
					if (mtrls[i].pTextureFilename != 0)
					{
						IDirect3DTexture9* tex = nullptr;
						std::wstring fileName = CString::CharToWstring(mtrls[i].pTextureFilename);
						D3DXCreateTextureFromFile
						(
							DEVICE,
							(dirPath + fileName).c_str(),
							&tex
						);
						m_textureNames.push_back(fileName);
						// save the loaded texture
						m_textures.push_back(tex);

						/* Find NormalMap */
						std::wstring normalMapName = fileName;
						CString::Replace(&normalMapName, L"_D_", L"_N_");
						IDirect3DTexture9 * normalMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + normalMapName);
						m_normals.push_back(normalMap);

						/* Find EmissiveMap */
						std::wstring emissiveMapName = fileName;
						CString::Replace(&emissiveMapName, L"_D_", L"_E_");
						IDirect3DTexture9* emissiveMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + emissiveMapName);
						m_emissives.push_back(emissiveMap);

						/* Find SpecularMap */
						std::wstring specularMapName = fileName;
						CString::Replace(&specularMapName, L"_D_", L"_SP_");
						IDirect3DTexture9* specularMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + specularMapName);
						m_speculars.push_back(specularMap);

						/* Find DiffuseMask */
						std::wstring diffuseMaskName = fileName;
						CString::Replace(&diffuseMaskName, L"_D_", L"_DM_");
						IDirect3DTexture9* diffuseMask = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + diffuseMaskName);
						m_diffuseMasks.push_back(diffuseMask);

						/* Insert Shader */
						bool isFirst = false;
						ID3DXEffect * pEffect = nullptr;
							isFirst = ENGINE->InsertShader(fileName, PATH->ShadersPathW() + L"StaticMesh.fx");
							ENGINE->TryGetShader(fileName, &pEffect);

						if (isFirst)
						{
							D3DXHANDLE albedoHandle = pEffect->GetParameterByName(0, "AlbedoTex");
							pEffect->SetTexture(albedoHandle, tex);

							/* Set NormalMap */
							D3DXHANDLE normalHandle = pEffect->GetParameterByName(0, "NormalTex");
							pEffect->SetTexture(normalHandle, normalMap);

							/* Set Emissive */
							D3DXHANDLE emissiveHandle = pEffect->GetParameterByName(0, "EmissiveTex");
							pEffect->SetTexture(emissiveHandle, emissiveMap);

							/* Set Specular */
							D3DXHANDLE specularHandle = pEffect->GetParameterByName(0, "SpecularTex");
							pEffect->SetTexture(specularHandle, specularMap);

							/* Set SpecularMask */
							D3DXHANDLE specularMaskHandle = pEffect->GetParameterByName(0, "SpecularMaskTex");
							pEffect->SetTexture(specularMaskHandle, NULL);

							/* Set DiffuseMask */
							D3DXHANDLE diffuseMaskHandle = pEffect->GetParameterByName(0, "DiffuseMaskTex");
							pEffect->SetTexture(diffuseMaskHandle, diffuseMask);
						}

						m_effects.push_back(pEffect);
					}
					else
					{
						m_textureNames.push_back(L"");
						// no texture for the ith subset
						m_textures.push_back(NULL);
						m_normals.push_back(NULL);
						m_emissives.push_back(NULL);
						m_speculars.push_back(NULL);
						m_diffuseMasks.push_back(NULL);

						m_effects.push_back(nullptr);
					}
				}
			}
			/* Create BoundingMesh */
			D3DXVECTOR3 center;
			float radius;
			ComputeBoundingSphere(&center, &radius);

			radius = radius * m_pTransform->m_scale.x();

			/* Create */
			CreateBoundingMesh(center, radius);


			/*if (IS_EDITOR)
				EDIT_ENGINE->TryGetShader(L"StaticMesh", &m_pef);
			else
				ENGINE->TryGetShader(L"StaticMesh", &m_pShader);*/

		}
	}
}

bool CollectObject::ComputeBoundingSphere(D3DXVECTOR3 * center, float * radius)
{
	if (m_pMesh == nullptr)
	{
		*center = D3DXVECTOR3(0, 0, 0);
		*radius = 0;
		return false;
	}
	BYTE* ptr = nullptr;

	// get the face count
	DWORD numVertices = m_pMesh->GetNumVertices();

	// get the fvf flags
	//DWORD fvfSize = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	D3DVERTEXELEMENT9 element[MAX_FVF_DECL_SIZE];
	m_pMesh->GetDeclaration(element);
	UINT declSize = D3DXGetDeclVertexSize(element, 0);
	// lock the vertex buffer
	m_pMesh->LockVertexBuffer(0, (void**)&ptr);

	HRESULT hr;
	hr = D3DXComputeBoundingSphere((D3DXVECTOR3*)ptr,
		numVertices,
		declSize,
		center, radius);
	assert(SUCCEEDED(hr));

	m_pMesh->UnlockVertexBuffer();


	return true;
}

std::wstring CollectObject::GetMeshPath() const
{
	return m_lastLoadedMeshPath;
}

void CollectObject::Collecting()
{
	if (m_bCollectable == false)return;

	float dist = D3DXVec3Length(&(PLAYER->m_pTransform->m_position - m_pTransform->m_position).operator D3DXVECTOR3());

	if (dist <= m_interactRadius)
	{
		GameScene* gameScene = static_cast<GameScene*>(GetScene());
		gameScene->GetUIManager()->ShowCollectInteractPanel();

		if (KEYBOARD->Press('F'))
		{
			if (m_bCollecting == false)
			{
				m_bCollecting = true;
				OnCollectBegin();
			}
			
			m_elapsed += TIMER->getDeltaTime();

			gameScene->GetUIManager()->ShowCollectProgressBar(m_elapsed / m_collectDelay);

			if (m_elapsed >= m_collectDelay)
			{
				m_elapsed = 0;
				m_bCollectable = false;
				DoCollect();
				OnCollected();
				OnCollectEnd();
				gameScene->GetUIManager()->HideCollectProgressBar();
			}
		}
		else
		{
			gameScene->GetUIManager()->HideCollectProgressBar();

			m_bCollecting = false;
			m_elapsed = 0;
		}
	}
	else
	{

		GameScene* gameScene = static_cast<GameScene*>(GetScene());

		if (m_bCollecting)
		{
			gameScene->GetUIManager()->HideCollectProgressBar();
		}
		m_bCollecting = false;
		m_elapsed = 0;
		//gameScene->GetUIManager()->HideCollectProgressBar();
		//gameScene->GetUIManager()->HideCollectInteractPanel();
	}
}

void CollectObject::DoCollect()
{
	EventDispatcher::TriggerEvent(QuestEvent::CollectQuestObject, (void*)this);

}

void CollectObject::OnCollected()
{
}

void CollectObject::OnCollectBegin()
{
}

void CollectObject::OnCollectEnd()
{
}

CollectObject * CollectObject::Create(Scene * pScene, std::wstring name, std::wstring dataPath)
{
	CollectObject* obj = new CollectObject(pScene, name);
	obj->Initialize(dataPath);
	return obj;
}
