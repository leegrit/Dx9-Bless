#include "stdafx.h"
#include "Player.h"
#include "PlayerController.h"
#include "PlayerNormalAttack.h"
#include "PlayerInfo.h"
#include "ExpTable.h"
#include "GameScene.h"
#include "UIManager.h"
#include "ProgressBar.h"
#include "Client_Events.h"
#include "PathManager.h"
#include "PlayerSkillBuff.h"
#include "PlayerSkillPress.h"
#include "PlayerSkillShield.h"
#include "PlayerSkillSwing.h"
#include "PlayerSkillSwingDown.h"
#include "PlayerSkillTornado.h"
#include "PlayerSkillUpper.h"
#include "PlayerSkillStab.h"
#include "PlayerAfterImage.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "PlayerShieldAttack.h"

Player::Player(Scene * pScene, NavMesh * pNavMesh)
	:Character(pScene, pNavMesh, D3DXVECTOR3(0, 10, 0), 8, ESkinningType::HardwareSkinning)
{
	SetLayer(Layer::Player);

	//SetSkinningType(ESkinningType::HardwareSkinning);


	EventDispatcher::AddEventListener(GameEvent::SendExp, std::to_string(GetInstanceID()),
		std::bind(&Player::OnExpChanged, this, placeholders::_1));
	EventDispatcher::AddEventListener(QuestEvent::QuestDialogOpen, std::to_string(GetInstanceID()),
		std::bind(&Player::OnDialogOpen, this, placeholders::_1));
	EventDispatcher::AddEventListener(QuestEvent::QuestDialogEnd, std::to_string(GetInstanceID()),
		std::bind(&Player::OnDialogEnd, this, placeholders::_1));

}

Player::~Player()
{
	EventDispatcher::RemoveEventListener(GameEvent::SendExp, std::to_string(GetInstanceID()));
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogOpen, std::to_string(GetInstanceID()));
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogEnd, std::to_string(GetInstanceID()));

}

void Player::Initialize(std::wstring dataPath)
{
	Pawn::Initialize(dataPath);
	//SetRenderEffectOption(RenderEffectOption::RimLight);
	//SetRimWidth(0.3f);
	SetParams(30, 1000, 1000);
	
	m_pPlayerController = PlayerController::Create(this);
	AddComponent(m_pPlayerController);
	AddComponent(PlayerNormalAttack::Create(this, m_pPlayerController));
	//AddComponent(PlayerSkillBuff::Create(this, m_pPlayerController));
	//AddComponent(PlayerSkillPress::Create(this, m_pPlayerController));
	m_pPlayerSkills.push_back((PlayerAction*)AddComponent(PlayerSkillShield::Create(this, m_pPlayerController)));
	m_pPlayerSkills.push_back((PlayerAction*)AddComponent(PlayerSkillSwing::Create(this, m_pPlayerController)));
	//AddComponent(PlayerSkillSwingDown::Create(this, m_pPlayerController));
	//m_pPlayerSkills.push_back((PlayerAction*)AddComponent(PlayerSkillStab::Create(this, m_pPlayerController)));
	m_pPlayerSkills.push_back((PlayerAction*)AddComponent(PlayerShieldAttack::Create(this, m_pPlayerController)));
	m_pPlayerSkills.push_back((PlayerAction*)AddComponent(PlayerSkillTornado::Create(this, m_pPlayerController)));
	m_pPlayerSkills.push_back((PlayerAction*)AddComponent(PlayerSkillBuff::Create(this, m_pPlayerController)));



	m_pAfterImage = PlayerAfterImage::Create(GetScene(), nullptr, PATH->DatasPathW() + L"HierarchyData/Hieracon_Player.json", ESkinningType::HardwareSkinning);
	m_pAfterImage->SetActive(false);
	m_pAfterImage->SetRenderEffectOption(RenderEffectOption::RimLight);
	m_pAfterImage->SetRimWidth(0.7f);

	m_pPlayerUW = DynamicMesh::Create(GetScene(), nullptr, L"Player", PATH->DatasPathW() + L"HierarchyData/PlayerUnWeapon.json", GetSkinningType());
	m_pPlayerUW->SetActive(false);

	m_pPegasus = DynamicMesh::Create(GetScene(), nullptr, L"Pegasus", PATH->DatasPathW() + L"HierarchyData/Pegasus.json", ESkinningType::SoftwareSkinning);
	m_pPegasus->SetActive(false);

	m_pPlayerController->SetUnWeaponMesh(m_pPlayerUW);
	m_pPlayerController->SetHorse(m_pPegasus);


	//////////////////////////////////////////////////////////////////////////
	// TEST
	//////////////////////////////////////////////////////////////////////////
	//SetDissolveTexture(PATH->AssetsPathW() + L"Texture/dissolveMap.jpg");
	//SetDissolveAmount(0.5f);
	//SetFringeAmount(0.01f);

}

