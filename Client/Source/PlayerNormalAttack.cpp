#include "stdafx.h"
#include "PlayerNormalAttack.h"

PlayerNormalAttack::PlayerNormalAttack(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update , pPlayer, pPlayerController, L"PlayerNormalAttack")
{
	SetParams(0.2f, 3, 0, 10, 10, false, D3DXVECTOR3(0, 10, 30));
}

PlayerNormalAttack::~PlayerNormalAttack()
{
}

void PlayerNormalAttack::Initialize()
{
	PlayerAction::Initialize();
}

void PlayerNormalAttack::Update()
{
	PlayerAction::Update();
	UpdateAction();
}

void PlayerNormalAttack::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerNormalAttack::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerNormalAttack::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerNormalAttack::OnHitOthers(Collider * other)
{
	PlayerAction::OnHitOthers(other);
}

void PlayerNormalAttack::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
}

void PlayerNormalAttack::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
}

void PlayerNormalAttack::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
}

UINT PlayerNormalAttack::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerNormalAttack::GetIdleAnimIndex() const
{
	return 39;
}

void PlayerNormalAttack::UpdateAction()
{
	if (MOUSE->Down(0))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerNormalAttack * PlayerNormalAttack::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerNormalAttack * com = new PlayerNormalAttack(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
