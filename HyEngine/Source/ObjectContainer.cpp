#include "StandardEngineFramework.h"
#include "ObjectContainer.h"
#include "Light.h"
#include "StaticMesh.h"
#include "DynamicMesh.h"
#include "UIElement.h"
#include "Effect.h"


using namespace HyEngine;

HyEngine::ObjectContainer::ObjectContainer()
{
	EventDispatcher::AddEventListener(EngineEvent::ObjectDestroyed, "ObjectContainer", [&](void*) 
	{
		m_bDirtyFlag = true;
		m_bObjectDestroyed = true;
	});
}
HyEngine::ObjectContainer::~ObjectContainer()
{
	EventDispatcher::RemoveEventListener(EngineEvent::ObjectDestroyed, "ObjectContainer");
}


void HyEngine::ObjectContainer::ClearGarbage()
{
	if (m_bObjectDestroyed == false)
		return;

	std::vector<Object*> garbages;

	/* Opaque objects */
	for (UINT i = 0; i < m_opaqueObjects.size(); i++)
	{
		if (m_opaqueObjects[i]->m_bWantsDestroy)
		{
			garbages.push_back(m_opaqueObjects[i]);
			m_opaqueObjects.erase(m_opaqueObjects.begin() + i);
			i--;
		}
	}

	/* Alpha objects */
	for (UINT i = 0; i < m_alphaObjects.size(); i++)
	{
		if (m_alphaObjects[i]->m_bWantsDestroy)
		{
			garbages.push_back(m_alphaObjects[i]);
			m_alphaObjects.erase(m_alphaObjects.begin() + i);
			i--;
		}
	}

	/* Invisible objects */
	for (UINT i = 0; i < m_invisibleObjects.size(); i++)
	{
		if (m_invisibleObjects[i]->m_bWantsDestroy)
		{
			garbages.push_back(m_invisibleObjects[i]);
			m_invisibleObjects.erase(m_invisibleObjects.begin() + i);
			i--;
		}
	}

	/* Dynamic Colliders */
	for (UINT i = 0; i < m_dynamicColliders.size(); i++)
	{
		if (m_dynamicColliders[i]->m_bWantsDestroy)
		{
			garbages.push_back(m_dynamicColliders[i]);
			m_dynamicColliders.erase(m_dynamicColliders.begin() + i);
			i--;
		}
	}

	/* Static Colliders */
	for (UINT i = 0; i < m_staticColliders.size(); i++)
	{
		if (m_staticColliders[i]->m_bWantsDestroy)
		{
			garbages.push_back(m_staticColliders[i]);
			m_staticColliders.erase(m_staticColliders.begin() + i);
			i--;
		}
	}

	/* Multipurpose Colliders */
	for (UINT i = 0; i < m_multipurposeColliders.size(); i++)
	{
		if (m_multipurposeColliders[i]->m_bWantsDestroy)
		{
			garbages.push_back(m_multipurposeColliders[i]);
			m_multipurposeColliders.erase(m_multipurposeColliders.begin() + i);
			i--;
		}
	}

	/* Lights */
	for (UINT i = 0; i < m_lights.size(); i++)
	{
		if (m_lights[i]->m_bWantsDestroy)
		{
			garbages.push_back(m_lights[i]);
			m_lights.erase(m_lights.begin() + i);
			i--;
		}
	}

	/* TODO : Particles */


	for (auto& garbage : garbages)
		Object::DestroyImmediate(garbage);

	m_bObjectDestroyed = false;
}

void HyEngine::ObjectContainer::ClearAll()
{
	/* Opaque */
	for (auto& obj : m_opaqueObjects)
		Object::DestroyImmediate(obj);
	m_opaqueObjects.clear();

	/* Alpha */
	for (auto& obj : m_alphaObjects)
		Object::DestroyImmediate(obj);
	m_alphaObjects.clear();

	/* Invisible */
	for (auto& obj : m_invisibleObjects)
		Object::DestroyImmediate(obj);
	m_invisibleObjects.clear();

	/* Dynamic */
	for (auto& col : m_dynamicColliders)
		Object::DestroyImmediate(col);
	m_dynamicColliders.clear();

	/* Static */
	for (auto& col : m_staticColliders)
		Object::DestroyImmediate(col);
	m_staticColliders.clear();

	/* Multipurpose */
	for (auto& col : m_multipurposeColliders)
		Object::DestroyImmediate(col);
	m_multipurposeColliders.clear();

	/* Light */
	for (auto& light : m_lights)
		Object::DestroyImmediate(light);
	m_lights.clear();

	SAFE_DELETE(m_pSkybox);
}

