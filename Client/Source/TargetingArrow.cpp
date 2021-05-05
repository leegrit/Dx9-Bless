#include "stdafx.h"
#include "TargetingArrow.h"
#include "TextureQuad.h"
#include "PathManager.h"

TargetingArrow::TargetingArrow(Scene * pScene, std::wstring name)
	: Billboard(pScene, nullptr, name, EBillboardType::All)
{

}

TargetingArrow::~TargetingArrow()
{
}

void TargetingArrow::Initialize()
{
	Billboard::Initialize();

	ENGINE->TryGetShader(L"TargetingUI", &m_pEffect);
	assert(m_pEffect);

	SetDiffuseTexture(PATH->AssetsPathW() + L"UI/TargetUI/FX_Target_001_TEX_KKJ33.png");

}

void TargetingArrow::Render()
{
	if (m_pTarget == nullptr) return;

	m_pEffect->SetMatrix("WorldMatrix", &GetBillboardMatrix());
	m_pEffect->SetMatrix("ViewMatrix", &CAMERA->GetViewMatrix());
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetProjectionMatrix());

	D3DXHANDLE DiffuseHandler = m_pEffect->GetParameterByName(0, "DiffuseTex");
	m_pEffect->SetTexture(DiffuseHandler, m_pDiffuse);

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

void TargetingArrow::Update()
{
	Billboard::Update();

	if (m_pTarget)
		m_pTransform->m_position = m_pTarget->m_pTransform->CalcOffset(m_focusOffset);


}

void TargetingArrow::Focus(GameObject * pTarget, D3DXVECTOR3 focusOffset)
{
	OnFocused();
	m_pTarget = pTarget;
	m_focusOffset = focusOffset;
	m_bFocused = true;
}

void TargetingArrow::LostFocus()
{
	OnLostFocused();
	m_bFocused = false;
}

void TargetingArrow::OnFocused()
{
}

void TargetingArrow::OnLostFocused()
{
}

TargetingArrow * TargetingArrow::Create(Scene * pScene, std::wstring name)
{
	TargetingArrow * obj = new TargetingArrow(pScene, name);
	obj->Initialize();
	return obj;
}


