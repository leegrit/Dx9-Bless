#include "stdafx.h"
#include "PlayerSkillUpper.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"

PlayerSkillUpper::PlayerSkillUpper(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerSkillUpper")
{
	SetParams(0.2f, 1, 0, 10, 10, false, D3DXVECTOR3(0, 10, 20));
}

PlayerSkillUpper::~PlayerSkillUpper()
{
}

void PlayerSkillUpper::Initialize()
{
	PlayerAction::Initialize();
}

void PlayerSkillUpper::Update()
{
	PlayerAction::Update();
	UpdateAction();
}

void PlayerSkillUpper::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerSkillUpper::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerSkillUpper::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerSkillUpper::OnHitOthers(Collider * other)
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

void PlayerSkillUpper::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage = false;

}

void PlayerSkillUpper::OnActionTimeElapsed(int seqIndex, float elapsed)
{
	PlayerAction::OnActionTimeElapsed(seqIndex, elapsed);
	std::cout << "실제 인덱스 : " << seqIndex << std::endl;
	if (m_bSendDamage == true) return;
	switch (seqIndex)
	{
	case 0:
		if (elapsed >= 0.3f)
		{
			for (auto& obj : m_hitEnemies)
			{
				GameScene* pScene = static_cast<GameScene*>(SCENE);
				if (pScene->GetBattleManager()->GetFocusedObject() == nullptr)
					return;
				/*if (obj->GetInstanceID() != pScene->GetBattleManager()->GetFocusedObject()->GetInstanceID())
				{
					continue;
				}*/

				Character* enemy = dynamic_cast<Character*>(obj);
				enemy->SendDamage(GetGameObject(), GetAttackDamage());
				//GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
				//pScene->GetEffectManager()->PlayEffect(L"PlayerNormalAttack_SwordTrailEffect");
				std::cout << "Do First" << std::endl;
				CAMERA->Shake(0.1f, 0.1f, 1.0f);
			}
			m_bSendDamage = true;
		}
		break;
	}
}

void PlayerSkillUpper::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
}

UINT PlayerSkillUpper::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerSkillUpper::GetIdleAnimIndex() const
{
	return 89;
}

void PlayerSkillUpper::UpdateAction()
{
	if (KEYBOARD->Down(48 + 2))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerSkillUpper * PlayerSkillUpper::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerSkillUpper * com = new PlayerSkillUpper(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
