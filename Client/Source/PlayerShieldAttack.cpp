#include "stdafx.h"
#include "PlayerShieldAttack.h"
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

PlayerShieldAttack::PlayerShieldAttack(GameObject * pPlayer, PlayerController * pPlayerController)
	:PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerShieldAttack")
{
	SetParams(0.2f,1, 3.0f, 10, 10, false, D3DXVECTOR3(0, 10, 20));
}

PlayerShieldAttack::~PlayerShieldAttack()
{
}

void PlayerShieldAttack::Initialize()
{
	PlayerAction::Initialize();
	m_pPlayerStatusData = static_cast<PlayerStatusData*>(ENGINE->GetScriptableData(L"PlayerStatusData"));
	m_pPlayerBuffInfo = static_cast<PlayerBuffInfo*>(ENGINE->GetScriptableData(L"PlayerBuffInfo"));

	GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());


	MeshEffectDesc shieldAttackEffectDesc;
	shieldAttackEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_common_trail_001_SM_CJH.X";
	shieldAttackEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Shock_003_Tex_KKJ.tga";
	shieldAttackEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Shock_003_Tex_KKJ.tga";
	shieldAttackEffectDesc.fadeOut = true;
	shieldAttackEffectDesc.fadeOutFactor = 0.5f;
	shieldAttackEffectDesc.isUVAnim = true;
	shieldAttackEffectDesc.uvDirection = D3DXVECTOR2(1, 0);
	shieldAttackEffectDesc.uvSpeed = 1;
	shieldAttackEffectDesc.lifeTime = 0.7f;
	m_pShieldEffect = pScene->GetEffectManager()->AddEffect(L"PlayerSkillShieldAttack_ShieldAttack", shieldAttackEffectDesc);
	m_pShieldEffect->SetRenderEffectOption(RenderEffectOption::Bloom);

	MeshEffectDesc waveEffectDesc;
	waveEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_PlateUVX_001_SM_CJS.X";
	waveEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_EnergyWave_001_TEX_HKB.tga";
	waveEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_EnergyWave_001_TEX_HKB.tga";
	waveEffectDesc.fadeOut = true;
	waveEffectDesc.fadeOutFactor = 0.7f;
	waveEffectDesc.isUVAnim = true;
	waveEffectDesc.lifeTime = 1.0f;
	waveEffectDesc.endScale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	m_pWaveEffect = pScene->GetEffectManager()->AddEffect(L"PlayerSkillShieldAttack_Wave", waveEffectDesc);
	//m_pWaveEffect->SetRenderEffectOption(RenderEffectOption::Bloom);

	MeshEffectDesc windEffectDesc;
	windEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_Vortex01_SM_KKJ.X";
	windEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_004_TEX_CJH.tga";
	windEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_swordtrail_004_TEX_CJH.tga";
	windEffectDesc.fadeOut = true;
	windEffectDesc.fadeOutFactor = 0.7f;
	windEffectDesc.isUVAnim = true;
	windEffectDesc.uvDirection = D3DXVECTOR2(1, 0);
	windEffectDesc.uvSpeed = 1;
	windEffectDesc.lifeTime = 1.0f;
	windEffectDesc.endRot = D3DXVECTOR3(0, -360, 0);
	windEffectDesc.endScale = D3DXVECTOR3(0.4f, 0, 0.4f);
	m_pWindEffect = pScene->GetEffectManager()->AddEffect(L"PlayerSkillShieldAttack_Wind", windEffectDesc);
	m_pWindEffect->SetRenderEffectOption(RenderEffectOption::Bloom);

}

void PlayerShieldAttack::Update()
{
	PlayerAction::Update();
	UpdateAction();

	m_pShieldEffect->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(0, 0, -2))
	);
	m_pShieldEffect->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, -90, 0)
	);
	m_pShieldEffect->SetOriginScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));

	m_pWaveEffect->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(0, 3, 9))
	);
	m_pWaveEffect->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 0, 0)
	);
	m_pWaveEffect->SetOriginScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));


	m_pWindEffect->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(0, 3, 8))
	);
	m_pWindEffect->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(180, 0, 0)
	);
	m_pWindEffect->SetOriginScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));




}

void PlayerShieldAttack::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerShieldAttack::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerShieldAttack::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerShieldAttack::OnHitOthers(Collider * other)
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

void PlayerShieldAttack::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage = false;

	Player * pPlayer = static_cast<Player*>(PLAYER);
	UINT animSet = pPlayer->GetCurAnimationIndex();
	pPlayer->SetAnimationSpeed(1.0f);


}

void PlayerShieldAttack::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);

	switch (seqIndex)
	{
	case 0 :
		if (elapsed >= 0.1f)
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			auto shield = pPlayer->GetShield();
			shield->SetRenderEffectOption(RenderEffectOption::RimLight);
			shield->SetRimWidth(1.0f);
			shield->SetRimColor(D3DXCOLOR(1, 1.0f, 0.0f, 1));
		}
		if (elapsed >= 0.7f && m_bSendDamage == false)
		{
			Player * pPlayer = static_cast<Player*>(PLAYER);
			auto shield = pPlayer->GetShield();
			shield->SetRimWidth(0.0f);

			GameScene* pScene = static_cast<GameScene*>(SCENE);
			pScene->GetEffectManager()->PlayEffect(L"PlayerSkillShieldAttack_ShieldAttack");
			pScene->GetEffectManager()->PlayEffect(L"PlayerSkillShieldAttack_Wave");
			pScene->GetEffectManager()->PlayEffect(L"PlayerSkillShieldAttack_Wind");
			for (auto& obj : m_hitEnemies)
			{
				/* 범위 공격은 해당안됨
				if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
					return;
				if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
				{
					continue;
				}
				*/

				Enemy* enemy = dynamic_cast<Enemy*>(obj);

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
			m_bSendDamage = true;
		}
		break;
	default :
		assert(false);
		break;
	}
}

void PlayerShieldAttack::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
	Player * pPlayer = static_cast<Player*>(PLAYER);
	pPlayer->SetAnimationSpeed(1.0f);
}

UINT PlayerShieldAttack::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerShieldAttack::GetIdleAnimIndex() const
{
	return 89;
}

void PlayerShieldAttack::UpdateAction()
{// swing skill index = 1
	PlayerSkillInfo* pPlayerSkillInfo = static_cast<PlayerSkillInfo*>(ENGINE->GetScriptableData(L"PlayerSkillInfo"));
	if (pPlayerSkillInfo->isLock[2] == true)
		return;

	if (KEYBOARD->Down(48 + 2))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerShieldAttack * PlayerShieldAttack::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerShieldAttack * com = new PlayerShieldAttack(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
