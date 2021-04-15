#include "stdafx.h"
#include "Character.h"

Character::Character(Scene * scene, NavMesh * pNavMesh, D3DXVECTOR3 colPosOffset, float colRadius)
	: Pawn(scene, nullptr, pNavMesh)
{
	m_pCollider = SphereCollider::Create(EColliderType::Static, this, colRadius, GetTargetLayer(),
		std::bind(&Character::OnCollision, this, placeholders::_1));
	m_pCollider->SetOffset(colPosOffset);
}

Character::~Character()
{
}

void Character::Initialize(std::wstring dataPath)
{
	Pawn::Initialize(dataPath);

}

void Character::Update()
{
	Pawn::Update();
}

float Character::GetMoveSpeed() const
{
	return m_moveSpeed;
}

float Character::GetMaxHP() const
{
	return m_maxHP;
}

float Character::GetCurHP() const
{
	return m_curHP;
}

float Character::GetMaxMP() const
{
	return m_maxMP;
}

float Character::GetCurMP() const
{
	return m_curMP;
}

void Character::SetParams(float moveSpd, float maxHP, float maxMP)
{
	m_moveSpeed = moveSpd;
	m_maxHP = maxHP;
	m_curHP = maxHP;
	m_maxMP = maxMP;
	m_curMP = maxMP;
}

UINT Character::GetTargetLayer()
{
	return Layer::Default;
}
