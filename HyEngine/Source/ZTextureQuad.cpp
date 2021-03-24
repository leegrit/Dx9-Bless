#include "StandardEngineFramework.h"
#include "ZTextureQuad.h"


#include "StandardEngineFramework.h"
#include "TextureQuad.h"
#include "VertexTypes.h"
#include "IndexTypes.h"

using namespace HyEngine;

void HyEngine::ZTextureQuad::Initialize(void * arg)
{
}

void HyEngine::ZTextureQuad::CreateVertex()
{
	HRESULT hr;

	m_vertexCount = 4;
	m_vertexSize = sizeof(TextureVertex);
	//	m_vertexFVF = TextureVertex::FVF;
	D3DVERTEXELEMENT9 element[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	DEVICE->CreateVertexDeclaration(element, &m_pDeclare);
	m_indexCount = 2;
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

	TextureVertex* vertices = LockVertices();
	{
		vertices[0] = TextureVertex(-0.5f,0, 0.5f,  0, 0);
		vertices[1] = TextureVertex(0.5f, 0, 0.5f,  1, 0);
		vertices[2] = TextureVertex(0.5f, 0, -0.5f,  1, 1);
		vertices[3] = TextureVertex(-0.5f,0,  -0.5f, 0, 1);
	}
	UnlockVertices();
}

void HyEngine::ZTextureQuad::CreateIndex()
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
		indices[0]._1 = 0;
		indices[0]._2 = 1;
		indices[0]._3 = 2;

		indices[1]._1 = 0;
		indices[1]._2 = 2;
		indices[1]._3 = 3;
	}
	UnlockIndices();
}

TextureVertex * HyEngine::ZTextureQuad::LockVertices()
{
	assert(m_pVertexBuffer != nullptr);
	TextureVertex* vertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	return vertices;
}

void HyEngine::ZTextureQuad::UnlockVertices()
{
	m_pVertexBuffer->Unlock();
}

Index16 * HyEngine::ZTextureQuad::LockIndices()
{
	assert(m_pIndexBuffer != nullptr);
	Index16* indices;
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	return indices;
}

void HyEngine::ZTextureQuad::UnlockIndices()
{
	m_pIndexBuffer->Unlock();
}
