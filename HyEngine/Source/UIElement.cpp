#include "StandardEngineFramework.h"
#include "UIElement.h"

using namespace HyEngine;

HyEngine::UIElement::UIElement(Scene * scene, GameObject * parent, int editID)
	: GameObject(ERenderType::RenderAlpha, scene, parent, L"UIElement")
{
	SetEditID(editID);
}

HyEngine::UIElement::UIElement(Scene * scene, std::wstring name)
	: GameObject(ERenderType::RenderAlpha, scene, nullptr, name)
{
}

UIElement::~UIElement()
{

}


void UIElement::Initialize()
{

}



void UIElement::Render()
{
	GameObject::Render();

}

void HyEngine::UIElement::UpdatedData(EDataType dataType)
{

}

UIElement * HyEngine::UIElement::Create(Scene * scene, GameObject * parent, int editID)
{
	return nullptr;
}

UIElement * HyEngine::UIElement::Create(Scene * scene)
{
	return nullptr;
}
