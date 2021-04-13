// #include "StandardEngineFramework.h"
// #include "EditMesh.h"
// #include "EditData.h"
// #include "GameObjectData.h"
// #include "MeshData.h"
// #include "PathManager.h"
// #include "ObjectContainer.h"
// #include "Light.h"
// 
// using namespace HyEngine;
// 
// EditMesh::EditMesh(Scene * scene, GameObject * parent, int editID)
// 	: EditObject(ERenderType::RenderOpaque, scene, parent, editID)
// {
// 	m_pMesh = MeshLoader::GetMesh(PATH->ResourcesPath() + "System/Cube.obj");
// 	//assert(m_pMesh);
// 	m_pBaseTex = (IDirect3DTexture9*)(TextureLoader::GetTexture(PATH->ResourcesPathW() + L"System/Checker.png"));
// 
// 
// }
// 
// EditMesh::~EditMesh()
// {
// 	Object::Destroy(m_pCollider);
// 	SAFE_RELEASE(m_pBaseTex);
// }
// 
// void EditMesh::Initialize()
// {
// 	m_pCollider = SphereCollider::Create(EColliderType::Multipurpose, this, 1, Layer::Player, [](Collider*) {});
// }
// 
// void EditMesh::Render()
// {
// 	GameObject::Render();
// 
// 	/* Get Shader */
// 	ID3DXEffect* pShader = nullptr;
// 	EDIT_ENGINE->TryGetShader(L"GBuffer", &pShader);
// 	assert(pShader);
// 
// 	/* Get Selected Cam */
// 	Camera* pSelectedCamera = nullptr;
// 	pSelectedCamera = GetScene()->GetSelectedCamera();
// 	assert(pSelectedCamera);
// 
// 
// 	if (m_pDxMesh)
// 	{
// 		for (int i = 0; i < m_mtrls.size(); i++)
// 		{
// 			/* Find Directional Light */
// 			Light* directionalLight = nullptr;
// 			auto& lights = GetScene()->GetObjectContainer()->GetRenderableLightAll();
// 			for (auto& light : lights)
// 			{
// 				if (light->Type() == ELightType::DIRECTIONAL)
// 				{
// 					directionalLight = light;
// 					break;
// 				}
// 			}
// 
// 			/* Set Light ViewMatrix */
// 			if (directionalLight != nullptr)
// 			{
// 				D3DXMATRIX lightViewMatrix;
// 				D3DXMATRIX lightProjMatrix;
// 
// 				D3DXMatrixLookAtLH(&lightViewMatrix,
// 					&pSelectedCamera->GetPosition().operator D3DXVECTOR3(),
// 					&(pSelectedCamera->GetPosition() + directionalLight->Direction()).operator D3DXVECTOR3(),
// 					&Vector3::Up
// 				);
// 				D3DXMatrixOrthoLH(&lightProjMatrix,
// 					10000, 10000, -10, 100);
// 
// 				pShader->SetValue("LightViewMatrix", &lightViewMatrix, sizeof(lightViewMatrix));
// 				pShader->SetValue("LightProjMatrix", &lightProjMatrix, sizeof(lightProjMatrix));
// 			}
// 
// 
// 			/* Set world, view and projection */
// 			pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
// 			pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
// 			pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));
// 
// 			/* Set world position */
// 			pShader->SetValue("WorldPosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));
// 
// 			/* Set albedo */
// 			D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
// 			pShader->SetTexture(albedoHandle, m_textures[i]);
// 
// 			/* Get Directory path */
// 			std::wstring dirPath = Path::GetDirectoryName(PATH->ResourcesPathW() + m_lastLoadedMeshPath);
// 
// 			/* Find normal map */
// 			std::wstring normalMapName = m_textureNames[i];
// 			CString::Replace(&normalMapName, L"_D_", L"_N_");
// 			IDirect3DTexture9* normalMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + normalMapName);
// 
// 			/* Find Emissive map */
// 			std::wstring emissiveMapName = m_textureNames[i];
// 			CString::Replace(&emissiveMapName, L"_D_", L"_E_");
// 			IDirect3DTexture9* emissiveMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + emissiveMapName);
// 
// 			/* Find Specular map */
// 			std::wstring specularMapName = m_textureNames[i];
// 			CString::Replace(&specularMapName, L"_D_", L"_SP_");
// 			IDirect3DTexture9* specularMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + specularMapName);
// 
// 			bool hasNormalMap = false;
// 
// 			/* If normalmap exists, set texture. */
// 			if (normalMap != nullptr)
// 			{
// 				hasNormalMap = true;
// 
// 				D3DXHANDLE normalHandle = pShader->GetParameterByName(0, "NormalTex");
// 				pShader->SetTexture(normalHandle, normalMap);
// 			}
// 			else
// 			{
// 				D3DXHANDLE normalHandle = pShader->GetParameterByName(0, "NormalTex");
// 				pShader->SetTexture(normalHandle, NULL);
// 			}
// 			pShader->SetValue("HasNormalMap", &hasNormalMap, sizeof(hasNormalMap));
// 
// 			/* If emissiveMap exists set texture */
// 			if (emissiveMap != nullptr)
// 			{
// 				D3DXHANDLE emissiveHandle = pShader->GetParameterByName(0, "EmissiveTex");
// 				pShader->SetTexture(emissiveHandle, emissiveMap);
// 			}
// 			else
// 			{
// 				D3DXHANDLE emissiveHandle = pShader->GetParameterByName(0, "EmissiveTex");
// 				pShader->SetTexture(emissiveHandle, NULL);
// 			}
// 
// 			/* If specularMap exists, set texture */
// 			if (specularMap != nullptr)
// 			{
// 				D3DXHANDLE specularHandle = pShader->GetParameterByName(0, "SpecularTex");
// 				pShader->SetTexture(specularHandle, specularMap);
// 			}
// 			else
// 			{
// 				D3DXHANDLE specularHandle = pShader->GetParameterByName(0, "SpecularTex");
// 				pShader->SetTexture(specularHandle, NULL);
// 			}
// 
// 			pShader->SetBool("HasEmissiveMap", false);
// 			if (directionalLight != nullptr)
// 				pShader->SetTechnique("GBufferWithShadow");
// 			else
// 				pShader->SetTechnique("GBuffer");
// 			pShader->Begin(0, 0);
// 			{
// 				pShader->BeginPass(0);
// 				m_pDxMesh->DrawSubset(i);
// 				pShader->EndPass();
// 			}
// 			pShader->End();
// 		}
// 	}
// 	else if (m_pMesh)
// 	{
// 		float farPlane = pSelectedCamera->GetFar();
// 		pShader->SetValue("Far", &farPlane, sizeof(pSelectedCamera->GetFar()));
// 
// 		/* Set world, view and projection */
// 		pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
// 		pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
// 		pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));
// 
// 		/* Set world position */
// 		pShader->SetValue("WorldPosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));
// 
// 		/* Set albedo */
// 		D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
// 		pShader->SetTexture(albedoHandle, m_pBaseTex);
// 		pShader->SetTechnique("GBuffer");
// 		pShader->Begin(0, 0);
// 		{
// 			pShader->BeginPass(0);
// 			assert(m_pMesh);
// 			DEVICE->SetStreamSource(0, m_pMesh->GetVertexBuffer(), 0, m_pMesh->GetVertexSize());
// 			DEVICE->SetVertexDeclaration(m_pMesh->GetDeclare());
// 			DEVICE->SetIndices(m_pMesh->GetIndexBuffer());
// 
// 			assert(m_pBaseTex);
// 			DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pMesh->GetVertexCount(), 0, m_pMesh->GetPrimitiveCount());
// 			pShader->EndPass();
// 		}
// 		pShader->End();
// 		
// 	}
// }
// 
// void HyEngine::EditMesh::DrawPrimitive()
// {
// 	for (int i = 0; i < m_mtrls.size(); i++)
// 	{
// 		m_pDxMesh->DrawSubset(i);
// 	}
// }
// 
// ID3DXMesh * HyEngine::EditMesh::GetDxMesh() const
// {
// 	return m_pDxMesh;
// }
// 
// bool HyEngine::EditMesh::CalcBounds(D3DXVECTOR3 * center, float * radius)
// {
// 	if (m_pDxMesh == nullptr)
// 		return false;
// 
// 	BYTE* ptr = nullptr;
// 
// 	// get the face count
// 	DWORD numVertices = m_pDxMesh->GetNumVertices();
// 
// 	// get the fvf flags
// 	DWORD fvfSize = D3DXGetFVFVertexSize(m_pDxMesh->GetFVF());
// 
// 	// lock the vertex buffer
// 	m_pDxMesh->LockVertexBuffer(0, (void**)&ptr);
// 
// 	HRESULT hr;
// 	hr = D3DXComputeBoundingSphere((D3DXVECTOR3*)ptr,
// 		numVertices,
// 		fvfSize,
// 		center, radius);
// 	assert(SUCCEEDED(hr));
// 
// 	m_pDxMesh->UnlockVertexBuffer();
// 
// 
// 	float scaleFactor = std::max(m_pTransform->m_scale.x(), m_pTransform->m_scale.y());
// 	scaleFactor = std::max(scaleFactor, m_pTransform->m_scale.z());
// 	// scale영향 받도록한다.
// 	*radius *= scaleFactor;
// 
// 	return true;
// 
// }
// 
// void HyEngine::EditMesh::UpdatedData(EDataType dataType)
// {
// 	switch (dataType)
// 	{
// 	case EDataType::MeshData:
// 		assert(m_pMeshData);
// 		MeshData* data = m_pMeshData;
// 		assert(data);
// 		std::wstring  meshPath = CString::CharToWstring(data->meshFilePath);
// 		std::wstring meshPathExt = HyEngine::Path::GetExtension(meshPath);
// 		std::wstring diffuseTexturePath = CString::CharToWstring(data->diffuseTexturePath);
// 		std::wstring diffuseTextureExt = HyEngine::Path::GetExtension(diffuseTexturePath);
// 
// 
// 		// mesh file
// 		if (std::wcscmp(meshPathExt.c_str(), L"obj") == 0) // 두 문자열이 동일할 경우
// 		{
// 			// obj format인 경우
// 			m_pMesh = MeshLoader::GetMesh(CString::ToString(ResourcePath::MeshFilePath + meshPath));
// 		}
// 		// xfile format인 경우
// 		else if (std::wcscmp(meshPathExt.c_str(), L"X") == 0 || std::wcscmp(meshPathExt.c_str(), L"x") == 0)
// 		{
// 			if (m_lastLoadedMeshPath != meshPath)
// 			{
// 				m_lastLoadedMeshPath = meshPath;
// 				HRESULT hr = 0;
// 
// 				ID3DXBuffer * adjBuffer = nullptr;
// 				ID3DXBuffer* mtrlBuffer = nullptr;
// 				DWORD numMtrls = 0;
// 				
// 
// 				hr = D3DXLoadMeshFromX
// 				(
// 					(PATH->ResourcesPathW() + meshPath).c_str(),
// 					D3DXMESH_MANAGED,
// 					DEVICE,
// 					&adjBuffer,
// 					&mtrlBuffer,
// 					0,
// 					&numMtrls,
// 					&m_pDxMesh
// 				);
// 				assert(SUCCEEDED(hr));
// 
// 				if (mtrlBuffer != 0 && numMtrls != 0)
// 				{
// 					D3DXMATERIAL * mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();
// 
// 					std::wstring dirPath = HyEngine::Path::GetDirectoryName(PATH->ResourcesPathW() + meshPath);
// 					for (int i = 0; i < numMtrls; i++)
// 					{
// 						// the MatD3D property doesn't have an ambient value set
// 						// when its loaded, so set it now:
// 						mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
// 						// save the ith material
// 						m_mtrls.push_back(mtrls[i]);
// 
// 						// check if the ith material has an associative texture
// 						if (mtrls[i].pTextureFilename != 0)
// 						{
// 							IDirect3DTexture9* tex = nullptr;
// 							std::wstring fileName = CString::CharToWstring(mtrls[i].pTextureFilename);
// 							D3DXCreateTextureFromFile
// 							(
// 								DEVICE,
// 								(dirPath + fileName).c_str(),
// 								&tex
// 							);
// 							m_textureNames.push_back(fileName);
// 							// save the loaded texture
// 							m_textures.push_back(tex);
// 						}
// 						else
// 						{
// 							m_textureNames.push_back(L"");
// 							// no texture for the ith subset
// 							m_textures.push_back(0);
// 						}
// 					}
// 				}
// 				mtrlBuffer->Release();
// 
// 				hr = m_pDxMesh->OptimizeInplace
// 				(
// 					D3DXMESHOPT_ATTRSORT |
// 					D3DXMESHOPT_COMPACT |
// 					D3DXMESHOPT_VERTEXCACHE,
// 					(DWORD*)adjBuffer->GetBufferPointer(),
// 					0, 0, 0
// 				);
// 
// 				adjBuffer->Release();
// 
// 				assert(SUCCEEDED(hr));
// 
//  
//  				D3DVERTEXELEMENT9 meshDeclaration[MAX_FVF_DECL_SIZE];
//  				DWORD vertexStride = m_pDxMesh->GetNumBytesPerVertex();
//  				if (SUCCEEDED(m_pDxMesh->GetDeclaration(meshDeclaration)))
//  				{
//  					DWORD numDeclarations = 0;
//  					for (int i = 0; (i < MAX_FVF_DECL_SIZE) && (meshDeclaration[i].Stream != 0xFF); i++)
//  					{
//  						numDeclarations++;
//  					}
//  					/* Tangent */
//  					meshDeclaration[numDeclarations].Stream = 0;
//  					meshDeclaration[numDeclarations].Offset = (WORD)vertexStride;
//  					meshDeclaration[numDeclarations].Type = D3DDECLTYPE_FLOAT3;
//  					meshDeclaration[numDeclarations].Method = D3DDECLMETHOD_DEFAULT;
//  					meshDeclaration[numDeclarations].Usage = D3DDECLUSAGE_TANGENT;
//  					meshDeclaration[numDeclarations].UsageIndex = 0;
//  
//  					/* Binormal */
//  					meshDeclaration[numDeclarations + 1].Stream = 0;
//  					meshDeclaration[numDeclarations + 1].Offset = (WORD)(vertexStride + 3 * sizeof(float));
//  					meshDeclaration[numDeclarations + 1].Type = D3DDECLTYPE_FLOAT3;
// 					meshDeclaration[numDeclarations + 1].Method = D3DDECLMETHOD_DEFAULT;
//  					meshDeclaration[numDeclarations + 1].Usage = D3DDECLUSAGE_BINORMAL;
//  					meshDeclaration[numDeclarations + 1].UsageIndex = 0;
//  
//  					/* Ending element */
//  					memset(&meshDeclaration[numDeclarations + 2], 0, sizeof(D3DVERTEXELEMENT9));
//  					meshDeclaration[numDeclarations + 2].Stream = 0xFF;
//  					meshDeclaration[numDeclarations + 2].Type = D3DDECLTYPE_UNUSED;
//  
//  					ID3DXMesh* clonedMesh = nullptr;
//  					if (SUCCEEDED(m_pDxMesh->CloneMesh(m_pDxMesh->GetOptions(), meshDeclaration, DEVICE, &clonedMesh)))
//  					{
//  						m_pDxMesh->Release();
//  						m_pDxMesh = clonedMesh;
//  					}
//  
//  				}
//  				m_pDxMesh->UpdateSemantics(meshDeclaration);
//  
//  
//  				/* Get adjacency */
//  				LPDWORD pAdjacency = new DWORD[m_pDxMesh->GetNumFaces() * 3];
//  				m_pDxMesh->GenerateAdjacency(0.0001f, pAdjacency);
//  
//  				/* Compute tangent vector */
//  				D3DXComputeTangent(m_pDxMesh, 0, 0, 0, 1, pAdjacency);
// 
// 
// 				// Collider 크기 변경
// 
// 				D3DXVECTOR3 center;
// 				float radius;
// 				CalcBounds(&center, &radius);
// 				assert(m_pCollider);
// 				SphereCollider* sphereCol = dynamic_cast<SphereCollider*>(m_pCollider);
// 				assert(sphereCol);
// 				sphereCol->SetRadius(radius);
// 				D3DXVECTOR3 originPos = m_pTransform->m_position;
// 				D3DXVECTOR3 offsetPos = center - originPos;
// 				sphereCol->SetOffset(offsetPos);
// 			}
// 		}
// 
// 		// texture file
// 		if ((std::wcscmp(diffuseTextureExt.c_str(), L"png") == 0) || (std::wcscmp(diffuseTextureExt.c_str(), L"tga") == 0))
// 		{
// 			m_pBaseTex = (IDirect3DTexture9*)(TextureLoader::GetTexture(PATH->ResourcesPathW() + diffuseTexturePath));
// 		}
// 		break;
// 	}
// }
// 
// //void HyEngine::EditMesh::SetMesh(const std::wstring & path)
// //{
// //	if (m_pMesh)
// //		m_pMesh.reset();
// //	m_pMesh = MeshLoader::GetMesh(CString::ToString(path));
// //}
// //
// //void HyEngine::EditMesh::SetDiffuse(const std::wstring & path)
// //{
// //	if (m_pBaseTex)
// //		m_pBaseTex.reset();
// //	m_pBaseTex = IDirect3DTexture9*(TextureLoader::GetTexture(path));
// //}
// //
// //void HyEngine::EditMesh::SetBumb(const std::wstring & path)
// //{
// //}
// //
// //void HyEngine::EditMesh::SetEmission(const std::wstring & path)
// //{
// //}
