#include "StandardEngineFramework.h"
#include "UIElement2.h"

using namespace HyEngine;

HyEngine::UIElement2::UIElement2(Scene * scene, GameObject * parent, int editID)
	: GameObject(ERenderType::RenderAlpha, scene, parent, L"UIElement")
{

}

HyEngine::UIElement2::UIElement2(Scene * scene, GameObject * parent)
	: GameObject(ERenderType::RenderAlpha, scene, parent, L"UIElement")
{
}

UIElement2::~UIElement2()
{

}


void UIElement2::Initialize()
{

}

void HyEngine::UIElement2::Initialize(std::wstring dataPath)
{
}

void UIElement2::Render()
{
	GameObject::Render();

}

void HyEngine::UIElement2::UpdatedData(EDataType dataType)
{
	// ¹Ì±¸Çö
	assert(false);
}

UIElement2 * HyEngine::UIElement2::Create(Scene * scene, GameObject * parent, int editID)
{
	return nullptr;
}

UIElement2 * HyEngine::UIElement2::Create(Scene * scene, GameObject * parent, std::wstring dataPath)
{
	return nullptr;
}
