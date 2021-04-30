#include "StandardEngineFramework.h"
#include "DummyBossIdle.h"
#include "DummyBoss.h"


void DummyBossIdle::Enter()
{
	m_component->SetAnimationSet(5);
}

void DummyBossIdle::Update()
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

	if (distance <= 200)
	{
		m_component->GetState()->Set("Move");
	}
}

void DummyBossIdle::Late_Update()
{
}

void DummyBossIdle::Exit()
{
}
