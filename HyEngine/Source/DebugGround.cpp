#include "StandardEngineFramework.h"
#include "DebugGround.h"
#include "VertexTypes.h"
#include "IndexTypes.h"

using namespace HyEngine;

DebugGround::DebugGround(Scene * scene, GameObject* parent)
	: GameObject(ERenderType::RenderTexture, scene, parent,L"Debug_Ground")
{
	Initialize();
}


void DebugGround::Render()
{

	GameObject::Render();
	HRESULT hr;


	// TODO : wire frame¿¡ »öÀÌ ¾ÈÀÔÇôÁü...
	hr = DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	assert(SUCCEEDED(hr));

	hr =  DEVICE->SetStreamSource(0, m_pVertexBuffer, 0, m_vertexSize);
	assert(SUCCEEDED(hr));

	hr = DEVICE->SetFVF(ColorVertex::FVF);
	assert(SUCCEEDED(hr));

	hr = DEVICE->SetIndices(m_pIndexBuffer);
	assert(SUCCEEDED(hr));


	hr = DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vertexCount, 0, m_triCount);
	assert(SUCCEEDED(hr));

	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void DebugGround::Initialize()
{
	m_vertexSize = sizeof(ColorVertex);
	m_vertexCount = m_xCount * m_zCount;
	m_triCount = (m_xCount - 1) * (m_zCount - 1) * 2;

	m_indexSize = sizeof(Index16);

	HRESULT hr;
	hr = DEVICE->CreateVertexBuffer
	(
		m_vertexCount * m_vertexSize,
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		nullptr
	);
	assert(SUCCEEDED(hr));
	hr = DEVICE->CreateIndexBuffer
	(
		m_triCount * m_indexSize,
		D3DUSAGE_WRITEONLY,
		Index16::FMT,
		D3DPOOL_MANAGED,
		&m_pIndexBuffer,
		nullptr
	);
	assert(SUCCEEDED(hr));


	ColorVertex* vertices = nullptr;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	int index = 0;

	for (int z = 0; z < m_zCount; ++z)
	{
		for (int x = 0; x < m_xCount; ++x)
		{
			index = z * m_xCount + x;
			if (m_vertexCount <= index)
				continue;

			vertices[index].x = (float)(x* m_spacing);
			vertices[index].y = 0.f;
			vertices[index].z = (float)z * m_spacing;
			vertices[index].color = D3DCOLOR_XRGB(0, 255, 0);
		}
	}

	m_pVertexBuffer->Unlock();

	Index16* indices = nullptr;

	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	int triIndex = 0;
	for (int z = 0; z < m_zCount - 1; z++)
	{
		for (int x = 0; x < m_xCount - 1; x++)
		{
			index = z * m_xCount + x;
			if (m_vertexCount <= index)
				continue;

			/* ¿À¸¥ÂÊ »ï°¢Çü */
			indices[triIndex]._1 = index + m_xCount;
			indices[triIndex]._2 = index + m_xCount + 1;
			indices[triIndex++]._3 = index + 1;

			/* ¿ÞÂÊ »ï°¢Çü */
			indices[triIndex]._1 = index + m_xCount;
			indices[triIndex]._2 = index + 1;
			indices[triIndex++]._3 = index;
		}
	}

	m_pIndexBuffer->Unlock();

	m_pTransform->SetPosition(-(m_xCount * m_spacing * 0.5f), 0.f, -(m_zCount * m_spacing * 0.5f));
	m_pTransform->SetScale(1, 1, 1);
}
