#include "StandardEngineFramework.h"
#include "Terrain.h"
#include "VertexTypes.h"
#include "IndexTypes.h"
#include "TextureLoader.h"
#include "PathManager.h"
#include "TerrainData.h"

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
	m_vertexSize = sizeof(TextureVertex);
	m_vertexCount = m_vertexCountX * m_vertexCountZ;
	m_triCount = (m_vertexCountX - 1) * (m_vertexCountZ - 1) * 2;
	m_fvf = TextureVertex::FVF;

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


	TextureVertex* pVertices = nullptr;
	
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
			}
		}
	}
	m_pVB->Unlock();

	Index32* pIndices = nullptr;

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

				/* left triangle */
				pIndices[triIndex]._1 = index + m_vertexCountX;
				pIndices[triIndex]._2 = index + 1;
				pIndices[triIndex++]._3 = index;
			}
		}
	}
	m_pIB->Unlock();

}

void HyEngine::Terrain::Update()
{
	GameObject::Update();
}

void HyEngine::Terrain::Render()
{
	GameObject::Render();
	if(m_pTexture)
		DEVICE->SetTexture(0, m_pTexture);
	if (m_pNormal)
	{
		// TODO
	}
	DEVICE->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	DEVICE->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	DEVICE->SetStreamSource(0, m_pVB, 0, m_vertexSize);
	DEVICE->SetFVF(m_fvf);
	DEVICE->SetIndices(m_pIB);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vertexCount, 0, m_triCount);
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
	m_vertexSize = sizeof(TextureVertex);
	m_vertexCount = m_vertexCountX * m_vertexCountZ;
	m_triCount = (m_vertexCountX - 1) * (m_vertexCountZ - 1) * 2;
	m_fvf = TextureVertex::FVF;

	m_indexSize = sizeof(Index32);
	m_indexFMT = D3DFMT_INDEX32;

	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
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


	TextureVertex* pVertices = nullptr;

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
			}
		}
	}
	m_pVB->Unlock();

	Index32* pIndices = nullptr;

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

				/* left triangle */
				pIndices[triIndex]._1 = index + m_vertexCountX;
				pIndices[triIndex]._2 = index + 1;
				pIndices[triIndex++]._3 = index;
			}
		}
	}
	m_pIB->Unlock();

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
