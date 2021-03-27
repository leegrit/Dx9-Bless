#include "StandardEngineFramework.h"
#include "EditTransformRect.h"
#include "DiffuseQuad.h"

HyEngine::EditTransformRect::EditTransformRect(Scene * scene, GameObject * parent)
	:GameObject(ERenderType::RenderTexture, scene, parent, L"TransformRect")
{

}

HyEngine::EditTransformRect::~EditTransformRect()
{
}

void HyEngine::EditTransformRect::Initialize()
{
	D3DCOLOR xyColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	D3DCOLOR zxColor = D3DCOLOR_ARGB(255, 0, 255, 0);
	D3DCOLOR zyColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	m_pXYRect = Geometry::CreateGeometry<DiffuseQuad>((void*)&xyColor);
	m_pZXRect = Geometry::CreateGeometry<DiffuseQuad>((void*)&zxColor);
	m_pZYRect = Geometry::CreateGeometry<DiffuseQuad>((void*)&zyColor);
	D3DXCreateEffectFromFile(DEVICE, L"../_Shaders/TextureShader.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);

}

void HyEngine::EditTransformRect::Render()
{
	GameObject::Render();


}

EditTransformRect * HyEngine::EditTransformRect::Create(Scene * scene, GameObject * parent)
{
	EditTransformRect* obj = new EditTransformRect(scene, parent);
	obj->Initialize();
	return obj;
}
