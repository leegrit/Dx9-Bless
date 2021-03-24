#include "StandardEngineFramework.h"
#include "Geometry.h"

using namespace HyEngine;

IDirect3DVertexBuffer9 * Geometry::GetVertexBuffer()
{
	return m_pVertexBuffer;
}

int Geometry::GetVertexSize()
{
	return m_vertexSize;
}

int Geometry::GetVertexCount()
{
	return m_vertexCount;
}

IDirect3DVertexDeclaration9 * HyEngine::Geometry::GetDeclare()
{
	return m_pDeclare;
}

DWORD Geometry::GetFVF()
{
	return m_vertexFVF;
}

IDirect3DIndexBuffer9 * Geometry::GetIndexBuffer()
{
	return m_pIndexBuffer;
}

int Geometry::GetPrimitiveCount()
{
	return m_primitiveCount;
}

//std::vector<Geometry*> Geometry::geometries;