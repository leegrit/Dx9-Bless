#include "StandardEngineFramework.h"
#include "DummyBossAttack.h"
#include "DummyBoss.h"

void DummyBossAttack::Enter()
{
	// юс╫ц
	m_component->SetAnimationSet(17);
	m_component->ClearHitOthers();
	m_elapsed = 0;
}

void DummyBossAttack::Update()
{
	if (m_component->IsDamaged())
	{
		m_component->GetState()->Set("Hit");
	}
	if (m_component->IsDied())
	{
		m_component->GetState()->Set("Die");
	}

	m_elapsed += TIMER->getDeltaTime();

	if (m_elapsed >= 0.3f && m_isAttacked == false)
	{
		m_component->SendDamageToOthers(50);
		m_isAttacked = true;
	}

	bool animEnd = false;
	animEnd = m_component->IsAnimationSetEnd();
	if (animEnd == true)
	{
		m_component->GetState()->Set("Idle");
	}

}

void DummyBossAttack::Late_Update()
{
}

void DummyBossAttack::Exit()
{
	m_component->ClearHitOthers();
}
