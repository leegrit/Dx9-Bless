#include "StandardEngineFramework.h"
#include "ProgressBar.h"
#include "TextureQuad.h"
#include "TextureLoader.h"
HyEngine::ProgressBar::ProgressBar(Scene * scene, std::wstring fillFilePath, std::wstring fillBackFilePath,float amount, const Vector3 position, const Quaternion rotation, const Vector3 scale, std::wstring name)
	: UIElement(scene, fillBackFilePath, position, rotation, scale, name)
{
	m_pFillTex = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(fillFilePath));
	m_pFillBack = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(fillBackFilePath));
	m_amount = amount;
}

HyEngine::ProgressBar::~ProgressBar()
{
}

void HyEngine::ProgressBar::Initialize()
{
	UIElement::Initialize();
	m_amount = 1;
}

void HyEngine::ProgressBar::Render()
{
	UIElement::Render();

	D3DXHANDLE fillHandle = m_pEffect->GetParameterByName(0, "ProgressTex");
	m_pEffect->SetTexture(fillHandle, m_pFillTex.get());
	D3DXHANDLE fillBackHandle = m_pEffect->GetParameterByName(0, "ProgressBackTex");
	m_pEffect->SetTexture(fillBackHandle, m_pFillBack.get());

	m_pEffect->SetValue("ProgressAmount", &m_amount, sizeof(m_amount));
	Draw("ProgressShader");
}
