#include "StandardEngineFramework.h"
#include "StaticMesh.h"
#include "ObjectContainer.h"
#include "Light.h"
#include "MeshData.h"
#include "HierarchyData.h"
#include "GameObjectData.h"
#include "PathManager.h"

using namespace HyEngine;

HyEngine::StaticMesh::StaticMesh(Scene * scene, GameObject * parent, int editID)
	:Mesh(ERenderType::RenderOpaque, scene, parent, L"StaticMesh"),
	m_pMesh(nullptr)
{
	SetEditID(editID);
}

HyEngine::StaticMesh::StaticMesh(Scene * scene, GameObject * parent, std::wstring name)
	: Mesh(ERenderType::RenderOpaque, scene, parent, name),
	m_pMesh(nullptr)
{
	if (m_pShader == nullptr)
	{
		D3DXCreateEffectFromFile(DEVICE, (PATH->ShadersPathW() + L"StaticMesh.fx").c_str(), nullptr, nullptr, 0, nullptr, &m_pShader, nullptr);
// 		if (IS_EDITOR)
// 			EDIT_ENGINE->TryGetShader(L"StaticMesh", &m_pShader);
// 		else
// 			ENGINE->TryGetShader(L"StaticMesh", &m_pShader);
	}

 	/* Set albedo */
 	m_albedoHandle = m_pShader->GetParameterByName(0, "AlbedoTex");
 
 	/* Set NormalMap */
 	m_normalHandle = m_pShader->GetParameterByName(0, "NormalTex");
 
 	/* Set Emissive */
 	m_emissiveHandle = m_pShader->GetParameterByName(0, "EmissiveTex");
 
 	/* Set Specular */
 	m_specularHandle = m_pShader->GetParameterByName(0, "SpecularTex");
 
 	/* Set SpecularMask */
 	m_specularMaskHandle = m_pShader->GetParameterByName(0, "SpecularMaskTex");
 
 	/* Set DiffuseMask */
 	m_diffuseMaskHandle = m_pShader->GetParameterByName(0, "DiffuseMaskTex");


}

HyEngine::StaticMesh::~StaticMesh()
{
	SAFE_RELEASE(m_pMesh);
}

void HyEngine::StaticMesh::Initialize()
{
}

void HyEngine::StaticMesh::Initialize(shared_ptr<HierarchyData> data)
{
	InsertGameData(data->gameObjectData);
	InsertMeshData(data->meshData);
}

void HyEngine::StaticMesh::Render()
{
	GameObject::Render();
	static int maxNumMatrls = 0;
	
	/* Get Shader */
 	if (m_pShader == nullptr)
 	{
 		if (IS_EDITOR)
 			EDIT_ENGINE->TryGetShader(L"StaticMesh", &m_pShader);
 		else
 			ENGINE->TryGetShader(L"StaticMesh", &m_pShader);
 	}
	assert(m_pShader);

	/* Get Selected Cam */
	Camera* pSelectedCamera = nullptr;
	pSelectedCamera = GetScene()->GetSelectedCamera();
	assert(pSelectedCamera);

	
	std::cout << "MaxNumMtrls : " << maxNumMatrls << std::endl;
	/* Set world, view and projection */
	m_pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
	m_pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
	m_pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));

	/* Set world position */
	m_pShader->SetValue("WorldPosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));

	for (int i = 0; i < m_mtrls.size(); i++)
	{
		
	
		/* Set albedo */
		D3DXHANDLE albedoHandle = m_pShader->GetParameterByName(0, "AlbedoTex");
 		m_pShader->SetTexture(albedoHandle, m_textures[i]);
 
 		/* Set NormalMap */
 		D3DXHANDLE normalHandle = m_pShader->GetParameterByName(0, "NormalTex");
 		m_pShader->SetTexture(normalHandle, m_normals[i]);
 
 		/* Set Emissive */
 		D3DXHANDLE emissiveHandle = m_pShader->GetParameterByName(0, "EmissiveTex");
 		m_pShader->SetTexture(emissiveHandle, m_emissives[i]);
 
 		/* Set Specular */
 		D3DXHANDLE specularHandle = m_pShader->GetParameterByName(0, "SpecularTex");
 		m_pShader->SetTexture(specularHandle, m_speculars[i]);
 
 		/* Set SpecularMask */
 		D3DXHANDLE specularMaskHandle = m_pShader->GetParameterByName(0, "SpecularMaskTex");
 		m_pShader->SetTexture(specularMaskHandle, NULL);
 
 		/* Set DiffuseMask */
 		D3DXHANDLE diffuseMaskHandle = m_pShader->GetParameterByName(0, "DiffuseMaskTex");
 		m_pShader->SetTexture(diffuseMaskHandle, m_diffuseMasks[i]);


		/*bool hasNormalMap = false;
		if (m_normals[i] != nullptr)
			hasNormalMap = true;
		m_pShader->SetValue("HasNormalMap", &hasNormalMap, sizeof(hasNormalMap));*/

		if (m_diffuseMasks[i] == nullptr)
			m_pShader->SetTechnique("StaticMesh");
		else
			m_pShader->SetTechnique("StaticMaskedMesh");
		m_pShader->Begin(0, 0);
		{
			m_pShader->BeginPass(0);
			m_pMesh->DrawSubset(i);
			m_pShader->EndPass();
		}
		m_pShader->End();
	}
}

