#include "stdafx.h"
#include "PlayerSkillTornado.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"
#include "SoundManager.h"
#include "Player.h"
#include "PlayerAfterImage.h"
#include "PlayerSkillInfo.h"


PlayerSkillTornado::PlayerSkillTornado(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerSkillTornado")
{
	SetParams(0.2f, 1, 10, 10, 10, false, D3DXVECTOR3(0, 10, 20));
}

PlayerSkillTornado::~PlayerSkillTornado()
{
}

void PlayerSkillTornado::Initialize()
{
	PlayerAction::Initialize();
}

void PlayerSkillTornado::Update()
{
	PlayerAction::Update();
	UpdateAction();
}

void PlayerSkillTornado::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerSkillTornado::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerSkillTornado::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerSkillTornado::OnHitOthers(Collider * other)
{
	PlayerAction::OnHitOthers(other);
	/* ���⼭ �������� ���� ������ �����Ѵ�. */
	GameObject* go = other->GetGameObject();
	for (auto& obj : m_hitEnemies)
	{
		if (obj == go)
			return;
	}
	m_hitEnemies.push_back(go);
}

void PlayerSkillTornado::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage = false;

	Player * pPlayer = static_cast<Player*>(PLAYER);
	UINT animSet = pPlayer->GetCurAnimationIndex();

	AfterEffectDesc desc;
	desc.animIndex = animSet;
	desc.color = D3DXCOLOR(1, 1, 1, 1);
	desc.lifeTime = 3.0f;

	GameScene* pScene = static_cast<GameScene*>(SCENE);
	m_testIndex = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);

}

void PlayerSkillTornado::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	case 0:
		if (elapsed >= 0.3f)
		{
			/* Test */
			//////////////////////////////////////////////////////////////////////////
			Player* pPlayer = static_cast<Player*>(PLAYER);
			auto weapon = pPlayer->GetWeapon();
			weapon->SetRenderEffectOption(RenderEffectOption::RimLight);
			weapon->SetRimWidth(1.0f);
			//////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////
			//Player * pPlayer = static_cast<Player*>(PLAYER);
			//PlayerAfterImage* pPlayerAfterImage = pPlayer->GetAfterImage();
			//pPlayerAfterImage->SetActive(true);
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_testIndex);
			//////////////////////////////////////////////////////////////////////////


			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerSkillTornado", L"Lups_SwordThrowing8.mp3", desc);
			for (auto& obj : m_hitEnemies)
			{
				
				if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
					return;
				/*if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
				{
					continue;
				}*/

				Character* enemy = dynamic_cast<Character*>(obj);
				enemy->SendDamage(GetGameObject(), GetAttackDamage());
				//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
				pScene->GetEffectManager()->PlayEffect(L"PlayerNormalAttack_SwordTrailEffect");
				std::cout << "Do First" << std::endl;
				CAMERA->Shake(0.1f, 0.1f, 1.0f);
			}
			m_bSendDamage = true;
		}
		else
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			PlayerAfterImage* pPlayerAfterImage =  pPlayer->GetAfterImage();
			pPlayerAfterImage->SetActive(false);
			pPlayerAfterImage->ForcedUpdateAnimation();
		}
		break;
	}
}

void PlayerSkillTornado::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
}

UINT PlayerSkillTornado::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerSkillTornado::GetIdleAnimIndex() const
{
	return 89;
}

void PlayerSkillTornado::UpdateAction()
{
	// shiled skill index = 3
	PlayerSkillInfo* pPlayerSkillInfo = static_cast<PlayerSkillInfo*>(ENGINE->GetScriptableData(L"PlayerSkillInfo"));
	if (pPlayerSkillInfo->isLock[3] == true)
		return;

	if (KEYBOARD->Down(48 + 3))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerSkillTornado * PlayerSkillTornado::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerSkillTornado * com = new PlayerSkillTornado(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
