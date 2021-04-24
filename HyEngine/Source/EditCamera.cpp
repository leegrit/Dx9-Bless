#include "StandardEngineFramework.h"
#include "EditCamera.h"

using namespace HyEngine;
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

	GetTransform()->SetPosition(0, 0, -10);
}

void EditCamera::Update()
{
	Camera::Update();

	SetProjectionMatrix
	(
		D3DX_PI * 0.5f, // 90 - degree
		WinMaxWidth / WinMaxHeight,
		1.0f,
		3000.0f
	);
	D3DXVECTOR3 target;
	target = (GetTransform()->m_position + GetTransform()->Forward() * 10).operator D3DXVECTOR3();
	SetViewMatrix(target);

	//SetViewMatrix()


	//D3DXMATRIX matScale;
	//D3DXMATRIX matRot;
	//D3DXMATRIX matPos;

	//D3DXMatrixScaling(&matScale, 1, 1, 1);
	//if (m_pTransform->m_rotationEuler == Vector3::Zero)
	//	D3DXMatrixRotationQuaternion(&matRot, &m_pTransform->m_rotation.operator D3DXQUATERNION());
	//else
	//	D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(m_pTransform->m_rotationEuler.y()), D3DXToRadian(m_pTransform->m_rotationEuler.x()), D3DXToRadian(m_pTransform->m_rotationEuler.z()));


	//D3DXMatrixTranslation(&matPos, -m_pTransform->m_position.x(),-m_pTransform->m_position.y(), -m_pTransform->m_position.z());

	//// юс╫ц
	//m_matView = matScale *  matPos* matRot;

	/*D3DXVECTOR3 xAxis;
	memcpy(&xAxis, &matRot.m[0][0], sizeof(D3DXVECTOR3));

	D3DXVECTOR3 yAxis;
	memcpy(&yAxis, &matRot.m[1][0], sizeof(D3DXVECTOR3));

	D3DXVECTOR3 zAxis;
	memcpy(&zAxis, &matRot.m[2][0], sizeof(D3DXVECTOR3));

	m_matView._11 = xAxis.x;
	m_matView._21 = xAxis.y;
	m_matView._31 = xAxis.z;

	m_matView._12 = yAxis.x;
	m_matView._22 = yAxis.y;
	m_matView._32 = yAxis.z;

	m_matView._13 = zAxis.x;
	m_matView._23 = zAxis.y;
	m_matView._33 = zAxis.z;

	m_matView._41 = D3DXVec3Dot(&m_pTransform->m_position.operator D3DXVECTOR3(), &xAxis);
	m_matView._42 = D3DXVec3Dot(&m_pTransform->m_position.operator D3DXVECTOR3(), &yAxis);
	m_matView._43 = D3DXVec3Dot(&m_pTransform->m_position.operator D3DXVECTOR3(), &zAxis);*/
}
