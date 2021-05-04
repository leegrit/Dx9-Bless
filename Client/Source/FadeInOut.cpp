#include "stdafx.h"
#include "FadeInOut.h"
#include "TextureQuad.h"
FadeInOut::FadeInOut(Scene * pScene)
	: UIElement(pScene, L"FadeInOut")
{
	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);

	ENGINE->TryGetShader(L"FadeInOut", &m_pEffect);
	assert(m_pEffect);


	m_pTransform->m_position = D3DXVECTOR3(0, 0, 0);
	m_pTransform->m_rotationEuler = D3DXVECTOR3(0, 0, 0);
	m_pTransform->m_scale = D3DXVECTOR3(WinMaxWidth, WinMaxHeight, 1);

}

FadeInOut::~FadeInOut()
{
}

void FadeInOut::Initialize()
{
	UIElement::Initialize();
}

void FadeInOut::Render()
{
	UIElement::Render();

	m_pEffect->SetMatrix("WorldMatrix", &m_pTransform->GetWorldMatrix());
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetOrthoMatrix());

	m_pEffect->SetFloat("Alpha", m_currentAlpha);

	m_pEffect->SetTechnique("FadeInOut");
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

void FadeInOut::Update()
{
	UIElement::Update();


	if (m_isFadeIn)
	{
		if (m_currentAlpha <= 0)
		{
			m_fadeInCompleted();
			SetActive(false);
		}
		m_currentAlpha -= m_speed * TIMER->getDeltaTime();
	}
	else
	{
		if (m_currentAlpha >= 1)
		{
			m_fadeOutCompleted();
			SetActive(false);
		}
		m_currentAlpha += m_speed * TIMER->getDeltaTime();
	}
}

void FadeInOut::FadeIn(std::function<void()> onFadeInCompleted, float speed)
{
	m_fadeInCompleted = onFadeInCompleted;
	m_currentAlpha = 1;
	SetActive(true);
	m_isFadeIn = true;
	m_speed = speed;
}

void FadeInOut::FadeOut(std::function<void()> onFadeOutCompleted, float speed)
{
	m_fadeOutCompleted = onFadeOutCompleted;
	m_currentAlpha = 0;
	SetActive(true);
	m_isFadeIn = false;
	m_speed = speed;
}

float FadeInOut::GetAlpha() const
{
	return m_currentAlpha;
}

FadeInOut * FadeInOut::Create(Scene * pScene)
{
	FadeInOut* obj = new FadeInOut(pScene);
	obj->Initialize();
	return obj;
}
