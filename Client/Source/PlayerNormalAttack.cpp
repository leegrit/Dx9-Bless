#include "stdafx.h"
#include "PlayerNormalAttack.h"
#include "Character.h"

PlayerNormalAttack::PlayerNormalAttack(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update , pPlayer, pPlayerController, L"PlayerNormalAttack")
{
	SetParams(0.2f, 3, 0, 10, 10, false, D3DXVECTOR3(0, 10, 20));
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
	/* 여기서 데미지를 보낼 적들을 저장한다. */
	GameObject* go = other->GetGameObject();
	for (auto& obj : m_hitEnemies)
	{
		if (obj == go)
			return;
	}
	m_hitEnemies.push_back(go);
}

void PlayerNormalAttack::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage = false;
}

void PlayerNormalAttack::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);

	if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	case 0:
		if (elapsed >= 0.3f)
		{
			for (auto& obj : m_hitEnemies)
			{
				Character* enemy = dynamic_cast<Character*>(obj);
				enemy->SendDamage(GetGameObject(), GetAttackDamage());
			}
			m_bSendDamage = true;
		}
		break;
	case 1:
		if (elapsed >= 0.3f)
		{
			for (auto& obj : m_hitEnemies)
			{
				Character* enemy = dynamic_cast<Character*>(obj);
				enemy->SendDamage(GetGameObject(), GetAttackDamage());
			}
			m_bSendDamage = true;
		}
		break;
	case 2:
		if (elapsed >= 0.5f)
		{
			for (auto& obj : m_hitEnemies)
			{
				Character* enemy = dynamic_cast<Character*>(obj);
				enemy->SendDamage(GetGameObject(), GetAttackDamage());
			}
			m_bSendDamage = true;
		}
		break;
	}
}

void PlayerNormalAttack::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
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
