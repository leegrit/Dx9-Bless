#include "StandardEngineFramework.h"
#include "EditCamera.h"

using namespace Editor;
EditCamera::EditCamera(Scene * scene, GameObject * parent)
	: Camera(scene, parent, L"EditCamera")
{
}

EditCamera::~EditCamera()
{
}

void EditCamera::Initialize()
{
	Camera::Initialize();

	GetTransform()->SetPosition(0, 10, -10);
}

void EditCamera::CameraUpdate()
{
	Camera::CameraUpdate();

	SetProjectionMatrix
	(
		D3DX_PI * 0.5f, // 90 - degree
		WinMaxWidth / WinMaxHeight,
		1.0f,
		1000.0f
	);
	SetViewMatrix(D3DXVECTOR3(0, 0, 0));
}
