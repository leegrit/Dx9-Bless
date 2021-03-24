#include "StandardEngineFramework.h"
#include "RaycastHit.h"
#include "Transform.h"
#include "Collider.h"
HyEngine::RaycastHit::RaycastHit(Collider * collider)
{
	this->m_pCollider = collider;
	this->m_pTransform = collider->GetGameObject()->m_pTransform;
}

HyEngine::RaycastHit::RaycastHit()
{
	this->m_pCollider = nullptr;
	this->m_pTransform = nullptr;
}
