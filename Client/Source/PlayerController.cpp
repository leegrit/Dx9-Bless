#include "stdafx.h"
#include "PlayerController.h"
#include "DynamicMesh.h"
#include "Character.h"
#include "GameScene.h"
#include "GameManager.h"
#include "UIManager.h"
#include "Player.h"
#include "Client_Events.h"
#include "PlayerCamera.h"
#include "SoundManager.h"
#include "Equipment.h"
#include "Sprite3D.h"
#include "PathManager.h"
#include "Sprite.h"

PlayerController::PlayerController(GameObject * pOwner)
	:Component(BehaviourType::Update, pOwner, L"PlayerController")
{
	//m_speed = 0.5f;
	// PLAYER는 반드시 Character를 상속받은 상태여야함
	Character* character = dynamic_cast<Character*>(pOwner);
	assert(character);
	m_speed = character->GetMoveSpeed();
	m_horseSpeed = m_speed + 30;
	m_playerState = EPlayerState::Idle;

	//EventDispatcher::AddEventListener(PlayerEvent::BeginCollect, "PlayerController",
	//	std::bind(&PlayerController::OnBeginCollect, this, placeholders::_1));
	//EventDispatcher::AddEventListener(PlayerEvent::EndCollect, "PlayerController",
	//	std::bind(&PlayerController::OnEndCollect, this, placeholders::_1));
	EventDispatcher::AddEventListener(UIEvent::ShopUIOpen, "PlayerController",
		std::bind(&PlayerController::OnShopOpen, this, placeholders::_1));
	EventDispatcher::AddEventListener(UIEvent::ShopUIClose, "PlayerController",
		std::bind(&PlayerController::OnShopClose, this, placeholders::_1));

}

PlayerController::~PlayerController()		
{
	//EventDispatcher::RemoveEventListener(PlayerEvent::BeginCollect, "PlayerController");
	//EventDispatcher::RemoveEventListener(PlayerEvent::EndCollect, "PlayerController");
	EventDispatcher::RemoveEventListener(UIEvent::ShopUIOpen, "PlayerController");
	EventDispatcher::RemoveEventListener(UIEvent::ShopUIClose, "PlayerController");

}

void PlayerController::Initialize()
{
	m_mouseCenter = MOUSE->GetPosition();
	m_playerState = EPlayerState::Weapon;

	m_pSummonEffect = Sprite::Create(GetGameObject()->GetScene(),
		L"SummonEffect",
		PATH->AssetsPathW() + L"Effect/Texture/SummonEffect", ELoopType::Default,
		36, 70);

}

void PlayerController::Update()
{
	if (ENGINE->GetGameMode() == EGameMode::EDIT_MODE)
		return;
	if (GetGameObject()->GetActive() == false)
		return;
	if (m_bShopOpen)
		return;

	GameScene* pScene = static_cast<GameScene*>(SCENE);
	if (pScene->GetGameManager()->IsPlayerMovable() == false)
	{
		SetAnimationSet(89);
		return;
	}
	
	UpdateRotation();
	UpdateMovement();
	UpdateAction();
}

void PlayerController::LateUpdate()
{
}

void PlayerController::OnEnable()
{
}

void PlayerController::OnDisable()
{
}

EPlayerState PlayerController::GetState() const
{
	return m_playerState;
}

PlayerController::EFormStat PlayerController::GetFormState()
{
	return m_formState;
}

void PlayerController::SetFormState(EFormStat formState)
{
	m_formState = formState;
}

void PlayerController::SetState(EPlayerState playerState)
{
	m_playerState = playerState;
}

void PlayerController::SetHorse(DynamicMesh * pDynamicMesh)
{
	m_pPegasus = pDynamicMesh;
}

void PlayerController::SetUnWeaponMesh(DynamicMesh * pDynamicMesh)
{
	m_pPlayerUW = pDynamicMesh;
}

bool PlayerController::IsMovable()
{
	if (m_bShopOpen)
		return false;

	return true;
}

void PlayerController::OnBeginCollect(void * collectType)
{
	m_collectType = *static_cast<ECollectMotionType*>(collectType);
	m_collectBeginElapsed = 0;
	m_collectEndElapsed = 0;
	m_bCollecting = true;

	

	//m_pPlayerUW->SetAnimationSet(304); // idle
	Player* pPlayer = static_cast<Player*>(GetGameObject());
	pPlayer->SetAnimationSet(62); // UnWewapon

	m_collectStep = ECollectStep::CollectBegin;

	m_bUnWeaponState = false;
}

