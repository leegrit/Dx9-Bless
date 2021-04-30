#include "StandardEngineFramework.h"
#include "DummyBoss.h"
#include "DummyBossAttack.h"
#include "DummyBossDie.h"
#include "DummyBossDied.h"
#include "DummyBossHit.h"
#include "DummyBossIdle.h"
#include "DummyBossMove.h"

DummyBoss::DummyBoss(Scene * pScene, NavMesh * pNavMesh)
	: NamedEnemy(pScene, pNavMesh, D3DXVECTOR3(0, 15, 0), 10)
{
	
}

DummyBoss::~DummyBoss()
{
	m_state.Release();
}

void DummyBoss::Initialize(std::wstring dataPath)
{
	NamedEnemy::Initialize(dataPath);

	SetParams(15, 1000, 1000);


	m_state.Add<DummyBossAttack>(this, "Attack");
	m_state.Add<DummyBossDie>(this, "Die");
	m_state.Add<DummyBossHit>(this, "Hit");
	m_state.Add<DummyBossIdle>(this, "Idle");
	m_state.Add<DummyBossMove>(this, "Move");
	m_state.Add<DummyBossDied>(this, "Died");

	m_state.Initialize("Idle");
}

void DummyBoss::Update()
{
	NamedEnemy::Update();

	m_state.Update();
}

UINT DummyBoss::GetTargetLayer()
{
	return Layer::Player;
}

void DummyBoss::OnCollision(Collider * other)
{
}

int DummyBoss::GetAttackCount()
{
	return 1;
}

Collider * DummyBoss::GetAttackCollider(int attackIndex)
{
	Collider * pAttackCollider = nullptr;
	if (attackIndex == 0)
	{
		pAttackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 10, Layer::Player,
			std::bind(&DummyBoss::OnHitOthers, this, placeholders::_1));
		pAttackCollider->SetOffset(D3DXVECTOR3(0, 0, 10));
	}
	else /* 한종류밖에 없음 */
		assert(false);

	return pAttackCollider;
}

void DummyBoss::OnHitOthers(Collider * other)
{
	AddHitOthers(other->GetGameObject());
}

DummyBoss * DummyBoss::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	DummyBoss* boss = new DummyBoss(pScene, pNavMesh);
	boss->Initialize(dataPath);
	return boss;
}
