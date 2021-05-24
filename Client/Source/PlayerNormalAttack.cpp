#include "stdafx.h"
#include "PlayerNormalAttack.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"
#include "SoundManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Equipment.h"
#include "PlayerBuffInfo.h"
#include "PlayerStatusData.h"
#include "PlayerController.h"
#include "PlayerEquipData.h"


PlayerNormalAttack::PlayerNormalAttack(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update , pPlayer, pPlayerController, L"PlayerNormalAttack")
{
	SetParams(0.2f, 3, 0, 10, 10, false, D3DXVECTOR3(0, 10, 20));
}

PlayerNormalAttack::~PlayerNormalAttack()
{
}

void PlayerNormalAttack::Initialize()
{
	PlayerAction::Initialize();

	m_pPlayerStatusData = static_cast<PlayerStatusData*>(ENGINE->GetScriptableData(L"PlayerStatusData"));
	m_pPlayerBuffInfo = static_cast<PlayerBuffInfo*>(ENGINE->GetScriptableData(L"PlayerBuffInfo"));
	m_pPlayerEquipData = static_cast<PlayerEquipData*>(ENGINE->GetScriptableData(L"PlayerEquipData"));

	/* Add Effect NormalAttack */
	MeshEffectDesc meshEffectDesc;
	meshEffectDesc.isUVAnim = true;
	meshEffectDesc.uvDirection = D3DXVECTOR2(1, 0);
	meshEffectDesc.uvSpeed = 0.7f;
	meshEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_trailLine_001_SM_CJH.X";
	meshEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH_Color3.png";
	meshEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	meshEffectDesc.lifeTime = 0.5f;

	GameScene* pScene = static_cast<GameScene*>( GetGameObject()->GetScene());
	m_pSwordTrail = pScene->GetEffectManager()->AddEffect(L"PlayerNormalAttack_SwordTrailEffect", meshEffectDesc);
	m_pSwordTrail->SetRenderEffectOption(RenderEffectOption::Bloom);
	//m_pSwordTrail->SetRenderEffectOption(PostRenderOption::Bloom);

	/* Add Effect NormalAttack */
	MeshEffectDesc meshEffectDesc_Second;
	meshEffectDesc_Second.isUVAnim = true;
	meshEffectDesc_Second.uvDirection = D3DXVECTOR2(1, 0);
	meshEffectDesc_Second.uvSpeed = 0.7f;
	meshEffectDesc_Second.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_trailLine_001_SM_CJH.X";
	meshEffectDesc_Second.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH_Color3.png";
	meshEffectDesc_Second.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	meshEffectDesc_Second.lifeTime = 0.5f;

	//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
	m_pSwordTrail_Second = pScene->GetEffectManager()->AddEffect(L"PlayerNormalAttack_SwordTrailEffect_Second", meshEffectDesc_Second);
	m_pSwordTrail_Second->SetRenderEffectOption(RenderEffectOption::Bloom);

	MeshEffectDesc meshEffectDesc_Third;
	meshEffectDesc_Third.isUVAnim = true;
	meshEffectDesc_Third.uvDirection = D3DXVECTOR2(0, -1);
	meshEffectDesc_Third.uvSpeed = 1.0f;
	meshEffectDesc_Third.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_X-Front_001_SM_CJS.X";
	meshEffectDesc_Third.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_toneido_01.tga";
	meshEffectDesc_Third.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_toneido_01.tga";
	meshEffectDesc_Third.lifeTime = 0.6f;


	//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
	m_pSwordTrail_Third = pScene->GetEffectManager()->AddEffect(L"PlayerNormalAttack_SwordTrailEffect_Third", meshEffectDesc_Third);

	MeshEffectDesc stabEffectDesc;
	stabEffectDesc.isUVAnim = true;
	stabEffectDesc.uvDirection = D3DXVECTOR2(1, 0);
	stabEffectDesc.uvSpeed = 1.0f;
	stabEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_TwistLine_001.X";
	stabEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_IceWhipDecal_001_Tex_PHS_Color.tga";
	stabEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_IceWhipDecal_001_Tex_PHS.tga";
	stabEffectDesc.lifeTime = 1.0f;
	stabEffectDesc.fadeOut = true;
	stabEffectDesc.endRot = D3DXVECTOR3(-360, 0, 0);


	m_pStabEffect = pScene->GetEffectManager()->AddEffect(L"PlayerNormalAttack_StabEffect", stabEffectDesc);
	m_pStabEffect->SetRenderEffectOption(RenderEffectOption::Bloom);
}

