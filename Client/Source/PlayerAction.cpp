#include "stdafx.h"
#include "PlayerAction.h"
#include "PlayerController.h"
#include "Player.h"
PlayerAction::PlayerAction(DWORD behaviourType, GameObject * pOwner, PlayerController * pPlayerController, std::wstring name)
	: ActionComponent(behaviourType, pOwner, name),
	m_pPlayerController(pPlayerController),
	m_coolTime(0),
	m_curCoolTime(0)

{
	assert(pOwner);
	assert(pPlayerController);
}

PlayerAction::~PlayerAction()
{
}

void PlayerAction::Initialize()
{
	ActionComponent::Initialize();

}

void PlayerAction::Update()
{
	ActionComponent::Update();
	
	m_curCoolTime += TIMER->getDeltaTime();
}

void PlayerAction::LateUpdate()
{
	ActionComponent::LateUpdate();
}

void PlayerAction::OnEnable()
{
	ActionComponent::OnEnable();
}

void PlayerAction::OnDisable()
{
	ActionComponent::OnDisable();
}

void PlayerAction::OnHitOthers(Collider * other)
{
}

void PlayerAction::OnSequenceStart(int seqIndex)
{
	m_pPlayerController->SetState(EPlayerState::Attack);
}

void PlayerAction::OnActionTimeElapsed(int seqIndex, float elapsed)
{

}

void PlayerAction::OnActionEnd()
{
	m_pPlayerController->SetState(EPlayerState::Idle);
	m_curCoolTime = 0;
}


float PlayerAction::GetCoolTime()
{
	return m_coolTime;
}

float PlayerAction::GetCurCoolTime()
{

	return m_curCoolTime;
}

void PlayerAction::SetParams(float atkDelay, int seqCount, float coolTime, float atkRange, float damage, bool bKnockBack, D3DXVECTOR3 colOffset)
{
	ActionComponent::SetParams(atkDelay, seqCount, atkRange, damage, bKnockBack, colOffset);
	m_coolTime = coolTime;
	m_curCoolTime = m_coolTime;
}

bool PlayerAction::DoAction(int animIndex)
{
	EPlayerState state = m_pPlayerController->GetState();

	if (state == EPlayerState::Hit) return false;
	if (state == EPlayerState::Die) return false;
	if (state == EPlayerState::Jump)return false;
	if (state == EPlayerState::OtherAction) return false;
	if (state == EPlayerState::OtherEvent) return false;
	if (m_coolTime > m_curCoolTime) return false;
	if (state == EPlayerState::Attack && IsAttackState() == false) return false;

	ActionComponent::DoAction(animIndex);
	
	return true;
}
