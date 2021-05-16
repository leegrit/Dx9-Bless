#include "stdafx.h"
#include "GoblinMove.h"
#include "Goblin.h"

void GoblinMove::Enter()
{
	m_component->SetAnimationSet(0);

}

void GoblinMove::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->GetState()->Set("Hit");
	}
	if (m_component->IsDied())
	{
		m_component->GetState()->Set("Die");
	}

	D3DXVECTOR3 skeletonePos = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
	D3DXVECTOR3 playerPos = PLAYER->m_pTransform->m_position.operator D3DXVECTOR3();

	float distance = D3DXVec3Length(&(playerPos - skeletonePos));

	if (distance > 100)
	{
		m_component->GetState()->Set("Idle");
	}
	if (distance <= 20)
	{
		m_component->GetState()->Set("Attack");
	}

	D3DXVECTOR3 dir = playerPos - skeletonePos;
	D3DXVec3Normalize(&dir, &dir);

	m_component->m_pTransform->LookAtEuler(playerPos);
	m_component->m_pTransform->Translate(dir * m_component->GetMoveSpeed() * TIMER->getDeltaTime());
}

void GoblinMove::Late_Update()
{
}

void GoblinMove::Exit()
{
}
