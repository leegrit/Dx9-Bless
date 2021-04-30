#include "stdafx.h"
#include "SkeletoneDie.h"
#include "Skeletone.h"

void SkeletoneDie::Enter()
{
	// DeadBody = 18
	m_component->SetAnimationSet(17);
}

void SkeletoneDie::Update()
{
	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Died");
	}
}

void SkeletoneDie::Late_Update()
{
}

void SkeletoneDie::Exit()
{
}
