#include "stdafx.h"
#include "SkeletoneMove.h"
#include "Skeletone.h"

void SkeletoneMove::Enter()
{
	m_component->SetAnimationSet(13);
}

void SkeletoneMove::Update()
{
	if(m_component->IsHit())
	{
		m_component->GetState()->Set("Hit");
	}

	D3DXVECTOR3 skeletonePos = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
	D3DXVECTOR3 playerPos = PLAYER->m_pTransform->m_position.operator D3DXVECTOR3();

	float distance = D3DXVec3Length(&(playerPos - skeletonePos));

	if (distance <= 20)
	{
		m_component->GetState()->Set("Attack");
	}

	D3DXVECTOR3 dir = playerPos - skeletonePos;
	D3DXVec3Normalize(&dir, &dir);

	m_component->m_pTransform->LookAtEuler(playerPos);
	m_component->m_pTransform->Translate(dir * m_component->GetMoveSpeed() * TIMER->getDeltaTime());
}

void SkeletoneMove::Late_Update()
{
}

void SkeletoneMove::Exit()
{
}
