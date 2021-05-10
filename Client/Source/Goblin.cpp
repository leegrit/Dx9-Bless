#include "stdafx.h"
#include "Goblin.h"
#include "NameFont.h"
#include "Client_Events.h"
#include "GoblinAttack.h"
#include "GoblinDie.h"
#include "GoblinDied.h"
#include "GoblinHit.h"
#include "GoblinIdle.h"
#include "GoblinMove.h"
#include "GameScene.h"


Goblin::Goblin(Scene * pScene, NavMesh * pNavMesh)
	:Enemy(pScene, pNavMesh, D3DXVECTOR3(0, 10, 0), 5, ESkinningType::HardwareSkinning)
{
	SetLayer(Layer::Enemy);

	//SetSkinningType(ESkinningType::HardwareSkinning);
}

Goblin::~Goblin()
{
	m_state.Release();
}

void Goblin::Initialize(std::wstring dataPath)
{
	Enemy::Initialize(dataPath);
	SetLayer(Layer::Enemy);

	m_pAttackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 10, Layer::Player,
		std::bind(&Goblin::OnHitOthers, this, placeholders::_1));
	m_pAttackCollider->SetOffset(m_colliderOffset);

	SetParams(10, 100, 100);

	m_state.Add<GoblinAttack>(this, "Attack");
	m_state.Add<GoblinDie>(this, "Die");
	m_state.Add<GoblinHit>(this, "Hit");
	m_state.Add<GoblinIdle>(this, "Idle");
	m_state.Add<GoblinMove>(this, "Move");
	m_state.Add<GoblinDied>(this, "Died");

	m_state.Initialize("Idle");

	m_pNameFont = new NameFont();
	m_pNameFont->Initialize(L"고블린", this, D3DXVECTOR2(0.8f, 0.8f), D3DXVECTOR3(0, 15, 0), -40, D3DXCOLOR(1, 1, 0, 1));

	ShowHPBar();
}

void Goblin::Update()
{
	Enemy::Update();
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	m_pNameFont->SetOffset(D3DXVECTOR3(0, 18, 0));
	m_pNameFont->SetCenterOffset(-20);
	m_state.Update();
}

void Goblin::Render()
{
	Enemy::Render();

	m_pNameFont->RenderFont();
}

UINT Goblin::GetTargetLayer()
{
	return Layer::Player;
}

void Goblin::OnCollision(Collider * other)
{

}

void Goblin::OnHitOthers(Collider * other)
{
	/* 여기서 데미지를 보낼 타겟을 저장한다. */
	AddHitOthers(other->GetGameObject());
}

void Goblin::OnDied()
{
	Enemy::OnDied();

	EventDispatcher::TriggerEvent(GameEvent::SendExp, (float*)&m_exp);
}

Goblin * Goblin::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	Goblin * obj = new Goblin(pScene, pNavMesh);
	obj->Initialize(dataPath);
	return obj;
}

float Goblin::GetFocusColliderSize()
{
	return 20;
}

D3DXVECTOR3 Goblin::GetFocusUIOffset()
{
	return D3DXVECTOR3(0, 5, 0);
}

int Goblin::GetLevel()
{
	return 13;
}

std::wstring Goblin::GetCharacterName()
{
	return L"고블린";
}

int Goblin::GetAttackCount()
{
	/* Goblin은 공격 종류가 1종류 */
	return 1;
}

Collider * Goblin::GetAttackCollider(int attackIndex)
{
	Collider* attackCollider = nullptr;
	if (attackIndex == 0)
	{
		attackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 5, Layer::Player,
			std::bind(&Goblin::OnHitOthers, this, placeholders::_1));
		attackCollider->SetOffset(D3DXVECTOR3(0, 0, 5));
	}
	else /* 1종류밖에 없음 */
		assert(false);

	return attackCollider;
}

