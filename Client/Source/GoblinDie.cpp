#include "stdafx.h"
#include "GoblinDie.h"
#include "Goblin.h"

void GoblinDie::Enter()
{
	m_component->SetAnimationSet(16); // die
}

void GoblinDie::Update()
{
	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd(0.3f);
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
