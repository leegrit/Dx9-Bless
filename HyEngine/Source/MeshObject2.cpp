//#include "StandardEngineFramework.h"
//#include "MeshObject.h"
//#include "Mesh.h"
//#include "Geometry.h"
//#include "TextureLoader.h"
//#include "MeshLoader.h"
//#include "CString.h"
//
//using namespace HyEngine;
//
//MeshObject::MeshObject(class Scene* scene,
//	GameObject* parent,
//	ERenderType renderType,
//	const std::wstring& meshFilePath,
//	const std::wstring& textureFilePath,
//	const std::wstring& tag)
//	: GameObject(renderType, scene, parent, tag)
//{
//	m_pTexture = TextureLoader::GetTexture(textureFilePath);
//	m_pMesh = MeshLoader::GetMesh(CString::ToString(meshFilePath));
//	//m_pMesh = new Mesh();
//	//m_pMesh->Load(CString::ToString(meshFilePath));
//}
//
//
//MeshObject::~MeshObject()
//{
//	//SAFE_RELEASE(m_pTexture);
//	//SAFE_DELETE(m_pMesh);
//}
//
//void HyEngine::MeshObject::Initialize()
//{
//
//}
//
//void HyEngine::MeshObject::Render()
//{
//	GameObject::Render();
//	DEVICE->SetTexture(0, m_pTexture);
//	DEVICE->SetStreamSource(0, m_pMesh->GetVertexBuffer(), 0, m_pMesh->GetVertexSize());
//	//DEVICE->SetFVF(m_pMesh->GetFVF());
//	DEVICE->SetIndices(m_pMesh->GetIndexBuffer());
//}
