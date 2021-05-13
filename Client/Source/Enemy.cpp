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
	leftHitEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Impact_Up_001_TEX_HKB.tga";
	leftHitEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Impact_Up_001_TEX_HKB.tga";
	leftHitEffectDesc.fadeOut = true;
	//leftHitEffectDesc.fadeIn = true;
	leftHitEffectDesc.fadeOutFactor = 0.5f;
	leftHitEffectDesc.lifeTime = 0.3f;
	leftHitEffectDesc.endScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	m_pLeftSwordHitEffect = pScene->GetEffectManager()->AddEffect(std::to_wstring(GetInstanceID()) + L"EnemyHitEffect_Left", leftHitEffectDesc);



	MeshEffectDesc rightHitEffectDesc;
	rightHitEffectDesc.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_Hit_001_SM.X";
	rightHitEffectDesc.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Impact_Up_001_TEX_HKB.tga";
	rightHitEffectDesc.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Impact_Up_001_TEX_HKB.tga";
	rightHitEffectDesc.fadeOut = true;
	//leftHitEffectDesc.fadeIn = true;
	leftHitEffectDesc.fadeOutFactor = 0.5f;
	rightHitEffectDesc.lifeTime = 0.3f;
	rightHitEffectDesc.endScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	m_pRightSwordHitEffect = pScene->GetEffectManager()->AddEffect(std::to_wstring(GetInstanceID()) + L"EnemyHitEffect_Right", rightHitEffectDesc);

	//Sprite * pSprite;
	m_pHitEffect = Sprite::Create(GetScene(), L"HitEffect",
		PATH->AssetsPathW() + L"Effect/Texture/Spark", ELoopType::Default, 4, 12);
	m_pHitEffect->SetActive(false);
	m_pHitEffect->m_pTransform->SetScale(10, 10, 10);
}

void Enemy::Update()
{
	Character::Update();
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
	
}

void Enemy::Render()
{
	Character::Render();
}

void Enemy::OnDamaged(GameObject* pSender, float damage, bool isCritical)
{
	m_pHpBarBillboard->SetAmount(GetCurHP() / GetMaxHP());

	GameScene* scene = static_cast<GameScene*>(SCENE);
	scene->GetUIManager()->PushDamageFont(damage, false, isCritical, m_pTransform->CalcOffset(D3DXVECTOR3(0, 10, 0)));

}

void Enemy::OnDied()
{
	m_pHpBarBillboard->SetAmount(0);
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
		m_pHitEffect->PlayAnimation();
		break;
	case EEnemyHitType::SwordRight:
		pScene->GetEffectManager()->PlayEffect(std::to_wstring(GetInstanceID()) + L"EnemyHitEffect_Right");
		m_pHitEffect->PlayAnimation();
		break;
	}
}

void Enemy::ShowHPBar()
{
	m_pHpBarBillboard->SetActive(true);
}
