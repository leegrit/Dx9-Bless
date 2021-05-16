#include "stdafx.h"
#include "FontTexture.h"
#include "TextureQuad.h"
#include "TextureLoader.h"

FontTexture::FontTexture(Scene * pScene, std::wstring name, std::wstring fontTexturePath, GameObject * pOwner, D3DXVECTOR3 offset)
	: Billboard(pScene, nullptr, name, EBillboardType::Y)
{
	m_pFontTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(fontTexturePath);
	assert(m_pFontTexture);
	m_pOwner = pOwner;
	m_offset = offset;
	m_color = D3DXCOLOR(0, 0, 0, 0);
	m_colorIntensity = 0;


}

FontTexture::~FontTexture()
{
}

void FontTexture::Initialize()
{
	Billboard::Initialize();
	ENGINE->TryGetShader(L"FontTexture", &m_pEffect);
	assert(m_pEffect);
}

void FontTexture::Render()
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

void FontTexture::Update()
{
	Billboard::Update();

	m_pTransform->m_position = m_pOwner->m_pTransform->CalcOffset(m_offset);
}

void FontTexture::SetColor(D3DXCOLOR color, float intensity)
{
	m_color = color;
}

void FontTexture::SetOffset(D3DXVECTOR3 offset)
{
	m_offset = offset;
}

FontTexture * FontTexture::Create(Scene * pScene, std::wstring name, std::wstring fontTexturePath, GameObject * pOwner, D3DXVECTOR3 offset)
{
	FontTexture * obj = new FontTexture(pScene, name, fontTexturePath, pOwner, offset);
	obj->Initialize();
	return obj;
}
