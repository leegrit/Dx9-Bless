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
#include "UpdateDispatcher.h"
#include "Equipment.h"
#include "PlayerStatusData.h"
#include "PlayerBuffInfo.h"
#include "Enemy.h"
#include "PlayerSkillInfo.h"
#include "PlayerEquipData.h"


PlayerSkillSwing::PlayerSkillSwing(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerSkillSwing")
{
	SetParams(0.2f, 1, 3.0f, 10, 10, false, D3DXVECTOR3(0, 10, 20));
	SetManaDemand(40);
}

PlayerSkillSwing::~PlayerSkillSwing()
{
}

void PlayerSkillSwing::Initialize()
{
	PlayerAction::Initialize();

	m_pPlayerStatusData = static_cast<PlayerStatusData*>(ENGINE->GetScriptableData(L"PlayerStatusData"));
	m_pPlayerBuffInfo = static_cast<PlayerBuffInfo*>(ENGINE->GetScriptableData(L"PlayerBuffInfo"));
	m_pPlayerEquipData = static_cast<PlayerEquipData*>(ENGINE->GetScriptableData(L"PlayerEquipData"));

	assert(m_pPlayerStatusData);

	GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());

	MeshEffectDesc firstActionTrailDesc;
	firstActionTrailDesc.isUVAnim = true;
	firstActionTrailDesc.uvDirection = D3DXVECTOR2(1, 0);
	firstActionTrailDesc.uvSpeed = 0.7f;
	firstActionTrailDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_trailLine_001_SM_CJH.X";
	firstActionTrailDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	firstActionTrailDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	firstActionTrailDesc.lifeTime = 0.5f;

	//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
	m_pFirstActionTrail = pScene->GetEffectManager()->AddEffect(L"PlayerSkillSwing_FirstActionTrail", firstActionTrailDesc);

	MeshEffectDesc secondActionTrailDesc;
	secondActionTrailDesc.isUVAnim = true;
	secondActionTrailDesc.uvDirection = D3DXVECTOR2(1, 0);
	secondActionTrailDesc.uvSpeed = 0.7f;
	secondActionTrailDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_trailLine_001_SM_CJH.X";
	secondActionTrailDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	secondActionTrailDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	secondActionTrailDesc.lifeTime = 0.5f;

	//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
	m_pSecondActionTrail = pScene->GetEffectManager()->AddEffect(L"PlayerSkillSwing_SecondActionTrail", secondActionTrailDesc);




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

	MeshEffectDesc FourthActionTrailDesc;
	FourthActionTrailDesc.isUVAnim = true;
	FourthActionTrailDesc.uvDirection = D3DXVECTOR2(1, 0);
	FourthActionTrailDesc.uvSpeed = 0.7f;
	FourthActionTrailDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_trailLine_001_SM_CJH.X";
	FourthActionTrailDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	FourthActionTrailDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	FourthActionTrailDesc.lifeTime = 0.5f;

	//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
	m_pFourthActionTrail = pScene->GetEffectManager()->AddEffect(L"PlayerSkillSwing_FourthActionTrail", FourthActionTrailDesc);

	MeshEffectDesc swingEffectDesc;
	swingEffectDesc.isUVAnim = true;
	swingEffectDesc.uvDirection = D3DXVECTOR2(0, 1);
	swingEffectDesc.uvSpeed = 1.0f;
	swingEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_landburncyclone.X";
	//swingEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_FireTile8.tga";
	//swingEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_003_TEX_CJH.tga";
	swingEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_trail_015_TEX_CJH_Color.tga";
	swingEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_trail_015_TEX_CJH.tga";

	swingEffectDesc.lifeTime = 1.0f;
	swingEffectDesc.fadeOut = true;
	swingEffectDesc.fadeOutFactor = 0.5f;
	swingEffectDesc.fadeIn = false;
	//swingEffectDesc.fadeInFactor = 0.2f;
	swingEffectDesc.endRot = D3DXVECTOR3(0, 360, 0);
	swingEffectDesc.endScale = D3DXVECTOR3(0, 0, 0);

	m_pSwingEffect = pScene->GetEffectManager()->AddEffect(L"PlayerSkillSwing_SwingEffect", swingEffectDesc);
	m_pSwingEffect->SetRenderEffectOption(RenderEffectOption::Bloom);
}

