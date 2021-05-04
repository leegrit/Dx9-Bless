#include "stdafx.h"

#include "WarpPoint.h"
#include "GameScene.h"
#include "UIManager.h"
WarpPoint::WarpPoint(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{
}

WarpPoint::~WarpPoint()
{
}

void WarpPoint::Initialize()
{

}

void WarpPoint::Update()
{
	GameObject::Update();

	float dist = D3DXVec3Length(&(PLAYER->m_pTransform->m_position - m_pTransform->m_position).operator D3DXVECTOR3());

	if (dist <= m_radius)
	{
		GameScene* gameScene = static_cast<GameScene*>(GetScene());
		gameScene->GetUIManager()->ShowWarpInteractPanel();


		if (KEYBOARD->Down('F'))
		{
			DoWarp();
		}
	}
	else
	{
		GameScene* gameScene = static_cast<GameScene*>(GetScene());
		gameScene->GetUIManager()->HideWarpInteractPanel();
	}
}

void WarpPoint::Render()
{
	GameObject::Render();
	assert(false);

}

void WarpPoint::DoWarp()
{
	ENGINE->SwitchScene(m_sceneIndex);
}

void WarpPoint::SetWarpScene(int sceneIndex)
{
	m_sceneIndex = sceneIndex;
}

WarpPoint * WarpPoint::Create(Scene * pScene, int sceneIndex, std::wstring name)
{
	WarpPoint * obj = new WarpPoint(pScene, name);
	obj->Initialize();
	obj->SetWarpScene(sceneIndex);
	return obj;
}
