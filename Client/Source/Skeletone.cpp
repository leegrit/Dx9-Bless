#include "stdafx.h"
#include "Skeletone.h"
#include "SkeletoneAttack.h"
#include "SkeletoneDie.h"
#include "SkeletoneHit.h"
#include "SkeletoneIdle.h"
#include "SkeletoneMove.h"

Skeletone::Skeletone(Scene * pScene, NavMesh * pNavMesh)
	:Character(pScene, pNavMesh, D3DXVECTOR3(0, 10, 0), 5)
{
	SetLayer(Layer::Enemy);
}

Skeletone::~Skeletone()
{
	m_state.Release();
}

void Skeletone::Initialize(std::wstring dataPath)
{
	Character::Initialize(dataPath);
	SetLayer(Layer::Enemy);

	SetParams(10, 100, 100);

	m_state.Add<SkeletoneAttack>(this, "Attack");
	m_state.Add<SkeletoneDie>(this, "Die");
	m_state.Add<SkeletoneHit>(this, "Hit");
	m_state.Add<SkeletoneIdle>(this, "Idle");
	m_state.Add<SkeletoneMove>(this, "Move");

	m_state.Initialize("Idle");
}

void Skeletone::Update()
{
	Character::Update();

	m_state.Update();
}

UINT Skeletone::GetTargetLayer() 
{
	return Layer::Player;
}

void Skeletone::OnCollision(Collider * other)
{
	if(other->GetGameObject()->GetLayer() & Layer::Player)
		int a = 0;
}

Skeletone * Skeletone::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	Skeletone * skeletone = new Skeletone(pScene, pNavMesh);
	skeletone->Initialize(dataPath);
	return skeletone;
}
