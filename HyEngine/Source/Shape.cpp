#include "StandardEngineFramework.h"
#include "Shape.h"

using namespace HyEngine;

IDirect3DVertexBuffer9 * Shape::GetVertexBuffer()
{
	return m_pVertexBuffer;
}

int Shape::GetVertexSize()
{
	return m_vertexSize;
}

int Shape::GetVertexCount()
{
	return m_vertexCount;
}

DWORD Shape::GetFVF()
{
	return m_vertexFVF;
}

IDirect3DIndexBuffer9 * Shape::GetIndexBuffer()
{
	return m_pIndexBuffer;
}

int Shape::GetPrimitiveCount()
{
	return m_primitiveCount;
}

std::vector<Shape*> Shape::geometries;