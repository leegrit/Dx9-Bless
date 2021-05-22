#include "stdafx.h"
#include "Enemy.h"
#include "EnemyHPBar.h"
#include "PathManager.h"
#include "GameScene.h"
#include "UIManager.h"
#include "Billboard.h"
#include "Effect.h"
#include "EffectManager.h"
#include "Sprite.h"
#include "SoundManager.h"
#include "ObjectContainer.h"
#include "Player.h"
#include "LightManager.h"

Enemy::Enemy(Scene * scene, NavMesh * pNavMesh, D3DXVECTOR3 colPosOffset, float colRadius, ESkinningType skinningType)
	: Character(scene, pNavMesh, colPosOffset, colRadius, skinningType)
{

}

Enemy::~Enemy()
{
}

void Enemy::Initialize(std::wstring dataPath)
{
	Character::Initialize(dataPath);
	m_pFocusCollider = SphereCollider::Create(EColliderType::Multipurpose,
		this, GetFocusColliderSize(), Layer::Default, nullptr);

	m_targets.clear();
	m_targets = GetScene()->GetObjectContainer()->GetOpaqueObjectAll(Layer::Player);



	/* Set Attack Data */
	m_attackCount = GetAttackCount();
	m_attackColliders.reserve(m_attackCount);
	for (int i = 0; i < m_attackCount; i++)
	{
		m_attackColliders.emplace_back(GetAttackCollider(i));
	}

	m_pHpBarBillboard = EnemyHPBar::Create(GetScene(), L"HPBar");
	m_pHpBarBillboard->SetFillTex(PATH->AssetsPathW() + L"UI/StatusGauge_3.png");
	m_pHpBarBillboard->SetBackTex(PATH->AssetsPathW() + L"UI/EnemyHPBack.png");
	m_pHpBarBillboard->SetAmount(1);
	m_pHpBarBillboard->m_pTransform->m_scale = D3DXVECTOR3(10, 0.5f, 1);
	m_pHpBarBillboard->SetActive(false);
	//m_pHPHitBar = HyEngine::Billboard::Create(GetScene(), this, L"EnemyHPHit", EBillboardType::Y);
	//m_pHPHitBar->SetDiffuseTexture(PATH->AssetsPathW() + L"UI/BLUINameTag_I1_56.png");
	//m_pHPHitBar->m_pTransform->SetScale(11, 2, 1);
	//m_pHPHitBar->SetActive(true);

	GameScene* pScene = static_cast<GameScene*>(GetScene());

	MeshEffectDesc leftHitEffectDesc;
	leftHitEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_Hit_001_SM.X";
	leftHitEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Impact_Up_001_TEX_HKB_Color.tga";
	leftHitEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Impact_Up_001_TEX_HKB.tga";
	leftHitEffectDesc.fadeOut = true;
	//leftHitEffectDesc.fadeIn = true;
	leftHitEffectDesc.fadeOutFactor = 0.5f;
	leftHitEffectDesc.lifeTime = 0.3f;
	leftHitEffectDesc.endScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f); // ���� 0.2
	m_pLeftSwordHitEffect = pScene->GetEffectManager()->AddEffect(std::to_wstring(GetInstanceID()) + L"EnemyHitEffect_Left", leftHitEffectDesc);



	MeshEffectDesc rightHitEffectDesc;
	rightHitEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_Hit_001_SM.X";
	rightHitEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Impact_Up_001_TEX_HKB_Color.tga";
	rightHitEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Impact_Up_001_TEX_HKB.tga";
	rightHitEffectDesc.fadeOut = true;
	//leftHitEffectDesc.fadeIn = true;
	leftHitEffectDesc.fadeOutFactor = 0.5f;
	rightHitEffectDesc.lifeTime = 0.3f;
	rightHitEffectDesc.endScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	m_pRightSwordHitEffect = pScene->GetEffectManager()->AddEffect(std::to_wstring(GetInstanceID()) + L"EnemyHitEffect_Right", rightHitEffectDesc);

	MeshEffectDesc leftBloodEffectDesc;
	leftBloodEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_Hit_001_SM.X";
	leftBloodEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/Blood1.tga";
	leftBloodEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Impact_Up_001_TEX_HKB.tga";
	leftBloodEffectDesc.fadeOut = true;
	leftBloodEffectDesc.fadeOutFactor = 0.5f;
	leftBloodEffectDesc.lifeTime = 0.3f;
	leftBloodEffectDesc.endScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	m_pLeftBloodEffect = pScene->GetEffectManager()->AddEffect(std::to_wstring(GetInstanceID()) + L"EnemyBloodEffect_Left", leftBloodEffectDesc);


	MeshEffectDesc rightBloodEffectDesc;
	rightBloodEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_Hit_001_SM.X";
	rightBloodEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/Blood1.tga";
	rightBloodEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Impact_Up_001_TEX_HKB.tga";
	rightBloodEffectDesc.fadeOut = true;
	rightBloodEffectDesc.fadeOutFactor = 0.5f;
	rightBloodEffectDesc.lifeTime = 0.3f;
	rightBloodEffectDesc.endScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	m_pRightBloodEffect = pScene->GetEffectManager()->AddEffect(std::to_wstring(GetInstanceID()) + L"EnemyBloodEffect_Right", rightBloodEffectDesc);



	//Sprite * pSprite;
	m_pHitEffect = Sprite::Create(GetScene(), L"HitEffect",
		PATH->AssetsPathW() + L"Effect/Texture/Spark", ELoopType::Default, 4, 12);
	m_pHitEffect->SetActive(false);
	m_pHitEffect->m_pTransform->SetScale(30, 30, 30);

	m_pHitEffect2 = Sprite::Create(GetScene(), L"HitEffect2",
		PATH->AssetsPathW() + L"Effect/Texture/Hit", ELoopType::Default, 14, 50);
	m_pHitEffect2->SetActive(false);
	m_pHitEffect2->m_pTransform->SetScale(30, 30, 30);
}

