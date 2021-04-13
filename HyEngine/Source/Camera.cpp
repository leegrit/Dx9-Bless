#include "StandardEngineFramework.h"
#include "Camera.h"
#include "Scene.h"
#include "Mesh.h"
#include "Terrain.h"
#include "NavPrimitive.h"

using namespace HyEngine;


HyEngine::Camera::Camera(Scene * scene, GameObject* parent, std::wstring tag)
	: GameObject(ERenderType::None, scene, parent, tag)
{
	
}

HyEngine::Camera::~Camera()
{

}

void HyEngine::Camera::SetProjectionMatrix(float fovy, float screenAspect, float screenNear, float screenFar)
{
	D3DXMatrixPerspectiveFovLH(
		&m_matProj,
		fovy,
		screenAspect,
		screenNear,
		screenFar
	);
	m_near = screenNear;
	m_far = screenFar;
	//DEVICE->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void HyEngine::Camera::SetBasicProjection()
{
	SetProjectionMatrix(m_fovy, m_aspect, m_defaultNear, m_defaultFar);
}

void HyEngine::Camera::SetLongProjection()
{
	D3DXMatrixPerspectiveFovLH(
		&m_matLongProj,
		m_fovy,
		m_aspect,
		m_defaultNear,
		m_longestFar
	);
}

void HyEngine::Camera::SetViewMatrix(const D3DXVECTOR3 & target)
{
	D3DXMatrixLookAtLH
	(
		&m_matView,
		&m_pTransform->m_position.operator D3DXVECTOR3(),
		&target,
		&Vector3::Up
	);
	//D3DXMATRIX mat;
	//D3DXMatrixLookAtLH
	//(
	//	&mat, 
	//	&D3DXVECTOR3(0, 0, -5),
	//	&D3DXVECTOR3(0, 0, 0),
	//	&Vector3::Up
	//);
	//DEVICE->SetTransform(D3DTS_VIEW, &mat);
}
void HyEngine::Camera::SetViewMatrix(const D3DXVECTOR3 & eye, const D3DXVECTOR3 & target)
{
	D3DXMatrixLookAtLH
	(
		&m_matView,
		&eye,
		&target,
		&Vector3::Up
	);
}

float HyEngine::Camera::GetNear() const
{
	return m_near;
}

float HyEngine::Camera::GetFar() const
{
	return m_far;
}

void HyEngine::Camera::Initialize()
{
	SetBasicProjection();
	SetLongProjection();
	D3DXMatrixIdentity(&m_matIdentityView);
	D3DXMatrixOrthoLH(&m_matOrtho,
		WinMaxWidth,
		WinMaxHeight,
		0.f,
		m_defaultFar);
}

void HyEngine::Camera::Update()
{
	FrustumUpdate();
	ShakeUpdate();
}

Vector3 HyEngine::Camera::GetPosition() const
{
	return m_pTransform->m_position;
}

Quaternion HyEngine::Camera::GetRotation() const
{
	return m_pTransform->m_rotation;
}

Vector3 HyEngine::Camera::GetRotationEuler() const
{
	return m_pTransform->m_rotationEuler;
}

D3DXMATRIX HyEngine::Camera::GetViewMatrix() const
{
	/*D3DXMATRIX viewMat;
	D3DXMatrixLookAtLH
	(
		&viewMat,
		&m_pTransform->m_position.operator D3DXVECTOR3(),
		&m_pTransform->Forward().operator D3DXVECTOR3(),
		&m_pTransform->Up().operator D3DXVECTOR3()
	);
*/
	return m_matView;
}

D3DXMATRIX HyEngine::Camera::GetProjectionMatrix() const
{
	return m_matProj;
}

D3DXMATRIX HyEngine::Camera::GetLongProjectionMatrix() const
{
	return m_matLongProj;
}

D3DXMATRIX HyEngine::Camera::GetProjectionMatrix(float fovy, float screenAspect, float screenNear, float screenFar)
{
	D3DXMATRIX result;
	D3DXMatrixPerspectiveFovLH(
		&result,
		fovy,
		screenAspect,
		screenNear,
		screenFar
	);
	return result;
}

D3DXMATRIX HyEngine::Camera::GetIdentityViewMatrix() const
{
	return m_matIdentityView;
}

D3DXMATRIX HyEngine::Camera::GetOrthoMatrix() const
{
	return m_matOrtho;
}


void HyEngine::Camera::SetPosition(float x, float y, float z)
{
	m_pTransform->SetPosition(x, y, z);
}

void HyEngine::Camera::SetRotationEuler(float x, float y, float z)
{
	m_pTransform->SetRotationEuler(D3DXVECTOR3(x, y, z));
}

Transform * HyEngine::Camera::GetTransform()
{
	return m_pTransform;
}

void HyEngine::Camera::UnProjection(_Out_ D3DXVECTOR3 * origin, _Out_  D3DXVECTOR3 * direction , Vector3 source)
{
	// type 1
	/*Vector3 position = source;

	out->x() = (position.x() * 2.0f / WinMaxWidth) - 1.0f;
	out->y() = (position.y() * 2.0f / WinMaxHeight) - 1.0f;
	out->z() = position.z();

	D3DXMATRIX wvp = world * GetViewMatrix() * GetProjectionMatrix();
	D3DXMatrixInverse(&wvp, nullptr, &wvp);

	D3DXVec3TransformCoord(&out->operator D3DXVECTOR3(), &out->operator D3DXVECTOR3(), &wvp);*/
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	// viewport -> proj space
	D3DXVECTOR3 mouse;
	mouse.x = source.x() / (WinMaxWidth * 0.5f) - 1.0f;
	mouse.y = 1.f - source.y() / (WinMaxHeight * 0.5f);
	mouse.z = 0.0f;

	// projection space -> view space
	D3DXMATRIX ProjMatInv;
	D3DXMatrixInverse(&ProjMatInv, 0, &GetProjectionMatrix());
	D3DXVec3TransformCoord(&mouse, &mouse, &ProjMatInv);

	// 뷰 스페이스 상에서 광선의 출발점과 방향을 결정
	D3DXVECTOR3 rayOrigin, rayDir;
	rayOrigin = D3DXVECTOR3(0, 0, 0);
	rayDir = mouse - rayOrigin;
	D3DXVec3Normalize(&rayDir, &rayDir);

	/* 뷰 스페이스에 있는 광선의 정보를 월드 스페이스로 변환 */
	D3DXMATRIX matInvView;
	D3DXMatrixInverse(&matInvView, 0, &GetViewMatrix());
	D3DXVec3TransformCoord(&rayOrigin, &rayOrigin, &matInvView);
	D3DXVec3TransformNormal(&rayDir, &rayDir, &matInvView);
	D3DXVec3Normalize(&rayDir, &rayDir);

	*origin = rayOrigin;
	*direction = rayDir;
}

void HyEngine::Camera::ShakeUpdate()
{
	if (shakeDuration > 0)
	{
		m_pTransform->m_position = m_pTransform->m_position + Vector3(
			DxHelper::GetRandomFloat(-1, 1),
			DxHelper::GetRandomFloat(-1, 1),
			DxHelper::GetRandomFloat(-1, 1))
			* shakeAmount;

		shakeDuration -= (float)TIMER->getUnscaleDeltaTime() * decreaseFactor;
	}
	else
	{
		shakeDuration = 0;
	}
}

void HyEngine::Camera::Shake(float shakeDuration, float shakeAmount, float decreaseFactor)
{
	this->shakeDuration = shakeDuration;
	this->shakeAmount = shakeAmount;
	this->decreaseFactor = decreaseFactor;
	originPos = m_pTransform->m_position;
}

void HyEngine::Camera::FrustumUpdate()
{
	D3DXMATRIX M = GetViewMatrix() * GetProjectionMatrix();

	m_leftPlane.a = M._14 + M._11;
	m_leftPlane.b = M._24 + M._21;
	m_leftPlane.c = M._34 + M._31;
	m_leftPlane.d = M._44 + M._41;
	D3DXPlaneNormalize(&m_leftPlane, &m_leftPlane);

	m_rightPlane.a = M._14 - M._11;
	m_rightPlane.b = M._24 - M._21;
	m_rightPlane.c = M._34 - M._31;
	m_rightPlane.d = M._44 - M._41;
	D3DXPlaneNormalize(&m_rightPlane, &m_rightPlane);

	m_topPlane.a = M._14 + M._12;
	m_topPlane.b = M._24 + M._22;
	m_topPlane.c = M._34 + M._32;
	m_topPlane.d = M._44 + M._42;
	D3DXPlaneNormalize(&m_topPlane, &m_topPlane);

	m_bottomPlane.a = M._14 + M._12;
	m_bottomPlane.b = M._24 + M._22;
	m_bottomPlane.c = M._34 + M._32;
	m_bottomPlane.d = M._44 + M._42;
	D3DXPlaneNormalize(&m_bottomPlane, &m_bottomPlane);

	m_nearPlane.a = M._13;
	m_nearPlane.b = M._23;
	m_nearPlane.c = M._33;
	m_nearPlane.d = M._43;
	D3DXPlaneNormalize(&m_nearPlane, &m_nearPlane);

	m_farPlane.a = M._14 - M._13;
	m_farPlane.b = M._24 - M._23;
	m_farPlane.c = M._34 - M._33;
	m_farPlane.d = M._44 - M._43;
	D3DXPlaneNormalize(&m_farPlane, &m_farPlane);
}

bool HyEngine::Camera::IsInFrustum(D3DXVECTOR3 & position)
{
	/*
		면과 위치를 내적했을 때 0보다 크면 안에 있는 것
		작으면 밖, 0이면 동일한 위치
		여섯 면을 모두 검사한다.
	*/
	if (D3DXPlaneDotCoord(&m_leftPlane, &position) < 0.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_rightPlane, &position) < 0.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_topPlane, &position) < 0.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_bottomPlane, &position) < 0.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_nearPlane, &position) < 0.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_farPlane, &position) < 0.0f)
		return false;

	return true;
}

