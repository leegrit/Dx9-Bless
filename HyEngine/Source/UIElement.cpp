#include "StandardEngineFramework.h"
#include "UIElement.h"
#include "..\Include\UIElement2.h"

using namespace HyEngine;

UIElement::UIElement(class Scene* scene,
	std::wstring imageFilePath,
	const Vector3 position,
	const Quaternion rotation,
	const Vector3 scale,
	std::wstring tag)
	: TextureObject(scene, nullptr, ERenderType::RenderOpaque, imageFilePath, tag)
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

HyEngine::UIElement::~UIElement()
{
}

void HyEngine::UIElement::Initialize()
{
}

void HyEngine::UIElement::Render()
{
}
