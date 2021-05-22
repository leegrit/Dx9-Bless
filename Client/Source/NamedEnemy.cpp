#include "StandardEngineFramework.h"
#include "NamedEnemy.h"

NamedEnemy::NamedEnemy(Scene * pScene, NavMesh * pNavMesh, D3DXVECTOR3 colPosOffset, float colRadius, ESkinningType skinningType)
	: Enemy(pScene, pNavMesh, colPosOffset, colRadius, skinningType)
{


}

NamedEnemy::~NamedEnemy()
{

}

void NamedEnemy::Initialize(std::wstring dataPath)
{
	Enemy::Initialize(dataPath);


}

void NamedEnemy::Update()
{
	Enemy::Update();
	if (m_hited)
	{
		m_hitElapsed += TIMER->getDeltaTime();
		if (m_hitElapsed >= m_reactionDuration)
		{
			m_hited = false;
			m_hitElapsed = 0;
		}
		SetRenderEffectOption(RenderEffectOption::RimLight);
		SetRimWidth(1.0f);
		SetRimColor(D3DXCOLOR(1, 1, 1, 1));
	}
	else
	{
		SetRimWidth(0.0f);
	}
	//SetRenderEffectOption(RenderEffectOption::None);
}

void NamedEnemy::Render()
{
	Enemy::Render();
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

void NamedEnemy::OnDamaged(GameObject * pSender, float damage, bool isCritical)
{
	Enemy::OnDamaged(pSender, damage, isCritical);
	m_hited = true;
	/*SetRenderEffectOption(RenderEffectOption::RimLight);
	SetRimWidth(1.0f);
	SetRimColor(D3DXCOLOR(1, 0, 0, 1));*/
}
