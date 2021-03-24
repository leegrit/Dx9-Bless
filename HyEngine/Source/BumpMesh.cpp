//#include "StandardEngineFramework.h"
//#include "BumpMesh.h"
//#include "ObjLoader.h"
//#include "VertexTypes.h"
//#include "IndexTypes.h"
//using namespace HyEngine;
//
//HyEngine::BumpMesh::BumpMesh()
//	//:IMesh()
//{
//}
//
//HyEngine::BumpMesh::~BumpMesh()
//{
//	
//}
//
//void HyEngine::BumpMesh::Load(std::string filePath)
//{
//	OBJL::Loader loader;
//	bool bSucceeded = loader.LoadFile(filePath);
//	assert(bSucceeded);
//
//	m_primCount = loader.LoadedIndices.size() / 3;
//	m_vertexCount = loader.LoadedVertices.size();
//	m_vertexSize = sizeof(BumpModelVertex);
//	
//	D3DVERTEXELEMENT9 element[]=
//	{
//		{0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
//		{0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
//		{0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
//		{0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
//		{0, 48, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
//		D3DDECL_END()
//	};
//	DEVICE->CreateVertexDeclaration(element, &m_pDeclare);
//
//	DEVICE->CreateVertexBuffer
//	(
//		m_vertexCount * m_vertexSize,
//		D3DUSAGE_DYNAMIC,
//		NULL,
//		D3DPOOL_DEFAULT,
//		&m_pVertexBuffer,
//		0
//	);
//
//
//
//
//	BumpModelVertex * vertices;
//	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);
//
//	for (UINT i = 0; i < m_vertexCount; i++)
//	{
//		vertices[i].x = loader.LoadedVertices[i].Position.X;
//		vertices[i].y = loader.LoadedVertices[i].Position.Y;
//		vertices[i].z = loader.LoadedVertices[i].Position.Z;
//
//		vertices[i].u = loader.LoadedVertices[i].TextureCoordinate.X;
//		vertices[i].v = loader.LoadedVertices[i].TextureCoordinate.Y;
//
//		vertices[i].normalX = loader.LoadedVertices[i].Normal.X;
//		vertices[i].normalY = loader.LoadedVertices[i].Normal.Y;
//		vertices[i].normalZ = loader.LoadedVertices[i].Normal.Z;
//
//		
//
//		// for calculate binormal and tangent
//		D3DXVECTOR3 tangent;
//		D3DXVECTOR3 binormal;
//		D3DXVECTOR3 c1;
//		D3DXVec3Cross(&c1, &D3DXVECTOR3(vertices[i].normalX, vertices[i].normalY, vertices[i].normalZ),&D3DXVECTOR3(0, 0, 1));
//		D3DXVECTOR3 c2;
//		D3DXVec3Cross(&c2, &D3DXVECTOR3(vertices[i].normalX, vertices[i].normalY, vertices[i].normalZ), &D3DXVECTOR3(0, 1, 0));
//		if (DxMath::Length(c1) > DxMath::Length(c2))
//			tangent = c1;
//		else
//			tangent = c2;
//		D3DXVec3Normalize(&tangent, &tangent);
//		D3DXVECTOR3 temp;
//		D3DXVec3Cross(&temp, &D3DXVECTOR3(vertices[i].normalX, vertices[i].normalY, vertices[i].normalZ), &tangent);
//		D3DXVec3Normalize(&binormal, &temp);
//
//		vertices[i].binormalX = binormal.x;
//		vertices[i].binormalY = binormal.y;
//		vertices[i].binormalZ = binormal.z;
//
//		vertices[i].tangentX = tangent.x;
//		vertices[i].tangentY = tangent.y;
//		vertices[i].tangentZ = tangent.z;
//
//	}
//	m_pVertexBuffer->Unlock();
//
//
//	DEVICE->CreateIndexBuffer
//	(
//		loader.LoadedIndices.size() * sizeof(unsigned int),
//		D3DUSAGE_DYNAMIC,
//		D3DFMT_INDEX32,
//		D3DPOOL_DEFAULT,
//		&m_pIndexBuffer,
//		nullptr
//	);
//
//	unsigned int * indices = nullptr;
//	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);
//
//	for (UINT i = 0; i < loader.LoadedIndices.size(); i++)
//	{
//		indices[i] = loader.LoadedIndices[i];
//	}
//	m_pIndexBuffer->Unlock();
//}
//
//IDirect3DVertexBuffer9 * HyEngine::BumpMesh::GetVertexBuffer()
//{
//	return m_pVertexBuffer;
//}
//
//int HyEngine::BumpMesh::GetVertexSize()
//{
//	return m_vertexSize;
//}
//
//int HyEngine::BumpMesh::GetVertexCount()
//{
//	return m_vertexCount;
//}
//
//DWORD HyEngine::BumpMesh::GetFVF()
//{
//	return m_vertexFVF;
//}
//
//IDirect3DIndexBuffer9 * HyEngine::BumpMesh::GetIndexBuffer()
//{
//	return m_pIndexBuffer;
//}
//
//int HyEngine::BumpMesh::GetPrimitiveCount()
//{
//	return m_primCount;
//}
