#include "stdafx.h"
#include "SkeletoneHit.h"
#include "Skeletone.h"

void SkeletoneHit::Enter()
{
	D3DXVECTOR3 skeletonePos = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
	D3DXVECTOR3 playerPos = PLAYER->m_pTransform->m_position.operator D3DXVECTOR3();
	D3DXVECTOR3 dir = playerPos - skeletonePos;
	D3DXVec3Normalize(&dir, &dir);

	D3DXVECTOR3 forward = m_component->m_pTransform->Forward();
	D3DXVec3Normalize(&forward, &forward);
	
	float dot = D3DXVec3Dot(&dir, &forward);
	/* 내적 결과가 양수일 경우 정면에서 공격당한 것 */
	if (dot > 0) 
	{
		m_component->SetAnimationSet(15);
	}
	else
	{
		m_component->SetAnimationSet(16);
	}


}

void SkeletoneHit::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->SetAnimationSet(14);
		m_component->GetState()->Set("Hit");
	}
	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Idle");
	}
}

void SkeletoneHit::Late_Update()
{
}

void SkeletoneHit::Exit()
{
	m_component->SetDamagedState(false);
}
