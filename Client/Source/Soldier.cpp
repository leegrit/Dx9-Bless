#include "stdafx.h"
#include "Soldier.h"
#include "NameFont.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "SoldierAttack.h"
#include "SoldierDie.h"
#include "SoldierDied.h"
#include "SoldierHit.h"
#include "SoldierIdle.h"
#include "SoldierMove.h"

StateController<Soldier>* Soldier::GetState() { return &m_state; }

Soldier * Soldier::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	Soldier * obj = new Soldier(pScene, pNavMesh);
	obj->Initialize(dataPath);
	return obj;
}

Soldier::Soldier(Scene * pScene, NavMesh * pNavMesh)
	: Enemy(pScene, pNavMesh, D3DXVECTOR3(0, 10, 0), 5, ESkinningType::SoftwareSkinning)
{
	SetLayer(Layer::Player);
}

Soldier::~Soldier()
{
	m_state.Release();
}

void Soldier::Initialize(std::wstring dataPath)
{
	Enemy::Initialize(dataPath);
	SetLayer(Layer::Player);

	m_pAttackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 10, Layer::Player,
		std::bind(&Soldier::OnHitOthers, this, placeholders::_1));
	m_pAttackCollider->SetOffset(m_colliderOffset);

	SetParams(10, 3000, 100);

	m_state.Add<SoldierAttack>(this, "Attack");
	m_state.Add<SoldierDie>(this, "Die");
	m_state.Add<SoldierHit>(this, "Hit");
	m_state.Add<SoldierIdle>(this, "Idle");
	m_state.Add<SoldierMove>(this, "Move");
	m_state.Add<SoldierDied>(this, "Died");

	m_state.Initialize("Idle");

	m_pNameFont = new NameFont();
	m_pNameFont->Initialize(L"병사", this, D3DXVECTOR2(0.8f, 0.8f), D3DXVECTOR3(0, 16, 0), 0, D3DXCOLOR(0, 1, 0, 1));

	ShowHPBar();
}

void Soldier::Update()
{
	Enemy::Update();
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	//m_pNameFont->SetOffset(D3DXVECTOR3(0, 18, 0));
	//m_pNameFont->SetCenterOffset(-20);
	m_state.Update();
}

void Soldier::Render()
{
	Enemy::Render();

	m_pNameFont->RenderFont();
}

void Soldier::OnDied()
{
	Enemy::OnDied();

	EventDispatcher::TriggerEvent(GameEvent::SendExp, (float*)&m_exp);
}

UINT Soldier::GetTargetLayer()
{
	return Layer::Enemy;
}

void Soldier::OnCollision(Collider * other)
{
}

int Soldier::GetAttackCount()
{
	return 1;
}

Collider * Soldier::GetAttackCollider(int attackIndex)
{
	Collider* attackCollider = nullptr;
	if (attackIndex == 0)
	{
		attackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 5, Layer::Player,
			std::bind(&Soldier::OnHitOthers, this, placeholders::_1));
		attackCollider->SetOffset(D3DXVECTOR3(0, 0, 5));
	}
	else /* 1종류밖에 없음 */
		assert(false);

	return attackCollider;
}

float Soldier::GetFocusColliderSize()
{
	return 0.0f;
}

D3DXVECTOR3 Soldier::GetFocusUIOffset()
{
	return D3DXVECTOR3();
}

int Soldier::GetLevel()
{
	return 0;
}

std::wstring Soldier::GetCharacterName()
{
	return L"";
}

void Soldier::OnHitOthers(Collider * other)
{
	/* 여기서 데미지를 보낼 타겟을 저장한다. */
	AddHitOthers(other->GetGameObject());
}
