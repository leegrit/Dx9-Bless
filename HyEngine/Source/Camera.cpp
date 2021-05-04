#include "StandardEngineFramework.h"
#include "Camera.h"
#include "Scene.h"
#include "Mesh.h"
#include "Terrain.h"
#include "NavPrimitive.h"
#include "LightObject.h"
#include "Light.h"



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
	if (D3DXPlaneDotCoord(&m_leftPlane, &position) < -radius)
	{
		return false;
	}

	if (D3DXPlaneDotCoord(&m_rightPlane, &position) < -radius)
	{
		return false;
	}

	if (D3DXPlaneDotCoord(&m_topPlane, &position) < -radius)
	{
		return false;
	}


	if (D3DXPlaneDotCoord(&m_bottomPlane, &position) < -radius)
	{
		return false;
	}

	if (D3DXPlaneDotCoord(&m_nearPlane, &position) < -radius)
	{
		return false;
	}

	if (D3DXPlaneDotCoord(&m_farPlane, &position) < -radius)
	{
		return false;
	}

	return true;
}

bool HyEngine::Camera::IsInFrustumWithRadius(D3DXVECTOR3 position, float radius)
{
	if (D3DXPlaneDotCoord(&m_leftPlane, &position)  < -radius)
	{
		return false;
	}

	if (D3DXPlaneDotCoord(&m_rightPlane, &position) < -radius)
	{
		return false;
	}

	if (D3DXPlaneDotCoord(&m_topPlane, &position) < -radius)
	{
		return false;
	}


	if (D3DXPlaneDotCoord(&m_bottomPlane, &position) < -radius)
	{
		return false;
	}

	if (D3DXPlaneDotCoord(&m_nearPlane, &position)   < -radius)
	{
		return false;
	}

	if (D3DXPlaneDotCoord(&m_farPlane, &position)  < -radius)
	{
		return false;
	}

	return true;
}


void HyEngine::Camera::ViewFrustumCulling(GameObject * obj)
{
	assert(obj != nullptr);	

	if (obj->GetCullable() == false)
		return;

	bool result = false;

	Mesh* mesh = nullptr;
	mesh = dynamic_cast<Mesh*>(obj);

	Terrain * terrain = nullptr;
	terrain = dynamic_cast<Terrain*>(obj);

	NavPrimitive * navPrimitive = nullptr;
	navPrimitive = dynamic_cast<NavPrimitive*>(obj);

	UIElement* uiElement = nullptr;
	uiElement = dynamic_cast<UIElement*>(obj);


	/* 메쉬인경우 */
	if (mesh != nullptr)
	{
		D3DXVECTOR3 center = D3DXVECTOR3(0, 0, 0);
		float radius = 0;
		bool isSucceeded =  mesh->ComputeBoundingSphere(&center, &radius);
		D3DXVec3TransformCoord(&center, &center, &mesh->m_pTransform->GetWorldMatrix());
		radius = radius * mesh->m_pTransform->m_scale.x();
		if (isSucceeded == false)
		{
			SEND_LOG_WARNING("Mesh CompiuteBoundingSphere Failed");
			return;
		}

		result = IsInFrustumWithMesh(center, radius);
	}
	else if (terrain != nullptr)
	{
		result = true;
		/*D3DXVECTOR3 center = D3DXVECTOR3(0, 0, 0);
		float radius = 0;
		bool isSucceeded = terrain->ComputeBoundingSphere(&center, &radius);
		if (isSucceeded == false)
		{
			SEND_LOG_WARNING("Terrain CompiuteBoundingSphere Failed");
			return;
		}

		result = IsInFrustumWithMesh(center, radius);*/
	}
	else if (navPrimitive != nullptr)
	{
		result = true;
	}
	else if (uiElement != nullptr)
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

void HyEngine::Camera::ViewFrustumCulling(Light * light)
{
	if (light->Type() == ELightType::DIRECTIONAL)
		return;

	bool result = IsInFrustumWithMesh(light->Position(), light->Range());

	light->IsCulled() = !result;
}

void HyEngine::Camera::ViewFrustumCulling(const std::vector<GameObject*>& objs)
{
	for (auto& obj : objs)
	{
		ViewFrustumCulling(obj);
	}
}
void HyEngine::Camera::ViewFrustumCulling(const std::vector<Light*>& lights)
{
	for (auto& light : lights)
	{
		ViewFrustumCulling(light);
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

void HyEngine::Camera::BeginFrustumCull(D3DXMATRIX viewMat, D3DXMATRIX projMat)
{
	D3DXMATRIX M = viewMat * projMat;

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

bool HyEngine::Camera::FrustumCulling(GameObject * obj)
{
	assert(obj != nullptr);

	if(obj->GetCullable() == false)
		return true;

	bool result = false;

	Mesh* mesh = nullptr;
	mesh = dynamic_cast<Mesh*>(obj);

	Terrain * terrain = nullptr;
	terrain = dynamic_cast<Terrain*>(obj);

	NavPrimitive * navPrimitive = nullptr;
	navPrimitive = dynamic_cast<NavPrimitive*>(obj);

	UIElement* uiElement = nullptr;
	uiElement = dynamic_cast<UIElement*>(obj);

	/* 메쉬인경우 */
	if (mesh != nullptr)
	{
		D3DXVECTOR3 center = D3DXVECTOR3(0, 0, 0);
		float radius = 0;
		bool isSucceeded = mesh->ComputeBoundingSphere(&center, &radius);

		if (isSucceeded == false)
		{
			SEND_LOG_WARNING("Mesh CompiuteBoundingSphere Failed");
			return true;
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
			return true;
		}

		result = IsInFrustumWithMesh(center, radius);
	}
	else if (navPrimitive != nullptr)
	{
		result = true;
	}
	else if (uiElement != nullptr)
	{
		result = true;
	}
	else
	{
		result = IsInFrustum(obj->m_pTransform->m_position.operator D3DXVECTOR3());
	}

	return !result;
}

void HyEngine::Camera::EndFrustumCull()
{
	/* 원상복귀 */
	FrustumUpdate();
}
