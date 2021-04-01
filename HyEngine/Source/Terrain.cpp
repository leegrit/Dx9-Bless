#include "StandardEngineFramework.h"
#include "Terrain.h"
#include "VertexTypes.h"
#include "IndexTypes.h"
#include "TextureLoader.h"
#include "PathManager.h"
#include "TerrainData.h"

HyEngine::Terrain::Terrain(Scene * scene, GameObject * parent, std::wstring name)
	: GameObject(ERenderType::RenderTexture, scene, parent, name)
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
	: GameObject(ERenderType::RenderTexture, scene, parent, name)
{
	SetEditID(editID);
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
					x * m_vertexInterval,
					0,
					z * m_vertexInterval
				);
				D3DXVECTOR2 uv = D3DXVECTOR2
				(
					x / (m_vertexCountX - 1),
					1.f - z / (m_vertexCountZ - 1.f)
				);

				pVertices->x = position.x;
				pVertices->y = position.y;
				pVertices->z = position.z;
				pVertices->u = uv.x;
				pVertices->v = uv.y;
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
}

void HyEngine::Terrain::Render()
{
	if(m_pTexture)
		DEVICE->SetTexture(0, m_pTexture);
	if (m_pNormal)
	{
		// TODO
	}

	DEVICE->SetStreamSource(0, m_pVB, 0, m_vertexSize);
	DEVICE->SetFVF(m_fvf);
	DEVICE->SetIndices(m_pIB);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vertexCount, 0, m_triCount);
}

void HyEngine::Terrain::UpdatedData(EDataType dataType)
{
	if (dataType != EDataType::TerrainData)
		return;

	m_vertexCountX = m_pTerrainData->vertexCountX;
	m_vertexCountZ = m_pTerrainData->vertexCountZ;
	m_vertexInterval = m_pTerrainData->vertexInterval;
	
	std::wstring diffusePath = CString::CharToWstring(m_pTerrainData->diffuseFilePath);
	m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->ResourcesPathW() +diffusePath);

	std::wstring normalPath = CString::CharToWstring(m_pTerrainData->normalFilePath);
	m_pNormal = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->ResourcesPathW() + normalPath);


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
					x * m_vertexInterval,
					0,
					z * m_vertexInterval
				);
				D3DXVECTOR2 uv = D3DXVECTOR2
				(
					x / (m_vertexCountX - 1),
					1.f - z / (m_vertexCountZ - 1.f)
				);

				pVertices->x = position.x;
				pVertices->y = position.y;
				pVertices->z = position.z;
				pVertices->u = uv.x;
				pVertices->v = uv.y;
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