bool HyEngine::Camera::IsInFrustumWithMesh(D3DXVECTOR3 & position, float radius)
{
	/*
	면과 위치를 내적했을 때 0보다 크면 안에 있는 것
	작으면 밖, 0이면 동일한 위치
	여섯 면을 모두 검사한다.
	*/
	if (D3DXPlaneDotCoord(&m_leftPlane, &position) < 0.0f)
	{
		float length =
			(m_leftPlane.a * position.x + m_leftPlane.b * position.y + m_leftPlane.c * position.z + m_leftPlane.d) / std::sqrt(m_leftPlane.a * m_leftPlane.a + m_leftPlane.b * m_leftPlane.b + m_leftPlane.c * m_leftPlane.c);
		if(length >= radius)
			return false;
	}

	if (D3DXPlaneDotCoord(&m_rightPlane, &position) < 0.0f) 
	{
		float length =
			(m_rightPlane.a * position.x + m_rightPlane.b * position.y + m_rightPlane.c * position.z + m_rightPlane.d) / std::sqrt(m_rightPlane.a * m_rightPlane.a + m_rightPlane.b * m_rightPlane.b + m_rightPlane.c * m_rightPlane.c);
		if (length >= radius)
			return false;
	}

	if (D3DXPlaneDotCoord(&m_topPlane, &position) < 0.0f)
	{
		float length =
			(m_topPlane.a * position.x + m_topPlane.b * position.y + m_topPlane.c * position.z + m_topPlane.d) / std::sqrt(m_topPlane.a * m_topPlane.a + m_topPlane.b * m_topPlane.b + m_topPlane.c * m_topPlane.c);
		if (length >= radius)
			return false;
	}


	if (D3DXPlaneDotCoord(&m_bottomPlane, &position) < 0.0f)
	{
		float length =
			(m_bottomPlane.a * position.x + m_bottomPlane.b * position.y + m_bottomPlane.c * position.z + m_bottomPlane.d) / std::sqrt(m_bottomPlane.a * m_bottomPlane.a + m_bottomPlane.b * m_bottomPlane.b + m_bottomPlane.c * m_bottomPlane.c);
		if (length >= radius)
			return false;
	}

	if (D3DXPlaneDotCoord(&m_nearPlane, &position) < 0.0f)
	{
		float length =
			(m_nearPlane.a * position.x + m_nearPlane.b * position.y + m_nearPlane.c * position.z + m_nearPlane.d) / std::sqrt(m_nearPlane.a * m_nearPlane.a + m_nearPlane.b * m_nearPlane.b + m_nearPlane.c * m_nearPlane.c);
		if (length >= radius)
			return false;
	}

	if (D3DXPlaneDotCoord(&m_farPlane, &position) < 0.0f)
	{
		float length =
			(m_farPlane.a * position.x + m_farPlane.b * position.y + m_farPlane.c * position.z + m_farPlane.d) / std::sqrt(m_farPlane.a * m_farPlane.a + m_farPlane.b * m_farPlane.b + m_farPlane.c * m_farPlane.c);
		if (length >= radius)
			return false;
	}

	return true;
}


