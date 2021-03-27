#include "StandardEngineFramework.h"
#include "DiffuseQuad.h"
#include "VertexTypes.h"
#include "IndexTypes.h"

void HyEngine::DiffuseQuad::Initialize(void * arg)
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

void HyEngine::DiffuseQuad::CreateVertex()
{
	HRESULT hr;

	m_vertexCount = 4;
	m_vertexSize = sizeof(ColorVertex);
	m_vertexFVF = ColorVertex::FVF;

	hr = DEVICE->CreateVertexBuffer
	(
		m_vertexCount * m_vertexSize,
		D3DUSAGE_DYNAMIC,
		ColorVertex::FVF,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		0
	);
	assert(SUCCEEDED(hr));

	ColorVertex* vertices = LockVertices();
	{
		vertices[0] = ColorVertex(0, 0, 0, m_color);
		vertices[1] = ColorVertex(1, 0, 0, m_color);
		vertices[2] = ColorVertex(1, 1, 0, m_color);
		vertices[3] = ColorVertex(0, 1, 0, m_color);
	}
	UnlockVertices();


}

void HyEngine::DiffuseQuad::CreateIndex()
{
	HRESULT hr;

	hr = DEVICE->CreateIndexBuffer
	(
		2 * sizeof(Index16),
		D3DUSAGE_DYNAMIC,
		Index16::FMT,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		nullptr
	);
	assert(SUCCEEDED(hr));

	Index16* indices = LockIndices();
	{
		indices[0]._1 = 3;
		indices[0]._2 = 2;
		indices[0]._3 = 0;

		indices[1]._1 = 2;
		indices[1]._2 = 1;
		indices[1]._3 = 0;
	}
	UnlockIndices();
}

ColorVertex * HyEngine::DiffuseQuad::LockVertices()
{
	assert(m_pVertexBuffer != nullptr);
	ColorVertex* vertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	return vertices;
}

void HyEngine::DiffuseQuad::UnlockVertices()
{
	m_pVertexBuffer->Unlock();
}

Index16 * HyEngine::DiffuseQuad::LockIndices()
{
	assert(m_pIndexBuffer != nullptr);
	Index16* indices;
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	return indices;
}

void HyEngine::DiffuseQuad::UnlockIndices()
{
	m_pIndexBuffer->Unlock();
}
