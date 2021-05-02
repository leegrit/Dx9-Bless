#include "StandardEngineFramework.h"
#include "Texture.h"
#include "TextureQuad.h"
#include "TextureLoader.h"

HyEngine::Texture::Texture(Scene * pScene, GameObject * pParent, std::wstring name)
	: GameObject(ERenderType::RenderAlpha, pScene, pParent, name)
{
	
}

void HyEngine::Texture::Render()
{
	GameObject::Render();

	Camera* pSelectedCamera = nullptr;
	pSelectedCamera = GetScene()->GetSelectedCamera();
	assert(pSelectedCamera);

	m_pEffect->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
	m_pEffect->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(D3DXMATRIX));
	m_pEffect->SetMatrix("ProjMatrix", &pSelectedCamera->GetProjectionMatrix());

	/* Set Diffuse */
	D3DXHANDLE diffuseHandle = m_pEffect->GetParameterByName(0, "DiffuseTex");
	m_pEffect->SetTexture(diffuseHandle, m_pDiffuse);

	/* Set Alpha */
	D3DXHANDLE alphaMaskHandle = m_pEffect->GetParameterByName(0, "AlphaMaskTex");
	m_pEffect->SetTexture(alphaMaskHandle, m_pAlphaMask);

	m_pEffect->SetTechnique("Texture");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);

		DEVICE->SetStreamSource(0, m_pTextureQuad->GetVertexBuffer(), 0, m_pTextureQuad->GetVertexSize());
		DEVICE->SetVertexDeclaration(m_pTextureQuad->GetDeclare());
		DEVICE->SetIndices(m_pTextureQuad->GetIndexBuffer());
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pTextureQuad->GetVertexCount(), 0, m_pTextureQuad->GetPrimitiveCount());

		m_pEffect->EndPass();
	}
	m_pEffect->End();
}

void HyEngine::Texture::Update()
{
	GameObject::Update();
}

void HyEngine::Texture::OnEnable()
{
	GameObject::OnEnable();
}

void HyEngine::Texture::OnDisable()
{
	GameObject::OnDisable();
}

void HyEngine::Texture::Initialize()
{
	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);

	ENGINE->TryGetShader(L"Texture", &m_pEffect);
	assert(m_pEffect);
}

void HyEngine::Texture::SetDiffuseTexture(std::wstring diffusePath)
{
	m_pDiffuse = (IDirect3DTexture9*)TextureLoader::GetTexture(diffusePath);
	
}



void HyEngine::Texture::SetAlphaMaskTexture(std::wstring alphaMaskPath)
{
	m_pAlphaMask = (IDirect3DTexture9*)TextureLoader::GetTexture(alphaMaskPath);
}
