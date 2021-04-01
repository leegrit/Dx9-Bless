#include "StandardEngineFramework.h"
#include "ImageSwitchButton.h"
#include "TextureQuad.h"
#include "TextureLoader.h"
using namespace HyEngine;

HyEngine::ImageSwitchButton::ImageSwitchButton(Scene * scene, std::wstring imageFilePath, std::wstring switchImagePath, const Vector3 position, const Quaternion rotation, const Vector3 scale, std::wstring tag)
	:UIButton(scene, imageFilePath, position, rotation, scale, tag)
{
	m_pSwitchImage = (IDirect3DTexture9*)(TextureLoader::GetTexture(switchImagePath));
}

HyEngine::ImageSwitchButton::~ImageSwitchButton()
{
}

void HyEngine::ImageSwitchButton::Initialize()
{
	UIButton::Initialize();

	m_pOriginTex = m_pTexture;
}

void HyEngine::ImageSwitchButton::Render()
{
	UIButton::Render();
	if (m_bImageChange)
		m_pTexture = m_pSwitchImage;
	else
		m_pTexture = m_pOriginTex;
	
	Draw("ButtonShader");
	
	/*DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
	0, 0, m_pTextureQuad->GetVertexCount(),
	0,
	m_pTextureQuad->GetPrimitiveCount());*/

	
}

void HyEngine::ImageSwitchButton::OnButtonDown()
{

}

void HyEngine::ImageSwitchButton::OnButtonUp()
{
	m_bImageChange = !m_bImageChange;
}

void HyEngine::ImageSwitchButton::OnCollisionStayWithMouse()
{
}
