#include "StandardEngineFramework.h"
#include "UIElement.h"

using namespace HyEngine;

UIElement::UIElement(class Scene* scene,
	std::wstring imageFilePath,
	const Vector3 position,
	const Quaternion rotation,
	const Vector3 scale,
	std::wstring tag)
	: TextureObject(scene, nullptr, ERenderType::RenderOpaque, imageFilePath,tag)
{
	m_pTransform->SetPosition(position);
	m_pTransform->m_rotation = rotation;
	m_pTransform->SetScale(scale);
}

HyEngine::UIElement::UIElement(Scene * scene, std::wstring imageFilePath, std::wstring name)
	: TextureObject(scene, nullptr, ERenderType::RenderOpaque, imageFilePath, name)
{
	m_pTransform->SetPosition(0, 0, 0);
	m_pTransform->SetScale(1, 1, 1);
}

UIElement::~UIElement()
{

}


void UIElement::Initialize()
{
	TextureObject::Initialize();
}

void UIElement::Render()
{
	TextureObject::Render();
	m_pEffect->SetValue("ViewMatrix", &CAMERA->GetIdentityViewMatrix(), sizeof(D3DXMATRIX));
	m_pEffect->SetValue("ProjMatrix", &CAMERA->GetOrthoMatrix(), sizeof(D3DXMATRIX));

}