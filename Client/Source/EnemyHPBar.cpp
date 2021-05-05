#include "stdafx.h"
#include "EnemyHPBar.h"
#include "TextureQuad.h"

EnemyHPBar::EnemyHPBar(Scene * pScene, std::wstring name)
	: Billboard(pScene, nullptr, name, EBillboardType::Y)
{

}

EnemyHPBar::~EnemyHPBar()
{
}

void EnemyHPBar::Initialize()
{
	Billboard::Initialize();

	ENGINE->TryGetShader(L"ProgressBar", &m_pEffect);
	assert(m_pEffect);

}

void EnemyHPBar::Render()
{
	m_pEffect->SetMatrix("WorldMatrix", &GetBillboardMatrix());
	m_pEffect->SetMatrix("ViewMatrix", &CAMERA->GetViewMatrix());
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetProjectionMatrix());

	D3DXHANDLE fillHandler  = m_pEffect->GetParameterByName(0, "FillTex");
	m_pEffect->SetTexture(fillHandler, m_pFillTex);

	D3DXHANDLE BackHandler = m_pEffect->GetParameterByName(0, "BackTex");
	m_pEffect->SetTexture(BackHandler, m_pBackTex);

	m_pEffect->SetFloat("Amount", m_amount);


	m_pEffect->SetTechnique("BillboardBar");
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

void EnemyHPBar::Update()
{
	Billboard::Update();
}

void EnemyHPBar::SetFillTex(std::wstring filePath)
{
	m_pFillTex = (IDirect3DTexture9*)TextureLoader::GetTexture(filePath);
}

void EnemyHPBar::SetBackTex(std::wstring filePath)
{
	m_pBackTex = (IDirect3DTexture9*)TextureLoader::GetTexture(filePath);
}

void EnemyHPBar::SetAmount(float amount)
{
	m_amount = amount;
}

EnemyHPBar * EnemyHPBar::Create(Scene * pScene, std::wstring name)
{
	EnemyHPBar * obj = new EnemyHPBar(pScene, name);
	obj->Initialize();
	return obj;
}