void HyEngine::ObjectContainer::ClearCache()
{
	/* Opaque */
	for (auto& opaque : m_opaqueCache)
		opaque.second.clear();
	m_opaqueCache.clear();

	/* Alpha */
	for (auto& alpha : m_alphaCache)
		alpha.second.clear();
	m_alphaCache.clear();

	/* Invisible */
	for (auto& invisible : m_invisibleCache)
		invisible.second.clear();
	m_invisibleCache.clear();

	/* Dynamic */
	for (auto& dynamic : m_dynamicCache)
		dynamic.second.clear();
	m_dynamicCache.clear();

	/* Static */
	for (auto& staticCache : m_staticCache)
		staticCache.second.clear();
	m_staticCache.clear();

	/* Multipurpose */
	for (auto& multipurpose : m_multipurposeCache)
		multipurpose.second.clear();
	m_multipurposeCache.clear();
}

void HyEngine::ObjectContainer::AddOpaqueObject(GameObject * obj)
{
	assert(obj->GetRenderType() == ERenderType::RenderOpaque);

	for (auto& opaque : m_opaqueObjects)
	{
		if (opaque == obj)
		{
			assert(false);
		}
	}

	m_opaqueObjects.push_back(obj);
	m_bDirtyFlag = true;
}

void HyEngine::ObjectContainer::AddAlphaObject(GameObject * obj)
{
	assert(obj->GetRenderType() == ERenderType::RenderAlpha);

	for (auto& alpha : m_alphaObjects)
	{
		if (alpha == obj)
		{
			assert(false);
		}
	}

	m_alphaObjects.push_back(obj);
	m_bDirtyFlag = true;
}

void HyEngine::ObjectContainer::AddInvisibleObject(GameObject * obj)
{
	assert(obj->GetRenderType() == ERenderType::None);

	for (auto& invisible : m_invisibleObjects)
	{
		if (invisible == obj)
		{
			assert(false);
		}
	}
	m_invisibleObjects.push_back(obj);
	m_bDirtyFlag = true;
}

void HyEngine::ObjectContainer::AddDynamicCollider(Collider * col)
{
	for (auto& dynamic : m_dynamicColliders)
	{
		if (dynamic == col)
		{
			assert(false);
		}
	}
	m_dynamicColliders.push_back(col);
	m_bDirtyFlag = true;
}

void HyEngine::ObjectContainer::AddStaticCollider(Collider * col)
{
	for (auto& staticCol : m_staticColliders)
	{
		if (staticCol == col)
		{
			assert(false);
		}
	}
	m_staticColliders.push_back(col);
	m_bDirtyFlag = true;
}

void HyEngine::ObjectContainer::AddMultipurposeCollider(Collider * col)
{
	for (auto& multiPurpose : m_multipurposeColliders)
	{
		if (multiPurpose == col)
		{
			assert(false);
		}
	}
	m_multipurposeColliders.push_back(col);
	m_bDirtyFlag = true;
}

void HyEngine::ObjectContainer::AddLight(Light * light)
{
	for (auto& l : m_lights)
	{
		assert(l != light);
	}
	m_lights.push_back(light);
	m_bDirtyFlag = true;
}

void HyEngine::ObjectContainer::SetSkybox(Skybox * skybox)
{
	assert(m_pSkybox != skybox);
	m_pSkybox = skybox;
}

bool HyEngine::ObjectContainer::TryGetGameObject(std::wstring name, _Out_ GameObject ** outObj)
{
	*outObj = nullptr;

	auto& container = GetGameObjectAll();

	for (auto& obj : container)
	{
		if (obj->GetName().compare(name) == 0)
		{
			*outObj = obj;
			return true;
		}
	}
	return false;
}

bool HyEngine::ObjectContainer::TryGetOpaqueObject(std::wstring name, _Out_ GameObject ** outObj)
{
	*outObj = nullptr;

	auto& container = GetOpaqueObjectAll();

	for (auto& obj : container)
	{
		if (obj->GetName().compare(name) == 0)
		{
			*outObj = obj;
			return true;
		}
	}
	return false;
}

bool HyEngine::ObjectContainer::TryGetAlphaObject(std::wstring name, _Out_ GameObject ** outObj)
{
	*outObj = nullptr;

	auto& container = GetAlphaObjectAll();

	for (auto& obj : container)
	{
		if (obj->GetName().compare(name) == 0)
		{
			*outObj = obj;
			return true;
		}
	}
	return false;
}

bool HyEngine::ObjectContainer::TryGetInvisibleObject(std::wstring name, _Out_ GameObject ** outObj)
{
	*outObj = nullptr;

	auto& container = GetInvisibleObjectAll();

	for (auto& obj : container)
	{
		if (obj->GetName().compare(name) == 0)
		{
			*outObj = obj;
			return true;
		}
	}
	return false;
}

