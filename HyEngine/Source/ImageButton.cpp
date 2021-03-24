#include  "StandardEngineFramework.h"
#include "ImageButton.h"
#include "TextureQuad.h"
#include "TextureLoader.h"
using namespace HyEngine;

HyEngine::ImageButton::ImageButton(Scene * scene, std::wstring imageFilePath, std::wstring switchImagePath, const Vector3 position, const Quaternion rotation, const Vector3 scale, std::wstring tag)
	:UIButton(scene, imageFilePath, position, rotation, scale, tag)
{
	m_pSwitchImage = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(switchImagePath));
}

HyEngine::ImageButton::~ImageButton()
{
}

void HyEngine::ImageButton::Initialize()
{
	UIButton::Initialize();

	m_pOriginTex = m_pTexture;
}

void HyEngine::ImageButton::Render()
{
	UIButton::Render();
	if (m_bImageChange)
		m_pTexture = m_pSwitchImage;
	else
		m_pTexture = m_pOriginTex;

	Draw("ButtonShader");


}

void HyEngine::ImageButton::OnButtonDown()
{

}

void HyEngine::ImageButton::OnButtonUp()
{

}

void HyEngine::ImageButton::OnCollisionStayWithMouse()
{
}