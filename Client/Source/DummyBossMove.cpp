#include "StandardEngineFramework.h"
#include "DummyBossMove.h"
#include "DummyBoss.h"

void DummyBossMove::Enter()
{
	m_component->SetAnimationSet(4);
}

void DummyBossMove::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->GetState()->Set("Hit");
	}
	if (m_component->IsDied())
	{
		m_component->GetState()->Set("Die");
	}

	D3DXVECTOR3 ownerPos = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
	D3DXVECTOR3 playerPos = PLAYER->m_pTransform->m_position.operator D3DXVECTOR3();

	float distance = D3DXVec3Length(&(playerPos - ownerPos));

	if (distance >= 200)
	{
		m_component->GetState()->Set("Idle");
	}
	if (distance <= 40)
	{
		m_component->GetState()->Set("Attack");
	}

	D3DXVECTOR3 dir = playerPos - ownerPos;
	D3DXVec3Normalize(&dir, &dir);

	m_component->m_pTransform->LookAtEuler(playerPos);
	m_component->m_pTransform->Translate(dir * m_component->GetMoveSpeed() * TIMER->getDeltaTime());

}

void DummyBossMove::Late_Update()
{
}

void DummyBossMove::Exit()
{
}
