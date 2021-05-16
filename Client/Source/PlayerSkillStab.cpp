#include "stdafx.h"
#include "PlayerSkillStab.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"
#include "SoundManager.h"
#include "Player.h"

PlayerSkillStab::PlayerSkillStab(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerSkillStab")
{
	SetParams(0.2f, 3, 3.0f, 10, 10, false, D3DXVECTOR3(0, 10, 20));
}

PlayerSkillStab::~PlayerSkillStab()
{
}

void PlayerSkillStab::Initialize()
{
	PlayerAction::Initialize();


}

void PlayerSkillStab::Update()
{
	PlayerAction::Update();
	UpdateAction();
}

void PlayerSkillStab::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerSkillStab::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerSkillStab::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerSkillStab::OnHitOthers(Collider * other)
{
	PlayerAction::OnHitOthers(other);
	/* 여기서 데미지를 보낼 적들을 저장한다. */
	GameObject* go = other->GetGameObject();
	for (auto& obj : m_hitEnemies)
	{
		if (obj == go)
			return;
	}
	m_hitEnemies.push_back(go);
}

void PlayerSkillStab::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage = false;
	m_bPlayAfterImage = false;

}

void PlayerSkillStab::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	std::cout << "실제 인덱스 : " << seqIndex << std::endl;
	if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	case 0:
		if (elapsed >= 0.1f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		if (elapsed >= 0.3f)
		{
			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
			for (auto& obj : m_hitEnemies)
			{
				GameScene* pScene = static_cast<GameScene*>(SCENE);
				if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
					return;
				if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
				{
					continue;
				}

				Character* enemy = dynamic_cast<Character*>(obj);
				enemy->SendDamage(GetGameObject(), GetAttackDamage());
				//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
				/*pScene->GetEffectManager()->PlayEffect(L"PlayerNormalAttack_SwordTrailEffect");
				std::cout << "Do First" << std::endl;*/
				pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect0");
				pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect1");
				CAMERA->Shake(0.1f, 0.1f, 1.0f);
			}
			m_bSendDamage = true;
		}
		break;
	case 1:
		if (elapsed >= 0.1f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		break;
	case 2:
		if (elapsed >= 0.1f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		break;
	case 3:
		if (elapsed >= 0.1f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		break;
	case 4:
		if (elapsed >= 0.1f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		break;
	}
}

void PlayerSkillStab::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
}

UINT PlayerSkillStab::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerSkillStab::GetIdleAnimIndex() const
{
	return 89;
}

void PlayerSkillStab::UpdateAction()
{
	if (KEYBOARD->Down(48 + 2))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerSkillStab * PlayerSkillStab::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerSkillStab * com = new PlayerSkillStab(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
