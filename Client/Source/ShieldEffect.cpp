#include "stdafx.h"
#include "ShieldEffect.h"

ShieldEffect::ShieldEffect(Scene * pScene)
	: MeshEffect(pScene)
{

}

ShieldEffect::~ShieldEffect()
{
}

void ShieldEffect::Render()
{
	m_pEffect->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
	m_pEffect->SetValue("ViewMatrix", &CAMERA->GetViewMatrix(), sizeof(CAMERA->GetViewMatrix()));
	m_pEffect->SetValue("ProjMatrix", &CAMERA->GetProjectionMatrix(), sizeof(CAMERA->GetProjectionMatrix()));

	/* Set Alpha mask */
	D3DXHANDLE normalHandle = m_pEffect->GetParameterByName(0, "NormalTex");
	m_pEffect->SetTexture(normalHandle, GetNormalTexture());

	m_pEffect->SetFloat("Alpha", GetAlpha());

	float rimWidth = 0.2f;

	D3DXVECTOR3 worldPos = m_pTransform->m_position;
	D3DXVECTOR3 cameraPos = CAMERA->m_pTransform->m_position;
	m_pEffect->SetValue("WorldPosition", &worldPos, sizeof(worldPos));
	m_pEffect->SetValue("EyePosition", &cameraPos, sizeof(cameraPos));
	m_pEffect->SetFloat("RimWidth", rimWidth);

	m_pEffect->SetTechnique("ShieldEffect");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);
		GetMesh()->DrawSubset(0);
		m_pEffect->EndPass();
	}
	m_pEffect->End();
}

void ShieldEffect::Initialize()
{

	ENGINE->TryGetShader(L"ShieldEffect", &m_pEffect);

	assert(m_pEffect);
}

ShieldEffect * ShieldEffect::Create(Scene * pScene)
{
	ShieldEffect* effect = new ShieldEffect(pScene);
	effect->Initialize();
	return effect;
}
