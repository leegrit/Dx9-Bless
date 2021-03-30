#include "StandardEngineFramework.h"
#include "EditMesh.h"
#include "EditData.h"
#include "GameObjectData.h"
#include "MeshData.h"
using namespace HyEngine;

EditMesh::EditMesh(Scene * scene, GameObject * parent, int editID)
	: EditObject(ERenderType::RenderMesh, scene, parent, editID)
{
	m_pMesh = MeshLoader::GetMesh("../../../_Resources/System/Cube.obj");
	//assert(m_pMesh);
	m_pBaseTex = static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(L"../../../_Resources/System/Checker.png"));


}

EditMesh::~EditMesh()
{
	Object::Destroy(m_pCollider);
	m_pMesh.reset();
	m_pBaseTex.reset();
}

void EditMesh::Initialize()
{
	m_pCollider = SphereCollider::Create(EColliderType::Multipurpose, this, 1, Layer::Player, [](Collider*) {});
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

ID3DXMesh * HyEngine::EditMesh::GetDxMesh() const
{
	return m_pDxMesh;
}

bool HyEngine::EditMesh::CalcBounds(D3DXVECTOR3 * center, float * radius)
{
	if (m_pDxMesh == nullptr)
		return false;

	BYTE* ptr = nullptr;

	// get the face count
	DWORD numVertices = m_pDxMesh->GetNumVertices();

	// get the fvf flags
	DWORD fvfSize = D3DXGetFVFVertexSize(m_pDxMesh->GetFVF());

	// lock the vertex buffer
	m_pDxMesh->LockVertexBuffer(0, (void**)&ptr);

	HRESULT hr;
	hr = D3DXComputeBoundingSphere((D3DXVECTOR3*)ptr,
		numVertices,
		fvfSize,
		center, radius);
	assert(SUCCEEDED(hr));

	m_pDxMesh->UnlockVertexBuffer();

	return true;

}

void HyEngine::EditMesh::UpdatedData(EDataType dataType)
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
			if (m_lastLoadedMeshPath != meshPath)
			{
				m_lastLoadedMeshPath = meshPath;
				HRESULT hr = 0;

				ID3DXBuffer * adjBuffer = nullptr;
				ID3DXBuffer* mtrlBuffer = nullptr;
				DWORD numMtrls = 0;
				

				hr = D3DXLoadMeshFromX
				(
					(ResourcePath::ResourcesPath + meshPath).c_str(),
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

					std::wstring dirPath = HyEngine::Path::GetDirectoryName(ResourcePath::ResourcesPath + meshPath);
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
								(dirPath + fileName).c_str(),
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


				// Collider 크기 변경

				D3DXVECTOR3 center;
				float radius;
				CalcBounds(&center, &radius);
				assert(m_pCollider);
				SphereCollider* sphereCol = dynamic_cast<SphereCollider*>(m_pCollider);
				assert(sphereCol);
				sphereCol->SetRadius(radius);
				D3DXVECTOR3 originPos = m_pTransform->m_position;
				D3DXVECTOR3 offsetPos = center - originPos;
				sphereCol->SetOffset(offsetPos);
			}
		}

		// texture file
		if ((std::wcscmp(diffuseTextureExt.c_str(), L"png") == 0) || (std::wcscmp(diffuseTextureExt.c_str(), L"tga") == 0))
		{
			m_pBaseTex = static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(ResourcePath::ResourcesPath + diffuseTexturePath));
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
