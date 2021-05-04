#include "StandardEngineFramework.h"
#include "ProgressBar.h"
#include "TextureQuad.h"

HyEngine::ProgressBar::ProgressBar(Scene * pScene, std::wstring name, std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
	: UIElement(pScene, name)
{
	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);
	ENGINE->TryGetShader(L"ProgressBar", &m_pEffect);
	assert(m_pEffect);

	m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(imageFilePath);
	m_pTransform->SetPosition(position);
	m_pTransform->m_rotationEuler = rotation;
	m_pTransform->SetScale(scale);
}

HyEngine::ProgressBar::~ProgressBar()
{
}

void HyEngine::ProgressBar::Initialize()
{
	UIElement::Initialize();
}

void HyEngine::ProgressBar::Render()
{
	UIElement::Render();


	m_pEffect->SetMatrix("WorldMatrix", &m_pTransform->GetWorldMatrix());
	m_pEffect->SetMatrix("ViewMatrix", &CAMERA->GetIdentityViewMatrix());
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetOrthoMatrix());

	D3DXHANDLE diffuseHandler = m_pEffect->GetParameterByName(0, "AlbedoTex");
	m_pEffect->SetTexture(diffuseHandler, m_pTexture);

	m_pEffect->SetFloat("Amount", m_amount);

	m_pEffect->SetTechnique("ProgressBar");
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

void HyEngine::ProgressBar::Update()
{
	UIElement::Update();

}

void HyEngine::ProgressBar::SetAmount(float amount)
{
	m_amount = amount;
}

ProgressBar * HyEngine::ProgressBar::Create(Scene * pScene,  std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, std::wstring name)
{
	ProgressBar * ui = new ProgressBar(pScene, name, imageFilePath, position, rotation, scale);
	ui->Initialize();
	return ui;
}