void PlayerNormalAttack::Update()
{
	PlayerAction::Update();
	UpdateAction();

	m_pSwordTrail->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(0, 8, 3))
	);
	m_pSwordTrail->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 240, 0)
	);
	m_pSwordTrail->SetOriginScale(D3DXVECTOR3(2, 2, 2));

	m_pSwordTrail_Second->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(-3, 5, -2))
	);
	m_pSwordTrail_Second->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 150, 193)
	);
	m_pSwordTrail_Second->SetOriginScale(D3DXVECTOR3(2, 2, 2));

	m_pSwordTrail_Third->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(2, 6, 14))
	);
	m_pSwordTrail_Third->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, -180, 0)
	);
	m_pSwordTrail_Third->SetOriginScale(D3DXVECTOR3(1.2, 1.2, 1.2));

	m_pStabEffect->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(-0.24, 7.76, 12.48))
	);
	m_pStabEffect->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, -95.6, 0)
	);
	m_pStabEffect->SetOriginScale(D3DXVECTOR3(0.5, 0.5, 0.5));

}

void PlayerNormalAttack::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerNormalAttack::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerNormalAttack::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerNormalAttack::OnHitOthers(Collider * other)
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

void PlayerNormalAttack::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage[0] = false;
	m_bSendDamage[1] = false;
	m_bSendDamage[2] = false;
	m_bPlayerAfterImage = false;

	Player * pPlayer = static_cast<Player*>(PLAYER);
	pPlayer->SetAnimationSpeed(1.0f);
	std::cout << "Seq Index : " << m_seqIndex << std::endl;
}

