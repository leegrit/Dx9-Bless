#include "stdafx.h"
#include "GoblinAttack.h"
#include "Goblin.h"

void GoblinAttack::Enter()
{
	m_component->SetAnimationSet(24);
	m_component->ClearHitOthers();
	m_elapsed = 0.0f;
	m_isAttacked = false;
}

void GoblinAttack::Update()
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

void GoblinAttack::Late_Update()
{
}

void GoblinAttack::Exit()
{
	m_component->ClearHitOthers();
}
