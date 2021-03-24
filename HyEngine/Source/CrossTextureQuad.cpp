#include "StandardEngineFramework.h"
#include "CrossTextureQuad.h"
#include "VertexTypes.h"
#include "IndexTypes.h"


void HyEngine::CrossTextureQuad::Initialize(void * arg)
{
	m_vertexCount = 8;
	m_vertexSize = sizeof(TextureVertex);

	m_indexCount = 4;

	m_primitiveCount = m_indexCount;
}

void HyEngine::CrossTextureQuad::CreateVertex()
{
	HRESULT hr;

	

	D3DVERTEXELEMENT9 element[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	DEVICE->CreateVertexDeclaration(element, &m_pDeclare);

	

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
		// 가로
		vertices[0] = TextureVertex(-0.5f, 0, 0.5f, 0, 0);
		vertices[1] = TextureVertex(0.5f, 0, 0.5f, 1, 0);
		vertices[2] = TextureVertex(0.5f, 0, -0.5f, 1, 1);
		vertices[3] = TextureVertex(-0.5f, 0, -0.5f, 0, 1);

		// 세로
		vertices[4] = TextureVertex(0.f, -0.5f, 0.5f, 0, 0);
		vertices[5] = TextureVertex(0.f, 0.5f, 0.5f, 1, 0);
		vertices[6] = TextureVertex(0.f, 0.5f, -0.5f, 1, 1);
		vertices[7] = TextureVertex(0.f, -0.5f, -0.5f, 0, 1);
	}
	UnlockVertices();
}

void HyEngine::CrossTextureQuad::CreateIndex()
{
	HRESULT hr;
	hr = DEVICE->CreateIndexBuffer
	(
		m_indexCount * sizeof(Index16),
		D3DUSAGE_DYNAMIC,
		Index16::FMT,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		nullptr
	);
	assert(SUCCEEDED(hr));

	Index16 * indices = LockIndices();
	{
		indices[0]._1 = 0;
		indices[0]._2 = 1;
		indices[0]._3 = 2;

		indices[1]._1 = 0;
		indices[1]._2 = 2;
		indices[1]._3 = 3;


		indices[2]._1 = 4;
		indices[2]._2 = 5;
		indices[2]._3 = 6;

		indices[3]._1 = 4;
		indices[3]._2 = 6;
		indices[3]._3 = 7;
	}
	UnlockIndices();
}

TextureVertex * HyEngine::CrossTextureQuad::LockVertices()
{
	assert(m_pVertexBuffer != nullptr);
	TextureVertex* vertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	return vertices;
}

void HyEngine::CrossTextureQuad::UnlockVertices()
{
	m_pVertexBuffer->Unlock();
}

Index16 * HyEngine::CrossTextureQuad::LockIndices()
{
	assert(m_pIndexBuffer != nullptr);
	Index16* indices;
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	return indices;
}

void HyEngine::CrossTextureQuad::UnlockIndices()
{
	m_pIndexBuffer->Unlock();
}
