#include "stdafx.h"
#include "TitleCamera.h"

TitleCamera::TitleCamera(Scene * scene, std::wstring name)
	: Camera(scene, nullptr, name)
{

}

TitleCamera::~TitleCamera()
{
}

void TitleCamera::Initialize()
{
	Camera::Initialize();
}

void TitleCamera::Update()
{
	Camera::Update();
	SetProjectionMatrix(D3DXToRadian(60.f), WinMaxWidth / WinMaxHeight, 1, 700);

	SetViewMatrix(D3DXVECTOR3(0, 0, -10), D3DXVECTOR3(0, 0, 0));
}

TitleCamera * TitleCamera::Create(Scene * scene, std::wstring name)
{
	TitleCamera* cam = new TitleCamera(scene, name);
	cam->Initialize();
	return cam;
}
