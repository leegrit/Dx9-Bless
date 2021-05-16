#include "stdafx.h"
#include "EnemyName.h"
#include "TextureQuad.h"
#include "TextureLoader.h"


EnemyName::EnemyName(Scene * pScene, std::wstring name, std::wstring nameTexturePath, GameObject * pOwner, D3DXVECTOR3 offset)
	: Billboard(pScene, nullptr, name, EBillboardType::Y)
{
	m_pFontTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(nameTexturePath);
	assert(m_pFontTexture);
	m_pOwner = pOwner;
	m_offset = offset;
	m_color = D3DXCOLOR(0, 0, 0, 0);
	m_colorIntensity = 0;

	m_pTransform->SetScale(5, 2, 1);
}

EnemyName::~EnemyName()
{
}

void EnemyName::Initialize()
{
	Billboard::Initialize();
	ENGINE->TryGetShader(L"FontTexture", &m_pEffect);
	assert(m_pEffect);
}

void EnemyName::Render()
{
	m_pEffect->SetMatrix("WorldMatrix", &GetBillboardMatrix());
	m_pEffect->SetMatrix("ViewMatrix", &CAMERA->GetViewMatrix());
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetProjectionMatrix());
	
	D3DXHANDLE fontHandler = m_pEffect->GetParameterByName(0, "FontTex");
	m_pEffect->SetTexture(fontHandler, m_pFontTexture);

	m_pEffect->SetValue("Color", &m_color, sizeof(m_color));
	m_pEffect->SetValue("ColorIntensity", &m_colorIntensity, sizeof(m_colorIntensity));

	m_pEffect->SetTechnique("FontTexture");
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

void EnemyName::Update()
{
	Billboard::Update();

	m_pTransform->m_position = m_pOwner->m_pTransform->CalcOffset(m_offset);
}

void EnemyName::SetColor(D3DXCOLOR color, float intensity)
{
	m_color = color;
}

void EnemyName::SetOffset(D3DXVECTOR3 offset)
{
	m_offset = offset;
}

EnemyName * EnemyName::Create(Scene * pScene, std::wstring name, std::wstring nameTexturePath, GameObject * pOwner, D3DXVECTOR3 offset)
{
	EnemyName * obj = new EnemyName(pScene, name, nameTexturePath,pOwner, offset);
	obj->Initialize();
	return obj;
}