Skybox * HyEngine::ObjectContainer::GetSkybox() const
{
	return m_pSkybox;
}

bool HyEngine::ObjectContainer::GetDirtyFlag()
{
	return m_bDirtyFlag;
}

std::vector<GameObject*> HyEngine::ObjectContainer::GetGameObjectAll()
{
	std::vector<GameObject*> mergedVec;

	mergedVec.insert(mergedVec.end(), m_opaqueObjects.begin(), m_opaqueObjects.end());
	mergedVec.insert(mergedVec.end(), m_alphaObjects.begin(), m_alphaObjects.end());
	mergedVec.insert(mergedVec.end(), m_invisibleObjects.begin(), m_invisibleObjects.end());

	return mergedVec;
}

std::vector<GameObject*>& HyEngine::ObjectContainer::GetOpaqueObjectAll()
{
	return m_opaqueObjects;
}

std::vector<GameObject*> HyEngine::ObjectContainer::GetRenderableOpaqueAll()
{
	return cpplinq::from_iterators(m_opaqueObjects.begin(), m_opaqueObjects.end())
		>> cpplinq::where([&](GameObject* obj)
	{
		if (obj->GetActive() == false) return false;
		if (obj->m_bWantsDestroy == true) return false;
		if (obj->GetViewFrustumCulled() == true) return false;
		return true;
	}) >> cpplinq::to_vector();
}

std::vector<GameObject*>& HyEngine::ObjectContainer::GetAlphaObjectAll()
{
	return m_alphaObjects;
}

std::vector<GameObject*> HyEngine::ObjectContainer::GetRenderableAlphaAll()
{
	return cpplinq::from_iterators(m_alphaObjects.begin(), m_alphaObjects.end())
		>> cpplinq::where([&](GameObject* obj)
	{
		if (obj->GetActive() == false) return false;
		if (obj->m_bWantsDestroy == true) return false;
		if (obj->GetViewFrustumCulled() == true) return false;
		return true;
	}) >> cpplinq::to_vector();
}

std::vector<GameObject*>& HyEngine::ObjectContainer::GetInvisibleObjectAll()
{
	return m_invisibleObjects;
}

std::vector<Collider*> HyEngine::ObjectContainer::GetRenderableColliderAll()
{
	std::vector<Collider*> mergedVec;

	mergedVec.insert(mergedVec.end(), m_dynamicColliders.begin(), m_dynamicColliders.end());
	mergedVec.insert(mergedVec.end(), m_staticColliders.begin(), m_staticColliders.end());
	mergedVec.insert(mergedVec.end(), m_multipurposeColliders.begin(), m_multipurposeColliders.end());

	return cpplinq::from_iterators(mergedVec.begin(), mergedVec.end())
		>> cpplinq::where([&](Collider* collider)
	{
		if (collider->GetActive() == false) return false;
		if (collider->m_bWantsDestroy == true) return false;
		return true;
	}) >> cpplinq::to_vector();
}

std::vector<Collider*>& HyEngine::ObjectContainer::GetDynamicColliderAll()
{
	return m_dynamicColliders;
}

std::vector<Collider*>& HyEngine::ObjectContainer::GetStaticColliderAll()
{
	return m_staticColliders;
}

std::vector<Collider*>& HyEngine::ObjectContainer::GetMultipurposeColliderAll()
{
	return m_multipurposeColliders;
}

std::vector<Light*>& HyEngine::ObjectContainer::GetLightAll()
{
	return m_lights;
}

std::vector<Light*> HyEngine::ObjectContainer::GetRenderableLightAll()
{
	return cpplinq::from_iterators(m_lights.begin(), m_lights.end())
		>> cpplinq::where([&](Light* light)
	{
		if (light->m_bWantsDestroy == true) return false;
		if (light->GetActive() == false) return false;
		if (light->IsCulled() == true) return false;
		return true;
	}) >> cpplinq::to_vector();
}

std::vector<GameObject*>& HyEngine::ObjectContainer::GetStaticMeshAll()
{
	return m_staticMeshes;
}

std::vector<GameObject*>& HyEngine::ObjectContainer::GetDynamicMeshAll()
{
	return m_dynamicMeshes;
}

std::vector<GameObject*>& HyEngine::ObjectContainer::GetUIElementAll()
{
	return m_uiElements;
}

std::vector<GameObject*>& HyEngine::ObjectContainer::GetEffectAll()
{
	return m_effects;
}

