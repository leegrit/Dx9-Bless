#include "StandardEngineFramework.h"
#include "DynamicCamera.h"

DynamicCamera::DynamicCamera(Scene * scene, GameObject * parent, wstring name)
	: Camera(scene, parent, name)
{
}

DynamicCamera::~DynamicCamera()
{
}

void DynamicCamera::Initialize()
{
	Camera::Initialize();
	SetProjectionMatrix
	(
		D3DXToRadian(90.f),
		WinMaxWidth / WinMaxHeight,
		1.0f,
		1000.0f
	);
	m_pTransform->SetPosition(0, 10, -10);
}

void DynamicCamera::CameraUpdate()
{
	Camera::CameraUpdate();

	if (KEYBOARD->Press('W'))
	{
		m_pTransform->Translate(m_pTransform->Forward() * m_speed * TIMER->getDeltaTime());
	}
	if (KEYBOARD->Press('S'))
	{
		m_pTransform->Translate(-m_pTransform->Forward() * m_speed * TIMER->getDeltaTime());
	}
	if (KEYBOARD->Press('A'))
	{
		m_pTransform->Translate(-m_pTransform->Right() * m_speed * TIMER->getDeltaTime());
	}
	if (KEYBOARD->Press('D'))
	{
		m_pTransform->Translate(m_pTransform->Right() * m_speed * TIMER->getDeltaTime());
	}
	if (MOUSE->Press(1))
	{
		D3DXVECTOR3 mousePos = MOUSE->GetPosition();

		mousePos.x = WinMaxWidth - mousePos.x;
		mousePos.y = WinMaxHeight - mousePos.y;

		mousePos.x = mousePos.x - WinMaxWidth * 0.5f;
		float xWeight = std::abs(mousePos.x) / (WinMaxWidth * 0.5f);
		mousePos.y = mousePos.y - WinMaxHeight * 0.5f;
		float yWeight = std::abs(mousePos.y) / (WinMaxHeight * 0.5f);
		mousePos.z = 0;

		D3DXVec3Normalize(&mousePos, &mousePos);


		m_pTransform->m_rotationEuler.x() = m_pTransform->m_rotationEuler.x() + mousePos.y * m_xRotMax;
		m_pTransform->m_rotationEuler.y() = m_pTransform->m_rotationEuler.y() + mousePos.x * m_yRotMax;
	}


	SetProjectionMatrix
	(
		D3DX_PI * 0.5f, // 90 - degree
		WinMaxWidth / WinMaxHeight,
		1.0f,
		1000.0f
	);
	D3DXVECTOR3 target;
	target = (GetTransform()->m_position + GetTransform()->Forward() * 10).operator D3DXVECTOR3();
	SetViewMatrix(target);

}
