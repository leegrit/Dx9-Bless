#include "StandardEngineFramework.h"
#include "EditMesh.h"
#include "EditData.h"
#include "GameObjectData.h"
#include "MeshData.h"
using namespace Editor;

EditMesh::EditMesh(Scene * scene, GameObject * parent, int editID)
	: EditObject(ERenderType::RenderMesh, scene, parent, editID)
{
	m_pMesh = MeshLoader::GetMesh("../../../_Resources/Mesh/Cube.obj");
	//assert(m_pMesh);
	m_pBaseTex = static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(L"../../../_Resources/Texture/Checker.png"));
}

EditMesh::~EditMesh()
{
	m_pMesh.reset();
	m_pBaseTex.reset();
}

void EditMesh::Initialize()
{

}

void EditMesh::Render()
{
	GameObject::Render();
	assert(m_pMesh);
	DEVICE->SetStreamSource(0, m_pMesh->GetVertexBuffer(), 0, m_pMesh->GetVertexSize());
	DEVICE->SetVertexDeclaration(m_pMesh->GetDeclare());
	DEVICE->SetIndices(m_pMesh->GetIndexBuffer());

	assert(m_pBaseTex);
	DEVICE->SetTexture(0, m_pBaseTex.get());

	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pMesh->GetVertexCount(), 0, m_pMesh->GetPrimitiveCount());
}

void Editor::EditMesh::UpdatedData(EDataType dataType)
{
	switch (dataType)
	{
	case EDataType::MeshData:
		assert(m_pMeshData);
		MeshData* data = m_pMeshData;
		assert(data);
		std::wstring  meshPath = CString::CharToWstring(data->meshFilePath);
		std::wstring meshPathExt = HyEngine::Path::GetExtension(meshPath);

		std::wstring diffuseTexturePath = CString::CharToWstring(data->diffuseTexturePath);
		std::wstring diffuseTextureExt = HyEngine::Path::GetExtension(diffuseTexturePath);
		// mesh file
		if (std::wcscmp(meshPathExt.c_str(), L"obj") == 0) // 두 문자열이 동일할 경우
		{
			// obj format인 경우
			m_pMesh = MeshLoader::GetMesh(CString::ToString(ResourcePath::MeshFilePath + meshPath));
		}
		// xfile format인 경우
		else if (std::wcscmp(meshPathExt.c_str(), L"X") == 0 || std::wcscmp(meshPathExt.c_str(), L"x") == 0)
		{

		}

		// texture file
		if ((std::wcscmp(diffuseTextureExt.c_str(), L"png") == 0) || (std::wcscmp(diffuseTextureExt.c_str(), L"tga") == 0))
		{
			m_pBaseTex = static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(ResourcePath::TextureFilePath + diffuseTexturePath));
		}
		break;
	}
}

//void HyEngine::EditMesh::SetMesh(const std::wstring & path)
//{
//	if (m_pMesh)
//		m_pMesh.reset();
//	m_pMesh = MeshLoader::GetMesh(CString::ToString(path));
//}
//
//void HyEngine::EditMesh::SetDiffuse(const std::wstring & path)
//{
//	if (m_pBaseTex)
//		m_pBaseTex.reset();
//	m_pBaseTex = static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(path));
//}
//
//void HyEngine::EditMesh::SetBumb(const std::wstring & path)
//{
//}
//
//void HyEngine::EditMesh::SetEmission(const std::wstring & path)
//{
//}
