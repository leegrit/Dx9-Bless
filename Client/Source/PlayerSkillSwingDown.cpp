#include "stdafx.h"
#include "PlayerSkillSwingDown.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"
#include "SoundManager.h"

PlayerSkillSwingDown::PlayerSkillSwingDown(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerSkillSwingDown")
{
	SetParams(0.2f, 1, 0, 10, 10, false, D3DXVECTOR3(0, 10, 20));
}

PlayerSkillSwingDown::~PlayerSkillSwingDown()
{
}

void PlayerSkillSwingDown::Initialize()
{
	PlayerAction::Initialize();
}

void PlayerSkillSwingDown::Update()
{
	PlayerAction::Update();
	UpdateAction();
}

void PlayerSkillSwingDown::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerSkillSwingDown::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerSkillSwingDown::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerSkillSwingDown::OnHitOthers(Collider * other)
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

void PlayerSkillSwingDown::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage = false;
}

void PlayerSkillSwingDown::OnActionTimeElapsed(int seqIndex, float elapsed)
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
			SOUND->PlaySound("PlayerSkillSwingDown", L"Lups_SwordThrowing0.mp3", desc);
			for (auto& obj : m_hitEnemies)
			{
				GameScene* pScene = static_cast<GameScene*>(SCENE);
				/*if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
					return;*/
				/*if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
				{
					continue;
				}*/

				Character* enemy = dynamic_cast<Character*>(obj);
				enemy->SendDamage(GetGameObject(), GetAttackDamage());
				//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
				//pScene->GetEffectManager()->PlayEffect(L"PlayerNormalAttack_SwordTrailEffect");
				std::cout << "Do First" << std::endl;
				CAMERA->Shake(0.1f, 0.1f, 1.0f);
			}
			m_bSendDamage = true;
		}
		break;
	}
}

void PlayerSkillSwingDown::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
}

UINT PlayerSkillSwingDown::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerSkillSwingDown::GetIdleAnimIndex() const
{
	return 89;
}

void PlayerSkillSwingDown::UpdateAction()
{
	if (KEYBOARD->Down(48 + 3))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerSkillSwingDown * PlayerSkillSwingDown::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerSkillSwingDown * com = new PlayerSkillSwingDown(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
