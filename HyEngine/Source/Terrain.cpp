#include "StandardEngineFramework.h"
#include "Terrain.h"
#include "VertexTypes.h"
#include "IndexTypes.h"
#include "TextureLoader.h"
#include "PathManager.h"
#include "TerrainData.h"

using namespace HyEngine;

HyEngine::Terrain::Terrain(Scene * scene, GameObject * parent, std::wstring name)
	: GameObject(ERenderType::RenderOpaque, scene, parent, name)
{
	/* Default Texture */
	try
	{
		m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->ResourcesPathW() + L"Assets/Tile/Tile_D_3.tga");
	}
	catch (exception e)
	{
		SEND_LOG_ERROR(e.what());
		m_pTexture = nullptr;
	}
}

HyEngine::Terrain::Terrain(Scene * scene, GameObject * parent, std::wstring name, int editID)
	: GameObject(ERenderType::RenderOpaque, scene, parent, name)
{
	SetEditID(editID);
	/* Default Texture */
	try
	{
		m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->ResourcesPathW() + L"Assets/Tile/Tile_D_3.tga");
	}
	catch (exception e)
	{
		SEND_LOG_ERROR(e.what());
		m_pTexture = nullptr;
	}
}

HyEngine::Terrain::~Terrain()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
}

void HyEngine::Terrain::Initialize()
{
	m_vertexSize = sizeof(BumpModelVertex);
	m_vertexCount = m_vertexCountX * m_vertexCountZ;
	m_triCount = (m_vertexCountX - 1) * (m_vertexCountZ - 1) * 2;
	//m_fvf = BumpModelVertex::FVF;
	D3DVERTEXELEMENT9 element[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0, 20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
		{0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
		D3DDECL_END()
	};
	DEVICE->CreateVertexDeclaration(element, &m_pDeclaration);

	m_indexSize = sizeof(Index32);
	m_indexFMT = D3DFMT_INDEX32;

	HRESULT hr;
	hr = DEVICE->CreateVertexBuffer
	(
		m_vertexCount * m_vertexSize,
		0,
		m_fvf,
		D3DPOOL_MANAGED,
		&m_pVB,
		nullptr
	);
	assert(SUCCEEDED(hr));

	hr = DEVICE->CreateIndexBuffer
	(
		m_triCount * m_indexSize,
		0,
		m_indexFMT,
		D3DPOOL_MANAGED,
		&m_pIB,
		nullptr
	);
	assert(SUCCEEDED(hr));


	BumpModelVertex* pVertices = nullptr;

	m_vtxPositions.clear();
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	{
		size_t index = 0;

		for (size_t z = 0; z < m_vertexCountZ; z++)
		{
			for (size_t x = 0; x < m_vertexCountX; x++)
			{
				index = z * m_vertexCountX + x;
				if (m_vertexCount <= index)
					continue;

				D3DXVECTOR3 position = D3DXVECTOR3
				(
					(float)x * m_vertexInterval,
					0,
					(float)z * m_vertexInterval
				);
				D3DXVECTOR2 uv = D3DXVECTOR2
				(
					(float)x / (m_vertexCountX - 1),
					1.f - (float)z / (m_vertexCountZ - 1.f)
				);

				pVertices[index].x = position.x;
				pVertices[index].y = position.y;
				pVertices[index].z = position.z;
				m_vtxPositions.emplace_back(D3DXVECTOR3
				(
					position.x,
					position.y,
					position.z
				));
				pVertices[index].u = uv.x * m_textureCountX;
				pVertices[index].v = uv.y * m_textureCountZ;

				/* Normal */
				pVertices[index].normalX = 0;
				pVertices[index].normalY = 1;
				pVertices[index].normalZ = 0;

				/* Tangent */

			}
		}
	}
	m_pVB->Unlock();

	Index32* pIndices = nullptr;
	std::vector<Index32> indicesVec;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);
	{
		size_t triIndex = 0;
		size_t index = 0;

		for (size_t z = 0; z < m_vertexCountZ - 1; z++)
		{
			for (size_t x = 0; x < m_vertexCountX - 1; x++)
			{
				index = z * m_vertexCountX + x;
				if (m_vertexCount <= index)
					continue;

				/* right triangle */
				pIndices[triIndex]._1 = index + m_vertexCountX;
				pIndices[triIndex]._2 = index + m_vertexCountX + 1;
				pIndices[triIndex++]._3 = index + 1;
				indicesVec.push_back(pIndices[triIndex - 1]);

				/* left triangle */
				pIndices[triIndex]._1 = index + m_vertexCountX;
				pIndices[triIndex]._2 = index + 1;
				pIndices[triIndex++]._3 = index;
				indicesVec.push_back(pIndices[triIndex - 1]);

			}
		}
	}
	m_pIB->Unlock();

	/* Calculate normal, tangent, binormal */
	// 위에서 필요한 모든 정보 구성이 완료된 후에 
	// 완료된 정보를 사용하여 tangent, binormal을 구한다.
	pVertices = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	{
		for (UINT i = 0; i < indicesVec.size(); i++)
		{
			D3DXVECTOR3 tangent;
			D3DXVECTOR3 binormal;
			D3DXVECTOR3 normal;

			/* Calculate Tangent binormal */
			DxHelper::CalculateTangentBinormal
			(
				&pVertices[indicesVec[i]._1],
				&pVertices[indicesVec[i]._2],
				&pVertices[indicesVec[i]._3],
				&tangent,
				&binormal
			);

			/* Calculate Normal */
			DxHelper::CalculateNormal
			(
				&tangent,
				&binormal,
				&normal
			);

			/* Set Normal */
			pVertices[indicesVec[i]._1].normalX = normal.x;
			pVertices[indicesVec[i]._2].normalY = normal.y;
			pVertices[indicesVec[i]._3].normalZ = normal.z;

			/* Set Tangent */
			pVertices[indicesVec[i]._1].tangentX = tangent.x;
			pVertices[indicesVec[i]._2].tangentY = tangent.y;
			pVertices[indicesVec[i]._3].tangentZ = tangent.z;

			/* Set Binormal */
			pVertices[indicesVec[i]._1].binormalX = binormal.x;
			pVertices[indicesVec[i]._2].binormalY = binormal.y;
			pVertices[indicesVec[i]._3].binormalZ = binormal.z;
		}
	}
	m_pVB->Unlock();
}