void HyEngine::StaticMesh::DrawPrimitive(ID3DXEffect* pShader)
{
	GameObject::DrawPrimitive(pShader);
	pShader->SetBool("IsSkinnedMesh", false);
	pShader->CommitChanges();
	for (int i = 0; i < m_mtrls.size(); i++)
	{
		m_pMesh->DrawSubset(i);
	}
}

void HyEngine::StaticMesh::UpdatedData(EDataType dataType)
{
	if (dataType != EDataType::MeshData) return;
	MeshData* data = m_pMeshData;
	assert(data);
	std::wstring  meshPath = CString::CharToWstring(data->meshFilePath);
	std::wstring meshPathExt = HyEngine::Path::GetExtension(meshPath);
	std::wstring diffuseTexturePath = CString::CharToWstring(data->diffuseTexturePath);
	std::wstring diffuseTextureExt = HyEngine::Path::GetExtension(diffuseTexturePath);


	// xfile format인 경우
	if (std::wcscmp(meshPathExt.c_str(), L"X") == 0 || std::wcscmp(meshPathExt.c_str(), L"x") == 0)
	{
		if (m_lastLoadedMeshPath != meshPath)
		{
			m_lastLoadedMeshPath = meshPath;
			HRESULT hr = 0;

			ID3DXBuffer * adjBuffer = nullptr;
			ID3DXBuffer* mtrlBuffer = nullptr;
			DWORD numMtrls = 0;


// 			hr = D3DXLoadMeshFromX
// 			(
// 				(PATH->ResourcesPathW() + meshPath).c_str(),
// 				D3DXMESH_MANAGED,
// 				DEVICE,
// 				&adjBuffer,
// 				&mtrlBuffer,
// 				0,
// 				&numMtrls,
// 				&m_pMesh
// 			);
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
					}
				}
			}
			//mtrlBuffer->Release();
