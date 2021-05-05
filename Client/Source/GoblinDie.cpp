#include "stdafx.h"
#include "GoblinDie.h"
#include "Goblin.h"

void GoblinDie::Enter()
{
	m_component->SetAnimationSet(20);
}

void GoblinDie::Update()
{
	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Died");
	}
}

void GoblinDie::Late_Update()
{
}

void GoblinDie::Exit()
{
}
