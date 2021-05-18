#include "stdafx.h"
#include "SoldierIdle.h"
#include "Soldier.h"
#include "ObjectContainer.h"
#include "GameScene.h"
void SoldierIdle::Enter()
{
	m_component->SetAnimationSet(22);
}

void SoldierIdle::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->GetState()->Set("Hit");
	}
	if (m_component->IsDied())
	{
		m_component->GetState()->Set("Die");
	}
	

	D3DXVECTOR3 position = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
	GameScene* pScene = static_cast<GameScene*>(m_component->GetScene());

	Character* pCharacter = static_cast<Character*>(m_component->GetTarget());
	if (m_component->GetTarget() && pCharacter->IsDied() == false)
	{
		D3DXVECTOR3 targetPos = m_component->GetTarget()->m_pTransform->m_position.operator D3DXVECTOR3();
		float distance = D3DXVec3Length(&(targetPos - position));
		if (distance <= 20)
		{
			m_component->GetState()->Set("Attack");
		}
	}



	GameObject* pClosestTarget = nullptr;
	float closestDist = FLT_MAX;

	for (GameObject* target : pScene->GetObjectGroup(EObjectGroup::EnemyGroup))
	{
		Character* pTarget = static_cast<Character*>(target);
		if (pTarget->IsDied())continue;

		D3DXVECTOR3 targetPos = target->m_pTransform->m_position.operator D3DXVECTOR3();

		float distance = D3DXVec3Length(&(targetPos - position));
		if (closestDist >= distance)
		{
			pClosestTarget = target;
			closestDist = distance;
		}

	}
	if (closestDist <= 100)
	{
		m_component->GetState()->Set("Move");
		m_component->SetTarget(pClosestTarget);
		return;
	}
}

void SoldierIdle::Late_Update()
{
}

void SoldierIdle::Exit()
{
}
