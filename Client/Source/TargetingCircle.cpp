#include "stdafx.h"
#include "TargetingCircle.h"
#include "TextureQuad.h"
#include "PathManager.h"
TargetingCircle::TargetingCircle(Scene * pScene, std::wstring name)
	: Billboard(pScene, nullptr, name,EBillboardType::All)
{

}

TargetingCircle::~TargetingCircle()
{
}

void TargetingCircle::Initialize()
{
	Billboard::Initialize();

	ENGINE->TryGetShader(L"TargetingUI", &m_pEffect);
	assert(m_pEffect);

	SetDiffuseTexture(PATH->AssetsPathW() + L"UI/TargetUI/FX_Target_Point_001_TEX_HKB13131.png");


}

void TargetingCircle::Render()
{
	if (m_pTarget == nullptr) return;

	m_pEffect->SetMatrix("WorldMatrix", &GetBillboardMatrix());
	m_pEffect->SetMatrix("ViewMatrix", &CAMERA->GetViewMatrix());
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetProjectionMatrix());

	D3DXHANDLE DiffuseHandler = m_pEffect->GetParameterByName(0, "DiffuseTex");
	m_pEffect->SetTexture(DiffuseHandler, m_pDiffuse);

	m_pEffect->SetFloat("Alpha", m_currentAlpha);

	m_pEffect->SetTechnique("TargetingUI");
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

void TargetingCircle::Update()
{
	Billboard::Update();

	if(m_pTarget)
		m_pTransform->m_position = m_pTarget->m_pTransform->CalcOffset(m_focusOffset);

	if (m_bFocused == true)
	{
		m_elapsed += TIMER->getDeltaTime() * m_changeEventSpeed;
		//float lerpFactor = std::min(m_elapsed, 1.0f);

		////float xSize = m_pTransform->m_scale.x();
		//float xSize = DxHelper::Lerp(m_focusChangeScale.x, m_originScale.x, lerpFactor);
		//m_pTransform->m_scale = D3DXVECTOR3(xSize, xSize, 1);

		m_currentAlpha = 1;
	}
	else if (m_bFocused == false)
	{
		m_elapsed += TIMER->getDeltaTime();
		float lerpFactor = std::min(m_elapsed, 1.0f);

		m_currentAlpha = DxHelper::Lerp(1, m_lostAlpha, lerpFactor);

	}
}

void TargetingCircle::Focus(GameObject * pTarget, D3DXVECTOR3 focusOffset)
{
	if (m_bFocused != true)
	{
		m_elapsed = 0;
	}
	OnFocused();
	m_pTarget = pTarget;
	m_focusOffset = focusOffset;
	m_bFocused = true;
}

void TargetingCircle::LostFocus()
{
	if (m_bFocused != false)
	{
		m_elapsed = 0;
	}
	OnLostFocused();
	m_bFocused = false;
}

void TargetingCircle::OnFocused()
{
}

void TargetingCircle::OnLostFocused()
{
}

TargetingCircle * TargetingCircle::Create(Scene * pScene, std::wstring name)
{
	TargetingCircle * obj = new TargetingCircle(pScene, name);
	obj->Initialize();
	return obj;
}
