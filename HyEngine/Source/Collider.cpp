#include "StandardEngineFramework.h"
#include "Collider.h"

HyEngine::Collider::Collider(EColliderShape colliderShape, EColliderType colliderType, GameObject * owner, UINT targetLayer, std::function<void(Collider*)> onCollision)
	: m_colliderShape(colliderShape),
	m_colliderType(colliderType),
	m_pOwner(owner),
	m_onCollision(onCollision),
	m_targetLayer(targetLayer),
	Object(L"Collider")
{
	assert(m_pOwner != nullptr);
	switch (m_colliderType)
	{
	case EColliderType::Dynamic :
		m_pOwner->GetScene()->AddDynamicCollider(this);
		break;
	case EColliderType::Static :
		m_pOwner->GetScene()->AddStaticCollider(this);
		break;
	case EColliderType::Multipurpose:
		m_pOwner->GetScene()->AddMultipurposeCollider(this);
		break;
	}

	// collider transform don't have owner.
	m_pTransform = new Transform(nullptr);
}

void HyEngine::Collider::Initialize()
{
}

void HyEngine::Collider::PositionUpdate()
{
	if (m_pOwner == nullptr) return;

	Vector3 result = m_pOwner->m_pTransform->m_position;
	result += m_pOwner->m_pTransform->Forward() * m_offset.z();
	result += m_pOwner->m_pTransform->Right() * m_offset.x();
	result += m_pOwner->m_pTransform->Up() * m_offset.y();

	m_pTransform->SetPosition(result);
	m_pTransform->m_rotation = m_pOwner->m_pTransform->m_rotation;
}

void HyEngine::Collider::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
}

bool HyEngine::Collider::GetActive() const
{
	assert(m_pOwner);

	return m_pOwner->GetActive();
}

void HyEngine::Collider::Calculate(Collider * other) const
{
}
