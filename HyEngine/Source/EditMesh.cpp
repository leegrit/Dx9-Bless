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

	if (m_pDxMesh)
	{
		for (int i = 0; i < m_mtrls.size(); i++)
		{
			DEVICE->SetMaterial(&m_mtrls[i]);
			DEVICE->SetTexture(0, m_textures[i]);
			m_pDxMesh->DrawSubset(i);
		}
	}
	else if (m_pMesh)
	{
		assert(m_pMesh);
		DEVICE->SetStreamSource(0, m_pMesh->GetVertexBuffer(), 0, m_pMesh->GetVertexSize());
		DEVICE->SetVertexDeclaration(m_pMesh->GetDeclare());
		DEVICE->SetIndices(m_pMesh->GetIndexBuffer());

		assert(m_pBaseTex);
		DEVICE->SetTexture(0, m_pBaseTex.get());
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pMesh->GetVertexCount(), 0, m_pMesh->GetPrimitiveCount());
	}
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
			HRESULT hr = 0;

			ID3DXBuffer * adjBuffer = nullptr;
			ID3DXBuffer* mtrlBuffer = nullptr;
			DWORD numMtrls = 0;

			hr = D3DXLoadMeshFromX
			(
				(ResourcePath::MeshFilePath + meshPath).c_str(),
				D3DXMESH_MANAGED,
				DEVICE,
				&adjBuffer,
				&mtrlBuffer,
				0,
				&numMtrls,
				&m_pDxMesh
			);
			assert(SUCCEEDED(hr));

			if (mtrlBuffer != 0 && numMtrls != 0)
			{
				D3DXMATERIAL * mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

				for (int i = 0; i < numMtrls; i++)
				{
					// the MatD3D property doesn't have an ambient value set
					// when its loaded, so set it now:
					mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

					// save the ith material
					m_mtrls.push_back(mtrls[i].MatD3D);

					// check if the ith material has an associative texture
					if (mtrls[i].pTextureFilename != 0)
					{
						IDirect3DTexture9* tex = nullptr;
						std::wstring fileName = CString::CharToWstring(mtrls[i].pTextureFilename);
						D3DXCreateTextureFromFile
						(
							DEVICE,
							(ResourcePath::TextureFilePath + fileName).c_str(),
							&tex
						);

						// save the loaded texture
						m_textures.push_back(tex);
					}
					else
					{
						// no texture for the ith subset
						m_textures.push_back(0);
					}
				}
			}
			mtrlBuffer->Release();

			hr = m_pDxMesh->OptimizeInplace
			(
				D3DXMESHOPT_ATTRSORT |
				D3DXMESHOPT_COMPACT |
				D3DXMESHOPT_VERTEXCACHE,
				(DWORD*)adjBuffer->GetBufferPointer(),
				0, 0, 0
			);

			adjBuffer->Release();

			assert(SUCCEEDED(hr));

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