void HyEngine::Camera::ViewFrustumCulling(GameObject * obj)
{
	assert(obj != nullptr);	

	bool result = false;

	Mesh* mesh = nullptr;
	mesh = dynamic_cast<Mesh*>(obj);

	Terrain * terrain = nullptr;
	terrain = dynamic_cast<Terrain*>(obj);

	NavPrimitive * navPrimitive = nullptr;
	navPrimitive = dynamic_cast<NavPrimitive*>(obj);

	/* 메쉬인경우 */
	if (mesh != nullptr)
	{
		D3DXVECTOR3 center = D3DXVECTOR3(0, 0, 0);
		float radius = 0;
		bool isSucceeded =  mesh->ComputeBoundingSphere(&center, &radius);

		if (isSucceeded == false)
		{
			SEND_LOG_WARNING("Mesh CompiuteBoundingSphere Failed");
			return;
		}

		result = IsInFrustumWithMesh(center, radius);
	}
	else if (terrain != nullptr)
	{
		D3DXVECTOR3 center = D3DXVECTOR3(0, 0, 0);
		float radius = 0;
		bool isSucceeded = terrain->ComputeBoundingSphere(&center, &radius);
		if (isSucceeded == false)
		{
			SEND_LOG_WARNING("Terrain CompiuteBoundingSphere Failed");
			return;
		}

		result = IsInFrustumWithMesh(center, radius);
	}
	else if (navPrimitive != nullptr)
	{
		result = true;
	}
	else
	{
		result = IsInFrustum(obj->m_pTransform->m_position.operator D3DXVECTOR3());
	}

	// frustum 안에 있으면 cull을 하지 않는다. 
	obj->SetViewFrustumCulled(!result);
}

void HyEngine::Camera::ViewFrustumCulling(const std::vector<GameObject*>& objs)
{
	for (auto& obj : objs)
	{
		ViewFrustumCulling(obj);
	}
}

bool HyEngine::Camera::IsInFrustumWithOutFar(D3DXVECTOR3 & position)
{
	/*
	면과 위치를 내적했을 때 0보다 크면 안에 있는 것
	작으면 밖, 0이면 동일한 위치
	여섯 면을 모두 검사한다.
	*/

	// 여기서 Far는 계산하지않는다.
	if (D3DXPlaneDotCoord(&m_leftPlane, &position) < 0.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_rightPlane, &position) < 0.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_topPlane, &position) < 0.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_bottomPlane, &position) < 0.0f)
		return false;

	if (D3DXPlaneDotCoord(&m_nearPlane, &position) < 0.0f)
		return false;

	return true;
}
