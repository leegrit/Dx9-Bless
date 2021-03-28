#include "StandardEngineFramework.h"
#include "Collider.h"
#include "SphereCollider.h"

HyEngine::SphereCollider::SphereCollider(EColliderType colliderType, GameObject* owner, int radius,UINT targetLayer, std::function<void(Collider*)>onCollision)
	: Collider(EColliderShape::Sphere, colliderType, owner,targetLayer, onCollision),
	m_radius(radius)
{

}

HyEngine::SphereCollider::~SphereCollider()
{
	SAFE_RELEASE(m_pSphereMesh);

}

void HyEngine::SphereCollider::Initialize()
{
	Collider::Initialize();
	D3DXCreateSphere
	(
		DEVICE,
		(float)m_radius,
		m_slices,
		m_stacks,
		&m_pSphereMesh,
		0
	);
}

void HyEngine::SphereCollider::Render()
{
	Collider::Render();

	m_pSphereMesh->DrawSubset(0);
}

void HyEngine::SphereCollider::Calculate(Collider * other) const
{
	Collider::Calculate(other);
	switch (other->GetColliderShape())
	{
	case EColliderShape::Sphere : 
		if (CalcToSphere(other))
		{
			if (m_onCollision)
				m_onCollision(other);
			if(other->m_onCollision)
				other->m_onCollision((Collider*)this);
		}
		break;
	case EColliderShape::Box : 
		if (CalcToBox(other))
		{
			if (m_onCollision)
				m_onCollision(other);
			if (other->m_onCollision)
				other->m_onCollision((Collider*)this);
		}
		break;
	case EColliderShape::AABB :
		if (CalcToAABB(other))
		{
			if (m_onCollision)
				m_onCollision(other);
			if (other->m_onCollision)
				other->m_onCollision((Collider*)this);
		}
		break;
	case EColliderShape::OBB :
		if (CalcToOBB(other))
		{
			if (m_onCollision)
				m_onCollision(other);
			if (other->m_onCollision)
				other->m_onCollision((Collider*)this);
		}
		break;
	}
}

bool HyEngine::SphereCollider::CalculateToDot(D3DXVECTOR3 dotPos)
{
	float length = D3DXVec3Length(&(dotPos - GetTransform()->m_position.operator D3DXVECTOR3()));
	if (length < m_radius)
		return true;
	return false;
}

void HyEngine::SphereCollider::SetRadius(float radius)
{
	SAFE_RELEASE(m_pSphereMesh);
	m_radius = radius;
	D3DXCreateSphere
	(
		DEVICE,
		(float)m_radius,
		m_slices,
		m_stacks,
		&m_pSphereMesh,
		0
	);

}

bool HyEngine::SphereCollider::CalcToSphere(Collider* other) const
{
	SphereCollider* col = dynamic_cast<SphereCollider*>(other);
	int collisionLength = m_radius + col->GetRadius();
	int length = (int)D3DXVec3Length(&(col->GetTransform()->m_position - m_pTransform->m_position).operator D3DXVECTOR3());
	
	if (length <= collisionLength)
		return true;

	return false;
}

bool HyEngine::SphereCollider::CalcToBox(Collider* other) const
{
	// don't use
	assert(false);
	return false;
}

bool HyEngine::SphereCollider::CalcToAABB(Collider* other) const
{
	// don't use
	assert(false);
	return false;
}

bool HyEngine::SphereCollider::CalcToOBB(Collider* other) const
{
	// don't use
	assert(false);
	return false;
}