void Enemy::Update()
{
	Character::Update();

	if (m_hited)
	{
		/*m_hitElapsed += TIMER->getDeltaTime();
		if (m_hitElapsed >= m_reactionDuration)
		{
			m_hited = false;
			m_hitElapsed = 0;
		}
		SetRenderEffectOption(RenderEffectOption::RimLight);
		SetRimWidth(1.0f);
		SetRimColor(D3DXCOLOR(1, 1, 1, 1));*/
	}
	else
	{
		//SetRimWidth(0.0f);
	}
	if (GetCurHP() != GetMaxHP())
	{
		GameScene* pScene = static_cast<GameScene*>(SCENE);
		m_pHpBarBillboard->m_pTransform->m_position = m_pTransform->CalcOffset(D3DXVECTOR3(0, 15, 0));
		//m_pHPHitBar->m_pTransform->m_position = m_pTransform->CalcOffset(D3DXVECTOR3(0, 15, 0));
		
		
	}
	
	m_pLeftSwordHitEffect->SetOriginPos(
		m_pTransform->CalcOffset(D3DXVECTOR3(0, 7, 0))
	);
	m_pLeftSwordHitEffect->SetOriginRot
	(
		PLAYER->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 90, 0)
	);
	m_pLeftSwordHitEffect->SetOriginScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));

	m_pRightSwordHitEffect->SetOriginPos(
		m_pTransform->CalcOffset(D3DXVECTOR3(0, 7, 0))
	);
	m_pRightSwordHitEffect->SetOriginRot
	(
		PLAYER->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, -90, 0)
	);
	m_pRightSwordHitEffect->SetOriginScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));

	m_pHitEffect->m_pTransform->SetPosition(m_pTransform->CalcOffset(D3DXVECTOR3( 0, 6, 0)));
	m_pHitEffect2->m_pTransform->SetPosition(m_pTransform->CalcOffset(D3DXVECTOR3(0, 6, 0)));

	m_pLeftBloodEffect->SetOriginPos(
		m_pTransform->CalcOffset(D3DXVECTOR3(0, 7, 0))
	);
	m_pLeftBloodEffect->SetOriginRot
	(
		PLAYER->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(-45, -90, 0)
	);
	m_pLeftBloodEffect->SetOriginScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));

	m_pRightBloodEffect->SetOriginPos(
		m_pTransform->CalcOffset(D3DXVECTOR3(0, 7, 0))
	);
	m_pRightBloodEffect->SetOriginRot
	(
		PLAYER->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(-45, 90, 0)
	);
	m_pRightBloodEffect->SetOriginScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));

}

