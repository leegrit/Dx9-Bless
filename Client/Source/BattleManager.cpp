#include "stdafx.h"
#include "BattleManager.h"
#include "Raycaster.h"
#include "RaycastHit.h"
#include "GameScene.h"
#include "UIManager.h"
#include "Character.h"
BattleManager::BattleManager(Scene * pScene)
{
	m_pScene = dynamic_cast<GameScene*>(pScene);
	assert(m_pScene);
}

BattleManager::~BattleManager()
{
}

void BattleManager::Initialize()
{
}

void BattleManager::Update()
{
	//////////////////////////////////////////////////////////////////////////
	// FOR FOCUS
	//////////////////////////////////////////////////////////////////////////
	D3DXVECTOR3 mousePos = MOUSE->GetPosition();
	mousePos = D3DXVECTOR3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0);
	D3DXVECTOR3 origin;
	D3DXVECTOR3 direction;

	CAMERA->UnProjection(&origin, &direction, mousePos);

	//RaycastHit* pRaycastHit = nullptr;
	Raycaster* pRaycaster = new Raycaster();

	auto raycastHits = pRaycaster->RaycastHitAll(origin, direction, Layer::Enemy, EColliderType::Multipurpose);
	float min = FLT_MAX;
	GameObject* pFocused = nullptr;
	for (auto& raycastHit : raycastHits)
	{
		Character* pCharacter = dynamic_cast<Character*>(raycastHit->m_pTransform->GetGameObject());
		if (pCharacter == nullptr)
			continue;
		if (pCharacter->IsDied())
			continue;
		float dist = D3DXVec3Length(&(PLAYER->m_pTransform->m_position - raycastHit->m_pTransform->m_position).operator D3DXVECTOR3());
		if (dist >= m_maxRadius)
			continue;
		if (dist < min)
		{
			min = dist;
			pFocused = raycastHit->m_pTransform->GetGameObject();
		}
	}

	if (pFocused == nullptr)
	{
		m_pScene->GetUIManager()->OnFocusLost();
		m_pFocusedObj = pFocused;
	}
	else if (m_pFocusedObj != nullptr &&  m_pFocusedObj == pFocused)
	{
		// 변동 없음
		m_pScene->GetUIManager()->OnFocusAgain(m_pFocusedObj);
	}
	else 
	{
		// Change Focus
		m_pFocusedObj = pFocused;

		m_pScene->GetUIManager()->OnFocusChanged(m_pFocusedObj);
	}

	//if (pRaycaster->Raycast(origin, direction, Layer::Enemy, EColliderType::Multipurpose, pRaycastHit))
	//{
	//	if (m_pFocusedObj == pRaycastHit->m_pTransform->GetGameObject())
	//	{
	//		// 변동 없음
	//	}
	//	else
	//	{
	//		// Change Focus
	//		m_pFocusedObj = pRaycastHit->m_pTransform->GetGameObject();

	//		m_pScene->GetUIManager()->OnFocusChanged(m_pFocusedObj);
	//	}
	//}
	//else
	//{
	//	// Lost Focus
	//	m_pScene->GetUIManager()->OnFocusLost();
	//}


}

GameObject * BattleManager::GetFocusedObject() const
{
	return m_pFocusedObj;
}
