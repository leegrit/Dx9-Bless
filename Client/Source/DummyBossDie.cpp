#include "StandardEngineFramework.h"
#include "DummyBossDie.h"
#include "DummyBoss.h"

void DummyBossDie::Enter()
{
	m_component->SetAnimationSet(14);
}

void DummyBossDie::Update()
{
	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Died");
	}
}

void DummyBossDie::Late_Update()
{
}

void DummyBossDie::Exit()
{
}
