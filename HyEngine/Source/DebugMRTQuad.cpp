#include "StandardEngineFramework.h"
#include "DebugMRTQuad.h"
#include "VertexTypes.h"
#include "IndexTypes.h"


HyEngine::DebugMRTQuad::DebugMRTQuad(float xPos, float yPos, float xSize, float ySize)
{

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
	vertices[0].position = D3DXVECTOR4(xPos - 0.5f, yPos - 0.5f, 0.f, 1.f);
	vertices[0].uv = D3DXVECTOR2(0.f, 0.f);

	vertices[1].position = D3DXVECTOR4(xPos - 0.5f + xSize, yPos - 0.5f, 0.f, 1.f);
	vertices[1].uv = D3DXVECTOR2(1.f, 0.f);

	vertices[2].position = D3DXVECTOR4(xPos + xSize - 0.5f, yPos + ySize - 0.5f, 0.f, 1.f);
	vertices[2].uv = D3DXVECTOR2(1.f, 1.f);

	vertices[3].position = D3DXVECTOR4(xPos - 0.5f, yPos + ySize - 0.5f, 0.f, 1.f);
	vertices[3].uv = D3DXVECTOR2(0.f, 1.f);

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

HyEngine::DebugMRTQuad::~DebugMRTQuad()
{
}
