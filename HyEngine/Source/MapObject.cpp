#include "StandardEngineFramework.h"
#include "MapObject.h"
#include "HierarchyData.h"
#include "GameObjectData.h"
#include "MeshData.h"
#include "PathManager.h"
HyEngine::MapObject::MapObject(Scene * scene, GameObject * parent, std::wstring name)
	: GameObject(ERenderType::RenderOpaque, scene, parent, name)
{

}

HyEngine::MapObject::~MapObject()
{
	SAFE_RELEASE(m_pMesh);
	for (auto& texture : m_textures)
		SAFE_RELEASE(texture);
}

void HyEngine::MapObject::Initialize(shared_ptr<HierarchyData> data)
{
	InsertGameData(data->gameObjectData);
	InsertMeshData(data->meshData);

	SetRenderEffectOption(RenderEffectOption::RimLight);
	SetRimWidth(0.6f);
}

void HyEngine::MapObject::Render()
{
	GameObject::Render();
	// 지금 임시로 FixedPipeline 사용, 이후 바꿔야한다.

	/* Get Shader */
	ID3DXEffect* pShader = nullptr;
	ENGINE->TryGetShader(L"GBuffer", &pShader);
	assert(pShader);

	/* Get Selected Cam */
	Camera* pSelectedCamera = nullptr;
	pSelectedCamera = GetScene()->GetSelectedCamera();
	assert(pSelectedCamera);

	for (int i = 0; i < m_mtrls.size(); i++)
	{
		/* Set world, view and projection */
		pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
		pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
		pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));

		/* Set world position */
		pShader->SetValue("WorldPosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));

		/* Set albedo */
		D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
		pShader->SetTexture(albedoHandle, m_textures[i]);

		pShader->SetTechnique("GBuffer");
		pShader->Begin(0, 0);
		{
			pShader->BeginPass(0);
			m_pMesh->DrawSubset(i);
			pShader->EndPass();
		}
		pShader->End();

	}
}

void HyEngine::MapObject::UpdatedData(EDataType dataType)
{
	if (dataType != EDataType::MeshData)return;
	HRESULT hr = 0;


	std::wstring meshPath = CString::CharToWstring(m_pMeshData->meshFilePath);


	ID3DXBuffer * adjBuffer = nullptr;
	ID3DXBuffer* mtrlBuffer = nullptr;
	DWORD numMtrls = 0;


	hr = D3DXLoadMeshFromX
	(
		(PATH->ResourcesPathW() + meshPath).c_str(),
		D3DXMESH_MANAGED,
		DEVICE,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&m_pMesh
	);
	assert(SUCCEEDED(hr));

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL * mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		std::wstring dirPath = HyEngine::Path::GetDirectoryName(PATH->ResourcesPathW() + meshPath);
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

	hr = m_pMesh->OptimizeInplace
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
