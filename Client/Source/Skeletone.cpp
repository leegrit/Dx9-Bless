#include "stdafx.h"
#include "Skeletone.h"
#include "SkeletoneAttack.h"
#include "SkeletoneDie.h"
#include "SkeletoneDied.h"
#include "SkeletoneHit.h"
#include "SkeletoneIdle.h"
#include "SkeletoneMove.h"
#include "NameFont.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "EnemyName.h"
#include "PathManager.h"


Skeletone::Skeletone(Scene * pScene, NavMesh * pNavMesh)
	:Enemy(pScene, pNavMesh, D3DXVECTOR3(0, 10, 0), 5, ESkinningType::HardwareSkinning)
{
	SetLayer(Layer::Enemy);

	//SetSkinningType(ESkinningType::HardwareSkinning);
}

Skeletone::~Skeletone()
{
	m_state.Release();
}

void Skeletone::Initialize(std::wstring dataPath)
{
	Enemy::Initialize(dataPath);
	SetLayer(Layer::Enemy);

	m_pAttackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 10, Layer::Player,
		std::bind(&Skeletone::OnHitOthers, this, placeholders::_1));
	m_pAttackCollider->SetOffset(m_colliderOffset);

	SetParams(10, 1000, 100);

	m_state.Add<SkeletoneAttack>(this, "Attack");
	m_state.Add<SkeletoneDie>(this, "Die");
	m_state.Add<SkeletoneHit>(this, "Hit");
	m_state.Add<SkeletoneIdle>(this, "Idle");
	m_state.Add<SkeletoneMove>(this, "Move");
	m_state.Add<SkeletoneDied>(this, "Died");

	m_state.Initialize("Idle");

	m_pNameFont = new NameFont();
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	m_pNameFont->Initialize(L"스켈레톤", this, D3DXVECTOR2(0.8f, 0.8f), D3DXVECTOR3(0, 18, 0), -20, D3DXCOLOR(1, 1, 0, 1));

	m_pEnemyName = EnemyName::Create(GetScene(), L"SkeletonName",
		PATH->AssetsPathW() + L"FontTexture/GoblinName.png", this, D3DXVECTOR3(0, 16.5f, 0));

	ShowHPBar();
}

void Skeletone::Update()
{
	Enemy::Update();
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	m_pNameFont->SetOffset(D3DXVECTOR3(0, 15, 0));
	m_pNameFont->SetCenterOffset(-20);

	m_state.Update();

	float sizeX = pScene->GetFloatA();
	float sizeY = pScene->GetFloatB();

	m_pEnemyName->m_pTransform->SetScale(3.5, 1.5, 1);
}

void Skeletone::Render()
{
	Enemy::Render();

	//m_pNameFont->RenderFont();
}

UINT Skeletone::GetTargetLayer() 
{
	return Layer::Player;
}

void Skeletone::OnCollision(Collider * other)
{

}

void Skeletone::OnHitOthers(Collider * other)
{
	/* 여기서 데미지를 보낼 타겟을 저장한다. */
	AddHitOthers(other->GetGameObject());
}

void Skeletone::OnDied()
{
	Enemy::OnDied();

	EventDispatcher::TriggerEvent(GameEvent::SendExp, (float*)&m_exp);
}

Skeletone * Skeletone::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	Skeletone * skeletone = new Skeletone(pScene, pNavMesh);
	skeletone->Initialize(dataPath);
	return skeletone;
}

float Skeletone::GetFocusColliderSize()
{
	return 20;
}

D3DXVECTOR3 Skeletone::GetFocusUIOffset()
{
	return D3DXVECTOR3(0, 5, 0);
}

std::wstring Skeletone::GetCharacterName()
{
	return L"스켈레톤";
}

int Skeletone::GetLevel()
{
	return 10;
}

int Skeletone::GetAttackCount()
{
	/* Skeletone은 공격 종류가 1종류 */
	return 1;
}

Collider * Skeletone::GetAttackCollider(int attackIndex)
{
	Collider* attackCollider = nullptr;
	if (attackIndex == 0)
	{
		attackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 5, Layer::Player,
			std::bind(&Skeletone::OnHitOthers, this, placeholders::_1));
		attackCollider->SetOffset(D3DXVECTOR3(0, 0, 5));
	}
	else /* 1종류밖에 없음 */
		assert(false);

	return attackCollider;
}
