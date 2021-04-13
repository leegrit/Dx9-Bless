#include "StandardEngineFramework.h"
#include "TextureEffect.h"
#include "EffectData.h"
#include "TextureQuad.h"
#include "PathManager.h"


HyEngine::TextureEffect::TextureEffect(Scene * scene, int editID)
	: Effect(scene, L"TextureEffect", editID)
{
}

HyEngine::TextureEffect::TextureEffect(Scene * scene)
	: Effect(scene, L"TextureEffect")
{

}

HyEngine::TextureEffect::~TextureEffect()
{
	SAFE_DELETE(m_pTextureQuad);
	SAFE_RELEASE(m_pDiffuseMap);
	SAFE_RELEASE(m_pAlphaMask);
}

void HyEngine::TextureEffect::OnEnable()
{
	Effect::OnEnable();
}

void HyEngine::TextureEffect::OnDisable()
{
	Effect::OnDisable();
}

void HyEngine::TextureEffect::Update()
{
	Effect::Update();
}

void HyEngine::TextureEffect::Render()
{
	Effect::Render();

	/* Get Shader */
	ID3DXEffect* pShader = nullptr;
	if (IS_EDITOR)
		EDIT_ENGINE->TryGetShader(L"TextureEffect", &pShader);
	else
		ENGINE->TryGetShader(L"TextureEffect", &pShader);
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

	pShader->SetTechnique("TextureEffect");
	pShader->Begin(0, 0);
	{
		pShader->BeginPass(0);

		DEVICE->SetStreamSource(0, m_pTextureQuad->GetVertexBuffer(), 0, m_pTextureQuad->GetVertexSize());
		DEVICE->SetVertexDeclaration(m_pTextureQuad->GetDeclare());
		DEVICE->SetIndices(m_pTextureQuad->GetIndexBuffer());
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pTextureQuad->GetVertexCount(), 0, m_pTextureQuad->GetPrimitiveCount());

		pShader->EndPass();
	}
	pShader->End();
}

void HyEngine::TextureEffect::UpdatedData(EDataType dataType)
{
	Effect::UpdatedData(dataType);

	if (dataType == EDataType::EffectData)
	{
		assert(m_pEffectData);

		/* Char to wstring */
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

	}
}

void HyEngine::TextureEffect::Initialize()
{
	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);
	assert(m_pTextureQuad);
}

TextureEffect * HyEngine::TextureEffect::Create(Scene * scene)
{
	TextureEffect* effect = new TextureEffect(scene);
	effect->Initialize();
	return effect;
}

TextureEffect * HyEngine::TextureEffect::Create(Scene * scene, int editID)
{
	TextureEffect * effect = new TextureEffect(scene, editID);
	effect->Initialize();
	return effect;
}
