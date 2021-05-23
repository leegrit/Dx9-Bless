#include "StandardEngineFramework.h"
#include "MeshEffect.h"
#include "EffectData.h"
#include "TextureLoader.h"
#include "PathManager.h"
#include "MeshLoader.h"

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
	/*SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pDiffuseMap);
	SAFE_RELEASE(m_pAlphaMask);*/

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

	/* UV Move Test */
	//static D3DXVECTOR2 uvMove = D3DXVECTOR2(0, 0);
	//uvMove += D3DXVECTOR2(0.002f, 0);
	//// 1을 넘어가면 소수점만 남기고 뺀다.
	//D3DXVECTOR2 uvMoveRes = D3DXVECTOR2(uvMove.x - (int)uvMove.x, uvMove.y - (int)uvMove.y);

	float pass = 0;
	if (m_isWrap)
	{
		pass = 1;
	}

	pShader->SetValue("UVMoveFactor", &GetUVOffset(), sizeof(GetUVOffset()));

	if (m_pAlphaMask == nullptr)
		pShader->SetTechnique("MeshEffect");
	else
		pShader->SetTechnique("MeshEffectWithAlphaMask");
	pShader->Begin(0, 0);
	{
		pShader->BeginPass(pass);
		m_pMesh->DrawSubset(0);
		pShader->EndPass();
	}
	pShader->End();

}

void HyEngine::MeshEffect::DrawPrimitive(ID3DXEffect * pEffect)
{
	pEffect->SetBool("IsMasked", true);
	D3DXHANDLE maskHandle = pEffect->GetParameterByName(0, "MaskTex");
	/* Set world, view and projection */
	pEffect->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
	pEffect->SetValue("ViewMatrix", &CAMERA->GetViewMatrix(), sizeof(CAMERA->GetViewMatrix()));
	pEffect->SetValue("ProjMatrix", &CAMERA->GetProjectionMatrix(), sizeof(CAMERA->GetProjectionMatrix()));

	if (m_pAlphaMask)
	{
		pEffect->SetTexture(maskHandle, m_pAlphaMask);
	}
	else
	{
		pEffect->SetTexture(maskHandle, m_pDiffuseMap);
	}
	pEffect->SetValue("UVMoveFactor", &GetUVOffset(), sizeof(GetUVOffset()));
	pEffect->CommitChanges();
	m_pMesh->DrawSubset(0);
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

void HyEngine::MeshEffect::SetDiffuseTexture(std::wstring path)
{
	/* Diffuse Load */
	IDirect3DTexture9 * tempDiffuse = (IDirect3DTexture9 *)TextureLoader::GetTexture(path);
	if (tempDiffuse != nullptr)
		m_pDiffuseMap = tempDiffuse;
}

void HyEngine::MeshEffect::SetAlphaMaskTexture(std::wstring path)
{
	/* AlphaMask Load */
	IDirect3DTexture9 * tempAlphaMask = (IDirect3DTexture9 *)TextureLoader::GetTexture( path);
	if (tempAlphaMask != nullptr)
		m_pAlphaMask = tempAlphaMask;
}

void HyEngine::MeshEffect::SetNormalMapTexture(std::wstring path)
{
	/* Diffuse Load */
	IDirect3DTexture9 * tempDiffuse = (IDirect3DTexture9 *)TextureLoader::GetTexture(path);
	if (tempDiffuse != nullptr)
		m_pNormalMap = tempDiffuse;
}

void HyEngine::MeshEffect::SetEffectMesh(std::wstring path)
{
	/* MeshLoad */
	if (m_lastMeshPath != path)
	{
		m_lastMeshPath = path;

		HRESULT hr = 0;

		ID3DXBuffer* adjBuffer = nullptr;
		ID3DXBuffer* mtrlBuffer = nullptr;
		DWORD numMtrls = 0;

		/* Load Mesh */
		MeshLoader::TryGetMesh(path, &adjBuffer,
			&mtrlBuffer,
			&numMtrls,
			&m_pMesh);

		//hr = D3DXLoadMeshFromX
		//(
		//	( path).c_str(),
		//	D3DXMESH_MANAGED,
		//	DEVICE,
		//	&adjBuffer,
		//	&mtrlBuffer,
		//	0,
		//	&numMtrls,
		//	&m_pMesh
		//);
		//assert(SUCCEEDED(hr));

		///* Material skips here */
		//mtrlBuffer->Release();

		///* Optimize */
		//hr = m_pMesh->OptimizeInplace
		//(
		//	D3DXMESHOPT_ATTRSORT |
		//	D3DXMESHOPT_COMPACT |
		//	D3DXMESHOPT_VERTEXCACHE,
		//	(DWORD*)adjBuffer->GetBufferPointer(),
		//	0, 0, 0
		//);
		//adjBuffer->Release();

		//assert(SUCCEEDED(hr));

	}
}

void HyEngine::MeshEffect::SetWrapMode(bool isWrap)
{
	m_isWrap = isWrap;
}

ID3DXMesh * HyEngine::MeshEffect::GetMesh() const
{
	return m_pMesh;
}

IDirect3DTexture9 * HyEngine::MeshEffect::GetDiffuseTexture() const
{
	return m_pDiffuseMap;
}

IDirect3DTexture9 * HyEngine::MeshEffect::GetNormalTexture() const
{
	return m_pNormalMap;
}

IDirect3DTexture9 * HyEngine::MeshEffect::GetAlphaMaskTexture() const
{
	return m_pAlphaMask;
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
