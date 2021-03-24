#include "StandardEngineFramework.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

using namespace HyEngine;


Component::Component(DWORD behaviourType, GameObject* owner, std::wstring tag)
	: Object(tag),
	m_behviourType(behaviourType),
	m_bActiveSelf(true),
	m_pOwner(owner)
{

}


Component::~Component()
{
}

void Component::Initialize()
{

	/*if (m_behviourType & BehaviourType::Update)
	{
		UpdateDispatcher::UpdateDispatch
		(
			std::bind(&Component::Update, this),
			std::bind(&Component::UpdateCompleted, this)
		);
	}
	if (m_behviourType & BehaviourType::LateUpdate)
	{
		UpdateDispatcher::LateUpdateDispatch
		(
			std::bind(&Component::LateUpdate, this),
			std::bind(&Component::LateUpdateCompleted, this)
		);
	}*/

	m_bInitialized = true;
}

bool Component::CompareTag(std::wstring tag)
{
	return m_tag == tag;
}

Transform * HyEngine::Component::GetTransform()
{
	return m_pOwner->m_pTransform;
}

void HyEngine::Component::SetActive(bool active)
{
	if (m_bActiveSelf != active)
	{
		if (active == true)
			OnEnable();
		else
			OnDisable();
	}
	m_bActiveSelf = active;
}

GameObject* HyEngine::Component::GetGameObject()
{
	return m_pOwner;
}