void HyEngine::Terrain::Update()
{
	GameObject::Update();
}

void HyEngine::Terrain::Render()
{
	GameObject::Render();

	/* Get Shader */
	ID3DXEffect * pShader = nullptr;
#ifdef _EDITOR
	EDIT_ENGINE->TryGetShader(L"GBuffer", &pShader);
#else
	ENGINE->TryGetShader(L"GBuffer", &pShader);
#endif
	assert(pShader);

	/* Get Selected Cam */
	Camera* pSelectedCamera = nullptr;
	pSelectedCamera = GetScene()->GetSelectedCamera();
	assert(pSelectedCamera);

	/* Set world, view, and projection */
	pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
	pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
	pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));

	/* Set world position */
	pShader->SetValue("WorldPosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));

	/* Sel albedo */
	D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
	pShader->SetTexture(albedoHandle, m_pTexture);

	/* Set Normal */
	D3DXHANDLE normalHandle = pShader->GetParameterByName(0, "NormalTex");
	pShader->SetTexture(normalHandle, m_pNormal);

	/* Set Emissive */
	D3DXHANDLE emissiveHandle = pShader->GetParameterByName(0, "EmissiveTex");
	pShader->SetTexture(emissiveHandle, NULL);

	/* Set Sepcular */
	D3DXHANDLE specularHandle = pShader->GetParameterByName(0, "SpecularTex");
	pShader->SetTexture(specularHandle, NULL);

	bool hasNormalMap = m_pNormal ? true : false;

	pShader->SetBool("HasNormalMap", hasNormalMap);

	pShader->SetTechnique("GBuffer");
	pShader->Begin(0, 0);
	{
		pShader->BeginPass(0);

		DEVICE->SetStreamSource(0, m_pVB, 0, m_vertexSize);
		DEVICE->SetVertexDeclaration(m_pDeclaration);
		DEVICE->SetIndices(m_pIB);
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vertexCount, 0, m_triCount);

		pShader->EndPass();
	}
	pShader->End();

}

