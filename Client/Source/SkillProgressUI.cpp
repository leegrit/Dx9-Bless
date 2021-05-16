#include "stdafx.h"
#include "SkillProgressUI.h"
#include "TextureQuad.h"

SkillProgressUI::SkillProgressUI(Scene * pScene, std::wstring name, std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
	: UIElement(pScene, name)
{
	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);
	ENGINE->TryGetShader(L"SkillProgressUI", &m_pEffect);
	assert(m_pEffect);

	m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(imageFilePath);
	m_pTransform->SetPosition(position);
	m_pTransform->m_rotationEuler = rotation;
	m_pTransform->SetScale(scale);
}

SkillProgressUI::~SkillProgressUI()
{
}

void SkillProgressUI::Initialize()
{
	UIElement::Initialize();
}

void SkillProgressUI::Render()
{
	UIElement::Render();


	m_pEffect->SetMatrix("WorldMatrix", &m_pTransform->GetWorldMatrix());
	m_pEffect->SetMatrix("ViewMatrix", &CAMERA->GetIdentityViewMatrix());
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetOrthoMatrix());

	D3DXHANDLE diffuseHandler = m_pEffect->GetParameterByName(0, "FillTex");
	m_pEffect->SetTexture(diffuseHandler, m_pTexture);

	m_pEffect->SetFloat("Amount", m_amount);

	m_pEffect->SetTechnique("SkillProgressUI");
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

void SkillProgressUI::Update()
{
	UIElement::Update();
}

void SkillProgressUI::SetAmount(float amount)
{
	m_amount = amount;
}

SkillProgressUI * SkillProgressUI::Create(Scene * pScene, std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, std::wstring name)
{
	SkillProgressUI * ui = new SkillProgressUI(pScene, name, imageFilePath, position, rotation, scale);
	ui->Initialize();
	return ui;
}
