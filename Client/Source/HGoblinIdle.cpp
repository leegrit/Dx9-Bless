#include "stdafx.h"
#include "HGoblinIdle.h"
#include "HGoblin.h"

void HGoblinIdle::Enter()
{
	m_component->SetAnimationSet(9);
}

void HGoblinIdle::Update()
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

	if (distance <= 100)
	{
		m_component->GetState()->Set("Move");
	}
}

void HGoblinIdle::Late_Update()
{
}

void HGoblinIdle::Exit()
{
}
