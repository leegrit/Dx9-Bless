#include "stdafx.h"
#include "SoldierAttack.h"
#include "Soldier.h"
void SoldierAttack::Enter()
{
	m_component->SetAnimationSet(1); // attack
	m_component->ClearHitOthers();
	m_elapsed = 0.0f;
	m_isAttacked = false;
}

void SoldierAttack::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->GetState()->Set("Hit");
	}
	if (m_component->IsDied())
	{
		m_component->GetState()->Set("Die");
	}

	m_elapsed += TIMER->getDeltaTime();

	if (m_elapsed >= 0.3f && m_isAttacked == false)
	{
		m_component->SendDamageToOthers(50);
		m_isAttacked = true;
	}

	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Idle");
	}
}

void SoldierAttack::Late_Update()
{
}

void SoldierAttack::Exit()
{
	m_component->ClearHitOthers();
}
