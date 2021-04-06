#include "StandardEngineFramework.h"
#include "Scene.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Collider.h"
#include "ParticleSystem.h"
#include "UIElement.h"
#include "Light.h"
#include "Skybox.h"
#include "NavMesh.h"
#include "ObjectContainer.h"
#include "CollisionCalculator.h"

using namespace HyEngine;


Scene::Scene()
{
	m_pCollisionCalculator = new CollisionCalculator();
	m_pObjectContainer = new ObjectContainer();
}
Scene::~Scene()
{
	SAFE_DELETE(m_pObjectContainer);
	EventDispatcher::Cleanup();
}

void HyEngine::Scene::LoadScene()
{
	Load();
}

void HyEngine::Scene::UnloadScene()
{
	Unload();
	m_pObjectContainer->ClearAll();

}

void HyEngine::Scene::UpdateScene()
{
	m_pObjectContainer->ClearGarbage();

	/* Opaque */
	for (auto& opaque : m_pObjectContainer->GetOpaqueObjectAll())
	{
		if (opaque->GetActive() == true &&
			opaque->m_bWantsDestroy == false)
			opaque->Update();
	}

	/* Alpha */
	for (auto& alpha : m_pObjectContainer->GetAlphaObjectAll())
	{
		if (alpha->GetActive() == true &&
			alpha->m_bWantsDestroy == false)
			alpha->Update();
	}

	/* Invisible */
	for (auto& invisible : m_pObjectContainer->GetInvisibleObjectAll())
	{
		if (invisible->GetActive() == true &&
			invisible->m_bWantsDestroy == false)
			invisible->Update();
	}

	/* Dynamic */
	for (auto& dynamic : m_pObjectContainer->GetDynamicColliderAll())
	{
		if (dynamic->GetActive() == true &&
			dynamic->m_bWantsDestroy == false)
			dynamic->Update();
	}

	/* Static */
	for (auto& staticCol : m_pObjectContainer->GetStaticColliderAll())
	{
		if (staticCol->GetActive() == true &&
			staticCol->m_bWantsDestroy == false)
			staticCol->Update();
	}

	/* Multipurpose */
	for (auto& multipurpose : m_pObjectContainer->GetMultipurposeColliderAll())
	{
		if (multipurpose->GetActive() == true &&
			multipurpose->m_bWantsDestroy == false)
			multipurpose->Update();
	}

	/* Collision Calculate */
	m_pCollisionCalculator->Calculate
	(
		m_pObjectContainer->GetDynamicColliderAll(),
		m_pObjectContainer->GetStaticColliderAll()
	);


	/* Update For Scene */
	Update();

	//////////////////////////////////////////////////////////////////////////
	// LATE UPDATE
	//////////////////////////////////////////////////////////////////////////
	/* Opaque */
	for (auto& opaque : m_pObjectContainer->GetOpaqueObjectAll())
	{
		if (opaque->GetActive() == true &&
			opaque->m_bWantsDestroy == false)
			opaque->LateUpdate();
	}

	/* Alpha */
	for (auto& alpha : m_pObjectContainer->GetAlphaObjectAll())
	{
		if (alpha->GetActive() == true &&
			alpha->m_bWantsDestroy == false)
			alpha->LateUpdate();
	}

	/* Invisible */
	for (auto& invisible : m_pObjectContainer->GetInvisibleObjectAll())
	{
		if (invisible->GetActive() == true &&
			invisible->m_bWantsDestroy == false)
			invisible->LateUpdate();
	}

	m_pObjectContainer->ClearCache();
}

void HyEngine::Scene::RenderScene(Renderer * renderer)
{
	renderer->Render(this);
}

bool HyEngine::Scene::SelectCamera(std::wstring name)
{
	return m_pObjectContainer->TryGetInvisibleObject(name, (GameObject**)&m_pSelectedCamera);
}

Camera * HyEngine::Scene::GetSelectedCamera() const
{
	return m_pSelectedCamera;
}

ObjectContainer * HyEngine::Scene::GetObjectContainer() const
{
	return m_pObjectContainer;
}

void HyEngine::Scene::ViewFrustumCull()
{
	m_pSelectedCamera->ViewFrustumCulling
	(
		m_pObjectContainer->GetOpaqueObjectAll()
	);
	m_pSelectedCamera->ViewFrustumCulling
	(
		m_pObjectContainer->GetAlphaObjectAll()
	);
}


