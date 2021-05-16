#include "stdafx.h"
#include "PlayerSkillUpper.h"
#include "Character.h"
#include "GameScene.h"
#include "BattleManager.h"
#include "EffectManager.h"
#include "PathManager.h"
#include "Effect.h"
#include "SoundManager.h"

PlayerSkillUpper::PlayerSkillUpper(GameObject * pPlayer, PlayerController * pPlayerController)
	: PlayerAction(BehaviourType::Update, pPlayer, pPlayerController, L"PlayerSkillUpper")
{
	SetParams(0.2f, 1, 3, 10, 10, false, D3DXVECTOR3(0, 10, 20));

	GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());


	MeshEffectDesc effectDesc0;
	effectDesc0.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_Vortex01_SM_KKJ.X";
	effectDesc0.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_Tornado.tga";
	effectDesc0.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_toneido_01.tga";
	effectDesc0.fadeOut = true;
	effectDesc0.lifeTime = 0.5f;
	effectDesc0.startScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	effectDesc0.endRot = D3DXVECTOR3(0, -360, 0);
	effectDesc0.endScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	m_pEffect0 = pScene->GetEffectManager()->AddEffect(L"PlayerSkillUpper_Effect0", effectDesc0);

	MeshEffectDesc effectDesc1;
	effectDesc1.meshPath = PATH->AssetsPathW() + L"Effect/EffectMesh/FX_EnergyWave.X";
	effectDesc1.diffusePath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_EnergyWave_001_TEX_HKB.tga";
	//effectDesc1.alphaMaskPath = PATH->AssetsPathW() + L"Effect/SingleTexture/FX_toneido_01.tga";
	effectDesc1.fadeOut = true;
	effectDesc1.lifeTime = 0.5f;
	effectDesc1.endScale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	m_pEffect1 = pScene->GetEffectManager()->AddEffect(L"PlayerSkillUpper_Effect1", effectDesc1);


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


	m_pEffect0->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(0, 11, 7))
	);
	m_pEffect0->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 0, 0)
	);
	m_pEffect0->SetOriginScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));

	m_pEffect1->SetOriginPos(
		GetGameObject()->m_pTransform->CalcOffset(D3DXVECTOR3(0, 0, 10))
	);
	m_pEffect1->SetOriginRot
	(
		GetGameObject()->m_pTransform->m_rotationEuler.operator D3DXVECTOR3() + D3DXVECTOR3(0, 0, 0)
	);
	m_pEffect1->SetOriginScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));

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
			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("PlayerSkillUpper", L"Lups_5Space.mp3", desc);
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
				pScene->GetEffectManager()->PlayEffect(L"PlayerSkillUpper_Effect0");
				pScene->GetEffectManager()->PlayEffect(L"PlayerSkillUpper_Effect1");
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
