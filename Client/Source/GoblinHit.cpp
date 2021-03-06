#include "stdafx.h"
#include "GoblinHit.h"
#include "Goblin.h"
#include "SoundManager.h"
void GoblinHit::Enter()
{
	D3DXVECTOR3 skeletonePos = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
	D3DXVECTOR3 playerPos = m_component->GetTarget()->m_pTransform->m_position;//PLAYER->m_pTransform->m_position.operator D3DXVECTOR3();
	D3DXVECTOR3 dir = playerPos - skeletonePos;
	D3DXVec3Normalize(&dir, &dir);

	D3DXVECTOR3 forward = m_component->m_pTransform->Forward();
	D3DXVec3Normalize(&forward, &forward);

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::RelativeVolume;
	desc.volume = 0.1f;
	desc.soundPosition = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
	SOUND->PlaySound("GoblinHitSound", L"008_goblin_04.wav", desc);

	float dot = D3DXVec3Dot(&dir, &forward);
	/* 내적 결과가 양수일 경우 정면에서 공격당한 것 */
	if (dot > 0)
	{
		m_component->SetAnimationSet(14);
	}
	else
	{
		m_component->SetAnimationSet(15);
	}
}

void GoblinHit::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->SetDamagedState(false);
	}
	if (m_component->IsDamaged())
	{
		m_component->GetState()->Set("Hit");
	}
	if (m_component->IsDied())
	{
		m_component->GetState()->Set("Die");
	}
	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Idle");
	}
}

void GoblinHit::Late_Update()
{
}

void GoblinHit::Exit()
{
	m_component->SetDamagedState(false);
}
