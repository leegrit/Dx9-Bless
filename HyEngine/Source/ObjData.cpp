//#include "StandardEngineFramework.h"
//#include "ObjData.h"
//#include "ObjLoader.h"
//using namespace HyEngine;
//
//
//void HyEngine::ObjData::Load(std::string filePath)
//{
//	
//	m_pLoader = new OBJL::Loader();
//	bool bSucceeded = m_pLoader->LoadFile(filePath);
//	assert(bSucceeded);
//
//	m_primCount = m_pLoader->LoadedIndices.size() / 3;
//	m_vertexCount = m_pLoader->LoadedVertices.size();
//	m_indexCount = m_pLoader->LoadedIndices.size();
//
//	m_bLoaded = true;
//}
//
//D3DXVECTOR3 HyEngine::ObjData::GetPosition(int index) const
//{
//	assert(m_bLoaded);
//	D3DXVECTOR3 result = D3DXVECTOR3(m_pLoader->LoadedVertices[index].Position.X,
//		m_pLoader->LoadedVertices[index].Position.Y,
//		m_pLoader->LoadedVertices[index].Position.Z);
//	return result;
//}
//
//D3DXVECTOR3 HyEngine::ObjData::GetTexcoord(int index) const
//{
//	assert(m_bLoaded);
//	D3DXVECTOR2 result = D3DXVECTOR2(m_pLoader->LoadedVertices[index].TextureCoordinate.X,
//		m_pLoader->LoadedVertices[index].TextureCoordinate.Y);
//	return result;
//}
//
//D3DXVECTOR3 HyEngine::ObjData::GetNormal(int index) const
//{
//	assert(m_bLoaded);
//	D3DXVECTOR3 result = D3DXVECTOR3(m_pLoader->LoadedVertices[index].Normal.X,
//		m_pLoader->LoadedVertices[index].Normal.Y,
//		m_pLoader->LoadedVertices[index].Normal.Z);
//	return result;
//}
//
//UINT HyEngine::ObjData::GetIndices(int index) const
//{
//	assert(m_bLoaded);
//	return m_pLoader->LoadedIndices[index];
//}
