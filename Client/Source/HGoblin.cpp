#include "stdafx.h"
#include "HGoblin.h"
#include "HGoblinAttack.h"
#include "HGoblinDie.h"
#include "HGoblinDied.h"
#include "HGoblinHit.h"
#include "HGoblinIdle.h"
#include "HGoblinMove.h"
#include "NameFont.h"
#include "Client_Events.h"

HGoblin::HGoblin(Scene * pScene, NavMesh * pNavMesh)
	: NamedEnemy(pScene, pNavMesh,D3DXVECTOR3(0, 15, 0), 10, ESkinningType::SoftwareSkinning)
{

}

HGoblin::~HGoblin()
{
	m_state.Release();
}

void HGoblin::Initialize(std::wstring dataPath)
{
	NamedEnemy::Initialize(dataPath);

	SetParams(15, 10000, 1000);


	m_state.Add<HGoblinAttack>(this, "Attack");
	m_state.Add<HGoblinDie>(this, "Die");
	m_state.Add<HGoblinHit>(this, "Hit");
	m_state.Add<HGoblinIdle>(this, "Idle");
	m_state.Add<HGoblinMove>(this, "Move");
	m_state.Add<HGoblinDied>(this, "Died");

	m_state.Initialize("Idle");

	m_pNameFont = new NameFont();
	m_pNameFont->Initialize(L"홉 고블린", this, D3DXVECTOR2(0.8f, 0.8f), D3DXVECTOR3(0, 16, 0), -40, D3DXCOLOR(1, 1, 0, 1));

	ShowHPBar();
}

void HGoblin::Update()
{
	NamedEnemy::Update();

	m_state.Update();


}

void HGoblin::Render()
{
	NamedEnemy::Render();

	m_pNameFont->RenderFont();
}

UINT HGoblin::GetTargetLayer()
{
	return Layer::Player;
}

void HGoblin::OnCollision(Collider * other)
{
}

int HGoblin::GetAttackCount()
{
	return 1;
}

Collider * HGoblin::GetAttackCollider(int attackIndex)
{
	Collider * pAttackCollider = nullptr;
	if (attackIndex == 0)
	{
		pAttackCollider = SphereCollider::Create(EColliderType::Dynamic, this, 10, Layer::Player,
			std::bind(&HGoblin::OnHitOthers, this, placeholders::_1));
		pAttackCollider->SetOffset(D3DXVECTOR3(0, 0, 10));
	}
	else /* 한종류밖에 없음 */
		assert(false);

	return pAttackCollider;
}

void HGoblin::OnHitOthers(Collider * other)
{
	AddHitOthers(other->GetGameObject());
}

float HGoblin::GetFocusColliderSize()
{
	return 20.0f;
}

D3DXVECTOR3 HGoblin::GetFocusUIOffset()
{
	return D3DXVECTOR3(0, 10, 0);
}

int HGoblin::GetLevel()
{
	return 30;
}

std::wstring HGoblin::GetCharacterName()
{
	return L"홉 고블린";
}

HGoblin * HGoblin::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	HGoblin* boss = new HGoblin(pScene, pNavMesh);
	boss->Initialize(dataPath);
	return boss;
}
