#include "stdafx.h"
#include "PlayerController.h"
#include "DynamicMesh.h"
#include "Character.h"
#include "GameScene.h"
#include "GameManager.h"
PlayerController::PlayerController(GameObject * pOwner)
	:Component(BehaviourType::Update, pOwner, L"PlayerController")
{
	//m_speed = 0.5f;
	// PLAYER는 반드시 Character를 상속받은 상태여야함
	Character* character = dynamic_cast<Character*>(pOwner);
	assert(character);
	m_speed = character->GetMoveSpeed();
	m_playerState = EPlayerState::Idle;
}

PlayerController::~PlayerController()		
{
}

void PlayerController::Initialize()
{
	m_mouseCenter = MOUSE->GetPosition();
}

void PlayerController::Update()
{
	if (ENGINE->GetGameMode() == EGameMode::EDIT_MODE)
		return;

	GameScene* pScene = static_cast<GameScene*>(SCENE);
	if (pScene->GetGameManager()->IsPlayerMovable() == false)
	{
		SetAnimationSet(39);
		return;
	}
	UpdateMovement();
	UpdateRotation();
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

void PlayerController::SetState(EPlayerState playerState)
{
	m_playerState = playerState;
}

void PlayerController::UpdateMovement()
{
	if (m_playerState == EPlayerState::Attack) return;
	if (KEYBOARD->Press('W'))
	{
		/* Forward + Left */
		if (KEYBOARD->Press('A'))
		{
			SetAnimationSet(11);
			GetTransform()->Translate(-GetTransform()->Right() * TIMER->getDeltaTime() * m_speed);
		}
		/* Forward + Right */
		else if (KEYBOARD->Press('D'))
		{
			SetAnimationSet(30);
			GetTransform()->Translate(GetTransform()->Right() * TIMER->getDeltaTime() * m_speed);
		}
		/* Only Forward */
		else
		{
			SetAnimationSet(31);
		}
		GetTransform()->Translate(GetTransform()->Forward() * TIMER->getDeltaTime() * m_speed);
	}
	else if (KEYBOARD->Press('S'))
	{
		/* Back + Left */
		if (KEYBOARD->Press('A'))
		{
			SetAnimationSet(33);
			GetTransform()->Translate(-GetTransform()->Right()  * TIMER->getDeltaTime()* m_speed);
		}
		/* Back + Right */
		else if (KEYBOARD->Press('D'))
		{
			SetAnimationSet(32);
			GetTransform()->Translate(GetTransform()->Right() * TIMER->getDeltaTime() * m_speed);
		}
		/* Only Back */
		else
		{
			SetAnimationSet(34);
		}
		GetTransform()->Translate(-GetTransform()->Forward()  * TIMER->getDeltaTime()* m_speed);
	}
	else if (KEYBOARD->Press('A'))
	{
		SetAnimationSet(29);
		GetTransform()->Translate(-GetTransform()->Right()  * TIMER->getDeltaTime()* m_speed);
	}
	else if (KEYBOARD->Press('D'))
	{
		SetAnimationSet(28);
		GetTransform()->Translate(GetTransform()->Right() * TIMER->getDeltaTime() * m_speed);
	}
	else
	{
		SetAnimationSet(39);
	}
}

void PlayerController::UpdateRotation()
{
	D3DXVECTOR3 mousePos = MOUSE->GetPosition();

	D3DXVECTOR3 offset = mousePos - m_mouseCenter;

	GetGameObject()->m_pTransform->m_rotationEuler.y() += offset.x;
	m_mouseCenter = mousePos;
}

void PlayerController::UpdateAction()
{
	if (MOUSE->Down(0))
	{

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
