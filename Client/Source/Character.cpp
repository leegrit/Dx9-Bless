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

bool Character::IsDamaged() const
{
	return m_isDamaged;
}

bool Character::IsDied() const
{
	return m_isDied;
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

void Character::SetDamagedState(bool isDamaged)
{
	m_isDamaged = isDamaged;
}

UINT Character::GetTargetLayer()
{
	return Layer::Default;
}

void Character::SendDamage(GameObject * sender, float damage)
{
	assert(m_isDied == false);

	float resultHP = m_curHP - damage;
	if (resultHP <= 0)
	{
		m_curHP = 0;
	}
	else
		m_curHP = resultHP;

	if (m_curHP <= 0)
		m_isDied = true;
	else
		m_isDamaged = true;
}
