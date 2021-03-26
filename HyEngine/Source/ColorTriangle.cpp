#include "StandardEngineFramework.h"
#include "ColorTriangle.h"
#include "VertexTypes.h"
#include "IndexTypes.h"

void HyEngine::ColorTriangle::Initialize(void * arg)
{
	if (arg != nullptr)
	{
		D3DCOLOR* color = (D3DCOLOR*)arg;
		assert(color);
		m_color = *color;
	}
	else
		m_color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void HyEngine::ColorTriangle::CreateVertex()
{
	HRESULT hr;
	m_vertexCount = 3;
	m_vertexSize = sizeof(ColorVertex);
	m_vertexFVF = ColorVertex::FVF;

	D3DVERTEXELEMENT9 element[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};
	DEVICE->CreateVertexDeclaration(element, &m_pDeclare);
	
	// 사실 index는 필요 없지만 통일성을 위해 사용한다.
	m_indexCount = 1;
	m_primitiveCount = m_indexCount;

	hr = DEVICE->CreateVertexBuffer
	(
		m_vertexCount * m_vertexSize,
		D3DUSAGE_DYNAMIC,
		NULL,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		0
	);
	assert(SUCCEEDED(hr));

	ColorVertex* vertices = LockVertices();
	{
		vertices[0] = ColorVertex(-0.5f, -0.5f, 0, m_color);
		vertices[1] = ColorVertex(0, 0.5f, 0, m_color);
		vertices[2] = ColorVertex(0.5f, -0.5f, 0, m_color);

	}
	UnlockVertices();



}

void HyEngine::ColorTriangle::CreateIndex()
{
	HRESULT hr;

	hr = DEVICE->CreateIndexBuffer
	(
		1 * sizeof(Index16),
		D3DUSAGE_DYNAMIC,
		Index16::FMT,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		nullptr
	);
	assert(SUCCEEDED(hr));

	Index16* indices = LockIndices();
	{
		indices[0]._1 = 0;
		indices[0]._2 = 1;
		indices[0]._3 = 2;
	}
	UnlockIndices();
}

ColorVertex * HyEngine::ColorTriangle::LockVertices()
{
	assert(m_pVertexBuffer != nullptr);
	ColorVertex* vertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	return vertices;
}

void HyEngine::ColorTriangle::UnlockVertices()
{
	m_pVertexBuffer->Unlock();
}

Index16 * HyEngine::ColorTriangle::LockIndices()
{
	assert(m_pIndexBuffer != nullptr);
	Index16* indices;
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	return indices;
}

void HyEngine::ColorTriangle::UnlockIndices()
{
	m_pIndexBuffer->Unlock();
}