// 
// 			hr = m_pMesh->OptimizeInplace
// 			(
// 				D3DXMESHOPT_ATTRSORT |
// 				D3DXMESHOPT_COMPACT |
// 				D3DXMESHOPT_VERTEXCACHE,
// 				(DWORD*)adjBuffer->GetBufferPointer(),
// 				0, 0, 0
// 			);
// 
// 			//adjBuffer->Release();
// 
// 			assert(SUCCEEDED(hr));
// 
// 
// 			D3DVERTEXELEMENT9 meshDeclaration[MAX_FVF_DECL_SIZE];
// 			DWORD vertexStride = m_pMesh->GetNumBytesPerVertex();
// 			if (SUCCEEDED(m_pMesh->GetDeclaration(meshDeclaration)))
// 			{
// 				DWORD numDeclarations = 0;
// 				for (int i = 0; (i < MAX_FVF_DECL_SIZE) && (meshDeclaration[i].Stream != 0xFF); i++)
// 				{
// 					numDeclarations++;
// 				}
// 				/* Tangent */
// 				meshDeclaration[numDeclarations].Stream = 0;
// 				meshDeclaration[numDeclarations].Offset = (WORD)vertexStride;
// 				meshDeclaration[numDeclarations].Type = D3DDECLTYPE_FLOAT3;
// 				meshDeclaration[numDeclarations].Method = D3DDECLMETHOD_DEFAULT;
// 				meshDeclaration[numDeclarations].Usage = D3DDECLUSAGE_TANGENT;
// 				meshDeclaration[numDeclarations].UsageIndex = 0;
// 
// 				/* Binormal */
// 				meshDeclaration[numDeclarations + 1].Stream = 0;
// 				meshDeclaration[numDeclarations + 1].Offset = (WORD)(vertexStride + 3 * sizeof(float));
// 				meshDeclaration[numDeclarations + 1].Type = D3DDECLTYPE_FLOAT3;
// 				meshDeclaration[numDeclarations + 1].Method = D3DDECLMETHOD_DEFAULT;
// 				meshDeclaration[numDeclarations + 1].Usage = D3DDECLUSAGE_BINORMAL;
// 				meshDeclaration[numDeclarations + 1].UsageIndex = 0;
// 
// 				/* Ending element */
// 				memset(&meshDeclaration[numDeclarations + 2], 0, sizeof(D3DVERTEXELEMENT9));
// 				meshDeclaration[numDeclarations + 2].Stream = 0xFF;
// 				meshDeclaration[numDeclarations + 2].Type = D3DDECLTYPE_UNUSED;
// 
// 				ID3DXMesh* clonedMesh = nullptr;
// 				if (SUCCEEDED(m_pMesh->CloneMesh(m_pMesh->GetOptions(), meshDeclaration, DEVICE, &clonedMesh)))
// 				{
// 					m_pMesh->Release();
// 					m_pMesh = clonedMesh;
// 				}
// 
// 			}
// 			m_pMesh->UpdateSemantics(meshDeclaration);
// 
// 
// 			/* Get adjacency */
// 			LPDWORD pAdjacency = new DWORD[m_pMesh->GetNumFaces() * 3];
// 			m_pMesh->GenerateAdjacency(0.0001f, pAdjacency);
// 
// 			/* Compute tangent vector */
// 			D3DXComputeTangent(m_pMesh, 0, 0, 0, 1, pAdjacency);

			/* Create BoundingMesh */
			D3DXVECTOR3 center;
			float radius;
			ComputeBoundingSphere(&center, &radius);

			radius = radius * m_pTransform->m_scale.x();

			/* Create */
			CreateBoundingMesh(center, radius);


			if (IS_EDITOR)
				EDIT_ENGINE->TryGetShader(L"StaticMesh", &m_pShader);
			else
				ENGINE->TryGetShader(L"StaticMesh", &m_pShader);

			/* Initialize Shader */
			//SAFE_RELEASE(m_pShader);

			// TODO : 우선 기본적으로 StaticMesh.fx를 쓰지만
			// meshMasked등 여러 옵션에 따른 쉐이더 설정을 하도록 수정해야하.ㅁ
			//D3DXCreateEffectFromFile(DEVICE, (PATH->ShadersPathW() + L"StaticMesh.fx").c_str(), nullptr, nullptr, 0, nullptr, &m_pShader, nullptr);
			///* Set albedo */
			//m_albedoHandle = m_pShader->GetParameterByName(0, "AlbedoTex");

			///* Set NormalMap */
			//m_normalHandle = m_pShader->GetParameterByName(0, "NormalTex");

			///* Set Emissive */
			//m_emissiveHandle = m_pShader->GetParameterByName(0, "EmissiveTex");

			///* Set Specular */
			//m_specularHandle = m_pShader->GetParameterByName(0, "SpecularTex");

			///* Set SpecularMask */
			//m_specularMaskHandle = m_pShader->GetParameterByName(0, "SpecularMaskTex");

			///* Set DiffuseMask */
			//m_diffuseMaskHandle = m_pShader->GetParameterByName(0, "DiffuseMaskTex");

			//for (int i = 0; i < m_mtrls.size(); i++)
			//{
			//	std::string albedoName = "AlbedoTex" + i;
			//	m_albedoHandles[i] = m_pShader->GetParameterByName(0, albedoName.c_str());
			//	m_pShader->SetTexture(m_albedoHandles[i], m_textures[i]);

			//	std::string normalName = "NormalTex" + i;
			//	m_normalHandles[i] = m_pShader->GetParameterByName(0, normalName.c_str());
			//	m_pShader->SetTexture(m_albedoHandles[i], m_normals[i]);

			//	std::string emissiveName = "EmissiveTex" + i;
			//	m_emissiveHandles[i] = m_pShader->GetParameterByName(0, emissiveName.c_str());
			//	m_pShader->SetTexture(m_albedoHandles[i], m_emissives[i]);

			//	std::string specularName = "SpecularTex" + i;
			//	m_specularHandles[i] = m_pShader->GetParameterByName(0, specularName.c_str());
			//	m_pShader->SetTexture(m_albedoHandles[i], m_speculars[i]);

			//	std::string specularMaskName = "SpecularMaskTex" + i;
			//	m_specularMaskHandles[i] = m_pShader->GetParameterByName(0, specularMaskName.c_str());
			//	m_pShader->SetTexture(m_albedoHandles[i], NULL);

			//	std::string diffuseMaskName = "DiffuseMaskTex" + i;
			//	m_diffuseMaskHandles[i] = m_pShader->GetParameterByName(0, diffuseMaskName.c_str());
			//	m_pShader->SetTexture(m_albedoHandles[i], m_diffuseMasks[i]);
			//}

			static int mtrlSize = 0;
			if (m_mtrls.size() > 10)
			{
				int a = 0;
			}

		}
	}
}

bool HyEngine::StaticMesh::ComputeBoundingSphere(D3DXVECTOR3 * center, float * radius)
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

ID3DXMesh * HyEngine::StaticMesh::GetMesh() const
{
	return m_pMesh;
}

bool HyEngine::StaticMesh::CalcBounds(D3DXVECTOR3 * center, float * radius)
{
	if (m_pMesh == nullptr)
		return false;

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


	float scaleFactor = std::max(m_pTransform->m_scale.x(), m_pTransform->m_scale.y());
	scaleFactor = std::max(scaleFactor, m_pTransform->m_scale.z());
	// scale영향 받도록한다.
	*radius *= scaleFactor;

	return true;
}

std::wstring HyEngine::StaticMesh::GetMeshPath() const
{
	return m_lastLoadedMeshPath;
}
