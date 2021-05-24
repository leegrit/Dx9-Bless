#include "stdafx.h"
#include "GoblinDied.h"
#include "Goblin.h"


void GoblinDied::Enter()
{
	m_component->SetAnimationSet(17);
	m_elapsed = 0.0f;
}

void GoblinDied::Update()
{
	m_elapsed += TIMER->getDeltaTime() * 0.2f;
	m_component->SetDissolveAmount(m_elapsed);
}

void GoblinDied::Late_Update()
{
}

void GoblinDied::Exit()
{
}
