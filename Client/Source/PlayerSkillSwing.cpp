#include "stdafx.h"
#include "PlayerSkillSwing.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"
#include "SoundManager.h"

PlayerSkillSwing::PlayerSkillSwing(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerSkillSwing")
{
	SetParams(0.2f, 1, 0, 10, 10, false, D3DXVECTOR3(0, 10, 20));
}

PlayerSkillSwing::~PlayerSkillSwing()
{
}

void PlayerSkillSwing::Initialize()
{
	PlayerAction::Initialize();
}

void PlayerSkillSwing::Update()
{
	PlayerAction::Update();
	UpdateAction();
}

void PlayerSkillSwing::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerSkillSwing::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerSkillSwing::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerSkillSwing::OnHitOthers(Collider * other)
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

void PlayerSkillSwing::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage = false;
	
}

void PlayerSkillSwing::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	std::cout << "실제 인덱스 : " << seqIndex << std::endl;
	if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	case 0:
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
				CAMERA->Shake(0.1f, 0.1f, 1.0f);
			}
			m_bSendDamage = true;
		}
		break;
	}
}

void PlayerSkillSwing::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
}

UINT PlayerSkillSwing::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerSkillSwing::GetIdleAnimIndex() const
{
	return 89;
}

void PlayerSkillSwing::UpdateAction()
{
	if (KEYBOARD->Down(48 + 1))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerSkillSwing * PlayerSkillSwing::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerSkillSwing * com = new PlayerSkillSwing(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
