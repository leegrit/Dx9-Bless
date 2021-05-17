#include "stdafx.h"
#include "HGoblinAttack.h"
#include "HGoblin.h"


void HGoblinAttack::Enter()
{
	m_component->SetAnimationSet(21); // attack
	m_component->ClearHitOthers();
	m_elapsed = 0.0f;
	m_isAttacked = false;
}

void HGoblinAttack::Update()
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

void HGoblinAttack::Late_Update()
{
}

void HGoblinAttack::Exit()
{
	m_component->ClearHitOthers();
}
