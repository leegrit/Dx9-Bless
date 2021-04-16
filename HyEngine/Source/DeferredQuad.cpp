#include "StandardEngineFramework.h"
#include "DeferredQuad.h"
#include "VertexTypes.h"
#include "IndexTypes.h"

using namespace HyEngine;

DeferredQuad::DeferredQuad()
{
	D3DVERTEXELEMENT9 element[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	DEVICE->CreateVertexDeclaration(element, &m_pDeclare);

	DEVICE->CreateVertexBuffer
	(
		4 * sizeof(TextureVertex),
		D3DUSAGE_DYNAMIC,
		NULL,
		D3DPOOL_DEFAULT,
		&_vb,
		0
	);
	TextureVertex* vertices;
	vertexSize = sizeof(TextureVertex);

	_vb->Lock(0, 0, (void**)&vertices, 0);
	vertices[0] = TextureVertex(-0.5f, -0.5f, 0,  0.0f, 1.0f);
	vertices[1] = TextureVertex(-0.5f, 0.5f, 0,  0.0f, 0.0f);
	vertices[2] = TextureVertex(0.5f, 0.5f, 0,1.0f, 0.0f);

	vertices[3] = TextureVertex(0.5f, -0.5f, 0,1.0f, 1.0f);
	_vb->Unlock();

	DEVICE->CreateIndexBuffer
	(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0
	);

	WORD* indices = 0;

	_ib->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;


	_ib->Unlock();
}

DeferredQuad::~DeferredQuad()
{
}