void PlayerController::OnEndCollect(void * collectType)
{
	m_collectStep = ECollectStep::CollectEnd;

	Player* pPlayer = static_cast<Player*>(GetGameObject());
	//pPlayer->SetAnimationSet(57); // Weapon90
	pPlayer->SetAnimationSet(90);
	m_pPlayerUW->SetAnimationSet(304); // idle
	m_bWeaponState = false;
}

void PlayerController::OnShopOpen(void *)
{
	m_bShopOpen = true;
}

void PlayerController::OnShopClose(void *)
{
	m_bShopOpen = false;
}

void PlayerController::UpdateMovement()
{
	if (m_playerState == EPlayerState::Attack) return;
	if (GetState() == EPlayerState::Collecting)
		return;
	if (m_collectStep != ECollectStep::DONE)
		return;
	if (m_formChangeStep != EFormChangeStep::Done)
		return;

	if (GetState() != EPlayerState::MountOnHorse)
	{
		if (KEYBOARD->Press('W') ||
			KEYBOARD->Press('S') ||
			KEYBOARD->Press('A') ||
			KEYBOARD->Press('D'))
		{
			if (KEYBOARD->Press('W'))
			{
				/* Forward + Left */
				if (KEYBOARD->Press('A'))
				{
					SetAnimationSet(78);
					GetTransform()->Translate(-GetTransform()->Right() * TIMER->getDeltaTime() * m_speed);
				}
				/* Forward + Right */
				else if (KEYBOARD->Press('D'))
				{
					SetAnimationSet(77);
					GetTransform()->Translate(GetTransform()->Right() * TIMER->getDeltaTime() * m_speed);
				}
				/* Only Forward */
				else
				{
					SetAnimationSet(44);
					/*Player* pPlayer = static_cast<Player*>(GetGameObject());
					double pos = pPlayer->GetCurAnimationPosition();
					std::cout << "pos : " << pos << std::endl;
					bool isEnd = false;
					isEnd = pPlayer->IsAnimationSetEnd();
					if (isEnd == true)
					{
						m_bLeftWalkSound = false;
						m_bRightWalkSound = false;
						std::cout << "end move " << std::endl;
					}*/

					

					/*if (pos < 0.2f)
					{
						m_bLeftWalkSound = false;
						m_bRightWalkSound = false;
					}*/

				}
				GetTransform()->Translate(GetTransform()->Forward() * TIMER->getDeltaTime() * m_speed);
			}
			else if (KEYBOARD->Press('S'))
			{
				/* Back + Left */
				if (KEYBOARD->Press('A'))
				{
					SetAnimationSet(83);
					GetTransform()->Translate(-GetTransform()->Right()  * TIMER->getDeltaTime()* m_speed);
				}
				/* Back + Right */
				else if (KEYBOARD->Press('D'))
				{
					SetAnimationSet(82);
					GetTransform()->Translate(GetTransform()->Right() * TIMER->getDeltaTime() * m_speed);
				}
				/* Only Back */
				else
				{
					SetAnimationSet(84);
				}
				GetTransform()->Translate(-GetTransform()->Forward()  * TIMER->getDeltaTime()* m_speed);
			}
			else if (KEYBOARD->Press('A'))
			{
				SetAnimationSet(74);
				GetTransform()->Translate(-GetTransform()->Right()  * TIMER->getDeltaTime()* m_speed);
			}
			else if (KEYBOARD->Press('D'))
			{
				SetAnimationSet(73);
				GetTransform()->Translate(GetTransform()->Right() * TIMER->getDeltaTime() * m_speed);
			}
			m_walkElapsed += TIMER->getDeltaTime();
			/*if (m_walkElapsed >= m_walkDelay)
			{
			m_walkElapsed = 0;
			m_bLeftWalkSound = false;
			m_bRightWalkSound = false;
			}*/
			if (m_walkElapsed >= 0.4f && m_bLeftWalkSound == false)
			{
				m_bLeftWalkSound = true;

				SoundDesc desc;
				desc.channelMode = FMOD_LOOP_OFF;
				desc.volumeType = EVolumeTYPE::AbsoluteVolume;
				desc.volume = 1;
				SOUND->PlaySound("LeftWalkSound", L"WalkSound2.ogg", desc);

			}
			if (m_walkElapsed >= 0.8f && m_bRightWalkSound == false)
			{
				m_bRightWalkSound = true;
				m_walkElapsed = 0;
				m_bLeftWalkSound = false;
				m_bRightWalkSound = false;
				SoundDesc desc;
				desc.channelMode = FMOD_LOOP_OFF;
				desc.volumeType = EVolumeTYPE::AbsoluteVolume;
				desc.volume = 1;
				SOUND->PlaySound("RightWalkSound", L"WalkSound2.ogg", desc);
			}
		}
		else
		{
			SetAnimationSet(89);
			
		}
	}
	else if (GetState() == EPlayerState::MountOnHorse)
	{
		if (KEYBOARD->Press('W') ||
			KEYBOARD->Press('S') ||
			KEYBOARD->Press('A') ||
			KEYBOARD->Press('D'))
		{
			if (KEYBOARD->Press('W'))
			{
				/* Forward + Left */
				//if (KEYBOARD->Press('A'))
				//{
				//	//SetAnimationSet(78);
				//	GetTransform()->Translate(-GetTransform()->Right() * TIMER->getDeltaTime() * m_horseSpeed);
				//}
				///* Forward + Right */
				//else if (KEYBOARD->Press('D'))
				//{
				//	//SetAnimationSet(77);
				//	GetTransform()->Translate(GetTransform()->Right() * TIMER->getDeltaTime() * m_horseSpeed);
				//}
				/* Only Forward */
				//else
				{
					m_pPegasus->SetAnimationSet(19);
					m_pPlayerUW->SetAnimationSet(249);
					//SetAnimationSet(44);
				}
				GetTransform()->Translate(GetTransform()->Forward() * TIMER->getDeltaTime() * m_horseSpeed);
			}
			else if (KEYBOARD->Press('S'))
			{
				/* Back + Left */
				//if (KEYBOARD->Press('A'))
				//{
				//	//SetAnimationSet(83);
				//	GetTransform()->Translate(-GetTransform()->Right()  * TIMER->getDeltaTime()* m_horseSpeed);
				//}
				///* Back + Right */
				//else if (KEYBOARD->Press('D'))
				//{
				//	//SetAnimationSet(82);
				//	GetTransform()->Translate(GetTransform()->Right() * TIMER->getDeltaTime() * m_horseSpeed);
				//}
				/* Only Back */
				//else
				{
					m_pPegasus->SetAnimationSet(12);
					m_pPlayerUW->SetAnimationSet(250);
					//SetAnimationSet(84);
				}
				GetTransform()->Translate(-GetTransform()->Forward()  * TIMER->getDeltaTime()* m_horseSpeed);
			}
			/*else if (KEYBOARD->Press('A'))
			{
				SetAnimationSet(74);
				GetTransform()->Translate(-GetTransform()->Right()  * TIMER->getDeltaTime()* m_speed);
			}
			else if (KEYBOARD->Press('D'))
			{
				SetAnimationSet(73);
				GetTransform()->Translate(GetTransform()->Right() * TIMER->getDeltaTime() * m_speed);
			}*/
			m_walkElapsed += TIMER->getDeltaTime();
			/*if (m_walkElapsed >= m_walkDelay)
			{
			m_walkElapsed = 0;
			m_bLeftWalkSound = false;
			m_bRightWalkSound = false;
			}*/
			if (m_walkElapsed >= 0.4f && m_bLeftWalkSound == false)
			{
				m_bLeftWalkSound = true;

				SoundDesc desc;
				desc.channelMode = FMOD_LOOP_OFF;
				desc.volumeType = EVolumeTYPE::AbsoluteVolume;
				desc.volume = 1;
				SOUND->PlaySound("LeftHorseWalkSound", L"HorseLeftWalk.ogg", desc);

			}
			if (m_walkElapsed >= 0.8f && m_bRightWalkSound == false)
			{
				m_bRightWalkSound = true;
				m_walkElapsed = 0;
				m_bLeftWalkSound = false;
				m_bRightWalkSound = false;
				SoundDesc desc;
				desc.channelMode = FMOD_LOOP_OFF;
				desc.volumeType = EVolumeTYPE::AbsoluteVolume;
				desc.volume = 1;
				SOUND->PlaySound("RightHorseWalkSound", L"HorseRightWalk.ogg", desc);
			}
		}
		else
		{
			m_pPlayerUW->SetAnimationSet(252);
			m_pPegasus->SetAnimationSet(4);
			//SetAnimationSet(89);
		}
	}
}