void PlayerNormalAttack::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	std::cout << "���� �ε��� : " << seqIndex << std::endl;
	//if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	case 0:
		if (elapsed >= 0.01f && m_pPlayerBuffInfo->bBuff)
		{


			Player* pPlayer = static_cast<Player*>(PLAYER);

			Equipment * pWeapon = static_cast<Equipment*>(pPlayer->GetWeapon());
			WeaponAfterEffectDesc weaponDesc;
			weaponDesc.lifeTime = 0.4f;
			weaponDesc.worldMat = pWeapon->GetWorldMatrix();
			weaponDesc.pOrigin = pWeapon;
			weaponDesc.afterEffectOption = AfterEffectOption::FadeOut;
			weaponDesc.color = D3DXCOLOR(1, 1, 0, 1);
			weaponDesc.fadeOutSpd = 2.0f;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayerWeaponAffterEffect(weaponDesc);
		}
		if (elapsed >= 0.3f && m_bSendDamage[0] == false)
		{
			m_bSendDamage[0] = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);

			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerNormalAttack_First", L"Lups_SwordThrowing5.mp3", desc);

			SoundDesc desc2;
			desc2.channelMode = FMOD_LOOP_OFF;
			desc2.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc2.volume = 1;
			SOUND->PlaySound("Attack_Voice_1", L"Attack_Voice_1.wav", desc2);


			pScene->GetEffectManager()->PlayEffect(L"PlayerNormalAttack_SwordTrailEffect");

			for (auto& obj : m_hitEnemies)
			{
				if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
					return;
				if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
				{
					continue;
				}

				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				float damage = m_damageScale[0] * (m_pPlayerStatusData->power + m_pPlayerEquipData->GetPower() + m_pPlayerBuffInfo->GetBuffAtk());
				//float damage = m_damageScale[0] * m_pPlayerStatusData->power;
				float minDamage = damage * 0.7f;
				float maxDamage = damage * 1.3f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				float playerCritical = m_pPlayerStatusData->critical;
				playerCritical = m_pPlayerBuffInfo->bBuff ? playerCritical * 3.0f : playerCritical;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
				if (isCritical)
				{
					enemy->PlayHitAnimation(EEnemyHitType::CriticalRight);
				}
				else
				{
					enemy->PlayHitAnimation(EEnemyHitType::SwordRight);
				}
				std::cout << "Do First" << std::endl;
				if (isCritical)
				{
					CAMERA->Shake(0.3f, 0.3f, 1.0f);
				}
				else
				{
					CAMERA->Shake(0.1f, 0.1f, 1.0f);
				}
				break;
			}
		}
		break;
	case 1:
		if (elapsed >= 0.01f && m_pPlayerBuffInfo->bBuff)
		{


			Player* pPlayer = static_cast<Player*>(PLAYER);

			Equipment * pWeapon = static_cast<Equipment*>(pPlayer->GetWeapon());
			WeaponAfterEffectDesc weaponDesc;
			weaponDesc.lifeTime = 0.4f;
			weaponDesc.worldMat = pWeapon->GetWorldMatrix();
			weaponDesc.pOrigin = pWeapon;
			weaponDesc.afterEffectOption = AfterEffectOption::FadeOut;
			weaponDesc.color = D3DXCOLOR(1, 1, 0, 1);
			weaponDesc.fadeOutSpd = 2.0f;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayerWeaponAffterEffect(weaponDesc);
		}
		if (elapsed >= 0.01f && m_bPlayerAfterImage == false && m_pPlayerBuffInfo->bBuff)
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			UINT animSet = pPlayer->GetCurAnimationIndex();
			pPlayer->SetAnimationSpeed(1.5f);
			AfterEffectDesc desc;
			desc.animIndex = animSet;
			desc.animPosition = pPlayer->GetCurAnimationPosition();
			desc.color = D3DXCOLOR(1, 0, 0, 1);
			desc.lifeTime = 0.5f;
			desc.afterEffectOption = AfterEffectOption::FadeOut | AfterEffectOption::ScaleEffect;
			desc.startScale = 1.2f;
			desc.endScale = 1.0f;
			desc.scaleSpd = 2.0f;

			GameScene* pScene = static_cast<GameScene*>(SCENE);
			int index = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);
			//GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(index);

			m_bPlayerAfterImage = true;
		}
		if (elapsed >= 0.3f && m_bSendDamage[0] == false)
		{
			m_bSendDamage[0] = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerNormalAttack_Second", L"Lups_SwordThrowing6.mp3", desc);

			SoundDesc desc2;
			desc2.channelMode = FMOD_LOOP_OFF;
			desc2.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc2.volume = 1;
			SOUND->PlaySound("Attack_Voice_2", L"Attack_Voice_2.wav", desc2);

			pScene->GetEffectManager()->PlayEffect(L"PlayerNormalAttack_SwordTrailEffect_Second");
			for (auto& obj : m_hitEnemies)
			{
				if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
					return;
				if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
				{
					continue;
				}

				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				float damage = m_damageScale[1] * (m_pPlayerStatusData->power + m_pPlayerEquipData->GetPower() + m_pPlayerBuffInfo->GetBuffAtk());
				float minDamage = damage * 0.7f;
				float maxDamage = damage * 1.3f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				float playerCritical = m_pPlayerStatusData->critical;
				playerCritical = m_pPlayerBuffInfo->bBuff ? playerCritical * 3.0f : playerCritical;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
				if (isCritical)
				{
					enemy->PlayHitAnimation(EEnemyHitType::CriticalLeft);
				}
				else
				{
					enemy->PlayHitAnimation(EEnemyHitType::SwordLeft);
				}
				std::cout << "Do First" << std::endl;
				if (isCritical)
				{
					CAMERA->Shake(0.3f, 0.3f, 1.0f);
				}
				else
				{
					CAMERA->Shake(0.1f, 0.1f, 1.0f);
				}
			}
		}
		break;
	case 2:
		if (elapsed >= 0.1f)
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			auto weapon = pPlayer->GetWeapon();
			weapon->SetRenderEffectOption(RenderEffectOption::RimLight);
			weapon->SetRimWidth(1.0f);
			weapon->SetRimColor(D3DXCOLOR(1, 1.0f, 0.0f, 1));
		}
		if (elapsed >= 0.01f && m_pPlayerBuffInfo->bBuff)
		{


			Player* pPlayer = static_cast<Player*>(PLAYER);

			Equipment * pWeapon = static_cast<Equipment*>(pPlayer->GetWeapon());
			WeaponAfterEffectDesc weaponDesc;
			weaponDesc.lifeTime = 0.4f;
			weaponDesc.worldMat = pWeapon->GetWorldMatrix();
			weaponDesc.pOrigin = pWeapon;
			weaponDesc.afterEffectOption = AfterEffectOption::FadeOut;
			weaponDesc.color = D3DXCOLOR(1, 1, 0, 1);
			weaponDesc.fadeOutSpd = 2.0f;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayerWeaponAffterEffect(weaponDesc);
		}
		if (elapsed >= 0.01f && m_bPlayerAfterImage == false && m_pPlayerBuffInfo->bBuff)
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			pPlayer->SetAnimationSpeed(1.5f);
			UINT animSet = pPlayer->GetCurAnimationIndex();

			AfterEffectDesc desc;
			desc.animIndex = animSet;
			desc.animPosition = pPlayer->GetCurAnimationPosition();
			desc.color = D3DXCOLOR(1, 1, 0, 1);
			desc.lifeTime = 0.5f;
			desc.afterEffectOption = AfterEffectOption::FadeOut | AfterEffectOption::ScaleEffect;
			desc.startScale = 1.2f;
			desc.endScale = 1.0f;
			desc.scaleSpd = 2.0f;

			GameScene* pScene = static_cast<GameScene*>(SCENE);
			int index = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);
			//GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(index);
			m_bPlayerAfterImage = true;
		}
		if (elapsed >= 0.3f && m_bSendDamage[0] == false)
		{
			

			m_bSendDamage[0] = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerNormalAttack_Third", L"Lups_SwordThrowing0.mp3", desc);

			SoundDesc desc2;
			desc2.channelMode = FMOD_LOOP_OFF;
			desc2.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc2.volume = 1;
			SOUND->PlaySound("Attack_Long_Voice_0", L"Attack_Long_Voice_0.wav", desc2);


			pScene->GetEffectManager()->PlayEffect(L"PlayerNormalAttack_StabEffect");
			for (auto& obj : m_hitEnemies)
			{
				if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
					return;
				if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
				{
					continue;
				}

				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				float damage = m_damageScale[2] * (m_pPlayerStatusData->power + m_pPlayerEquipData->GetPower() + m_pPlayerBuffInfo->GetBuffAtk());
				float minDamage = damage * 0.7f;
				float maxDamage = damage * 1.3f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				float playerCritical = m_pPlayerStatusData->critical;
				playerCritical = m_pPlayerBuffInfo->bBuff ? playerCritical * 3.0f : playerCritical;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
				if (isCritical)
				{
					enemy->PlayHitAnimation(EEnemyHitType::CriticalRight);
				}
				else
				{
					enemy->PlayHitAnimation(EEnemyHitType::SwordRight);
				}
				std::cout << "Do First" << std::endl;
				if (isCritical)
				{
					CAMERA->Shake(0.3f, 0.3f, 1.0f);
				}
				else
				{
					CAMERA->Shake(0.1f, 0.1f, 1.0f);
				}
			}
		}
		if (elapsed >= 0.4f && m_bSendDamage[1] == false)
		{
			m_bSendDamage[1] = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);

			for (auto& obj : m_hitEnemies)
			{
				if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
					return;
				if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
				{
					continue;
				}

				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				float damage = m_damageScale[2] * (m_pPlayerStatusData->power + m_pPlayerEquipData->GetPower() + m_pPlayerBuffInfo->GetBuffAtk());
				float minDamage = damage * 0.7f;
				float maxDamage = damage * 1.3f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				float playerCritical = m_pPlayerStatusData->critical;
				playerCritical = m_pPlayerBuffInfo->bBuff ? playerCritical * 3.0f : playerCritical;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
				if (isCritical)
				{
					enemy->PlayHitAnimation(EEnemyHitType::CriticalRight);
				}
				else
				{
					enemy->PlayHitAnimation(EEnemyHitType::SwordRight);
				}
				if (isCritical)
				{
					CAMERA->Shake(0.3f, 0.3f, 1.0f);
				}
				else
				{
					CAMERA->Shake(0.1f, 0.1f, 1.0f);
				}
			}
		}
		if (elapsed >= 0.5f && m_bSendDamage[2] == false)
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			auto weapon = pPlayer->GetWeapon();
			weapon->SetRimWidth(0.0f);

			m_bSendDamage[2] = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);

			for (auto& obj : m_hitEnemies)
			{
				if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
					return;
				if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
				{
					continue;
				}

				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				float damage = m_damageScale[2] * (m_pPlayerStatusData->power + m_pPlayerEquipData->GetPower() + m_pPlayerBuffInfo->GetBuffAtk());
				float minDamage = damage * 0.7f;
				float maxDamage = damage * 1.3f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				float playerCritical = m_pPlayerStatusData->critical;
				playerCritical = m_pPlayerBuffInfo->bBuff ? playerCritical * 3.0f : playerCritical;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
				if (isCritical)
				{
					enemy->PlayHitAnimation(EEnemyHitType::CriticalRight);
				}
				else
				{
					enemy->PlayHitAnimation(EEnemyHitType::SwordRight);
				}
				if (isCritical)
				{
					CAMERA->Shake(0.3f, 0.3f, 1.0f);
				}
				else
				{
					CAMERA->Shake(0.1f, 0.1f, 1.0f);
				}
			}
		}
		break;
	}
}

void PlayerNormalAttack::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
}

UINT PlayerNormalAttack::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerNormalAttack::GetIdleAnimIndex() const
{
	return 89;
}

void PlayerNormalAttack::UpdateAction()
{
	PlayerController* pController = PLAYER->GetComponent<PlayerController>();
	if (pController->IsMovable() == false)
		return;
	if (MOUSE->Down(0))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerNormalAttack * PlayerNormalAttack::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerNormalAttack * com = new PlayerNormalAttack(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
