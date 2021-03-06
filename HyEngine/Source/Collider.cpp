#include "StandardEngineFramework.h"
#include "Collider.h"
#include "ObjectContainer.h"

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
		m_pOwner->GetScene()->GetObjectContainer()->AddDynamicCollider(this);
		break;
	case EColliderType::Static :
		m_pOwner->GetScene()->GetObjectContainer()->AddStaticCollider(this);
		break;
	case EColliderType::Multipurpose:
		m_pOwner->GetScene()->GetObjectContainer()->AddMultipurposeCollider(this);
		break;
	}

	// collider transform don't have owner.
	m_pTransform = new Transform(nullptr);
}
Collider::~Collider()
{
	SAFE_DELETE(m_pTransform);
}
void HyEngine::Collider::Initialize()
{
}

void HyEngine::Collider::Update()
{
	if (m_pOwner == nullptr) return;

	Vector3 result = m_pOwner->m_pTransform->m_position;
	result += m_pOwner->m_pTransform->Forward() * m_offset.z();
	result += m_pOwner->m_pTransform->Right() * m_offset.x();
	result += m_pOwner->m_pTransform->Up() * m_offset.y();

	m_pTransform->SetPosition(result);
	//m_pTransform->m_rotation = m_pOwner->m_pTransform->m_rotation;
}

void HyEngine::Collider::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());

	if (IS_CLIENT)
	{
		bool bRender = ENGINE->CheckRenderOption(RenderOptions::RenderCollider);
		if (bRender == false)
			return;
	}
}

bool HyEngine::Collider::GetActive() const
{
	return m_bActiveSelf;
}

void HyEngine::Collider::Calculate(Collider * other) const
{
}