void PlayerController::UpdateRotation()
{
	D3DXVECTOR3 mousePos = MOUSE->GetPosition();

	//D3DXVECTOR3 offset = mousePos - m_mouseCenter;//D3DXVECTOR3(WinMaxWidth * 0.5f, WinMaxHeight* 0.5f, 0);
	D3DXVECTOR3 offset = mousePos - D3DXVECTOR3(WinMaxWidth * 0.5f, WinMaxHeight* 0.5f, 0);
	/*if (offset.x > 0)
	{
		GetGameObject()->m_pTransform->m_rotationEuler.y() += 1;
	}
	else
		GetGameObject()->m_pTransform->m_rotationEuler.y() -= 1;*/
	GetGameObject()->m_pTransform->m_rotationEuler.y() += offset.x;
	m_mouseCenter = mousePos;

	/*PlayerCamera* pCamera = dynamic_cast<PlayerCamera*>(CAMERA);
	if (pCamera != nullptr)
		pCamera->Update();*/
}

void PlayerController::UpdateAction()
{
	if (m_playerState == EPlayerState::Attack) return;

	RideAction();
	//CollectAction();
	//FormChangeAction();
}

void PlayerController::RideAction()
{
	if (GetState() == EPlayerState::Collecting)
		return;

	if (GetState() == EPlayerState::MountOnHorse)
	{
		m_pPlayerUW->m_pTransform->m_position = GetTransform()->CalcOffset(D3DXVECTOR3(0, 5, 0));
		m_pPlayerUW->m_pTransform->m_rotationEuler = GetTransform()->m_rotationEuler;
		m_pPlayerUW->m_pTransform->m_scale = GetTransform()->m_scale;
		m_pPegasus->m_pTransform->m_position = GetTransform()->m_position;
		m_pPegasus->m_pTransform->m_rotationEuler = GetTransform()->m_rotationEuler;
		m_pPegasus->m_pTransform->m_scale = GetTransform()->m_scale;
	}

	if (KEYBOARD->Up('T'))
	{
		if (GetState() == EPlayerState::MountOnHorse)
		{
			m_bCanclePegasus = true;
		}
		else
			m_bSummonPegasus = true;

	}
	if (m_bCanclePegasus)
	{
		m_pSummonEffect->m_pTransform->m_position = GetTransform()->CalcOffset(D3DXVECTOR3(0, 5, 0));
		m_pSummonEffect->m_pTransform->m_scale = D3DXVECTOR3(15, 15, 15);
		m_pSummonEffect->PlayAnimation();

		Player *pPlayer = static_cast<Player*>(PLAYER);
		Equipment* pWeapon = static_cast<Equipment*> (pPlayer->GetWeapon());
		Equipment* pShield = static_cast<Equipment*> (pPlayer->GetShield());
		pWeapon->SetOwner(pPlayer);
		pWeapon->SetBoneName(L"Bip01-R-Finger22");
		pWeapon->m_pTransform->m_position = D3DXVECTOR3(0, 0, 0);
		pWeapon->m_pTransform->m_rotationEuler = D3DXVECTOR3(0, 0, 0);
		pWeapon->m_pTransform->m_scale = D3DXVECTOR3(1.5f, 1.5f, 1.5f);

		pShield->SetOwner(pPlayer);
		pShield->SetBoneName(L"Bip01-L-Hand");
		pShield->m_pTransform->m_position = D3DXVECTOR3(0, 0, 0);
		pShield->m_pTransform->m_rotationEuler = D3DXVECTOR3(0, 0, 180);
		pShield->m_pTransform->m_scale = D3DXVECTOR3(1, 1, 1);

		m_pPlayerUW->SetActive(false);
		m_pPegasus->SetActive(false);
		SetState(EPlayerState::Idle);
		SetAnimationSet(89);
		m_bCanclePegasus = false;
	}
	else if (m_bSummonPegasus)
	{
		m_summonElapsed += TIMER->getDeltaTime();

		GameScene* pScene = static_cast<GameScene*>(GetGameObject()->GetScene());
		assert(pScene);

		pScene->GetUIManager()->ShowSummonProgressBar((float)m_summonElapsed / m_delay);
		if (m_summonElapsed >= m_delay)
		{
			pScene->GetUIManager()->HideSummonProgressBar();
			m_pSummonEffect->m_pTransform->m_position = GetTransform()->CalcOffset(D3DXVECTOR3(0, 5, 0));
			m_pSummonEffect->m_pTransform->m_scale = D3DXVECTOR3(15, 15, 15);
			m_pSummonEffect->PlayAnimation();
			m_summonElapsed = 0;
			m_bSummonPegasus = false;
			SetState(EPlayerState::MountOnHorse);
			m_pPlayerUW->SetAnimationSet(252);
			m_pPegasus->SetAnimationSet(4);
			m_pPlayerUW->SetActive(true);
			m_pPegasus->SetActive(true);
			m_pPlayerUW->m_pTransform->m_position = GetTransform()->CalcOffset(D3DXVECTOR3(0, 5, 0));
			m_pPlayerUW->m_pTransform->m_rotationEuler = GetTransform()->m_rotationEuler;
			m_pPlayerUW->m_pTransform->m_scale = GetTransform()->m_scale;
			m_pPegasus->m_pTransform->m_position = GetTransform()->m_position;
			m_pPegasus->m_pTransform->m_rotationEuler = GetTransform()->m_rotationEuler;
			m_pPegasus->m_pTransform->m_scale = GetTransform()->m_scale;

			Player *pPlayer = static_cast<Player*>(PLAYER);
			Equipment* pWeapon = static_cast<Equipment*> (pPlayer->GetWeapon());
			Equipment* pShield = static_cast<Equipment*> (pPlayer->GetShield());
			pWeapon->SetOwner(m_pPlayerUW);
			pWeapon->SetBoneName(L"BN_L_Hip");
			pWeapon->m_pTransform->m_position = D3DXVECTOR3(-6, -3.5, 0);
			pWeapon->m_pTransform->m_rotationEuler = D3DXVECTOR3(-90, 0, -90);
			pWeapon->m_pTransform->m_scale = D3DXVECTOR3(1.5f, 1.5f, 1.5f);

			pShield->SetOwner(m_pPlayerUW);
			pShield->SetBoneName(L"Bip01-Spine2");
			pShield->m_pTransform->m_position = D3DXVECTOR3(0, 0, -2);
			pShield->m_pTransform->m_rotationEuler = D3DXVECTOR3(0, 0, -90);
			pShield->m_pTransform->m_scale = D3DXVECTOR3(1, 1, 1);

			SoundDesc desc;
			desc.channelMode = FMOD_LOOP_OFF;
			desc.volumeType = EVolumeTYPE::AbsoluteVolume;
			desc.volume = 1;
			SOUND->PlaySound("HorseCries", L"HorseCries.ogg", desc);
		}
	}
}

