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

Player::Player(Scene * pScene, NavMesh * pNavMesh)
	:Character(pScene, pNavMesh, D3DXVECTOR3(0, 10, 0), 8, ESkinningType::HardwareSkinning)
{
	SetLayer(Layer::Player);

	//SetSkinningType(ESkinningType::HardwareSkinning);


	EventDispatcher::AddEventListener(GameEvent::SendExp, std::to_string(GetInstanceID()),
		std::bind(&Player::OnExpChanged, this, placeholders::_1));
}

Player::~Player()
{
	EventDispatcher::RemoveEventListener(GameEvent::SendExp, std::to_string(GetInstanceID()));
}

void Player::Initialize(std::wstring dataPath)
{
	Pawn::Initialize(dataPath);
	SetParams(50, 1000, 1000);
	
	m_pPlayerController = PlayerController::Create(this);
	AddComponent(m_pPlayerController);
	AddComponent(PlayerNormalAttack::Create(this, m_pPlayerController));

	m_pPlayerUW = DynamicMesh::Create(GetScene(), nullptr, L"Player", PATH->DatasPathW() + L"HierarchyData/PlayerUnWeapon.json", GetSkinningType());
	m_pPlayerUW->SetActive(false);

	m_pPegasus = DynamicMesh::Create(GetScene(), nullptr, L"Pegasus", PATH->DatasPathW() + L"HierarchyData/Pegasus.json", ESkinningType::SoftwareSkinning);
	m_pPegasus->SetActive(false);

	m_pPlayerController->SetUnWeaponMesh(m_pPlayerUW);
	m_pPlayerController->SetHorse(m_pPegasus);
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
	if (m_pHPBarUI == nullptr)
	{
		GameScene * scene = static_cast<GameScene*>(SCENE);
		m_pMPBarUI = static_cast<ProgressBar*>( scene->GetUIManager()->GetStaticUI(L"PlayerMP_Fill"));
	}
	m_pMPBarUI->SetAmount(GetCurMP() / GetMaxMP());
}

void Player::Update()
{
	Pawn::Update();
	/*if (MOUSE->Down(1))
	{
		SetAnimationSet(0);
	}*/

	/*if (KEYBOARD->Up(VK_F1))
	{
		if (m_bMount == false)
		{
			m_pPlayerUW->SetAnimationSet(249);
			m_pPegasus->SetAnimationSet(19);
			m_pPlayerUW->SetActive(true);
			m_pPegasus->SetActive(true);
			m_pPlayerUW->m_pTransform->m_position = m_pTransform->CalcOffset(D3DXVECTOR3(0, 5, 0));
			m_pPlayerUW->m_pTransform->m_rotationEuler = m_pTransform->m_rotationEuler;
			m_pPlayerUW->m_pTransform->m_scale = m_pTransform->m_scale;
			m_pPegasus->m_pTransform->m_position = m_pTransform->m_position;
			m_pPegasus->m_pTransform->m_rotationEuler = m_pTransform->m_rotationEuler;
			m_pPegasus->m_pTransform->m_scale = m_pTransform->m_scale;

		}
	}*/

	/*if (KEYBOARD->Press('F'))
	{
		if (m_beginElapsed == 0)
		{
			m_pPlayerController->SetState(EPlayerState::PutInWeapon);
			m_pPlayerUW->SetAnimationSet(304);
			SetAnimationSet(112);
		}
		m_beginElapsed += TIMER->getDeltaTime();
		if (m_beginElapsed >= m_delay && m_isUnWeapon == false)
		{
			m_isUnWeapon = true;
			m_pPlayerUW->SetActive(true);
			m_pPlayerUW->SetAnimationSet(298);
			m_pPlayerUW->m_pTransform->m_position = m_pTransform->m_position;
			m_pPlayerUW->m_pTransform->m_rotationEuler = m_pTransform->m_rotationEuler;
			m_pPlayerUW->m_pTransform->m_scale = m_pTransform->m_scale;
		}
	}
	if (KEYBOARD->Up('F'))
	{

	}*/

	//if (KEYBOARD->Up('R'))
	//{
	//	if (m_isUnWeapon == false)
	//	{
	//		m_bPutInWeapon = true;
	//		SetAnimationSet(81); // PutInWepaon Animation
	//		m_pPlayerUW->SetAnimationSet(304);
	//		m_pPlayerController->SetState(EPlayerState::PutInWeapon);
	//	}
	//	else if (m_isUnWeapon)
	//	{
	//		m_bPutOutWeapon = true;
	//		m_isUnWeapon = false;
	//		m_pPlayerUW->SetAnimationSet(304);
	//		//SetAnimationSet(81);
	//		m_pPlayerUW->SetActive(false);
	//		SetAnimationSet(76);
	//		m_pPlayerController->SetState(EPlayerState::PutInWeapon);
	//	}
	//}
	//if (m_bPutInWeapon)
	//{
	//	bool bEnd = IsAnimationSetEnd();
	//	if (bEnd == true)
	//	{
	//		m_pPlayerController->SetState(EPlayerState::Idle);
	//		SetAnimationSet(112); // idle
	//		m_pPlayerUW->SetAnimationSet(304); // idle

	//		m_bPutInWeapon = false;
	//		/* Form Change */
	//		m_pPlayerUW->m_pTransform->m_position = m_pTransform->m_position;
	//		m_pPlayerUW->m_pTransform->m_rotationEuler = m_pTransform->m_rotationEuler;
	//		m_pPlayerUW->m_pTransform->m_scale = m_pTransform->m_scale;

	//		m_pPlayerUW->SetActive(true);
	//		m_isUnWeapon = true;
	//	}
	//	
	//}
	//if (m_bPutOutWeapon)
	//{
	//	bool bEnd = IsAnimationSetEnd();
	//	if (bEnd == true)
	//	{
	//		m_pPlayerController->SetState(EPlayerState::Idle);
	//		SetAnimationSet(112); // idle
	//		m_pPlayerUW->SetActive(false);
	//		m_bPutOutWeapon = false;
	//		m_isUnWeapon = false;
	//	}
	//}
	//if (m_isUnWeapon)
	//{
	//	m_pPlayerUW->m_pTransform->m_position = m_pTransform->m_position;
	//	m_pPlayerUW->m_pTransform->m_rotationEuler = m_pTransform->m_rotationEuler;
	//	m_pPlayerUW->m_pTransform->m_scale = m_pTransform->m_scale;
	//}
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
	Pawn::Render();
}

void Player::OnExpChanged( void*) 
{
	if (m_pExpBarUI == nullptr)
	{
		GameScene * scene = static_cast<GameScene*>(SCENE);
		m_pExpBarUI = static_cast<ProgressBar*>(scene->GetUIManager()->GetStaticUI(L"PlayerExp_Fill"));
	}
	GameScene* pScene = static_cast<GameScene*>(SCENE);
	float amount;
	if (pScene->GetPlayerInfo()->level == 1)
	{
		amount = pScene->GetPlayerInfo()->exp / pScene->GetExpTable()->expTable[pScene->GetPlayerInfo()->level - 1];
	}
	else
	{
		// º¸Á¤Ä¡
		float temp = pScene->GetExpTable()->expTable[pScene->GetPlayerInfo()->level - 2];
		amount = pScene->GetPlayerInfo()->exp - temp / pScene->GetExpTable()->expTable[pScene->GetPlayerInfo()->level - 1] - temp;
	}
	m_pExpBarUI->SetAmount(amount);
}
