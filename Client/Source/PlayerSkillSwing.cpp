#include "stdafx.h"
#include "PlayerSkillSwing.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"
#include "SoundManager.h"
#include "Player.h"

PlayerSkillSwing::PlayerSkillSwing(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerSkillSwing")
{
	SetParams(0.2f, 5, 3.0f, 10, 10, false, D3DXVECTOR3(0, 10, 20));
}

PlayerSkillSwing::~PlayerSkillSwing()
{
}

void PlayerSkillSwing::Initialize()
{
	PlayerAction::Initialize();

	GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());

	MeshEffectDesc effectDesc0; 
	effectDesc0.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_Helix_005.X";
	effectDesc0.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Tornado.tga";
	effectDesc0.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_toneido_01.tga";
	effectDesc0.fadeOut = true;
	effectDesc0.lifeTime = 0.5f;
	effectDesc0.endRot = D3DXVECTOR3(0, -360, 0);
	effectDesc0.endScale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	m_pEffect0 = pScene->GetEffectManager()->AddEffect(L"PlayerSkillSwing_Effect0", effectDesc0);

	MeshEffectDesc effectDesc1;
	effectDesc1.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_Helix_008_SM_KKJA.X";
	effectDesc1.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Tornado.tga";
	effectDesc1.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_toneido_01.tga";
	effectDesc1.fadeOut = true;
	effectDesc1.lifeTime = 0.5f;
	effectDesc1.endRot = D3DXVECTOR3(0, -360, 0);
	effectDesc1.endScale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	m_pEffect1 = pScene->GetEffectManager()->AddEffect(L"PlayerSkillSwing_Effect1", effectDesc1);



}

void PlayerSkillSwing::Update()
{
	PlayerAction::Update();
	UpdateAction();

	m_pEffect0->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(0, 0, 10))
	);
	m_pEffect0->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 0, 0)
	);
	m_pEffect0->SetOriginScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));

	m_pEffect1->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(0, 0, 10))
	);
	m_pEffect1->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 0, 0)
	);
	m_pEffect1->SetOriginScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));

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
	m_bPlayAfterImage = false;

	Player * pPlayer = static_cast<Player*>(PLAYER);
	UINT animSet = pPlayer->GetCurAnimationIndex();


	AfterEffectDesc desc;
	desc.animIndex = animSet;
	desc.color = D3DXCOLOR(1, 0, 0, 1);
	desc.lifeTime = 0.5f;
	desc.afterEffectOption = AfterEffectOption::FadeOut | AfterEffectOption::ScaleEffect;
	desc.startScale = 1.1f;
	desc.endScale = 1.0f;
	desc.scaleSpd = 2.0f;

	GameScene* pScene = static_cast<GameScene*>(SCENE);
	m_afterImageIndex = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);
	//GameScene* pScene = static_cast<GameScene*>(SCENE);
	//pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

}

void PlayerSkillSwing::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	std::cout << "실제 인덱스 : " << seqIndex << std::endl;
	if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	case 0:
		if (elapsed >= 0.01f && m_bPlayAfterImage == false)
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
		if (elapsed >= 0.01f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		break;
	case 2:
		if (elapsed >= 0.01f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		break;
	case 3:
		if (elapsed >= 0.01f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		break;
	case 4 :
		if (elapsed >= 0.01f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

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