void PlayerController::CollectAction()
{
	if (m_bCollecting)
	{
		if (m_collectStep == ECollectStep::CollectBegin)
		{
			m_collectBeginElapsed += TIMER->getDeltaTime();
			if (m_collectBeginElapsed < m_collectDelay && m_collectStep == ECollectStep::CollectBegin
				&& IsAnimationEnd() && m_bUnWeaponState == false)
			{
				m_pPlayerUW->SetAnimationSet(304); // idle
				SetAnimationSet(90); // idle
				m_bUnWeaponState = true;
			}
			if (m_collectBeginElapsed >= m_collectDelay && m_collectStep == ECollectStep::CollectBegin)
			{
				m_collectStep = ECollectStep::Collecting;
				m_pPlayerUW->SetActive(true);
				SetState(EPlayerState::Collecting);
				m_pPlayerUW->SetAnimationSet(264); // looting M
				m_pPlayerUW->m_pTransform->m_position = GetTransform()->m_position;
				m_pPlayerUW->m_pTransform->m_rotationEuler = GetTransform()->m_rotationEuler;
				m_pPlayerUW->m_pTransform->m_scale = GetTransform()->m_scale;
			}
		}
		if (m_collectStep == ECollectStep::CollectEnd)
		{
			m_collectEndElapsed += TIMER->getDeltaTime();
			//if (m_collectEndElapsed < m_collectDelay && m_collectStep == ECollectStep::CollectEnd
			//	&& IsAnimationEnd())
			//{
			//	m_pPlayerUW->SetAnimationSet(304); // idle
			//	SetAnimationSet(90); // idle
			//}
			if (m_collectEndElapsed >= m_collectToWeaponDelay && m_bWeaponState == false)
			{
				// weapon anim
				m_pPlayerUW->SetActive(false);
				SetState(EPlayerState::Idle);
				SetAnimationSet(57);
				m_bWeaponState = true;
			}

			if (m_bWeaponState == true && IsAnimationEnd() && m_collectStep == ECollectStep::CollectEnd)
			{
				m_collectStep = ECollectStep::DONE;
				//m_pPlayerUW->SetActive(false);
				//SetState(EPlayerState::Idle);

			}
		}
	}
}