void PlayerSkillSwing::Update()
{
	PlayerAction::Update();
	UpdateAction();

	m_pFirstActionTrail->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(0, 8, 3))
	);
	m_pFirstActionTrail->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 240, 0)
	);
	m_pFirstActionTrail->SetOriginScale(D3DXVECTOR3(2, 2, 2));

	m_pSecondActionTrail->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(-3, 5, -2))
	);
	m_pSecondActionTrail->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 150, 193)
	);
	m_pSecondActionTrail->SetOriginScale(D3DXVECTOR3(2, 2, 2));


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
	

	m_pSwingEffect->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(0, 0, 0))
	);
	m_pSwingEffect->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 0, 0)
	);
	m_pSwingEffect->SetOriginScale(D3DXVECTOR3(1, 0.3, 1));
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
	m_bFinalSendDamage[0] = false;
	m_bFinalSendDamage[1] = false;
	m_bFinalSendDamage[2] = false;
	m_bFinalSendDamage[3] = false;
	m_bFinalAfterImage[0] = false;
	m_bFinalAfterImage[1] = false;
	m_bFinalAfterImage[2] = false;
	m_bFinalAfterImage[3] = false;

	Player * pPlayer = static_cast<Player*>(PLAYER);
	UINT animSet = pPlayer->GetCurAnimationIndex();
	pPlayer->SetAnimationSpeed(1.0f);


	////AfterEffectDesc desc;
	////desc.animIndex = animSet;
	////desc.color = D3DXCOLOR(1, 0, 0, 1);
	////desc.lifeTime = 0.5f;
	////desc.afterEffectOption = AfterEffectOption::FadeOut | AfterEffectOption::ScaleEffect;
	////desc.startScale = 1.2f;
	////desc.endScale = 1.0f;
	////desc.scaleSpd = 2.0f;

	////GameScene* pScene = static_cast<GameScene*>(SCENE);
	////m_afterImageIndex = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);
	//////GameScene* pScene = static_cast<GameScene*>(SCENE);
	////pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);


}

