#include "StandardEngineFramework.h"
#include "NamedEnemy.h"

NamedEnemy::NamedEnemy(Scene * pScene, NavMesh * pNavMesh, D3DXVECTOR3 colPosOffset, float colRadius)
	: Enemy(pScene, pNavMesh, colPosOffset, colRadius)
{


}

NamedEnemy::~NamedEnemy()
{

}

void NamedEnemy::Initialize(std::wstring dataPath)
{
	Character::Initialize(dataPath);


}

void NamedEnemy::Update()
{
	Character::Update();


}

UINT NamedEnemy::GetTargetLayer()
{
	return 0;
}

void NamedEnemy::OnCollision(Collider * other)
{
}

int NamedEnemy::GetAttackCount()
{
	return 0;
}

Collider * NamedEnemy::GetAttackCollider(int attackIndex)
{
	return nullptr;
}