void Enemy::Render()
{
	Character::Render();
}

void Enemy::OnDamaged(GameObject* pSender, float damage, bool isCritical)
{
	m_pHpBarBillboard->SetAmount(GetCurHP() / GetMaxHP());
	
	Player * pPlayer = dynamic_cast<Player*>(pSender);

	GameScene* scene = static_cast<GameScene*>(SCENE);
	if (pPlayer)
	{
		scene->GetUIManager()->PushDamageFont(damage, false, isCritical, m_pTransform->CalcOffset(D3DXVECTOR3(0, 10, 0)));
	}
	m_pTarget = pSender;
	/* �ӽ� */
	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::RelativeVolume;
	desc.volume = 1;
	desc.soundPosition = m_pTransform->m_position.operator D3DXVECTOR3();
	SOUND->PlaySound("EnemyHit", L"Attacked_1.mp3", desc);

	//m_hited = true;
}

void Enemy::OnDied()
{
	m_pHpBarBillboard->SetAmount(0);
}

void Enemy::OnEnable()
{
	Character::OnEnable();
	if(m_pHPHitBar)
		m_pHPHitBar->SetActive(true);
	if (m_pHpBarBillboard)
		m_pHpBarBillboard->SetActive(true);
}

void Enemy::OnDisable()
{
	Character::OnDisable();
	if (m_pHPHitBar)
		m_pHPHitBar->SetActive(false);
	if (m_pHpBarBillboard)
		m_pHpBarBillboard->SetActive(false);
}



void Enemy::AddHitOthers(GameObject * other)
{
	for (auto& obj : m_hitOthers)
	{
		if (obj == other)
			return;
	}
	m_hitOthers.push_back(other);
}

void Enemy::SendDamageToOthers(float damage)
{
	for (auto& obj : m_hitOthers)
	{
		Character* other = dynamic_cast<Character*>(obj);
		assert(other);
		other->SendDamage(this, damage);
	}
}

void Enemy::ClearHitOthers()
{
	m_hitOthers.clear();
}

void Enemy::PlayHitAnimation(EEnemyHitType enemyHitType)
{
	GameScene* pScene = static_cast<GameScene*>(GetScene());
	switch (enemyHitType)
	{
	case EEnemyHitType::SwordLeft:
		pScene->GetEffectManager()->PlayEffect(std::to_wstring(GetInstanceID()) + L"EnemyHitEffect_Left");
		pScene->GetEffectManager()->PlayEffect(std::to_wstring(GetInstanceID()) + L"EnemyBloodEffect_Left");
		m_pHitEffect->PlayAnimation();
		m_pHitEffect2->PlayAnimation();
		pScene->GetLightManager()->GenerateLight(std::to_wstring(GetInstanceID()) + L"_EnemyHit",
			m_pTransform->CalcOffset(D3DXVECTOR3(0, 10, 0)), D3DXCOLOR(1, 0.5, 0.2, 1), 1, 20, 0, 0.0, 0.01, 0.15f);
		break;
	case EEnemyHitType::SwordRight:
		pScene->GetEffectManager()->PlayEffect(std::to_wstring(GetInstanceID()) + L"EnemyHitEffect_Right");
		pScene->GetEffectManager()->PlayEffect(std::to_wstring(GetInstanceID()) + L"EnemyBloodEffect_Right");
		m_pHitEffect->PlayAnimation();
		m_pHitEffect2->PlayAnimation();
		pScene->GetLightManager()->GenerateLight(std::to_wstring(GetInstanceID()) + L"_EnemyHit",
			m_pTransform->CalcOffset(D3DXVECTOR3(0, 10, 0)), D3DXCOLOR(1, 0.5, 0.2, 1), 1, 20, 0, 0.0, 0.01, 0.15f);
		break;
	}
}

GameObject * Enemy::GetTarget() const
{
	return m_pTarget;
}

void Enemy::SetTarget(GameObject * pTarget)
{
	m_pTarget = pTarget;
}

const std::vector<GameObject*>& Enemy::GetTargets() const
{
	return m_targets;
}

void Enemy::ShowHPBar()
{
	m_pHpBarBillboard->SetActive(true);
}
