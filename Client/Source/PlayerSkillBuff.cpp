#include "stdafx.h"
#include "PlayerSkillBuff.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"
#include "SoundManager.h"


PlayerSkillBuff::PlayerSkillBuff(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerNormalAttack")
{
	SetParams(0.2f, 1, 10, 10, 10, false, D3DXVECTOR3(0, 10, 20));
}

PlayerSkillBuff::~PlayerSkillBuff()
{
}

void PlayerSkillBuff::Initialize()
{
	PlayerAction::Initialize();
}

void PlayerSkillBuff::Update()
{
	PlayerAction::Update();
	UpdateAction();
}

void PlayerSkillBuff::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerSkillBuff::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerSkillBuff::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerSkillBuff::OnHitOthers(Collider * other)
{
	PlayerAction::OnHitOthers(other);
}

void PlayerSkillBuff::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage = false;
}

void PlayerSkillBuff::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	std::cout << "½ÇÁ¦ ÀÎµ¦½º : " << seqIndex << std::endl;
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
			SOUND->PlaySound("PlayerSkillBuff", L"Lups_6.mp3", desc);
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
			m_bSendDamage = true;
		}
		break;
	}
}

void PlayerSkillBuff::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
}

UINT PlayerSkillBuff::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerSkillBuff::GetIdleAnimIndex() const
{
	return 89;
}

void PlayerSkillBuff::UpdateAction()
{
	if (KEYBOARD->Down(48 + 4))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerSkillBuff * PlayerSkillBuff::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerSkillBuff * com = new PlayerSkillBuff(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
