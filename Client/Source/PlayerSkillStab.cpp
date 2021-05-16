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

	GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());


	MeshEffectDesc firstActionTrailDesc;
	firstActionTrailDesc.isUVAnim = true;
	firstActionTrailDesc.uvDirection = D3DXVECTOR2(1, 0);
	firstActionTrailDesc.uvSpeed = 0.7f;
	firstActionTrailDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_trailLine_001_SM_CJH.X";
	firstActionTrailDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	firstActionTrailDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	firstActionTrailDesc.lifeTime = 0.5f;

	m_pFirstActionTrail = pScene->GetEffectManager()->AddEffect(L"PlayerSkillStab_FirstActionTrail", firstActionTrailDesc);

	MeshEffectDesc secondActionTrailDesc;
	secondActionTrailDesc.isUVAnim = true;
	secondActionTrailDesc.uvDirection = D3DXVECTOR2(0, -1);
	secondActionTrailDesc.uvSpeed = 1.0f;
	secondActionTrailDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_X-Front_001_SM_CJS.X";
	secondActionTrailDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_toneido_01.tga";
	secondActionTrailDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_toneido_01.tga";
	secondActionTrailDesc.lifeTime = 0.6f;

	//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
	m_pSecondActionTrail = pScene->GetEffectManager()->AddEffect(L"PlayerSkillStab_SecondActionTrail", secondActionTrailDesc);

	MeshEffectDesc thirdActionTrailDesc;
	thirdActionTrailDesc.isUVAnim = true;
	thirdActionTrailDesc.uvDirection = D3DXVECTOR2(0, -1);
	thirdActionTrailDesc.uvSpeed = 1.0f;
	thirdActionTrailDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_X-Front_001_SM_CJS.X";
	thirdActionTrailDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_toneido_01.tga";
	thirdActionTrailDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_toneido_01.tga";
	thirdActionTrailDesc.lifeTime = 0.6f;

	//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
	m_pThridActionTrail = pScene->GetEffectManager()->AddEffect(L"PlayerSkillStab_ThirdActionTrail", thirdActionTrailDesc);


}

void PlayerSkillStab::Update()
{
	PlayerAction::Update();
	UpdateAction();


	m_pFirstActionTrail->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(-3, 5, -2))
	);
	m_pFirstActionTrail->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 150, 193)
	);
	m_pFirstActionTrail->SetOriginScale(D3DXVECTOR3(2, 2, 2));

	m_pSecondActionTrail->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(2, 6, 14))
	);
	m_pSecondActionTrail->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, -180, 0)
	);
	m_pSecondActionTrail->SetOriginScale(D3DXVECTOR3(1.2, 1.2, 1.2));

	m_pThridActionTrail->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(2, 6, 18))
	);
	m_pThridActionTrail->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, -180, 0)
	);
	m_pThridActionTrail->SetOriginScale(D3DXVECTOR3(1.2, 1.2, 1.2));



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

	Player * pPlayer = static_cast<Player*>(PLAYER);
	UINT animSet = pPlayer->GetCurAnimationIndex();
	//pPlayer->SetAnimationSpeed(1.0f);


	AfterEffectDesc desc;
	desc.animIndex = animSet;
	desc.color = D3DXCOLOR(1, 0, 0, 1);
	desc.lifeTime = 0.5f;
	desc.afterEffectOption = AfterEffectOption::FadeOut | AfterEffectOption::ScaleEffect;
	desc.startScale = 1.2f;
	desc.endScale = 1.0f;
	desc.scaleSpd = 2.0f;

	GameScene* pScene = static_cast<GameScene*>(SCENE);
	m_afterImageIndex = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);
	//GameScene* pScene = static_cast<GameScene*>(SCENE);
//	pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);


}

void PlayerSkillStab::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	std::cout << "실제 인덱스 : " << seqIndex << std::endl;
	//if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	case 0:
		if (elapsed >= 0.1f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		if (elapsed >= 0.3f && m_bSendDamage == false)
		{
			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayEffect(L"PlayerSkillStab_FirstActionTrail");

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
				//pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect0");
				//pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect1");
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
			//pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		if (elapsed >= 0.3f && m_bSendDamage == false)
		{
			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayEffect(L"PlayerSkillStab_SecondActionTrail");

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
				//pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect0");
				//pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect1");
				CAMERA->Shake(0.1f, 0.1f, 1.0f);
			}
			m_bSendDamage = true;
		}
		break;
	case 2:
		if (elapsed >= 0.01f)
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			UINT animSet = pPlayer->GetCurAnimationIndex();

			AfterEffectDesc desc;
			desc.animIndex = animSet;
			desc.animPosition = pPlayer->GetCurAnimationPosition();
			desc.color = D3DXCOLOR(1, 1, 1, 1.f);
			desc.lifeTime = 0.3f;
			desc.afterEffectOption = AfterEffectOption::FadeOut;

			GameScene* pScene = static_cast<GameScene*>(SCENE);
			auto index = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);
			//GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(index);

		}
		if (elapsed >= 0.1f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		/*if (elapsed >= 0.7f)
		{
			m_bSendDamage = true;
		}*/
		if (elapsed >= 0.3f && m_bSendDamage == false)
		{
			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayEffect(L"PlayerSkillStab_ThirdActionTrail");

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
				//pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect0");
				//pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect1");
				CAMERA->Shake(0.1f, 0.1f, 1.0f);
			}
			m_bSendDamage = true;
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
