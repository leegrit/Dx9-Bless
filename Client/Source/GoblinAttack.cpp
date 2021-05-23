#include "stdafx.h"
#include "GoblinAttack.h"
#include "Goblin.h"
#include "SoundManager.h"

void GoblinAttack::Enter()
{
	m_component->SetAnimationSet(19); // attack
	m_component->ClearHitOthers();
	m_elapsed = 0.0f;
	m_isAttacked = false;
}

void GoblinAttack::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->SetDamagedState(false);
	}
	if (m_component->IsDied())
	{
		m_component->GetState()->Set("Die");
	}

	m_elapsed += TIMER->getDeltaTime();

	if (m_elapsed >= 0.5f && m_isAttacked == false)
	{
		SoundDesc desc;
		desc.channelMode = FMOD_LOOP_OFF;
		desc.volumeType = EVolumeTYPE::RelativeVolume;
		desc.volume = 0.1f;
		desc.soundPosition = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
		SOUND->PlaySound("GoblinAtkSound", L"008_goblin_01.wav", desc);
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

void GoblinAttack::Late_Update()
{
}

void GoblinAttack::Exit()
{
	m_component->ClearHitOthers();
}
