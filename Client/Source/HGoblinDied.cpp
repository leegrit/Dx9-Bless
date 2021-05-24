#include "stdafx.h"
#include "HGoblinDied.h"
#include "HGoblin.h"

void HGoblinDied::Enter()
{
	m_component->SetAnimationSet(20);
	m_elapsed = 0.0f;
}

void HGoblinDied::Update()
{
	m_elapsed += TIMER->getDeltaTime() * 0.2f;
	m_component->SetDissolveAmount(m_elapsed);
}

void HGoblinDied::Late_Update()
{
}

void HGoblinDied::Exit()
{
}
