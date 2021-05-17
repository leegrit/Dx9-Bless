#include "stdafx.h"
#include "HGoblinDie.h"
#include "HGoblin.h"

void HGoblinDie::Enter()
{
	m_component->SetAnimationSet(19); // die
}

void HGoblinDie::Update()
{
	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Died");
	}
}

void HGoblinDie::Late_Update()
{
}

void HGoblinDie::Exit()
{
}
