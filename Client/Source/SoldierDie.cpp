#include "stdafx.h"
#include "SoldierDie.h"
#include "Soldier.h"

void SoldierDie::Enter()
{
	m_component->SetAnimationSet(25); // die
}

void SoldierDie::Update()
{
	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Died");
	}
}

void SoldierDie::Late_Update()
{
}

void SoldierDie::Exit()
{
}
