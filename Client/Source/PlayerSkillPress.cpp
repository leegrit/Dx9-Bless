#include "stdafx.h"
#include "PlayerSkillPress.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"

PlayerSkillPress::PlayerSkillPress(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerNormalAttack")
{
	SetParams(0.2f, 1, 0, 10, 10, false, D3DXVECTOR3(0, 10, 20));
}

PlayerSkillPress::~PlayerSkillPress()
{
}

void PlayerSkillPress::Initialize()
{
	PlayerAction::Initialize();
}

void PlayerSkillPress::Update()
{
	PlayerAction::Update();
	UpdateAction();
}

void PlayerSkillPress::LateUpdate()
{
	PlayerAction::LateUpdate();
}

void PlayerSkillPress::OnEnable()
{
	PlayerAction::OnEnable();
}

void PlayerSkillPress::OnDisable()
{
	PlayerAction::OnDisable();
}

void PlayerSkillPress::OnHitOthers(Collider * other)
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

void PlayerSkillPress::OnSequenceStart(int seqIndex)
{
	PlayerAction::OnSequenceStart(seqIndex);
	m_seqIndex = seqIndex + 1;
	m_hitEnemies.clear();
	m_bSendDamage = false;
}

void PlayerSkillPress::OnActionTimeElapsed(int seqIndex, float elapsed)
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
				pScene->GetEffectManager()->PlayEffect(L"PlayerNormalAttack_SwordTrailEffect");
				std::cout << "Do First" << std::endl;
				CAMERA->Shake(0.1f, 0.1f, 1.0f);
			}
			m_bSendDamage = true;
		}
		break;
	}
}

void PlayerSkillPress::OnActionEnd()
{
	PlayerAction::OnActionEnd();
	m_seqIndex = 0;
	m_hitEnemies.clear();
}

UINT PlayerSkillPress::GetTargetLayer() const
{
	return Layer::Enemy;
}

int PlayerSkillPress::GetIdleAnimIndex() const
{
	return 89;
}

void PlayerSkillPress::UpdateAction()
{
	if (KEYBOARD->Down(48 + 5))
	{
		DoAction(m_animIndexes[m_seqIndex]);
	}
}

PlayerSkillPress * PlayerSkillPress::Create(GameObject * pPlayer, PlayerController * pPlayerController)
{
	PlayerSkillPress * com = new PlayerSkillPress(pPlayer, pPlayerController);
	com->Initialize();
	return com;
}
