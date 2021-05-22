#include "stdafx.h"
#include "StaticCamera.h"

StaticCamera::StaticCamera(Scene * pScene, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
	: Camera(pScene, nullptr, L"StaticCamera")
{
	m_pTransform->m_position = pos;
	m_pTransform->m_rotationEuler = rot;

}

StaticCamera::~StaticCamera()
{
}

void StaticCamera::Initialize()
{
	Camera::Initialize();
}

void StaticCamera::Update()
{
	Camera::Update();

	D3DXVECTOR3 forward = m_pTransform->Forward();
	forward = m_pTransform->m_position.operator D3DXVECTOR3() + forward;

	SetViewMatrix(forward);
}

StaticCamera * StaticCamera::Create(Scene * pScene, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	StaticCamera * cam = new StaticCamera(pScene, pos, rot);
	cam->Initialize();
	return cam;
}
