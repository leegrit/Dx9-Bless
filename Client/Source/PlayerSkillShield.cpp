#include "stdafx.h"
#include "PlayerSkillShield.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"
#include "SoundManager.h"

PlayerSkillShield::PlayerSkillShield(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerSkillShield")
{
	SetParams(0.2f, 1, 0, 10, 0, false, D3DXVECTOR3(0, 10, 20));
}

PlayerSkillShield::~PlayerSkillShield()
{
}

void PlayerSkillShield::Initialize()
{
	PlayerAction::Initialize();
}

void PlayerSkillShield::Update()
{
	PlayerAction::Update();
	UpdateAction();


}

void PlayerSkillShield::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerSkillShield::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerSkillShield::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerSkillShield::OnHitOthers(Collider * other)
{
	PlayerAction::OnHitOthers(other);
}

void PlayerSkillShield::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage = false;
}

void PlayerSkillShield::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	std::cout << "½ÇÁ¦ ÀÎµ¦½º : " << seqIndex << std::endl;
	if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	case 0:
		if (elapsed >= 0.3f)
		{
			//for (auto& obj : m_hitEnemies)
			//{
			//	GameScene* pScene = static_cast<GameScene*>(SCENE);
			//	if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
			//		return;
			//	if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
			//	{
			//		continue;
			//	}

			//	Character* enemy = dynamic_cast<Character*>(obj);
			//	enemy->SendDamage(GetGameObject(), GetAttackDamage());
			//	//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
			//	pScene->GetEffectManager()->PlayEffect(L"PlayerNormalAttack_SwordTrailEffect");
			//	std::cout << "Do First" << std::endl;
			//	CAMERA->Shake(0.1f, 0.1f, 1.0f);
			//}
			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerSkillShield",L"Lups_Guard.mp3",  desc);
			m_bSendDamage = true;
		}
		break;
	}
}

void PlayerSkillShield::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
}

UINT PlayerSkillShield::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerSkillShield::GetIdleAnimIndex() const
{
	return 89;
}

void PlayerSkillShield::UpdateAction()
{
	if (KEYBOARD->Down(VK_SHIFT))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerSkillShield * PlayerSkillShield::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerSkillShield * com = new PlayerSkillShield(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
