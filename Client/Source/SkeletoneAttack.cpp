#include "stdafx.h"
#include "SkeletoneAttack.h"
#include "Skeletone.h"

void SkeletoneAttack::Enter()
{
	m_component->SetAnimationSet(20);
}

void SkeletoneAttack::Update()
{
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
