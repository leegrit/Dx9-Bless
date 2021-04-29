#include "stdafx.h"
#include "SkeletoneAttack.h"
#include "Skeletone.h"

void SkeletoneAttack::Enter()
{
	m_component->SetAnimationSet(20);
}

void SkeletoneAttack::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->GetState()->Set("Hit");
	}
	if (m_component->IsDamaged())
	{
		m_component->GetState()->Set("Die");
	}
	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Idle");
	}
}

void SkeletoneAttack::Late_Update()
{
}

void SkeletoneAttack::Exit()
{
}
