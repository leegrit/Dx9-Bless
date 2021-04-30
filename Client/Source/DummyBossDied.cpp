#include "StandardEngineFramework.h"
#include "DummyBossDied.h"
#include "DummyBoss.h"

void DummyBossDied::Enter()
{
	m_component->SetAnimationSet(15);
}

void DummyBossDied::Update()
{
}

void DummyBossDied::Late_Update()
{
}

void DummyBossDied::Exit()
{
}
