#include "StandardEngineFramework.h"
#include "MeshEffect.h"
#include "EffectData.h"
#include "TextureLoader.h"
#include "PathManager.h"


HyEngine::MeshEffect::MeshEffect(Scene * scene, int editID)
	: Effect(scene, L"MeshEffect", editID)
{
}

HyEngine::MeshEffect::MeshEffect(Scene * scene)
	: Effect(scene, L"MeshEffect")
{

}

HyEngine::MeshEffect::~MeshEffect()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pDiffuseMap);
	SAFE_RELEASE(m_pAlphaMask);

}

void HyEngine::MeshEffect::OnEnable()
{
	Effect::OnEnable();
}

void HyEngine::MeshEffect::OnDisable()
{
	Effect::OnDisable();
}

void HyEngine::MeshEffect::Update()
{
	Effect::Update();


}

void HyEngine::MeshEffect::Render()
{
	Effect::Render();

	if (m_pMesh == nullptr) return;
	if (m_pDiffuseMap == nullptr) return;


	/* Get Shader */
	ID3DXEffect* pShader = nullptr;
	if (IS_EDITOR)
		EDIT_ENGINE->TryGetShader(L"MeshEffect", &pShader);
	else
		ENGINE->TryGetShader(L"MeshEffect", &pShader);
	assert(pShader);

	/* Get Selected Cam */
	Camera* pSelectedCamera = nullptr;
	pSelectedCamera = GetScene()->GetSelectedCamera();
	assert(pSelectedCamera);

	/* Set world, view and projection */
	pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
	pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
	pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));

	/* Set albedo */
	D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
	pShader->SetTexture(albedoHandle, m_pDiffuseMap);

	/* Set Alpha mask */
	D3DXHANDLE alphaHandle = pShader->GetParameterByName(0, "AlphaMaskTex");
	pShader->SetTexture(alphaHandle, m_pAlphaMask);

	pShader->SetFloat("Alpha", GetAlpha());

	if (m_pAlphaMask == nullptr)
		pShader->SetTechnique("MeshEffect");
	else
		pShader->SetTechnique("MeshEffectWithAlphaMask");
	pShader->Begin(0, 0);
	{
		pShader->BeginPass(0);
		m_pMesh->DrawSubset(0);
		pShader->EndPass();
	}
	pShader->End();

}

void HyEngine::MeshEffect::UpdatedData(EDataType dataType)
{
	Effect::UpdatedData(dataType);
	
	if (dataType == EDataType::EffectData)
	{
		assert(m_pEffectData);

		/* char to wstring */
		std::wstring meshPath = CString::CharToWstring(m_pEffectData->meshPath);
		std::wstring diffusePath = CString::CharToWstring(m_pEffectData->diffusePath);
		std::wstring alphaMaskPath = CString::CharToWstring(m_pEffectData->alphaMaskPath);

		/* Diffuse Load */
		IDirect3DTexture9 * tempDiffuse = (IDirect3DTexture9 *)TextureLoader::GetTexture(PATH->ResourcesPathW() + diffusePath);
		if (tempDiffuse != nullptr)
			m_pDiffuseMap = tempDiffuse;

		/* AlphaMask Load */
		IDirect3DTexture9 * tempAlphaMask = (IDirect3DTexture9 *)TextureLoader::GetTexture(PATH->ResourcesPathW() + alphaMaskPath);
		if (tempAlphaMask != nullptr)
			m_pAlphaMask = tempAlphaMask;

		/* MeshLoad */
		if (m_lastMeshPath != meshPath)
		{
			m_lastMeshPath = meshPath;

			HRESULT hr = 0;

			ID3DXBuffer* adjBuffer = nullptr;
			ID3DXBuffer* mtrlBuffer = nullptr;
			DWORD numMtrls = 0;

			/* Load Mesh */
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

			/* Material skips here */
			mtrlBuffer->Release();

			/* Optimize */
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
	}
}

void HyEngine::MeshEffect::Initialize()
{

}

MeshEffect * HyEngine::MeshEffect::Create(Scene * scene)
{
	MeshEffect* effect = new MeshEffect(scene);
	effect->Initialize();
	return effect;
}

MeshEffect * HyEngine::MeshEffect::Create(Scene * scene, int editID)
{
	MeshEffect* effect = new MeshEffect(scene, editID);
	effect->Initialize();
	return effect;
}
