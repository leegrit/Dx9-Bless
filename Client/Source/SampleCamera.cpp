#include "stdafx.h"
#include "SampleCamera.h"

SampleCamera::SampleCamera(Scene * scene, GameObject * parent, wstring name)
	: Camera(scene, parent, name)
{
}

SampleCamera::~SampleCamera()
{
}

void SampleCamera::Initialize()
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

void SampleCamera::CameraUpdate()
{
	Camera::CameraUpdate();
	SetViewMatrix(Vector3(0, 0, 0).operator D3DXVECTOR3());
}