Player * Player::Create(Scene * pScene, NavMesh * pNavMesh, std::wstring dataPath)
{
	Player* player = new Player(pScene, pNavMesh);
	player->Initialize(dataPath);
	return player;
}

void Player::OnCollision(Collider * other)
{
}

void Player::OnDamaged(GameObject * pSender, float damage, bool isCritical)
{
	GameScene* scene = static_cast<GameScene*>(SCENE);
	scene->GetUIManager()->PushDamageFont(damage, true, isCritical, m_pTransform->CalcOffset(D3DXVECTOR3(0, 10, 0)));
	CAMERA->Shake(0.2f, 0.2f, 1.0f);

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 1;
	SOUND->PlaySound("PlayerHit", L"Hit_Player_Blood.wav", desc);


}

void Player::OnHPChanged()
{
	if (m_pHPBarUI == nullptr)
	{
		GameScene * scene = static_cast<GameScene*>(SCENE);
		m_pHPBarUI = static_cast<HyEngine::ProgressBar*>(scene->GetUIManager()->GetStaticUI(L"PlayerHP_Fill"));
	}
	m_pHPBarUI->SetAmount(GetCurHP() / GetMaxHP());
}

void Player::OnMPChanged()
{
	if (m_pMPBarUI == nullptr)
	{
		GameScene * scene = static_cast<GameScene*>(SCENE);
		m_pMPBarUI = static_cast<ProgressBar*>( scene->GetUIManager()->GetStaticUI(L"PlayerMP_Fill"));
	}
	m_pMPBarUI->SetAmount(GetCurMP() / GetMaxMP());
}

void Player::Update()
{
	Pawn::Update();

	m_pAfterImage->m_pTransform->SetPosition(m_pTransform->m_position);
	m_pAfterImage->m_pTransform->m_rotationEuler = m_pTransform->m_rotationEuler;
	m_pAfterImage->m_pTransform->SetScale(m_pTransform->m_scale);


	//////////////////////////////////////////////////////////////////////////
	// WEAPON EFFECT TEST
	//////////////////////////////////////////////////////////////////////////
	//WeaponAfterEffectDesc desc;
	//desc.lifeTime = 0.5f;
	//desc.worldMat = m_pWeapon->GetWorldMatrix();
	//GameScene* pScene = static_cast<GameScene*>(GetScene());
	//pScene->GetEffectManager()->PlayerWeaponAffterEffect(desc);

}

void Player::Render()
{
	/*if (m_isUnWeapon == true)
		return;
	if (m_bMount == true)
		return;*/
	if (m_pPlayerController->GetState() == EPlayerState::MountOnHorse)
		return;
	if (m_pPlayerController->GetState() == EPlayerState::Collecting)
		return;
	if (m_pPlayerController->GetFormState() == PlayerController::EFormStat::UnWeapon)
		return;
	Pawn::Render();
}

void Player::OnExpChanged( void*) 
{
	if (m_pExpBarUI == nullptr)
	{
		GameScene * scene = static_cast<GameScene*>(SCENE);
		m_pExpBarUI = static_cast<ProgressBar*>(scene->GetUIManager()->GetStaticUI(L"PlayerExp_Fill"));
		m_pExpBarUI->SetRenderQueue(2000);
	}
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	float amount;
	if (pScene->GetPlayerInfo()->level == 1)
	{
		amount = pScene->GetPlayerInfo()->exp / (float)pScene->GetExpTable()->expTable[pScene->GetPlayerInfo()->level - 1];
	}
	else
	{
		// º¸Á¤Ä¡
		float temp = pScene->GetExpTable()->expTable[pScene->GetPlayerInfo()->level - 2];
		amount = (pScene->GetPlayerInfo()->exp - temp) / (pScene->GetExpTable()->expTable[pScene->GetPlayerInfo()->level - 1] - temp);
	}
	m_pExpBarUI->SetAmount(amount);
}

void Player::OnDialogOpen(void *)
{
	SetActive(false);
}

void Player::OnDialogEnd(void *)
{
	SetActive(true);
}

PlayerAction * Player::GetPlayerSkill(int skillIndex)
{
	return m_pPlayerSkills.at(skillIndex);
}

void Player::SetWeapon(GameObject * weapon)
{
	m_pWeapon = weapon;
}

void Player::SetShield(GameObject * shield)
{
	m_pShield = shield;
}



GameObject * Player::GetWeapon()
{
	return m_pWeapon;
}

GameObject * Player::GetShield()
{
	return m_pShield;
}

PlayerAfterImage * Player::GetAfterImage() const
{
	return m_pAfterImage;
}