void HyEngine::Terrain::UpdatedData(EDataType dataType)
{
	if (dataType != EDataType::TerrainData)
		return;

	/* Invalid Data */
	if (m_pTerrainData->vertexCountX <= 0)
	{
		SEND_LOG_WARNING("Invalid TerrainData : vertexCountX is zero");
		return;
	}
	if (m_pTerrainData->vertexCountZ <= 0)
	{
		SEND_LOG_WARNING("Invalid TerrainData : vertexCountZ is zero");
		return;
	}
	if (m_pTerrainData->vertexInterval <= 0)
	{
		SEND_LOG_WARNING("Invalid TerrainData : vertexInterval is zero");
		return;
	}
	if (m_pTerrainData->textureCountX <= 0)
	{
		SEND_LOG_WARNING("Invalid TerrainData : textureCountX is zero");
		return;
	}
	if (m_pTerrainData->textureCountZ <= 0)
	{
		SEND_LOG_WARNING("Invalid TerrainData : textureCountZ is zero");
		return;
	}


	m_vertexCountX = m_pTerrainData->vertexCountX;
	m_vertexCountZ = m_pTerrainData->vertexCountZ;
	m_textureCountX = m_pTerrainData->textureCountX;
	m_textureCountZ = m_pTerrainData->textureCountZ;
	m_vertexInterval = m_pTerrainData->vertexInterval;

	std::wstring diffusePath = CString::CharToWstring(m_pTerrainData->diffuseFilePath);
	IDirect3DTexture9* tempTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->ResourcesPathW() + diffusePath);
	if (tempTexture != nullptr)
		m_pTexture = tempTexture;


	std::wstring normalPath = CString::CharToWstring(m_pTerrainData->normalFilePath);
	IDirect3DTexture9* tempNormal = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->ResourcesPathW() + normalPath);
	if (tempNormal != nullptr)
		m_pNormal = tempNormal;


	/* 변경된 데이터 기반으로 재구성 */
	m_vertexSize = sizeof(BumpModelVertex);
	m_vertexCount = m_vertexCountX * m_vertexCountZ;
	m_triCount = (m_vertexCountX - 1) * (m_vertexCountZ - 1) * 2;
	//m_fvf = BumpModelVertex::FVF;
	D3DVERTEXELEMENT9 element[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 0, 20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
		{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
		D3DDECL_END()
	};
	DEVICE->CreateVertexDeclaration(element, &m_pDeclaration);

	m_indexSize = sizeof(Index32);
	m_indexFMT = D3DFMT_INDEX32;

	HRESULT hr;
	hr = DEVICE->CreateVertexBuffer
	(
		m_vertexCount * m_vertexSize,
		0,
		m_fvf,
		D3DPOOL_MANAGED,
		&m_pVB,
		nullptr
	);
	assert(SUCCEEDED(hr));

	hr = DEVICE->CreateIndexBuffer
	(
		m_triCount * m_indexSize,
		0,
		m_indexFMT,
		D3DPOOL_MANAGED,
		&m_pIB,
		nullptr
	);
	assert(SUCCEEDED(hr));


	BumpModelVertex* pVertices = nullptr;

	m_vtxPositions.clear();
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	{
		size_t index = 0;

		for (size_t z = 0; z < m_vertexCountZ; z++)
		{
			for (size_t x = 0; x < m_vertexCountX; x++)
			{
				index = z * m_vertexCountX + x;
				if (m_vertexCount <= index)
					continue;

				D3DXVECTOR3 position = D3DXVECTOR3
				(
					(float)x * m_vertexInterval,
					0,
					(float)z * m_vertexInterval
				);
				D3DXVECTOR2 uv = D3DXVECTOR2
				(
					(float)x / (m_vertexCountX - 1),
					1.f - (float)z / (m_vertexCountZ - 1.f)
				);

				pVertices[index].x = position.x;
				pVertices[index].y = position.y;
				pVertices[index].z = position.z;
				m_vtxPositions.emplace_back(D3DXVECTOR3
				(
					position.x,
					position.y,
					position.z
				));
				pVertices[index].u = uv.x * m_textureCountX;
				pVertices[index].v = uv.y * m_textureCountZ;

				/* Normal */
				pVertices[index].normalX = 0;
				pVertices[index].normalY = 1;
				pVertices[index].normalZ = 0;

				/* Tangent */

			}
		}
	}
	m_pVB->Unlock();

	Index32* pIndices = nullptr;
	std::vector<Index32> indicesVec;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);
	{
		size_t triIndex = 0;
		size_t index = 0;

		for (size_t z = 0; z < m_vertexCountZ - 1; z++)
		{
			for (size_t x = 0; x < m_vertexCountX - 1; x++)
			{
				index = z * m_vertexCountX + x;
				if (m_vertexCount <= index)
					continue;

				/* right triangle */
				pIndices[triIndex]._1 = index + m_vertexCountX;
				pIndices[triIndex]._2 = index + m_vertexCountX + 1;
				pIndices[triIndex++]._3 = index + 1;
				indicesVec.push_back(pIndices[triIndex - 1]);

				/* left triangle */
				pIndices[triIndex]._1 = index + m_vertexCountX;
				pIndices[triIndex]._2 = index + 1;
				pIndices[triIndex++]._3 = index;
				indicesVec.push_back(pIndices[triIndex - 1]);

			}
		}
	}
	m_pIB->Unlock();

	/* Calculate normal, tangent, binormal */
	// 위에서 필요한 모든 정보 구성이 완료된 후에 
	// 완료된 정보를 사용하여 tangent, binormal을 구한다.
	pVertices = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	{
		for (UINT i = 0; i < indicesVec.size(); i++)
		{
			D3DXVECTOR3 tangent;
			D3DXVECTOR3 binormal;
			D3DXVECTOR3 normal;

			/* Calculate Tangent binormal */
			DxHelper::CalculateTangentBinormal
			(
				&pVertices[indicesVec[i]._1],
				&pVertices[indicesVec[i]._2],
				&pVertices[indicesVec[i]._3],
				&tangent,
				&binormal
			);

			/* Calculate Normal */
			DxHelper::CalculateNormal
			(
				&tangent,
				&binormal,
				&normal
			);

			/* Set Normal */
			pVertices[indicesVec[i]._1].normalX = normal.x;
			pVertices[indicesVec[i]._2].normalY = normal.y;
			pVertices[indicesVec[i]._3].normalZ = normal.z;

			/* Set Tangent */
			pVertices[indicesVec[i]._1].tangentX = tangent.x;
			pVertices[indicesVec[i]._2].tangentY = tangent.y;
			pVertices[indicesVec[i]._3].tangentZ = tangent.z;

			/* Set Binormal */
			pVertices[indicesVec[i]._1].binormalX = binormal.x;
			pVertices[indicesVec[i]._2].binormalY = binormal.y;
			pVertices[indicesVec[i]._3].binormalZ = binormal.z;
		}
	}
	m_pVB->Unlock();

}

