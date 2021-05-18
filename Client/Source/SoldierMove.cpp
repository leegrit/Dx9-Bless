#include "stdafx.h"
#include "SoldierMove.h"
#include "Soldier.h"
#include "GameScene.h"

void SoldierMove::Enter()
{
	m_component->SetAnimationSet(7);
}

void SoldierMove::Update()
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
	if (m_component->GetTarget() == nullptr)
	{
		m_component->GetState()->Set("Idle");
		return;
	}
	D3DXVECTOR3 targetPos = m_component->GetTarget()->m_pTransform->m_position;

	float distance = D3DXVec3Length(&(targetPos - position));


	if (distance > 100)
	{
		m_component->GetState()->Set("Idle");
	}
	if (distance <= 20)
	{
		m_component->GetState()->Set("Attack");
	}

	D3DXVECTOR3 dir = targetPos - position;
	D3DXVec3Normalize(&dir, &dir);

	m_component->m_pTransform->LookAtEuler(targetPos);
	m_component->m_pTransform->Translate(dir * m_component->GetMoveSpeed() * TIMER->getDeltaTime());
}

void SoldierMove::Late_Update()
{
}

void SoldierMove::Exit()
{
}
