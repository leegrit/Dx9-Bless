#include "stdafx.h"
#include "ZoomInCamera.h"

ZoomInCamera::ZoomInCamera(Scene * pScene, GameObject * pTarget, std::wstring name)
	: Camera(pScene, nullptr, name),
	m_pTarget(pTarget),
	m_offset(0, 10, 10)
{

}

ZoomInCamera::~ZoomInCamera()
{
}

void ZoomInCamera::Initialize()
{
	Camera::Initialize();
}

void ZoomInCamera::Update()
{
	Camera::Update();


	SetProjectionMatrix(D3DXToRadian(60), WinMaxWidth / WinMaxHeight, 0.001, 700);


	m_pTransform->m_position = m_pTarget->m_pTransform->CalcOffset(m_offset);
	D3DXVECTOR3 atOffset = D3DXVECTOR3(0, m_offset.y, 0);

	m_at = m_pTarget->m_pTransform->CalcOffset(atOffset);

	SetViewMatrix(m_at);
}

void ZoomInCamera::SetOffset(D3DXVECTOR3 offset)
{
	m_offset = offset;
}

ZoomInCamera * ZoomInCamera::Create(Scene * pScene, GameObject * pTarget, std::wstring name)
{
	ZoomInCamera *obj = new ZoomInCamera(pScene, pTarget, name);
	obj->Initialize();
	return obj;
}
