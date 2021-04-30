#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Scene * scene, NavMesh * pNavMesh, D3DXVECTOR3 colPosOffset, float colRadius)
	: Character(scene, pNavMesh, colPosOffset, colRadius)
{

}

Enemy::~Enemy()
{
}

void Enemy::Initialize(std::wstring dataPath)
{
	Character::Initialize(dataPath);

	/* Set Attack Data */
	m_attackCount = GetAttackCount();
	m_attackColliders.reserve(m_attackCount);
	for (int i = 0; i < m_attackCount; i++)
	{
		m_attackColliders.emplace_back(GetAttackCollider(i));
	}
}

void Enemy::Update()
{
	Character::Update();
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
