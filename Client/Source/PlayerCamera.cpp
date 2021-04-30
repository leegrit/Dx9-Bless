#include "stdafx.h"
#include "PlayerCamera.h"

PlayerCamera::PlayerCamera(Scene * scene, GameObject * player, wstring name) 
	: Camera(scene, nullptr, name),
	m_pPlayer(player)
{
	
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Initialize()
{
	Camera::Initialize();
	//SetProjectionMatrix(D3DXToRadian(60.f), WinMaxWidth / WinMaxHeight, 0.01, 15);
	
	m_mouseCenter = MOUSE->GetPosition();
}

void PlayerCamera::Update()
{
	Camera::Update();

	ParamChange();
	Movement();

	//SetBasicProjection();
	//SetProjectionMatrix(D3DXToRadian(45.f), WinMaxWidth / WinMaxHeight, 0.01, 15);
	SetProjectionMatrix(D3DXToRadian(45.f), WinMaxWidth / WinMaxHeight, 1, 700);

	SetViewMatrix(m_pPlayer->m_pTransform->m_position.operator D3DXVECTOR3());
}

void PlayerCamera::ParamChange()
{
	D3DXVECTOR3 mousePos = MOUSE->GetPosition();
	D3DXVECTOR3 offset = mousePos - m_mouseCenter;


	m_rotDegree -= offset.y * m_rotSpdFactor;
	if (m_rotDegree >= m_rotDegreeMax)
		m_rotDegree = m_rotDegreeMax;
	else if (m_rotDegree <= m_rotDegreeMin)
		m_rotDegree = m_rotDegreeMin;

	m_mouseCenter = mousePos;


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

PlayerCamera * PlayerCamera::Create(Scene * scene, GameObject * player, wstring name)
{
	PlayerCamera * cam = new PlayerCamera(scene, player, name);
	cam->Initialize();
	return cam;
}
