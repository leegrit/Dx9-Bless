#include "stdafx.h"
#include "InteractManager.h"
#include "ObjectContainer.h"
#include "CollectObject.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "UIManager.h"

InteractManager::InteractManager(GameScene * pScene)
	: m_pScene(pScene)
{
	m_bInteractable = true;
}

InteractManager::~InteractManager()
{
}

void InteractManager::Initialize()
{
	auto& container = m_pScene->GetObjectContainer()->GetOpaqueObjectAll();

	for (auto& obj : container)
	{
		CollectObject* pCollectObj = dynamic_cast<CollectObject*>(obj);
		if (pCollectObj == nullptr)
			continue;
		m_collectObjects.push_back(pCollectObj);
	}
}

void InteractManager::Update()
{
	/*if (m_bInteractable == false)
		return;*/

	bool bExistCloseObj = false;

	for (auto& obj : m_collectObjects)
	{
		float dist = D3DXVec3Length(&(PLAYER->m_pTransform->m_position.operator D3DXVECTOR3() - obj->m_pTransform->m_position.operator D3DXVECTOR3()));
		if (dist <= m_interDist)
		{
			bExistCloseObj = true;
		}
		obj->Collecting();
	}
	if (bExistCloseObj == true)
	{
		// 여기서 말걸기 UI 띄우기
		GameScene* gameScene = static_cast<GameScene*>(m_pScene);
		gameScene->GetUIManager()->ShowCollectInteractPanel();
	}
	else
	{
		GameScene* gameScene = static_cast<GameScene*>(m_pScene);
		gameScene->GetUIManager()->HideCollectInteractPanel();

	}
}
