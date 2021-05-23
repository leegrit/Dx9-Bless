#include "stdafx.h"
#include "HGoblinAttack2.h"
#include "HGoblin.h"
#include "GameScene.h"
#include "EffectManager.h"
#include "SoundManager.h"

void HGoblinAttack2::Enter()
{
	m_component->SetAnimationSet(22);
	m_component->ClearHitOthers();
	m_elapsed = 0.0f;
	m_isAttacked = false;
}

void HGoblinAttack2::Update()
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
		SOUND->PlaySound("HGoblinAtk2Sound", L"common_swing_lv5.wav", desc);

		pScene->GetEffectManager()->PlayEffect(std::to_wstring(m_component->GetInstanceID()) + L"SwingEffect");


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

void HGoblinAttack2::Late_Update()
{
}

void HGoblinAttack2::Exit()
{
	m_component->ClearHitOthers();
}