void PlayerController::FormChangeAction()
{
	if (GetState() == EPlayerState::UnWeapon)
	{
		m_pPlayerUW->m_pTransform->m_position = GetTransform()->m_position;
		m_pPlayerUW->m_pTransform->m_rotationEuler = GetTransform()->m_rotationEuler;
		m_pPlayerUW->m_pTransform->m_scale = GetTransform()->m_scale;
	}
	if (KEYBOARD->Up('R') && m_bChangeToUnweapon == false && m_bChangeToWeapon == false
		&& m_formChangeStep == EFormChangeStep::Done)
	{
		if (GetFormState() == EFormStat::UnWeapon)
		{
			m_bChangeToWeapon = true;
		}
		else if (GetFormState() == EFormStat::Weapon)
		{
			m_bChangeToUnweapon = true;
		}
	}

	if (m_bChangeToWeapon && m_formChangeStep == EFormChangeStep::Done)
	{
		Player* pPlayer = static_cast<Player*>(GetGameObject());
		pPlayer->SetAnimationSet(57); // Weapon
		m_formChangeStep = EFormChangeStep::Begin;
		//m_bChangeToWeapon = false;
	}
	if (m_bChangeToUnweapon && m_formChangeStep == EFormChangeStep::Done)
	{
		Player* pPlayer = static_cast<Player*>(GetGameObject());
		pPlayer->SetAnimationSet(62); // UnWewapon
		m_formChangeStep = EFormChangeStep::Begin;
		//m_bChangeToUnweapon = false;
	}

	if (m_formChangeStep == EFormChangeStep::Begin)
	{
		if (m_bChangeToUnweapon)
		{
			if (IsAnimationEnd())
			{
				m_pPlayerUW->SetAnimationSet(304); // idle
				SetAnimationSet(90); // idle
				m_formChangeElapsed = 0;
				m_formChangeStep = EFormChangeStep::End;
				//m_formChangeStep = EFormChangeStep::Done;
				m_pPlayerUW->m_pTransform->m_position = GetTransform()->m_position;
				m_pPlayerUW->m_pTransform->m_rotationEuler = GetTransform()->m_rotationEuler;
				m_pPlayerUW->m_pTransform->m_scale = GetTransform()->m_scale;
			}
		}
		else if (m_bChangeToWeapon)
		{

		}
	}
	if (m_formChangeStep == EFormChangeStep::End)
	{
		if (m_bChangeToUnweapon)
		{
			m_formChangeElapsed += TIMER->getDeltaTime();
			if (m_formChangeElapsed >= m_formChangeDelay)
			{
				m_formChangeStep = EFormChangeStep::Done;
				m_bChangeToUnweapon = false;
				m_pPlayerUW->SetActive(true);
				SetFormState(EFormStat::UnWeapon);
			}
		}
		else if (m_bChangeToWeapon)
		{

		}
	}

}

void PlayerController::SetAnimationSet(int index)
{
	DynamicMesh* mesh = dynamic_cast<DynamicMesh*>(GetGameObject());
	assert(mesh != nullptr);

	mesh->SetAnimationSet(index);
}

bool PlayerController::IsAnimationEnd()
{
	DynamicMesh* mesh = dynamic_cast<DynamicMesh*>(GetGameObject());
	assert(mesh != nullptr);

	return mesh->IsAnimationSetEnd();
}

PlayerController * PlayerController::Create(GameObject * pOwner)
{
	PlayerController* com = new PlayerController(pOwner);
	com->Initialize();
	return com;
}
