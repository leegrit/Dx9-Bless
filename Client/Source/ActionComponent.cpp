#include "stdafx.h"
#include "ActionComponent.h"
#include "DynamicMesh.h"

ActionComponent::ActionComponent(DWORD type, GameObject * pOwner, std::wstring name)
	: Component(type,pOwner, name),
	m_attackDelay(0.2f),
	m_attackSeqCount(1),
	m_curSequence(0),
	m_attackRange(10),
	m_damage(10),
	m_bKnockBack(0),
	m_bNextAttack(false),
	m_nextAnimIndex(-1)
{

}

ActionComponent::~ActionComponent()
{
	Object::Destroy(m_pAttackCollider);
}

void ActionComponent::Initialize()
{


}

void ActionComponent::Update()
{

	if (m_bAttackState)
	{
		m_attackElapsed += TIMER->getDeltaTime();
		OnActionTimeElapsed(m_curSequence, m_attackElapsed);
	}

	if (m_bNextAttack == true)
	{
		DynamicMesh * pMesh = dynamic_cast<DynamicMesh*>(GetGameObject());
		assert(pMesh);
		bool animEnd = false;

		if (m_nextSequence != 0)
		{
			animEnd = pMesh->IsAnimationSetEnd(0.5);
		}
		else
			animEnd = true;
		if (animEnd == true)
		{
			//m_pPlayerController->SetState(EPlayerState::Attack);
			m_bAttackState = true;

			m_curSequence = m_nextSequence;

			pMesh->SetAnimationSet(m_nextAnimIndex);

			/* ���� ���� ���� */
			OnSequenceStart(m_curSequence);
			m_attackElapsed = 0;

			
			m_pAttackCollider->SetActive(true);

			m_bNextAttack = false;
		}
	}
	else if(m_bAttackState)
	{
		DynamicMesh * pMesh = dynamic_cast<DynamicMesh*>(GetGameObject());
		assert(pMesh);

		bool animEnd = pMesh->IsAnimationSetEnd(0.5);

		if (animEnd == true)
		{
			m_pAttackCollider->SetActive(false);
			OnActionEnd();
			m_bAttackState = false;
			pMesh->SetAnimationSet(GetIdleAnimIndex());
		}
	}
}

void ActionComponent::LateUpdate()
{
}

void ActionComponent::OnEnable()
{

}

void ActionComponent::OnDisable()
{
}


float ActionComponent::GetAttackDamage() const
{
	float minDmg = m_damage * 0.8f;
	float maxDmg = m_damage * 1.2f;
	return DxHelper::GetRandomFloat(minDmg, maxDmg);
}

bool ActionComponent::IsAttackState() const
{
	return m_bAttackState;
}

void ActionComponent::SetParams(float atkDelay, int seqCount,  float atkRange, float damage, bool bKnockBack, D3DXVECTOR3 colOffset)
{
	m_attackDelay = atkDelay;
	m_attackSeqCount = seqCount;
	m_attackRange = atkRange;
	m_damage = damage;
	m_bKnockBack = bKnockBack;
	m_colliderOffset = colOffset;

	m_pAttackCollider = SphereCollider::Create(EColliderType::Dynamic, GetGameObject(), m_attackRange, GetTargetLayer(),
		std::bind(&ActionComponent::OnHitOthers, this, placeholders::_1));
	m_pAttackCollider->SetOffset(m_colliderOffset);
}

bool ActionComponent::DoAction(int animIndex)
{
	/* Action�� DoAction�� ȣ������ �� */
	if (m_bAttackState == true)
	{
		if (m_bNextAttack == true)
			return false;
		if (m_curSequence == m_attackSeqCount - 1)
			return false;

		/* ���� �޺��� �ִ� ���¿��� ���� Ű�� ������ ��� */
		if (m_curSequence < m_attackSeqCount - 1)
		{
			m_bNextAttack = true;
			m_nextSequence++;
			m_nextAnimIndex = animIndex;
		}
		/* ������ �޺� ���� �߿� ���� Ű�� ������ ��� */
		else
		{
			m_bNextAttack = true;
			m_nextSequence = 0;
			m_nextAnimIndex = animIndex;
		}
	}
	else 
	{
		m_nextSequence = 0;
		m_bNextAttack = true;
		m_nextAnimIndex = animIndex;
	}
	return true;
}
