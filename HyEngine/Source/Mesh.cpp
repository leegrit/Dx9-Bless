#include "StandardEngineFramework.h"
#include "Mesh.h"

HyEngine::Mesh::Mesh(ERenderType renderType, Scene * scene, GameObject * parent, std::wstring name)
	: GameObject(ERenderType::RenderOpaque, scene, parent, name)
{

}

HyEngine::Mesh::~Mesh()
{
}

void HyEngine::Mesh::Render()
{
}

void HyEngine::Mesh::DrawPrimitive(ID3DXEffect* pShader)
{

}

void HyEngine::Mesh::UpdatedData(EDataType dataType)
{

}

void HyEngine::Mesh::OnEnable()
{
	GameObject::OnEnable();
}

void HyEngine::Mesh::OnDisable()
{
	GameObject::OnDisable();
}

bool HyEngine::Mesh::ComputeBoundingSphere(D3DXVECTOR3 * center, float * radius)
{
	*center = D3DXVECTOR3(0, 0, 0);
	*radius = 0;
	return false;
}

void HyEngine::Mesh::RenderBoundingMesh(ID3DXEffect * pEffect)
{
	// boundingMesh가 없으면 occlusion culling이 적용되지 않기 때문에 
	// 되도록 생성해줘야한다.
	if (m_pBoundingMesh == nullptr)
		return;

	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matPos;
	D3DXMATRIX matWorld;

	D3DXMatrixScaling(&matScale, 1, 1, 1);
	D3DXMatrixRotationYawPitchRoll(&matRot, 0, 0, 0);
	D3DXVECTOR3 pos;
	D3DXVec3TransformCoord(&pos, &m_boundingCenter, &m_pTransform->GetWorldMatrix());
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, pos.z);

	matWorld = matScale * matRot * matPos;

	/* Find Camera */

	Camera* pSelectedCamera;
	if (IS_EDITOR)
		pSelectedCamera = EDIT_SCENE->GetSelectedCamera();
	else
		pSelectedCamera = SCENE->GetSelectedCamera();

	pEffect->SetValue("WorldMatrix", &matWorld, sizeof(matWorld));
	pEffect->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
	pEffect->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));

	pEffect->CommitChanges();
	m_pBoundingMesh->DrawSubset(0);
}

void HyEngine::Mesh::OcclusionCulled(bool isCulled)
{
	m_occlusionCulled = isCulled;
}

bool HyEngine::Mesh::IsOcclusionCulled()
{
	return m_occlusionCulled;
}

D3DXVECTOR3 HyEngine::Mesh::GetBoundingCenter()
{
	return m_boundingCenter;
}

D3DXVECTOR3 HyEngine::Mesh::GetBoundingWorldPos()
{
	D3DXVECTOR3 pos;
	D3DXVec3TransformCoord(&pos, &m_boundingCenter, &m_pTransform->GetWorldMatrix());
	return pos;
}

float HyEngine::Mesh::GetBoundingRadius()
{
	return m_boundingRadius;
}

void HyEngine::Mesh::CreateBoundingMesh(D3DXVECTOR3 center, float radius)
{
	D3DXCreateSphere
	(
		DEVICE,
		radius,
		10,
		10,
		&m_pBoundingMesh,
		0
	);
	m_boundingCenter = center;
	m_boundingRadius = radius;
}