void PlayerSkillSwing::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	std::cout << "실제 인덱스 : " << seqIndex << std::endl;
	//if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	//case 0:
	//	if (elapsed >= 0.01f && m_pPlayerBuffInfo->bBuff)
	//	{

	//		Player* pPlayer = static_cast<Player*>(PLAYER);

	//		Equipment * pWeapon = static_cast<Equipment*>(pPlayer->GetWeapon());
	//		WeaponAfterEffectDesc weaponDesc;
	//		weaponDesc.lifeTime = 0.4f;
	//		weaponDesc.worldMat = pWeapon->GetWorldMatrix();
	//		weaponDesc.pOrigin = pWeapon;
	//		weaponDesc.afterEffectOption = AfterEffectOption::FadeOut;
	//		weaponDesc.color = D3DXCOLOR(1, 1, 0, 1);
	//		weaponDesc.fadeOutSpd = 2.0f;
	//		GameScene* pScene = static_cast<GameScene*>(SCENE);
	//		pScene->GetEffectManager()->PlayerWeaponAffterEffect(weaponDesc);

	//	}
	//	if (elapsed >= 0.01f && m_bPlayAfterImage == false && m_pPlayerBuffInfo->bBuff)
	//	{
	//		Player * pPlayer = static_cast<Player*>(PLAYER);
	//		UINT animSet = pPlayer->GetCurAnimationIndex();
	//		//pPlayer->SetAnimationSpeed(1.5f);
	//		AfterEffectDesc desc;
	//		desc.animIndex = animSet;
	//		desc.animPosition = pPlayer->GetCurAnimationPosition();
	//		desc.color = D3DXCOLOR(1, 0, 0, 1);
	//		desc.lifeTime = 0.5f;
	//		desc.afterEffectOption = AfterEffectOption::FadeOut | AfterEffectOption::ScaleEffect;
	//		desc.startScale = 1.2f;
	//		desc.endScale = 1.0f;
	//		desc.scaleSpd = 2.0f;

	//		GameScene* pScene = static_cast<GameScene*>(SCENE);
	//		int index = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);
	//		//GameScene* pScene = static_cast<GameScene*>(SCENE);
	//		pScene->GetEffectManager()->PlayAffterEffect(index);

	//		m_bPlayAfterImage = true;
	//	}
	//	if (elapsed >= 0.3f && m_bSendDamage == false)
	//	{
	//		SoundDesc desc;
	//		desc.channelMode = FMOD_LOOP_OFF;
	//		desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	//		desc.volume = 1;
	//		SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
	//		GameScene* pScene = static_cast<GameScene*>(SCENE);

	//		pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_FirstActionTrail");

	//		for (auto& obj : m_hitEnemies)
	//		{
	//			GameScene* pScene = static_cast<GameScene*>(SCENE);
	//			if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
	//				return;
	//			if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
	//			{
	//				continue;
	//			}

	//			Enemy* enemy = dynamic_cast<Enemy*>(obj);

	//			float damage = m_damageScale[0] * m_pPlayerStatusData->power;
	//			float minDamage = damage * 0.5f;
	//			float maxDamage = damage * 1.5f;
	//			damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
	//			float critical = DxHelper::GetRandomFloat(0, 1);
	//			bool isCritical = false;
	//			float playerCritical = m_pPlayerStatusData->critical;
	//			playerCritical = m_pPlayerBuffInfo->bBuff ? playerCritical * 3.0f : playerCritical;
	//			if (critical < m_pPlayerStatusData->critical)
	//			{
	//				isCritical = true;
	//				damage *= 2.0f;
	//			}

	//			enemy->SendDamage(GetGameObject(), damage, isCritical);
	//			enemy->PlayHitAnimation(EEnemyHitType::SwordRight);
	//			if (isCritical)
	//			{
	//				CAMERA->Shake(0.3f, 0.3f, 1.0f);
	//			}
	//			else
	//			{
	//				CAMERA->Shake(0.1f, 0.1f, 1.0f);
	//			}
	//			
	//		}
	//		m_bSendDamage = true;
	//	}
	//	break;
	//case 0:
	//	if (elapsed >= 0.01f && m_pPlayerBuffInfo->bBuff)
	//	{
	//		Player* pPlayer = static_cast<Player*>(PLAYER);

	//		Equipment * pWeapon = static_cast<Equipment*>(pPlayer->GetWeapon());
	//		WeaponAfterEffectDesc weaponDesc;
	//		weaponDesc.lifeTime = 0.4f;
	//		weaponDesc.worldMat = pWeapon->GetWorldMatrix();
	//		weaponDesc.pOrigin = pWeapon;
	//		weaponDesc.afterEffectOption = AfterEffectOption::FadeOut;
	//		weaponDesc.color = D3DXCOLOR(1, 1, 0, 1);
	//		weaponDesc.fadeOutSpd = 2.0f;
	//		GameScene* pScene = static_cast<GameScene*>(SCENE);
	//		pScene->GetEffectManager()->PlayerWeaponAffterEffect(weaponDesc);
	//	}
	//	if (elapsed >= 0.01f && m_bPlayAfterImage == false && m_pPlayerBuffInfo->bBuff)
	//	{
	//		Player * pPlayer = static_cast<Player*>(PLAYER);
	//		UINT animSet = pPlayer->GetCurAnimationIndex();
	//		//pPlayer->SetAnimationSpeed(1.5f);
	//		AfterEffectDesc desc;
	//		desc.animIndex = animSet;
	//		desc.animPosition = pPlayer->GetCurAnimationPosition();
	//		desc.color = D3DXCOLOR(1, 0, 0, 1);
	//		desc.lifeTime = 0.5f;
	//		desc.afterEffectOption = AfterEffectOption::FadeOut | AfterEffectOption::ScaleEffect;
	//		desc.startScale = 1.2f;
	//		desc.endScale = 1.0f;
	//		desc.scaleSpd = 2.0f;

	//		GameScene* pScene = static_cast<GameScene*>(SCENE);
	//		int index = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);
	//		//GameScene* pScene = static_cast<GameScene*>(SCENE);
	//		pScene->GetEffectManager()->PlayAffterEffect(index);

	//		m_bPlayAfterImage = true;
	//	}
	//	if (elapsed >= 0.3f && m_bSendDamage == false)
	//	{
	//		SoundDesc desc;
	//		desc.channelMode = FMOD_LOOP_OFF;
	//		desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	//		desc.volume = 1;
	//		SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
	//		GameScene* pScene = static_cast<GameScene*>(SCENE);

	//		pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_SecondActionTrail");

	//		for (auto& obj : m_hitEnemies)
	//		{
	//			GameScene* pScene = static_cast<GameScene*>(SCENE);
	//			if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
	//				return;
	//			if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
	//			{
	//				continue;
	//			}

	//			Enemy* enemy = dynamic_cast<Enemy*>(obj);

	//			float damage = m_damageScale[1] * m_pPlayerStatusData->power;
	//			float minDamage = damage * 0.5f;
	//			float maxDamage = damage * 1.5f;
	//			damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
	//			float critical = DxHelper::GetRandomFloat(0, 1);
	//			bool isCritical = false;
	//			float playerCritical = m_pPlayerStatusData->critical;
	//			playerCritical = m_pPlayerBuffInfo->bBuff ? playerCritical * 3.0f : playerCritical;
	//			if (critical < m_pPlayerStatusData->critical)
	//			{
	//				isCritical = true;
	//				damage *= 2.0f;
	//			}

	//			enemy->SendDamage(GetGameObject(), damage, isCritical);
	//			enemy->PlayHitAnimation(EEnemyHitType::SwordLeft);

	//			if (isCritical)
	//			{
	//				CAMERA->Shake(0.3f, 0.3f, 1.0f);
	//			}
	//			else
	//			{
	//				CAMERA->Shake(0.1f, 0.1f, 1.0f);
	//			}
	//		}
	//		m_bSendDamage = true;
	//	}
	//	break;
	case 0:
		/*if (elapsed >= 0.01f && m_pPlayerBuffInfo->bBuff)
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
		if (elapsed >= 0.01f && m_bPlayAfterImage == false && m_pPlayerBuffInfo->bBuff)
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			pPlayer->SetAnimationSpeed(0.4f);
			UINT animSet = pPlayer->GetCurAnimationIndex();

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
			m_bPlayAfterImage = true;

		}
		if (elapsed >= 0.1f && m_pPlayerBuffInfo->bBuff &&
			elapsed < 1.5f)
		{
			m_afterImageDuration += TIMER->getDeltaTime();
			if (m_afterImageDuration >= m_afterImageDelay)
			{
				m_afterImageDuration = 0;
				Player * pPlayer = static_cast<Player*>(PLAYER);
				//pPlayer->SetAnimationSpeed(1.5f);
				UINT animSet = pPlayer->GetCurAnimationIndex();

				AfterEffectDesc desc;
				desc.animIndex = animSet;
				desc.animPosition = pPlayer->GetCurAnimationPosition();
				desc.color = D3DXCOLOR(1, 1, 1, 1);
				desc.lifeTime = 0.5f;
				desc.afterEffectOption = AfterEffectOption::FadeOut;

				GameScene* pScene = static_cast<GameScene*>(SCENE);
				int index = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);
				//GameScene* pScene = static_cast<GameScene*>(SCENE);
				pScene->GetEffectManager()->PlayAffterEffect(index);
				//m_bFinalAfterImage[0] = true;
			}
		}*/
		if (elapsed >= 0.1f)
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			auto weapon = pPlayer->GetWeapon();
			weapon->SetRenderEffectOption(RenderEffectOption::RimLight);
			weapon->SetRimWidth(1.0f);
			weapon->SetRimColor(D3DXCOLOR(1, 1.0f, 0.0f, 1));

		}
		if (elapsed >= 1.0f && m_bPlayAfterImage == false)
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			//pPlayer->SetAnimationSpeed(0.4f);
			UINT animSet = pPlayer->GetCurAnimationIndex();

			//AfterEffectDesc desc;
			//desc.animIndex = animSet;
			//desc.animPosition = pPlayer->GetCurAnimationPosition();
			//desc.color = D3DXCOLOR(0.6, 0.6, 1, 1);
			//desc.lifeTime = 0.3f;
			//desc.afterEffectOption = AfterEffectOption::FadeOut | AfterEffectOption::ScaleEffect;
			//desc.startScale = 1.3f;
			//desc.endScale = 1.0f;
			//desc.scaleSpd = 1.5f;

			//GameScene* pScene = static_cast<GameScene*>(SCENE);
			//int index = pScene->GetEffectManager()->AddAfterEffect(desc, nullptr);
			////GameScene* pScene = static_cast<GameScene*>(SCENE);
			//pScene->GetEffectManager()->PlayAffterEffect(index);
			m_bPlayAfterImage = true;

			//PLAYER->SetRenderEffectOption(RenderEffectOption::RimLight);
			//PLAYER->SetRimColor(D3DXCOLOR(0.6, 0.6, 1, 1));
			//PLAYER->SetRimWidth(1.0);
		}
		if (elapsed >= 0.7f && m_bSendDamage == false)
		{
			m_bSendDamage = true;
			Player * pPlayer = static_cast<Player*>(PLAYER);
			//pPlayer->SetAnimationSpeed(0.3f);

			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
			SOUND->PlaySound("PlayerSkillSwing_Fire", L"FireWall.mp3", desc);
			GameScene* pScene = static_cast<GameScene*>(SCENE);

			//pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect0");
			//pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect1");
			pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_SwingEffect");
			for (auto& obj : m_hitEnemies)
			{
				GameScene* pScene = static_cast<GameScene*>(SCENE);


				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				float damage = m_damageScale[0] * (m_pPlayerStatusData->power + m_pPlayerEquipData->GetPower() + m_pPlayerBuffInfo->GetBuffAtk());
				float minDamage = damage * 0.5f;
				float maxDamage = damage * 1.5f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				enemy->PlayHitAnimation(EEnemyHitType::SwordLeft);

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
		if (elapsed >= 0.8f && m_bFinalSendDamage[0] == false)
		{
			m_bFinalSendDamage[0] = true;

			GameScene* pScene = static_cast<GameScene*>(SCENE);
			for (auto& obj : m_hitEnemies)
			{
				GameScene* pScene = static_cast<GameScene*>(SCENE);


				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				float damage = m_damageScale[0] * (m_pPlayerStatusData->power + m_pPlayerEquipData->GetPower() + m_pPlayerBuffInfo->GetBuffAtk());
				float minDamage = damage * 0.5f;
				float maxDamage = damage * 1.5f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				enemy->PlayHitAnimation(EEnemyHitType::SwordLeft);

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
		if (elapsed >= 0.9f && m_bFinalSendDamage[1] == false)
		{
			m_bFinalSendDamage[1] = true;

			GameScene* pScene = static_cast<GameScene*>(SCENE);
			for (auto& obj : m_hitEnemies)
			{
				GameScene* pScene = static_cast<GameScene*>(SCENE);


				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				float damage = m_damageScale[0] * (m_pPlayerStatusData->power + m_pPlayerEquipData->GetPower() + m_pPlayerBuffInfo->GetBuffAtk());
				float minDamage = damage * 0.5f;
				float maxDamage = damage * 1.5f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				enemy->PlayHitAnimation(EEnemyHitType::SwordLeft);

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
		if (elapsed >= 1.0f && m_bFinalSendDamage[2] == false)
		{
			m_bFinalSendDamage[2] = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			for (auto& obj : m_hitEnemies)
			{


				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				float damage = m_damageScale[0] * (m_pPlayerStatusData->power + m_pPlayerEquipData->GetPower() + m_pPlayerBuffInfo->GetBuffAtk());
				float minDamage = damage * 0.5f;
				float maxDamage = damage * 1.5f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				enemy->PlayHitAnimation(EEnemyHitType::SwordLeft);

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
		if (elapsed >= 1.1f && m_bFinalSendDamage[3] == false)
		{
			m_bFinalSendDamage[3] = true;
			Player * pPlayer = static_cast<Player*>(PLAYER);
			auto weapon = pPlayer->GetWeapon();
			weapon->SetRimWidth(0.0f);
			PLAYER->SetRimWidth(0.0);
			pPlayer->SetAnimationSpeed(1.0f);
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			for (auto& obj : m_hitEnemies)
			{
				GameScene* pScene = static_cast<GameScene*>(SCENE);


				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				float damage = m_damageScale[0] * (m_pPlayerStatusData->power + m_pPlayerEquipData->GetPower() + m_pPlayerBuffInfo->GetBuffAtk());
				float minDamage = damage * 0.5f;
				float maxDamage = damage * 1.5f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				enemy->PlayHitAnimation(EEnemyHitType::SwordLeft);

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
		//if (elapsed >= 1.6f && m_bFinalSendDamage[0] == false && m_pPlayerBuffInfo->bBuff)
		//{
		//	SoundDesc desc;
		//	desc.channelMode = FMOD_LOOP_OFF;
		//	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
		//	desc.volume = 1;
		//	//SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
		//	GameScene* pScene = static_cast<GameScene*>(SCENE);

		//	//pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect0");
		//	//pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect1");

		//	for (auto& obj : m_hitEnemies)
		//	{
		//		GameScene* pScene = static_cast<GameScene*>(SCENE);
		//		if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
		//			return;
		//		if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
		//		{
		//			continue;
		//		}


		//		Enemy* enemy = dynamic_cast<Enemy*>(obj);

		//		float damage = m_damageScale[0] * m_pPlayerStatusData->power;
		//		float minDamage = damage * 0.5f;
		//		float maxDamage = damage * 1.5f;
		//		damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
		//		float critical = DxHelper::GetRandomFloat(0, 1);
		//		bool isCritical = false;
		//		if (critical < m_pPlayerStatusData->critical)
		//		{
		//			isCritical = true;
		//			damage *= 2.0f;
		//		}

		//		enemy->SendDamage(GetGameObject(), damage, isCritical);
		//		enemy->PlayHitAnimation(EEnemyHitType::SwordLeft);

		//		if (isCritical)
		//		{
		//			CAMERA->Shake(0.3f, 0.3f, 1.0f);
		//		}
		//		else
		//		{
		//			CAMERA->Shake(0.1f, 0.1f, 1.0f);
		//		}
		//	}
		//	m_bFinalSendDamage[0] = true;
		//}
		//if (elapsed >= 1.7f && m_bFinalSendDamage[1] == false && m_pPlayerBuffInfo->bBuff)
		//{
		//	SoundDesc desc;
		//	desc.channelMode = FMOD_LOOP_OFF;
		//	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
		//	desc.volume = 1;
		//	SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
		//	GameScene* pScene = static_cast<GameScene*>(SCENE);

		//	pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect0");
		//	pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect1");

		//	for (auto& obj : m_hitEnemies)
		//	{
		//		GameScene* pScene = static_cast<GameScene*>(SCENE);
		//		if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
		//			return;
		//		if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
		//		{
		//			continue;
		//		}


		//		Enemy* enemy = dynamic_cast<Enemy*>(obj);

		//		float damage = m_damageScale[0] * m_pPlayerStatusData->power;
		//		float minDamage = damage * 0.5f;
		//		float maxDamage = damage * 1.5f;
		//		damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
		//		float critical = DxHelper::GetRandomFloat(0, 1);
		//		bool isCritical = false;
		//		if (critical < m_pPlayerStatusData->critical)
		//		{
		//			isCritical = true;
		//			damage *= 2.0f;
		//		}

		//		enemy->SendDamage(GetGameObject(), damage, isCritical);
		//		enemy->PlayHitAnimation(EEnemyHitType::SwordRight);

		//		if (isCritical)
		//		{
		//			CAMERA->Shake(0.3f, 0.3f, 1.0f);
		//		}
		//		else
		//		{
		//			CAMERA->Shake(0.1f, 0.1f, 1.0f);
		//		}
		//	}
		//	m_bFinalSendDamage[1] = true;
		//}
		//if (elapsed >= 1.8f && m_bFinalSendDamage[2] == false && m_pPlayerBuffInfo->bBuff)
		//{
		//	SoundDesc desc;
		//	desc.channelMode = FMOD_LOOP_OFF;
		//	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
		//	desc.volume = 1;
		//	SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
		//	GameScene* pScene = static_cast<GameScene*>(SCENE);

		//	pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect0");
		//	pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect1");

		//	for (auto& obj : m_hitEnemies)
		//	{
		//		GameScene* pScene = static_cast<GameScene*>(SCENE);
		//		if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
		//			return;
		//		if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
		//		{
		//			continue;
		//		}


		//		Enemy* enemy = dynamic_cast<Enemy*>(obj);

		//		float damage = m_damageScale[0] * m_pPlayerStatusData->power;
		//		float minDamage = damage * 0.5f;
		//		float maxDamage = damage * 1.5f;
		//		damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
		//		float critical = DxHelper::GetRandomFloat(0, 1);
		//		bool isCritical = false;
		//		if (critical < m_pPlayerStatusData->critical)
		//		{
		//			isCritical = true;
		//			damage *= 2.0f;
		//		}

		//		enemy->SendDamage(GetGameObject(), damage, isCritical);
		//		enemy->PlayHitAnimation(EEnemyHitType::SwordLeft);

		//		if (isCritical)
		//		{
		//			CAMERA->Shake(0.3f, 0.3f, 1.0f);
		//		}
		//		else
		//		{
		//			CAMERA->Shake(0.1f, 0.1f, 1.0f);
		//		}
		//	}
		//	m_bFinalSendDamage[2] = true;
		//}
		//if (elapsed >= 1.9f && m_bFinalSendDamage[3] == false && m_pPlayerBuffInfo->bBuff)
		//{
		//	SoundDesc desc;
		//	desc.channelMode = FMOD_LOOP_OFF;
		//	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
		//	desc.volume = 1;
		//	SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
		//	GameScene* pScene = static_cast<GameScene*>(SCENE);

		//	pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect0");
		//	pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_Effect1");
		//	
		//	for (auto& obj : m_hitEnemies)
		//	{
		//		GameScene* pScene = static_cast<GameScene*>(SCENE);
		//		if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
		//			return;
		//		if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
		//		{
		//			continue;
		//		}


		//		Enemy* enemy = dynamic_cast<Enemy*>(obj);

		//		float damage = m_damageScale[0] * m_pPlayerStatusData->power;
		//		float minDamage = damage * 0.5f;
		//		float maxDamage = damage * 1.5f;
		//		damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
		//		float critical = DxHelper::GetRandomFloat(0, 1);
		//		bool isCritical = false;
		//		if (critical < m_pPlayerStatusData->critical)
		//		{
		//			isCritical = true;
		//			damage *= 2.0f;
		//		}

		//		enemy->SendDamage(GetGameObject(), damage, isCritical);
		//		enemy->PlayHitAnimation(EEnemyHitType::SwordRight);

		//		if (isCritical)
		//		{
		//			CAMERA->Shake(0.3f, 0.3f, 1.0f);
		//		}
		//		else
		//		{
		//			CAMERA->Shake(0.1f, 0.1f, 1.0f);
		//		}
		//	}
		//	m_bFinalSendDamage[3] = true;
		//}

		break;
	case 3:
		if (elapsed >= 0.01f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			//pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		if (elapsed >= 0.3f)
		{
			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerSkillSwing", L"Lups_SwordThrowing3.mp3", desc);
			GameScene* pScene = static_cast<GameScene*>(SCENE);

			pScene->GetEffectManager()->PlayEffect(L"PlayerSkillSwing_FourthActionTrail");

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
				float damage = m_damageScale[0] * m_pPlayerStatusData->power;
				float minDamage = damage * 0.5f;
				float maxDamage = damage * 1.5f;
				damage = DxHelper::GetRandomFloat(minDamage, maxDamage);
				float critical = DxHelper::GetRandomFloat(0, 1);
				bool isCritical = false;
				if (critical < m_pPlayerStatusData->critical)
				{
					isCritical = true;
					damage *= 2.0f;
				}

				enemy->SendDamage(GetGameObject(), damage, isCritical);
				//enemy->SendDamage(GetGameObject(), GetAttackDamage());
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
	/*case 4 :
		if (elapsed >= 0.01f && m_bPlayAfterImage == false)
		{
			m_bPlayAfterImage = true;
			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayAffterEffect(m_afterImageIndex);

		}
		break;*/
	}
}

void PlayerSkillSwing::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
	Player * pPlayer = static_cast<Player*>(PLAYER);
	pPlayer->SetAnimationSpeed(1.0f);
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
	// swing skill index = 1
	PlayerSkillInfo* pPlayerSkillInfo = static_cast<PlayerSkillInfo*>(ENGINE->GetScriptableData(L"PlayerSkillInfo"));
	if (pPlayerSkillInfo->isLock[1] == true)
		return;

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
