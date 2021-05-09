#include "stdafx.h"
#include "Enemy.h"
#include "EnemyHPBar.h"
#include "PathManager.h"
#include "GameScene.h"
#include "UIManager.h"
#include "Billboard.h"
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

void Enemy::ShowHPBar()
{
	m_pHpBarBillboard->SetActive(true);
}
