#include "stdafx.h"
#include "PlayerCamera.h"
#include "GameManager.h"
#include "GameScene.h"
#include "Client_Events.h"
#include "PlayerController.h"

PlayerCamera::PlayerCamera(Scene * scene, GameObject * player, wstring name) 
	: Camera(scene, nullptr, name),
	m_pPlayer(player)
{
	EventDispatcher::AddEventListener(QuestEvent::QuestDialogOpen, "PlayerCamera",
		std::bind(&PlayerCamera::OnDialogOpen, this, placeholders::_1));
	EventDispatcher::AddEventListener(QuestEvent::QuestDialogEnd, "PlayerCamera",
		std::bind(&PlayerCamera::OnDialogEnd, this, placeholders::_1));
}

PlayerCamera::~PlayerCamera()
{
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogOpen, "PlayerCamera");
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogEnd, "PlayerCamera");

}

void PlayerCamera::Initialize()
{
	Camera::Initialize();
	//SetProjectionMatrix(D3DXToRadian(60.f), WinMaxWidth / WinMaxHeight, 0.01, 15);
	
	m_mouseCenter = MOUSE->GetPosition();
}

void PlayerCamera::Update()
{
	if (CAMERA->GetInstanceID() != GetInstanceID())
		return;

	GameScene* pScene = static_cast<GameScene*>(SCENE);
	if (pScene->GetGameManager()->IsPlayerMovable() == false)
	{
		return;
	}
	else
	{

	}

	if (ENGINE->GetGameMode() == EGameMode::GAME_MODE &&
		m_bMouseFix)
		MouseFix();
	ParamChange();
	Movement();

	//SetBasicProjection();
	//SetProjectionMatrix(D3DXToRadian(45.f), WinMaxWidth / WinMaxHeight, 0.01, 15);
	SetProjectionMatrix(D3DXToRadian(60), WinMaxWidth / WinMaxHeight, 1, 700/*700*/);

	
	Camera::Update();
	SetViewMatrix(m_pPlayer->m_pTransform->CalcOffset(D3DXVECTOR3(0, 15, 0)));

}

void PlayerCamera::OnDialogOpen(void *)
{
	m_bMouseFix = false;
}

void PlayerCamera::OnDialogEnd(void *)
{
	m_bMouseFix = true;
}

void PlayerCamera::ParamChange()
{
	D3DXVECTOR3 mousePos = MOUSE->GetPosition();
	//D3DXVECTOR3 offset = mousePos - m_mouseCenter;//D3DXVECTOR3(WinMaxWidth* 0.5f, WinMaxHeight* 0.5f, 0);
	D3DXVECTOR3 offset = mousePos - D3DXVECTOR3(WinMaxWidth* 0.5f, WinMaxHeight* 0.5f, 0);

	m_rotDegree -= offset.y * m_rotSpdFactor;
	if (m_rotDegree >= m_rotDegreeMax)
		m_rotDegree = m_rotDegreeMax;
	else if (m_rotDegree <= m_rotDegreeMin)
		m_rotDegree = m_rotDegreeMin;

	m_mouseCenter = mousePos;
	//m_mouseCenter = D3DXVECTOR3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0);
	//MOUSE->SetPosition(m_mouseCenter);

	/* юс╫ц */
	if (KEYBOARD->Press(VK_ADD))
	{
		m_distanceToTarget -= 10.f * TIMER->getDeltaTime();
	}
	if (KEYBOARD->Press(VK_SUBTRACT))
	{
		m_distanceToTarget += 10.f * TIMER->getDeltaTime();
	}

	if (KEYBOARD->Press('U'))
	{
		m_rotDegree += 5.f * TIMER->getDeltaTime();
	}
	if (KEYBOARD->Press('J'))
	{
		m_rotDegree -= 5.f * TIMER->getDeltaTime();
	}
}

void PlayerCamera::Movement()
{
	assert(m_pPlayer);
	if (m_pPlayer->GetComponent<PlayerController>()->GetState() == EPlayerState::Shield)
		return;

	/* Get Forward of target */
	D3DXVECTOR3 targetForward;
	memcpy(&targetForward, &m_pPlayer->m_pTransform->GetWorldMatrix().m[2][0], sizeof(D3DXVECTOR3));
	D3DXVec3Normalize(&targetForward, &targetForward);

	/* Get Offset From target*/
	D3DXVECTOR3 invForward = targetForward * -m_distanceToTarget;

	/* Get Right of target */
	D3DXVECTOR3 targetRight;
	memcpy(&targetRight, &m_pPlayer->m_pTransform->GetWorldMatrix().m[0][0], sizeof(D3DXVECTOR3));
	D3DXVec3Normalize(&targetRight, &targetRight);

	/* Rotation RightAxis */
	D3DXMATRIX matRot;
	D3DXMatrixRotationAxis(&matRot, &targetRight, D3DXToRadian(m_rotDegree));

	/* Rotation Offset */
	D3DXVec3TransformNormal(&invForward, &invForward, &matRot);

	m_pTransform->SetPosition(invForward + m_pPlayer->m_pTransform->m_position.operator D3DXVECTOR3());
}

void PlayerCamera::MouseFix()
{
	POINT ptMouse = { WinMaxWidth >> 1, WinMaxHeight >> 1 };
	RECT rt;
	GetClientRect(DirectXDevice::Get()->GetHWnd(), &rt);
	ClientToScreen(DirectXDevice::Get()->GetHWnd(), &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}
//
//void PlayerCamera::MouseMove()
//{
//	D3DXVECTOR3 mousePos = MOUSE->GetPosition();
//	D3DXVECTOR3 howMove = D3DXVECTOR3(WinMaxWidth * 0.5f, WinMaxHeight* 0.)
//
//}

PlayerCamera * PlayerCamera::Create(Scene * scene, GameObject * player, wstring name)
{
	PlayerCamera * cam = new PlayerCamera(scene, player, name);
	cam->Initialize();
	return cam;
}
