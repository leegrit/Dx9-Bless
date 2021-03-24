#include "StandardEngineFramework.h"
#include "Mesh.h"
#include "ObjLoader.h"
#include "VertexTypes.h"
#include "IndexTypes.h"
using namespace HyEngine;

HyEngine::Mesh::Mesh()
{
	
}

HyEngine::Mesh::~Mesh()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void HyEngine::Mesh::Load(std::string filePath)
{
	// fixed pipeline 
	/*
	OBJL::Loader loader;
	bool bSucceeded = loader.LoadFile(filePath);
	assert(bSucceeded);

	m_primCount = loader.LoadedIndices.size() / 3;
	m_vertexCount = loader.LoadedVertices.size();
	m_vertexSize = sizeof(ModelVertex);
	m_vertexFVF = ModelVertex::FVF;

	DEVICE->CreateVertexBuffer
	(
		loader.LoadedVertices.size() * sizeof(ModelVertex),
		D3DUSAGE_DYNAMIC,
		ModelVertex::FVF,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		0
	);

	ModelVertex* vertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	for (UINT i = 0; i < loader.LoadedVertices.size(); i++)
	{
		vertices[i].x = loader.LoadedVertices[i].Position.X;
		vertices[i].y = loader.LoadedVertices[i].Position.Y;
		vertices[i].z = loader.LoadedVertices[i].Position.Z;

		vertices[i].nx = loader.LoadedVertices[i].Normal.X;
		vertices[i].ny = loader.LoadedVertices[i].Normal.Y;
		vertices[i].nz = loader.LoadedVertices[i].Normal.Z;

		vertices[i].u = loader.LoadedVertices[i].TextureCoordinate.X;
		vertices[i].v = loader.LoadedVertices[i].TextureCoordinate.Y;
	}

	m_pVertexBuffer->Unlock();

	DEVICE->CreateIndexBuffer
	(
		loader.LoadedIndices.size() * sizeof(unsigned int),
		D3DUSAGE_DYNAMIC,
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		nullptr
	);

	unsigned int * indices = nullptr;
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	for (UINT i = 0; i < loader.LoadedIndices.size(); i++)
	{
		indices[i] = loader.LoadedIndices[i];
	}
	m_pIndexBuffer->Unlock();*/

	// for shader
	OBJL::Loader loader;
	bool bSucceeded = loader.LoadFile(filePath);
	assert(bSucceeded);

	m_primCount = loader.LoadedIndices.size() / 3;
	m_vertexCount = loader.LoadedVertices.size();
	m_vertexSize = sizeof(BumpModelVertex);
	D3DVERTEXELEMENT9 element[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 0, 20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
		{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
		D3DDECL_END()
	};
	DEVICE->CreateVertexDeclaration(element, &m_pDeclare);

	DEVICE->CreateVertexBuffer
	(
		m_vertexCount * m_vertexSize,
		D3DUSAGE_DYNAMIC,
		NULL,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		0
	);




	BumpModelVertex * vertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	m_radius = 0;
	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].x = loader.LoadedVertices[i].Position.X;
		vertices[i].y = loader.LoadedVertices[i].Position.Y;
		vertices[i].z = loader.LoadedVertices[i].Position.Z;

		float distance = D3DXVec3Length(&(Vector3::Zero - D3DXVECTOR3(vertices[i].x, vertices[i].y, vertices[i].z)));
		if (distance >= m_radius)
			m_radius = distance;


		vertices[i].u = loader.LoadedVertices[i].TextureCoordinate.X;
		vertices[i].v = 1 - loader.LoadedVertices[i].TextureCoordinate.Y;

		vertices[i].normalX = loader.LoadedVertices[i].Normal.X;
		vertices[i].normalY = loader.LoadedVertices[i].Normal.Y;
		vertices[i].normalZ = loader.LoadedVertices[i].Normal.Z;



		// for calculate binormal and tangent
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 binormal;
		D3DXVECTOR3 c1;
		D3DXVec3Cross(&c1, &D3DXVECTOR3(vertices[i].normalX, vertices[i].normalY, vertices[i].normalZ), &D3DXVECTOR3(0, 0, 1));
		D3DXVECTOR3 c2;
		D3DXVec3Cross(&c2, &D3DXVECTOR3(vertices[i].normalX, vertices[i].normalY, vertices[i].normalZ), &D3DXVECTOR3(0, 1, 0));
		if (DxMath::Length(c1) > DxMath::Length(c2))
			tangent = c1;
		else
			tangent = c2;
		D3DXVec3Normalize(&tangent, &tangent);
		D3DXVECTOR3 temp;
		D3DXVec3Cross(&temp, &D3DXVECTOR3(vertices[i].normalX, vertices[i].normalY, vertices[i].normalZ), &tangent);
		D3DXVec3Normalize(&binormal, &temp);

		vertices[i].binormalX = binormal.x;
		vertices[i].binormalY = binormal.y;
		vertices[i].binormalZ = binormal.z;

		vertices[i].tangentX = tangent.x;
		vertices[i].tangentY = tangent.y;
		vertices[i].tangentZ = tangent.z;

	}
	m_pVertexBuffer->Unlock();


	DEVICE->CreateIndexBuffer
	(
		loader.LoadedIndices.size() * sizeof(unsigned int),
		D3DUSAGE_DYNAMIC,
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		nullptr
	);

	unsigned int * indices = nullptr;
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	for (UINT i = 0; i < loader.LoadedIndices.size(); i++)
	{
		indices[i] = loader.LoadedIndices[i];
	}
	m_pIndexBuffer->Unlock();
}


IDirect3DVertexBuffer9 * HyEngine::Mesh::GetVertexBuffer()
{
	return m_pVertexBuffer;
}

int HyEngine::Mesh::GetVertexSize()
{
	return m_vertexSize;
}

int HyEngine::Mesh::GetVertexCount()
{
	return m_vertexCount;
}

IDirect3DIndexBuffer9 * HyEngine::Mesh::GetIndexBuffer()
{
	return m_pIndexBuffer;
}

int HyEngine::Mesh::GetPrimitiveCount()
{
	return m_primCount;
}

IDirect3DVertexDeclaration9 * HyEngine::Mesh::GetDeclare()
{
	return m_pDeclare;
}

float HyEngine::Mesh::GetRadius()
{
	return m_radius;
}

