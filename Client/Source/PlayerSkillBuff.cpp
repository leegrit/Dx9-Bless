#include "stdafx.h"
#include "PlayerSkillBuff.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"
#include "SoundManager.h"
#include "Player.h"
#include "Equipment.h"
#include "PlayerBuffInfo.h"
#include "PlayerSkillInfo.h"


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

	m_pPlayerBuffInfo = static_cast<PlayerBuffInfo*>(ENGINE->GetScriptableData(L"PlayerBuffInfo"));
}

void PlayerSkillBuff::Update()
{
	PlayerAction::Update();
	UpdateAction();

	if (m_pPlayerBuffInfo->bBuff)
	{
		m_buffElapsed += TIMER->getDeltaTime();
		if (m_buffElapsed >= m_buffDuration)
		{
			m_buffElapsed = 0;
			m_pPlayerBuffInfo->bBuff = false;

		}
		Player* pPlayer = static_cast<Player*>(PLAYER);

		Equipment * pWeapon = static_cast<Equipment*>(pPlayer->GetWeapon());
		pWeapon->SetRenderEffectOption(RenderEffectOption::RimLight);
		pWeapon->SetRimWidth(1.0f);
		pWeapon->SetRimColor(D3DXCOLOR(1, 1, 0, 1));

		
		
	}
	else
	{
		Player* pPlayer = static_cast<Player*>(PLAYER);

		Equipment * pWeapon = static_cast<Equipment*>(pPlayer->GetWeapon());
		float rimWidth = pWeapon->GetRimWidth();
		if (rimWidth <= 0.0f)
		{
			pWeapon->SetRenderEffectOption(RenderEffectOption::None);
		}
		else
		{
			rimWidth -= TIMER->getDeltaTime();
			rimWidth = rimWidth <= 0.0f ? 0.0 : rimWidth;
			pWeapon->SetRimWidth(rimWidth);
		}
		
		
	}
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
	m_bPlayAfterImage = false;
}

void PlayerSkillBuff::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	std::cout << "½ÇÁ¦ ÀÎµ¦½º : " << seqIndex << std::endl;
	if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	case 0:
		if (elapsed >= 0.5f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;

			Player* pPlayer = static_cast<Player*>(PLAYER);

			Equipment * pWeapon = static_cast<Equipment*>(pPlayer->GetWeapon());

			WeaponAfterEffectDesc desc;
			desc.lifeTime = 0.4f;
			desc.worldMat = pWeapon->GetWorldMatrix();
			desc.pOrigin = pWeapon;
			desc.afterEffectOption = AfterEffectOption::ScaleEffect | AfterEffectOption::FadeOut;
			desc.startScale = 2.0f;
			desc.endScale = 1.0f; 
			desc.scaleSpd = 1.5f;
			desc.color = D3DXCOLOR(1, 1, 0, 1);
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayerWeaponAffterEffect(desc);

			pPlayer->SetAnimationSpeed(0.6f);
		}

		if (elapsed >= 0.5f)
		{
			m_pPlayerBuffInfo->bBuff = true;
			m_buffElapsed = 0;
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
	Player* pPlayer = static_cast<Player*>(PLAYER);
	pPlayer->SetAnimationSpeed(1.0f);
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
	// shiled skill index = 4
	PlayerSkillInfo* pPlayerSkillInfo = static_cast<PlayerSkillInfo*>(ENGINE->GetScriptableData(L"PlayerSkillInfo"));
	if (pPlayerSkillInfo->isLock[4] == true)
		return;

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
