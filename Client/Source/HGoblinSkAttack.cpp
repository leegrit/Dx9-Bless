#include "stdafx.h"
#include "HGoblinSkAttack.h"
#include "HGoblin.h"
#include "GameScene.h"
#include "EffectManager.h"
#include "SoundManager.h"
void HGoblinSkAttack::Enter()
{
	m_component->SetAnimationSet(2); // attack
	m_component->ClearHitOthers();
	m_elapsed = 0.0f;
	m_isAttacked = false;
	m_isAttacked2 = false;

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::RelativeVolume;
	desc.volume = 1.0f;
	desc.soundPosition = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
	SOUND->PlaySound("HGoblinComboVoice", L"Hanuman_Combo_Voice.wav", desc);
}

void HGoblinSkAttack::Update()
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

	if (m_elapsed >= 0.5f && m_isAttacked == false)
	{
		GameScene* pScene = static_cast<GameScene*>(m_component->GetScene());
		SoundDesc desc;
		desc.channelMode = FMOD_LOOP_OFF;
		desc.volumeType = EVolumeTYPE::RelativeVolume;
		desc.volume = 1.0f;
		desc.soundPosition = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
		SOUND->PlaySound("HGoblinSKAtkSound", L"common_swing_lv4.wav", desc);

		pScene->GetEffectManager()->PlayEffect(std::to_wstring(m_component->GetInstanceID()) + L"SKSwingDownEffect");


		m_component->SendDamageToOthers(50);
		m_isAttacked = true;
	}
	if (m_elapsed >= 1.1f && m_isAttacked2 == false)
	{
		GameScene* pScene = static_cast<GameScene*>(m_component->GetScene());

		SoundDesc desc;
		desc.channelMode = FMOD_LOOP_OFF;
		desc.volumeType = EVolumeTYPE::RelativeVolume;
		desc.volume = 1.0f;
		desc.soundPosition = m_component->m_pTransform->m_position.operator D3DXVECTOR3();
		SOUND->PlaySound("HGoblinAtkSound", L"common_swing_lv7.wav", desc);
		pScene->GetEffectManager()->PlayEffect(std::to_wstring(m_component->GetInstanceID()) + L"SKSwingEffect");


		m_component->SendDamageToOthers(50);
		m_isAttacked2 = true;
	}

	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Idle");
	}
}

void HGoblinSkAttack::Late_Update()
{
}

void HGoblinSkAttack::Exit()
{
	m_component->ClearHitOthers();
}
