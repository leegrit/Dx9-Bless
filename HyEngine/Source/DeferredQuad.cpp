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
		4 * sizeof(VTXSCREEN),
		D3DUSAGE_DYNAMIC,
		VTXSCREEN::FVF,
		D3DPOOL_DEFAULT,
		&_vb,
		0
	);
	VTXSCREEN* vertices;
	vertexSize = sizeof(VTXSCREEN);

	_vb->Lock(0, 0, (void**)&vertices, 0);
	/*vertices[0] = TextureVertex(-WinMaxWidth * 0.5f, -WinMaxHeight * 0.5f, 0, 0.0f, 1.0f);
	vertices[1] = TextureVertex(-WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0, 0.0f, 0.0f);
	vertices[2] = TextureVertex(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0, 1.0f, 0.0f);

	vertices[3] = TextureVertex(WinMaxWidth * 0.5f, -WinMaxHeight * 0.5f, 0, 1.0f, 1.0f);*/
	/*vertices[0] = TextureVertex(-0.5f, -0.5f, 0, 0.0f, 1.0f);
	vertices[1] = TextureVertex(-0.5f, 0.5f, 0, 0.0f, 0.0f);
	vertices[2] = TextureVertex(0.5f, 0.5f, 0, 1.0f, 0.0f);

	vertices[3] = TextureVertex(0.5f, -0.5f, 0, 1.0f, 1.0f);*/

	/*vertices[0] = TextureVertex(-1.f - (1/  WinMaxWidth), -1.f - (1 / WinMaxHeight), 0, 0.0f, 1.0f);
	vertices[1] = TextureVertex(-1.f - (1 / WinMaxWidth), 1.f - (1 / WinMaxHeight), 0, 0.0f, 0.0f);
	vertices[2] = TextureVertex(1.f - (1 / WinMaxWidth), 1.f - (1 / WinMaxHeight), 0, 1.0f, 0.0f);

	vertices[3] = TextureVertex(1.f - (1 / WinMaxWidth), -1.f - (1 / WinMaxHeight), 0, 1.0f, 1.0f);*/
	D3DVIEWPORT9		ViewPort;
	DEVICE->GetViewport(&ViewPort);

	vertices[0].position = D3DXVECTOR4(0.f - 0.5f, 0.f - 0.5f, 0.f, 1.f);
	vertices[0].uv = D3DXVECTOR2(0.f, 0.f);
	
	vertices[1].position = D3DXVECTOR4(ViewPort.Width - 0.5f, 0.f - 0.5f, 0.f, 1.f);
	vertices[1].uv = D3DXVECTOR2(1.f, 0.f);
	
	vertices[2].position = D3DXVECTOR4(ViewPort.Width - 0.5f, ViewPort.Height - 0.5f, 0.f, 1.f);
	vertices[2].uv = D3DXVECTOR2(1.f, 1.f);

	vertices[3].position = D3DXVECTOR4(0.f - 0.5f, ViewPort.Height - 0.5f, 0.f, 1.f);
	vertices[3].uv = D3DXVECTOR2(0.f, 1.f);

	//vertices[0].position = D3DXVECTOR4(-1.f , -1.f, 0, 1);// VTXSCREEN(-1.f - (1 / WinMaxWidth), -1.f - (1 / WinMaxHeight), 0, 0.0f, 1.0f);
	//vertices[0].uv = D3DXVECTOR2(0, 1);

	//vertices[1].position = D3DXVECTOR4(-1.f , 1.f , 0, 1);// VTXSCREEN(-1.f - (1 / WinMaxWidth), -1.f - (1 / WinMaxHeight), 0, 0.0f, 1.0f);
	//vertices[1].uv = D3DXVECTOR2(0, 0);
	//vertices[2].position = D3DXVECTOR4(1.f , 1.f , 0, 1);// VTXSCREEN(-1.f - (1 / WinMaxWidth), -1.f - (1 / WinMaxHeight), 0, 0.0f, 1.0f);
	//vertices[2].uv = D3DXVECTOR2(1, 0);
	//vertices[3].position = D3DXVECTOR4(1.f , -1.f , 0, 1);// VTXSCREEN(-1.f - (1 / WinMaxWidth), -1.f - (1 / WinMaxHeight), 0, 0.0f, 1.0f);
	//vertices[3].uv = D3DXVECTOR2(1, 1);

	/*vertices[1] = VTXSCREEN(-1.f - (1 / WinMaxWidth), 1.f - (1 / WinMaxHeight), 0, 0.0f, 0.0f);
	vertices[2] = VTXSCREEN(1.f - (1 / WinMaxWidth), 1.f - (1 / WinMaxHeight), 0, 1.0f, 0.0f);

	vertices[3] = VTXSCREEN(1.f - (1 / WinMaxWidth), -1.f - (1 / WinMaxHeight), 0, 1.0f, 1.0f);*/
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