bool HyEngine::Terrain::TryPickOnTerrain(D3DXVECTOR3 origin, D3DXVECTOR3 direction, _Out_ D3DXVECTOR3 * pPickedPos)
{
	*pPickedPos = D3DXVECTOR3(0, 0, 0);
	UINT indices[3];
	float u, v, dist;
	for (UINT i = 0; i < m_vertexCountZ - 1; i++)
	{
		for (UINT j = 0; j < m_vertexCountX - 1; j++)
		{
			UINT index = i * m_vertexCountX + j;

			/* right triangle */
			indices[0] = index + m_vertexCountX;
			indices[1] = index + m_vertexCountX + 1;
			indices[2] = index + 1;

			bool isHit = false;
			isHit = D3DXIntersectTri
			(
				&m_vtxPositions[indices[1]],
				&m_vtxPositions[indices[2]],
				&m_vtxPositions[indices[0]],
				&origin, &direction, &u, &v, &dist
			);

			if (isHit)
			{
				D3DXVECTOR3 worldOrigin;
				D3DXVec3TransformCoord(&worldOrigin, &origin, &m_pTransform->GetWorldMatrix());
				D3DXVECTOR3 worldDir;
				D3DXVec3TransformNormal(&worldDir, &direction, &m_pTransform->GetWorldMatrix());

				D3DXVECTOR3 result = worldOrigin + worldDir* dist;

				*pPickedPos = result;
				return true;
				// 				/* PickedPos is local position */
				// 				*pPickedPos = D3DXVECTOR3
				// 				(
				// 					m_vtxPositions[indices[1]].x + u * (m_vtxPositions[indices[0]].x - m_vtxPositions[indices[1]].x),
				// 					0.0f,
				// 					m_vtxPositions[indices[1]].z + v * (m_vtxPositions[indices[2]].z - m_vtxPositions[indices[1]].z)
				// 				);
				// 				
				// 				/* Must be translated to world space */
				// 				D3DXVec3TransformCoord(pPickedPos, pPickedPos, &m_pTransform->GetWorldMatrix());
				// 				return true;
			}


			/* Left Triangle */
			indices[0] = index + m_vertexCountX;
			indices[1] = index + 1;
			indices[2] = index;

			isHit = D3DXIntersectTri
			(
				&m_vtxPositions[indices[2]],
				&m_vtxPositions[indices[0]],
				&m_vtxPositions[indices[1]],
				&origin, &direction, &u, &v, &dist
			);

			if (isHit)
			{
				D3DXVECTOR3 worldOrigin;
				D3DXVec3TransformCoord(&worldOrigin, &origin, &m_pTransform->GetWorldMatrix());
				D3DXVECTOR3 worldDir;
				D3DXVec3TransformNormal(&worldDir, &direction, &m_pTransform->GetWorldMatrix());

				D3DXVECTOR3 result = worldOrigin + worldDir* dist;

				*pPickedPos = result;

				// 
				// 				/* PickedPos is local position */
				// 				*pPickedPos = D3DXVECTOR3
				// 				(
				// 					m_vtxPositions[indices[2]].x + u * (m_vtxPositions[indices[1]].x - m_vtxPositions[indices[2]].x),
				// 					0.0f,
				// 					m_vtxPositions[indices[2]].z + v * (m_vtxPositions[indices[0]].z - m_vtxPositions[indices[2]].z)
				// 				);
				// 
				// 				/* Must be translated to world space */
				// 				D3DXVec3TransformCoord(pPickedPos, pPickedPos, &m_pTransform->GetWorldMatrix());
				return true;
			}
		}
	}
	return false;
}
