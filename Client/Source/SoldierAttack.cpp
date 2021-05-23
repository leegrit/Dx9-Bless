#include "stdafx.h"
#include "SoldierAttack.h"
#include "Soldier.h"
#include "SoundManager.h"
void SoldierAttack::Enter()
{
	m_component->SetAnimationSet(1); // attack
	m_component->ClearHitOthers();
	m_elapsed = 0.0f;
	m_isAttacked = false;
}

void SoldierAttack::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->GetState()->Set("Hit");
	}
	if (m_component->IsDied())
	{
		m_component->GetState()->Set("Die");
	}

	m_elapsed += TIMER->getDeltaTime();

	if (m_elapsed >= 0.3f && m_isAttacked == false)
	{
		SoundDesc desc;
		desc.channelMode = FMOD_LOOP_OFF;
		desc.volumeType = EVolumeTYPE::RelativeVolume;
		desc.volume = 0.1f;
		desc.soundPosition = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
		SOUND->PlaySound("SoldierAtkSound", L"Attack_Voice_0.wav", desc);
		m_component->SendDamageToOthers(50);
		m_isAttacked = true;
	}

	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Idle");
	}
}

void SoldierAttack::Late_Update()
{
}

void SoldierAttack::Exit()
{
	m_component->ClearHitOthers();
}
