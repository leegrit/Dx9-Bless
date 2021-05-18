#include "stdafx.h"
#include "SoldierDied.h"
#include "Soldier.h"

void SoldierDied::Enter()
{
	m_component->SetAnimationSet(26);
}

void SoldierDied::Update()
{
}

void SoldierDied::Late_Update()
{
}

void SoldierDied::Exit()
{
}
