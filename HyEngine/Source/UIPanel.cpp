#include "StandardEngineFramework.h"
#include "UIPanel.h"
#include "TextureQuad.h"

using namespace HyEngine;

HyEngine::UIPanel::UIPanel(Scene * scene, std::wstring imageFilePath, const Vector3 position, const Quaternion rotation, const Vector3 scale, std::wstring tag)
	: UIElement(scene, imageFilePath, position,rotation, scale, tag)
{

}

HyEngine::UIPanel::~UIPanel()
{
}

void HyEngine::UIPanel::Initialize()
{
	UIElement::Initialize();

}

void HyEngine::UIPanel::Render()
{
	UIElement::Render();
	Draw("PanelShader");
}
