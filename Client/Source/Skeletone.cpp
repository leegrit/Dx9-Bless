#include "stdafx.h"
#include "Skeletone.h"
#include "SkeletoneAttack.h"
#include "SkeletoneDie.h"
#include "SkeletoneDied.h"
#include "SkeletoneHit.h"
#include "SkeletoneIdle.h"
#include "SkeletoneMove.h"
#include "NameFont.h"

Skeletone::Skeletone(Scene * pScene, NavMesh * pNavMesh)
	:Enemy(pScene, pNavMesh, D3DXVECTOR3(0, 10, 0), 5)
{
	SetLayer(Layer::Enemy);

	SetSkinningType(ESkinningType::HardwareSkinning);
}

Skeletone::~Skeletone()
{
	m_state.Release();
}

void Skeletone::Initialize(std::wstring dataPath)
{
	Character::Initialize(dataPath);
	SetLayer(Layer::Enemy);

	m_pAttackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 10, Layer::Player,
		std::bind(&Skeletone::OnHitOthers, this, placeholders::_1));
	m_pAttackCollider->SetOffset(m_colliderOffset);

	SetParams(10, 100, 100);

	m_state.Add<SkeletoneAttack>(this, "Attack");
	m_state.Add<SkeletoneDie>(this, "Die");
	m_state.Add<SkeletoneHit>(this, "Hit");
	m_state.Add<SkeletoneIdle>(this, "Idle");
	m_state.Add<SkeletoneMove>(this, "Move");
	m_state.Add<SkeletoneDied>(this, "Died");

	m_state.Initialize("Idle");

	m_pNameFont = new NameFont();
	m_pNameFont->Initialize(L"스켈레톤", this, D3DXVECTOR2(0.5f, 0.5f), D3DXVECTOR3(0, 12, 0), -30, D3DXCOLOR(1, 0, 0, 1));
}

void Skeletone::Update()
{
	Character::Update();

	m_state.Update();
}

void Skeletone::Render()
{
	Enemy::Render();

	m_pNameFont->RenderFont();
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

Skeletone * Skeletone::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	Skeletone * skeletone = new Skeletone(pScene, pNavMesh);
	skeletone->Initialize(dataPath);
	return skeletone;
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
