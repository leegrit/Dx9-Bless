#include "stdafx.h"
#include "HGoblinAttack.h"
#include "HGoblin.h"
#include "GameScene.h"
#include "EffectManager.h"
#include "SoundManager.h"

void HGoblinAttack::Enter()
{
	m_component->SetAnimationSet(21); // attack
	m_component->ClearHitOthers();
	m_elapsed = 0.0f;
	m_isAttacked = false;
}

void HGoblinAttack::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->SetDamagedState(false);
		//m_component->GetState()->Set("Hit");
	}
	if (m_component->IsDied())
	{
		m_component->GetState()->Set("Die");
	}

	m_elapsed += TIMER->getDeltaTime();

	if (m_elapsed >= 0.5f && m_isAttacked == false)
	{
		GameScene* pScene = static_cast<GameScene*>(m_component->GetScene());

		SoundDesc desc;
		desc.channelMode = FMOD_LOOP_OFF;
		desc.volumeType = EVolumeTYPE::RelativeVolume;
		desc.volume = 1.0f;
		desc.soundPosition = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
		SOUND->PlaySound("HGoblinAtkSound", L"common_swing_lv4.wav", desc);


		pScene->GetEffectManager()->PlayEffect(std::to_wstring(m_component->GetInstanceID()) + L"SwingDownEffect");


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

void HGoblinAttack::Late_Update()
{
}

void HGoblinAttack::Exit()
{
	m_component->ClearHitOthers();
}