std::vector<GameObject*>& HyEngine::ObjectContainer::GetOpaqueObjectAll(UINT layer)
{
	auto& iter = m_opaqueCache.find(layer);
	if (iter == m_opaqueCache.end())
	{
		auto& result = cpplinq::from_iterators(m_opaqueObjects.begin(), m_opaqueObjects.end())
			>> cpplinq::where([&](GameObject* obj)
		{
			if (obj->GetLayer() & layer && obj->GetActive())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_opaqueCache.insert(std::make_pair(layer, result));
		return m_opaqueCache[layer];
	}
	else
		return iter->second;
}

std::vector<GameObject*>& HyEngine::ObjectContainer::GetAlphaObjectAll(UINT layer)
{
	auto& iter = m_alphaCache.find(layer);
	if (iter == m_alphaCache.end())
	{
		auto& result = cpplinq::from_iterators(m_alphaObjects.begin(), m_alphaObjects.end())
			>> cpplinq::where([&](GameObject* obj)
		{
			if (obj->GetLayer() & layer && obj->GetActive())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_alphaCache.insert(std::make_pair(layer, result));
		return m_alphaCache[layer];
	}
	else
		return iter->second;
}

std::vector<GameObject*>& HyEngine::ObjectContainer::GetInvisibleObjectAll(UINT layer)
{
	auto& iter = m_invisibleCache.find(layer);
	if (iter == m_invisibleCache.end())
	{
		auto& result = cpplinq::from_iterators(m_invisibleObjects.begin(), m_invisibleObjects.end())
			>> cpplinq::where([&](GameObject* obj)
		{
			if (obj->GetLayer() & layer && obj->GetActive())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_invisibleCache.insert(std::make_pair(layer, result));
		return m_invisibleCache[layer];
	}
	else
		return iter->second;
}

std::vector<Collider*>& HyEngine::ObjectContainer::GetDynamicColliderAll(UINT layer)
{
	auto& iter = m_dynamicCache.find(layer);
	if (iter == m_dynamicCache.end())
	{
		auto& result = cpplinq::from_iterators(m_dynamicColliders.begin(), m_dynamicColliders.end())
			>> cpplinq::where([&](Collider* obj)
		{
			if (obj->GetGameObject()->GetLayer() & layer && obj->GetActive())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_dynamicCache.insert(std::make_pair(layer, result));
		return m_dynamicCache[layer];
	}
	else
		return iter->second;
}

std::vector<Collider*>& HyEngine::ObjectContainer::GetStaticColliderAll(UINT layer)
{
	auto& iter = m_staticCache.find(layer);
	if (iter == m_staticCache.end())
	{
		auto& result = cpplinq::from_iterators(m_staticColliders.begin(), m_staticColliders.end())
			>> cpplinq::where([&](Collider* obj)
		{
			if (obj->GetGameObject()->GetLayer() & layer && obj->GetActive())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_staticCache.insert(std::make_pair(layer, result));
		return m_staticCache[layer];
	}
	else
		return iter->second;
}

std::vector<Collider*>& HyEngine::ObjectContainer::GetMultipurposeColliderAll(UINT layer)
{
	auto& iter = m_multipurposeCache.find(layer);
	if (iter == m_multipurposeCache.end())
	{
		auto& result = cpplinq::from_iterators(m_multipurposeColliders.begin(), m_multipurposeColliders.end())
			>> cpplinq::where([&](Collider* obj)
		{
			if (obj->GetGameObject()->GetLayer() & layer && obj->GetActive())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_multipurposeCache.insert(std::make_pair(layer, result));
		return m_multipurposeCache[layer];
	}
	else
		return iter->second;
}

void HyEngine::ObjectContainer::SeperateContainers()
{
	if (m_bDirtyFlag == false)
		return;

	m_staticMeshes.clear();
	m_dynamicMeshes.clear();
	m_uiElements.clear();
	m_effects.clear();

	for (auto& obj : m_opaqueObjects)
	{
		StaticMesh* staticMesh = dynamic_cast<StaticMesh*>(obj);
		if (staticMesh != nullptr)
		{
			m_staticMeshes.push_back(staticMesh);
			continue;
		}

		DynamicMesh* dynamicMesh = dynamic_cast<DynamicMesh*>(obj);
		if (dynamicMesh != nullptr)
		{
			m_dynamicMeshes.push_back(dynamicMesh);
			continue;
		}
	}
	for (auto& obj : m_alphaObjects)
	{
		UIElement* uiElement = dynamic_cast<UIElement*>(obj);
		if (uiElement != nullptr)
		{
			m_uiElements.push_back(uiElement);
			continue;
		}

		Effect* effect = dynamic_cast<Effect*>(obj);
		if (effect != nullptr)
		{
			m_effects.push_back(effect);
			continue;
		}
	}


	m_bDirtyFlag = false;
}
