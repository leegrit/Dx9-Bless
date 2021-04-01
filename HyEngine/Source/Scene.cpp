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

using namespace HyEngine;


Scene::Scene()
{

}
Scene::~Scene()
{
	/*for (auto& obj : m_opaqueObjects)
		Object::DestroyImmediate(obj);
	m_opaqueObjects.clear();
	for (auto& obj : m_alphaObjects)
		Object::DestroyImmediate(obj);
	m_alphaObjects.clear();
	for (auto& obj : m_textureObjects)
		Object::DestroyImmediate(obj);
	m_textureObjects.clear();
	for (auto& obj : m_alphaTextureObjects)
		Object::DestroyImmediate(obj);
	m_alphaObjects.clear();*/
	for (auto& obj : m_meshObjects)
		Object::DestroyImmediate(obj);
	m_meshObjects.clear();
	for (auto& obj : m_textureObjects)
		Object::DestroyImmediate(obj);
	m_textureObjects.clear();
	for (auto& obj : m_invisibleObjects)
		Object::DestroyImmediate(obj);
	m_invisibleObjects.clear();
	for (auto& obj : m_uiObjects)
		Object::DestroyImmediate(obj);
	m_uiObjects.clear();
	for (auto& obj : m_dynamicColliders)
		Object::DestroyImmediate(obj);
	m_dynamicColliders.clear();
	for (auto& obj : m_staticColliders)
		Object::DestroyImmediate(obj);
	m_staticColliders.clear();
	for (auto& obj : m_multipurposeColliders)
		Object::DestroyImmediate(obj);
	m_multipurposeColliders.clear();
	for (auto& navMesh : m_navMeshs)
		SAFE_DELETE(navMesh);
	m_navMeshs.clear();
	SAFE_DELETE(m_pSkybox);
	SAFE_DELETE(m_pGlobalLight);

	EventDispatcher::Cleanup();
}

//void Scene::LoadScene(SerializedScene & scene, const Settings::Window & windowSettings)
//{
//	Load(scene);
//}
void Scene::LoadScene()
{
	// 기본 캠설정 
	// 다른 캠 원한다면 외부에서 AddCamera 해야한다.
	Camera* cam = Camera::Create(this, L"DefaultCamera");
	m_cameras.insert(std::make_pair(L"DefaultCamera", cam));
	m_pSelectedCamera = cam;
	Load();
}

void Scene::UnloadScene()
{
	for (auto& obj : m_meshObjects)
		Object::DestroyImmediate(obj);
	m_meshObjects.clear();
	for (auto& obj : m_textureObjects)
		Object::DestroyImmediate(obj);
	m_textureObjects.clear();
	for (auto& obj : m_invisibleObjects)
		Object::DestroyImmediate(obj);
	m_invisibleObjects.clear();
	for (auto& obj : m_uiObjects)
		Object::DestroyImmediate(obj);
	m_uiObjects.clear();

	//m_lights.clear();
	for (auto& obj : m_dynamicColliders)
		Object::DestroyImmediate(obj);
	m_dynamicColliders.clear();
	for (auto& obj : m_staticColliders)
		Object::DestroyImmediate(obj);
	m_staticColliders.clear();
	for (auto& obj : m_multipurposeColliders)
		Object::DestroyImmediate(obj);
	m_multipurposeColliders.clear();
	for (auto& particle : m_particleSystems)
		delete particle;
	m_particleSystems.clear();
	SAFE_DELETE(m_pSkybox);
	SAFE_DELETE(m_pGlobalLight);

	EventDispatcher::Cleanup();
	Unload();

	TIMER->setTimeScale(1);
}

void Scene::UpdateScene()
{
	// check want destroy
	CheckWantDestroy();

	// camera update 
	m_pSelectedCamera->CameraUpdate();

	if(m_pSkybox)
		m_pSkybox->Update();

	// all component update
	UpdateGameObject();

	// collider update for position
	UpdateCollider();

	// collision calculatio
	CollisionCalculate();

	// update ui
	UpdateUI();
	//UpdateSkybox();

	// update scene
	Update();
	
	// all component late update
	LateUpdateGameObject();
	


	UpdateParticle();




	//  temp code
	/*for (UINT i = 0; i < m_particleSystems.size(); i++)
	{
		if (m_particleSystems[i]->isDead() || m_particleSystems[i]->isEmpty())
		{
			delete m_particleSystems[i];
			m_particleSystems.erase(m_particleSystems.begin() + i);
		}
	}*/

	// removable object remove

	// 여기서 임시로 저장해뒀던 탐색 정보들을 초기화해준다.
	for (auto& meshCache : m_meshObjCache)
		meshCache.second.clear();
	m_meshObjCache.clear();
	for (auto& textureCache : m_textureObjCache)
		textureCache.second.clear();
	m_textureObjCache.clear();
	for (auto& invisibleCache : m_invisibleObjCache)
		invisibleCache.second.clear();
	m_invisibleObjCache.clear();
	for (auto& dynamicCache : m_dynamicColCache)
		dynamicCache.second.clear();
	m_dynamicColCache.clear();
	for (auto& staticCache : m_staticColCache)
		staticCache.second.clear();
	m_staticColCache.clear();
	for (auto& multipurposeCache : m_multipurposeColCache)
		multipurposeCache.second.clear();
	m_multipurposeColCache.clear();

	for (auto& removeFunction : m_removeFunctions)
	{
		removeFunction();
	}
	m_removeFunctions.clear();
}


void Scene::RenderScene(Renderer * renderer)
{
	DEVICE->SetTransform(D3DTS_VIEW, &m_pSelectedCamera->GetViewMatrix());
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_pSelectedCamera->GetProjectionMatrix());
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	renderer->SetAlphaContext();
	RenderSkybox(); // fixed pipeline
	
#ifdef _DEBUG
#ifdef COLLIDER_RENDER
	{
		DWORD fillMode;
		DEVICE->GetRenderState(D3DRS_FILLMODE, &fillMode);
		DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		RenderCollider(); // Fixed Pipeline
		DEVICE->SetRenderState(D3DRS_FILLMODE, fillMode);
	}
#endif
#endif
	renderer->SetOpaqueContext();
	renderer->SetEnableLight();
	RenderMesh();
	//renderer->SetDisableLight();
	renderer->SetAlphaContext();
	RenderTexture();
	//RenderLight(); // Deferred 응용 예정

	RenderParticle();// fixed pipeline
	RenderUI();


}

void HyEngine::Scene::ViewFrustumCull()
{
	m_pSelectedCamera->ViewFrustumCulling(m_meshObjects);
	m_pSelectedCamera->ViewFrustumCulling(m_textureObjects);
}

void HyEngine::Scene::RenderMesh() const
{
	auto& renderableObjects = cpplinq::from_iterators(m_meshObjects.begin(), m_meshObjects.end())
		>> cpplinq::where([&](const GameObject* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->GetViewFrustumCulled() == true)
			return false;

		return true;

	}) >> cpplinq::to_vector();


	for (auto& meshObj : renderableObjects)
	{
			meshObj->Render();
	}
}

void HyEngine::Scene::RenderTexture() const
{
	auto& renderableObjects = cpplinq::from_iterators(m_textureObjects.begin(), m_textureObjects.end())
		>> cpplinq::where([&](const GameObject* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->GetViewFrustumCulled() == true)
			return false;
		return true;

	}) >> cpplinq::to_vector();

	for (auto& textureObj : renderableObjects)
	{
		textureObj->Render();
	}
}

void HyEngine::Scene::RenderCollider() const
{
	auto& renderableDynamic = cpplinq::from_iterators(m_dynamicColliders.begin(), m_dynamicColliders.end())
		>> cpplinq::where([&](const Collider* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->GetGameObject()->GetViewFrustumCulled() == true)
			return false;
		return true;

	}) >> cpplinq::to_vector();

	auto& renderableStatic = cpplinq::from_iterators(m_staticColliders.begin(), m_staticColliders.end())
		>> cpplinq::where([&](const Collider* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->GetGameObject()->GetViewFrustumCulled() == true)
			return false;

		return true;
	}) >> cpplinq::to_vector();

	auto& renderableMultipurpose = cpplinq::from_iterators(m_multipurposeColliders.begin(), m_multipurposeColliders.end())
		>> cpplinq::where([&](const Collider* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->GetGameObject()->GetViewFrustumCulled() == true)
			return false;
		return true;

	}) >> cpplinq::to_vector();

	for (auto& col : renderableDynamic)
	{
			col->Render();
	}
	for (auto& col : renderableStatic)
	{
			col->Render();
	}
	for (auto& col : renderableMultipurpose)
	{
			col->Render();
	}
}

void HyEngine::Scene::RenderUI() 
{

	std::sort(m_uiObjects.begin(), m_uiObjects.end(), [](GameObject*a, GameObject* b)
	{
		return a->GetRenderQueue() > b->GetRenderQueue();
	});
	for (auto& ui : m_uiObjects)
	{
		if (ui->GetActive())
			ui->Render();
	}
}

void HyEngine::Scene::RenderSkybox() const
{
	if(m_pSkybox)
		m_pSkybox->Render();
}

void HyEngine::Scene::RenderParticle() const
{
	for (auto& pSystem : m_particleSystems)
	{
		if (!pSystem->isDead() && !pSystem->isEmpty() && pSystem->GetActive())
			pSystem->Render();
	}
}

void HyEngine::Scene::UpdateGameObject()
{

	for (auto& obj : m_meshObjects)
	{
		if(obj->GetActive() && obj->m_bWantsDestroy == false)
			obj->Update();
	}
	for (auto& obj : m_textureObjects)
	{
		if(obj->GetActive() && obj->m_bWantsDestroy == false)
			obj->Update();
	}
	for (auto& obj : m_invisibleObjects)
	{
		if(obj->GetActive() && obj->m_bWantsDestroy == false)
			obj->Update();
	}


}

void HyEngine::Scene::UpdateUI()
{
	for (auto& ui : m_uiObjects)
	{
		if(ui->GetActive() && ui->m_bWantsDestroy == false)
			ui->Update();
	}
}


void HyEngine::Scene::UpdateCollider()
{
	for (auto& col : m_dynamicColliders)
	{
		if(col->GetActive() && col->m_bWantsDestroy == false)
			col->PositionUpdate();
	}
	for (auto& col : m_staticColliders)
	{
		if(col->GetActive() && col->m_bWantsDestroy == false)
			col->PositionUpdate();
	}
	for (auto& col : m_multipurposeColliders)
	{
		if (col->GetActive() && col->m_bWantsDestroy == false)
			col->PositionUpdate();
	}
}

void HyEngine::Scene::UpdateParticle()
{

	auto& systems = cpplinq::from_iterators(m_particleSystems.begin(), m_particleSystems.end())
		>> cpplinq::where([&](ParticleSystem* sys)
	{
		/*if (sys->isDead())
			return false;
		if (sys->isEmpty())
			return false;*/
		if (sys->GetActive() == false || sys->m_bWantsDestroy == true)
			return false;
		return true;

	}) >> cpplinq::to_vector();
	for (auto& pSystem : systems)
	{
			pSystem->Update();
	}
}

void HyEngine::Scene::LateUpdateGameObject()
{

	for (auto& obj : m_meshObjects)
	{
		if(obj->GetActive() && obj->m_bWantsDestroy == false)
			obj->LateUpdate();
	}
	for (auto& obj : m_textureObjects)
	{
		if(obj->GetActive() && obj->m_bWantsDestroy == false)
			obj->LateUpdate();
	}
	for (auto& obj : m_invisibleObjects)
	{
		if(obj->GetActive() && obj->m_bWantsDestroy == false)
			obj->LateUpdate();
	}
}

void HyEngine::Scene::CheckWantDestroy()
{
	// 일반 반복문에서 DestroyImmediate를 해주면
	// 그 내부 소멸자에서 다른 오브젝트를 Destroy해주게 되고
	// Destroy된 오브젝트는 유예기간 없이 곧바로 삭제되기때문에
	// 외부에서 참조가 발생할 확률이 높아진다.
	// 이를 해결하기 위해 삭제될 오브젝트를 한곳에 모아두고
	// 모든 조건 확인이 끝난 후 한꺼번에 삭제해준다.

	/*auto& meshWantDestroyed = cpplinq::from_iterators(m_meshObjects.begin(), m_meshObjects.end())
		>> cpplinq::where([&](GameObject* obj)
	{
		if (obj->m_bWantsDestroy)
			return true;
		else
			return false;
	}) >> cpplinq::to_vector();
*/
	std::vector<Object*> destroyObjs;
	for (UINT i = 0; i < m_meshObjects.size();)
	{
		if (m_meshObjects[i]->m_bWantsDestroy)
		{
			//Object::DestroyImmediate(m_meshObjects[i]);
			destroyObjs.push_back(m_meshObjects[i]);
			m_meshObjects.erase(m_meshObjects.begin() + i);
		}
		else
			i++;
	}


	for (UINT i = 0; i < m_textureObjects.size();)
	{
		if (m_textureObjects[i]->m_bWantsDestroy)
		{
			//Object::DestroyImmediate(m_textureObjects[i]);
			destroyObjs.push_back(m_textureObjects[i]);
			m_textureObjects.erase(m_textureObjects.begin() + i);
		}
		else
			i++;
	}

	for (UINT i = 0; i < m_invisibleObjects.size(); )
	{
		if (m_invisibleObjects[i]->m_bWantsDestroy)
		{
			//Object::DestroyImmediate(m_invisibleObjects[i]);
			destroyObjs.push_back(m_invisibleObjects[i]);
			m_invisibleObjects.erase(m_invisibleObjects.begin() + i);
		}
		else
			i++;
	}


	for (UINT i = 0; i < m_dynamicColliders.size();)
	{
		if (m_dynamicColliders[i]->m_bWantsDestroy)
		{
			//Object::DestroyImmediate(m_dynamicColliders[i]);
			destroyObjs.push_back(m_dynamicColliders[i]);
			m_dynamicColliders.erase(m_dynamicColliders.begin() + i);
		}
		else
			i++;
	}

	for (UINT i = 0; i < m_staticColliders.size();)
	{
		if (m_staticColliders[i]->m_bWantsDestroy)
		{
			//Object::DestroyImmediate(m_staticColliders[i]);
			destroyObjs.push_back(m_staticColliders[i]);
			m_staticColliders.erase(m_staticColliders.begin() + i);
		}
		else
			i++;
	}
	for (UINT i = 0; i < m_multipurposeColliders.size();)
	{
		if (m_multipurposeColliders[i]->m_bWantsDestroy)
		{
			//Object::DestroyImmediate(m_multipurposeColliders[i]);
			destroyObjs.push_back(m_multipurposeColliders[i]);
			m_multipurposeColliders.erase(m_multipurposeColliders.begin() + i);
		}
		else
			i++;
	}
	for (UINT i = 0; i < m_particleSystems.size();)
	{
		if (m_particleSystems[i]->m_bWantsDestroy)
		{
			//Object::DestroyImmediate(m_particleSystems[i]);
			destroyObjs.push_back(m_particleSystems[i]);
			m_particleSystems.erase(m_particleSystems.begin() + i);
		}
		else
			i++;
	}
	for (auto& obj : destroyObjs)
		Object::DestroyImmediate(obj);
}

void HyEngine::Scene::CollisionCalculate()
{
	auto& dynamicContainer = cpplinq::from_iterators(m_dynamicColliders.begin(), m_dynamicColliders.end())
		>> cpplinq::where([&](const Collider* col)
	{
		if (col->GetActive() == false)
			return false;
		if (col->m_bWantsDestroy == true)
			return false;
		return true;
	}) >> cpplinq::to_vector();
	auto& staticContainer = cpplinq::from_iterators(m_staticColliders.begin(), m_staticColliders.end())
		>> cpplinq::where([&](const Collider* col)
	{
		if (col->GetActive() == false)
			return false;
		if (col->m_bWantsDestroy == true)
			return false;
		return true;
	}) >> cpplinq::to_vector();


	for (auto& col : dynamicContainer)
	{
		auto& dynamicTargets = cpplinq::from_iterators(dynamicContainer.begin(), dynamicContainer.end())
			>> cpplinq::where([&](const Collider* targetCol)
		{
			if (col->GetTargetLayer() & targetCol->GetGameObject()->GetLayer())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		auto& staticTargets = cpplinq::from_iterators(staticContainer.begin(), staticContainer.end())
			>> cpplinq::where([&](const Collider* targetCol)
		{
			if (col->GetTargetLayer() & targetCol->GetGameObject()->GetLayer())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();

		for (auto& dynamicCol : dynamicTargets)
		{
			if (dynamicCol == col) continue;

			col->Calculate(dynamicCol);
		}
		for (auto& staticCol : staticTargets)
		{
			col->Calculate(staticCol);
		}
	}
}

//void Scene::AddOpaqueObject(GameObject * obj)
//{
//	assert(obj->GetRenderType() == ERenderType::RenderOpaque);
//
//#ifdef _DEBUG
//	for (auto& opaqueObj : m_opaqueObjects)
//	{
//		if (opaqueObj == obj)
//			assert(false);
//	}
//#endif
//	
//	m_opaqueObjects.push_back(obj);
//}

//void Scene::AddAlphaObject(GameObject * obj)
//{
//	assert(obj->GetRenderType() == ERenderType::RenderAlpha);
//
//#ifdef _DEBUG
//	for (auto& alphaObject : m_alphaObjects)
//	{
//		if (alphaObject == obj)
//			assert(false);
//	}
//#endif
//
//	m_alphaObjects.push_back(obj);
//}
void HyEngine::Scene::AddMeshObject(GameObject * obj)
{
	assert(obj->GetRenderType() == ERenderType::RenderMesh);

#ifdef _DEBUG
	for (auto& meshObj : m_meshObjects)
	{
		if (meshObj == obj)
			assert(false);
	}
#endif

	m_meshObjects.push_back(obj);
}
void HyEngine::Scene::AddTextureObject(GameObject * obj)
{
	assert(obj->GetRenderType() == ERenderType::RenderTexture);

#ifdef _DEBUG
	for (auto& textureObj : m_textureObjects)
	{
		if (textureObj == obj)
			assert(false);
	}
#endif

	m_textureObjects.push_back(obj);
}

//void HyEngine::Scene::AddAlphaTextureObject(GameObject * obj)
//{
//	assert(obj->GetRenderType() == ERenderType::AlphaTexture);
//
//
//#ifdef _DEBUG
//	for (auto& textureObj : m_alphaTextureObjects)
//	{
//		if (textureObj == obj)
//			assert(false);
//	}
//#endif
//	m_alphaTextureObjects.push_back(obj);
//}

void Scene::AddInvisibleObject(GameObject * obj)
{
	assert(obj->GetRenderType() == ERenderType::None);

#ifdef _DEBUG
	for (auto& invisibleObj : m_invisibleObjects)
	{
		if (invisibleObj == obj)
			assert(false);
	}
#endif

	m_invisibleObjects.push_back(obj);
}
//
//void HyEngine::Scene::AddUserInterface(IUserInterface * ui)
//{
//#ifdef _DEBUG
//	for (auto& uiObj : m_uiObjects)
//	{
//		if (uiObj == ui)
//			assert(false);
//	}
//#endif
//
//	m_uiObjects.push_back(ui);
//}

void HyEngine::Scene::AddUIObject(GameObject * obj)
{
	assert(obj->GetRenderType() == ERenderType::RenderUI);
#ifdef _DEBUG
	for (auto& uiObj : m_uiObjects)
	{
		if (uiObj == obj)
			assert(false);
	}
#endif
	m_uiObjects.push_back(obj);

}

//void HyEngine::Scene::AddLight(int lightIndex, D3DLIGHT9 light)
//{
//	// Don't use
//	assert(false);
//	m_lights.push_back(std::make_pair(lightIndex, light));
//}

void HyEngine::Scene::AddCamera(std::wstring tag, Camera * camera)
{
#ifdef _DEBUG
	for (auto& cam : m_invisibleObjects)
	{
		if (cam->CompareName(tag))
			return;
	}
#endif
	//m_cameras.insert(std::make_pair( tag, camera));
}

void HyEngine::Scene::AddDynamicCollider(Collider * collider)
{
#ifdef _DEBUG
	for (auto& col : m_dynamicColliders)
	{
		if (col == collider)
			assert(false);
	}
#endif
	m_dynamicColliders.push_back(collider);
}

void HyEngine::Scene::AddStaticCollider(Collider * collider)
{
#ifdef _DEBUG
	for (auto& col : m_staticColliders)
	{
		if (col == collider)
			assert(false);
	}
#endif

	m_staticColliders.push_back(collider);
}

void HyEngine::Scene::AddMultipurposeCollider(Collider * collider)
{
#ifdef _DEBUG
	for (auto& col : m_multipurposeColliders)
	{
		if (col == collider)
			assert(false);
	}
#endif

	m_multipurposeColliders.push_back(collider);
}

void HyEngine::Scene::AddParticleSystem(ParticleSystem * particleSystem)
{
#ifdef _DEBUG
	for (auto& pSystem : m_particleSystems)
	{
		if (pSystem == particleSystem)
			assert(false);
	}
#endif
	m_particleSystems.push_back(particleSystem);
}

void HyEngine::Scene::AddNavMesh(NavMesh * navMesh)
{
	m_navMeshs.push_back(navMesh);
}

void HyEngine::Scene::SetPlayer(std::wstring playerName)
{
	m_pPlayer = GetGameObject(playerName);
}

void HyEngine::Scene::SetSkybox(Skybox * skybox)
{
	m_pSkybox = skybox;
}


void HyEngine::Scene::SetGlobalLight(Light * light)
{
	// global light must be directional light
	assert(light->Type() == ELightType::DIRECTIONAL);
	m_pGlobalLight = light;
}

bool HyEngine::Scene::SelectCamera(std::wstring tag)
{
	for (auto& obj : m_invisibleObjects)
	{
		if (obj->CompareName(tag))
		{
			m_pSelectedCamera = dynamic_cast<Camera*>(obj);
			return true;
		}
	}
	return false;
	/*auto& cam = m_cameras.find(tag);
	if (cam == m_cameras.end())
		return false;
	else
	{
		m_pSelectedCamera = cam->second;
		return true;
	}*/
}

GameObject * HyEngine::Scene::GetGameObject(std::wstring name)
{
	/*for (auto& obj : m_opaqueObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	for (auto& obj : m_alphaObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}*/
	for (auto& obj : m_meshObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	for (auto& obj : m_textureObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	for (auto& obj : m_invisibleObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	return nullptr;
}
//
//GameObject * HyEngine::Scene::GetOpaqueObject(std::wstring name)
//{
//	for (auto& obj : m_opaqueObjects)
//	{
//		if (obj->CompareName(name))
//			return obj;
//	}
//	return nullptr;
//}
//
//GameObject * HyEngine::Scene::GetAlphaObject(std::wstring name)
//{
//	for (auto& obj : m_alphaObjects)
//	{
//		if (obj->CompareName(name))
//			return obj;
//	}
//	return nullptr;
//}
GameObject * HyEngine::Scene::GetMeshObject(std::wstring name)
{
	for (auto& obj : m_meshObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	return nullptr;
}
std::vector<class GameObject*>& HyEngine::Scene::GetMeshObjectAll()
{
	return m_meshObjects;
}
GameObject * HyEngine::Scene::GetTextureObject(std::wstring name)
{
	for (auto& obj : m_textureObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	return nullptr;
}

std::vector<class GameObject*>& HyEngine::Scene::GetTextureObjectAll()
{
	return m_textureObjects;
}

std::vector<GameObject*>& HyEngine::Scene::GetTextureObjectAll(UINT layer)
{
	auto& iter = m_textureObjCache.find(layer);
	if (m_textureObjCache.end() == iter)
	{
		auto& result = cpplinq::from_iterators(this->m_textureObjects.begin(), this->m_textureObjects.end())
			>> cpplinq::where([&](GameObject* obj)
		{
			if (obj->GetLayer() & layer && obj->GetActive())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_textureObjCache.insert(std::make_pair(layer, result));
		return m_textureObjCache[layer];
	}
	else
		return iter->second;
}

//GameObject * HyEngine::Scene::GetAlphaTextureObject(std::wstring name)
//{
//	for (auto& obj : m_alphaTextureObjects)
//	{
//		if (obj->CompareName(name))
//			return obj;
//	}
//	return nullptr;
//}

GameObject * HyEngine::Scene::GetInvisibleObject(std::wstring name)
{
	for (auto& obj : m_invisibleObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	return nullptr;
}

std::vector<class GameObject*>& HyEngine::Scene::GetInvisibleObjectAll()
{
	return m_invisibleObjects;
}

std::vector<class GameObject*>& HyEngine::Scene::GetInvisibleObjectAll(UINT layer)
{
	auto& iter = m_invisibleObjCache.find(layer);
	if (m_invisibleObjCache.end() == iter)
	{
		auto& result = cpplinq::from_iterators(this->m_invisibleObjects.begin(), this->m_invisibleObjects.end())
			>> cpplinq::where([&](GameObject* obj)
		{
			if (obj->GetLayer() & layer && obj->GetActive())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_invisibleObjCache.insert(std::make_pair(layer, result));
		return m_invisibleObjCache[layer];
	}
	else
		return iter->second;
}

std::vector<GameObject*> HyEngine::Scene::GetMeshObjectAll(std::function<bool(GameObject*)> condition)
{
	std::vector<GameObject*> result = cpplinq::from_iterators(this->m_meshObjects.begin(), m_meshObjects.end())
		>> cpplinq::where([=](GameObject* obj)
	{
		if (condition(obj))
		{
			return true;
		}
		else
			return false;
	})>>cpplinq::to_vector();

	return result;
}

std::vector<class Collider*>& HyEngine::Scene::GetDynamicColliderAll()
{
	/*return cpplinq::from_iterators(this->m_dynamicColliders.begin(), this->m_dynamicColliders.end())
		>> cpplinq::where([&](Collider* objPtr)
	{
		if ( objPtr->GetActive())
			return true;
		else
			return false;
	}) >> cpplinq::to_vector();*/
	return m_dynamicColliders;
}

std::vector<class Collider*>& HyEngine::Scene::GetStaticColliderAll()
{
	/*return cpplinq::from_iterators(this->m_staticColliders.begin(), this->m_staticColliders.end())
		>> cpplinq::where([&](Collider* objPtr)
	{
		if (objPtr->GetActive())
			return true;
		else
			return false;
	}) >> cpplinq::to_vector();*/
	return m_staticColliders;
}

std::vector<class Collider*>& HyEngine::Scene::GetMultipurposeColliderAll()
{
	/*return cpplinq::from_iterators(this->m_multipurposeColliders.begin(), this->m_multipurposeColliders.end())
		>> cpplinq::where([&](Collider* objPtr)
	{
		if (objPtr->GetActive())
			return true;
		else
			return false;
	}) >> cpplinq::to_vector();*/
	return m_multipurposeColliders;
}

std::vector<class Collider*> HyEngine::Scene::GetDynamicColliderAll(UINT layer)
{
	auto& iter = m_dynamicColCache.find(layer);
	if (m_dynamicColCache.end() == iter)
	{
		auto& result = cpplinq::from_iterators(this->m_dynamicColliders.begin(), this->m_dynamicColliders.end())
			>> cpplinq::where([&](Collider* objPtr)
		{
			if (objPtr->GetGameObject()->GetLayer() & layer && objPtr->GetActive() && objPtr->m_bWantsDestroy == false)
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_dynamicColCache.insert(std::make_pair(layer, result));
		return m_dynamicColCache[layer];
	}
	else
		return iter->second;
}

std::vector<class Collider*> HyEngine::Scene::GetStaticColliderAll(UINT layer)
{
	auto& iter = m_staticColCache.find(layer);
	if (m_staticColCache.end() == iter)
	{
		auto& result = cpplinq::from_iterators(this->m_staticColliders.begin(), this->m_staticColliders.end())
			>> cpplinq::where([&](Collider* objPtr)
		{
			if (objPtr->GetGameObject()->GetLayer() & layer && objPtr->GetActive() && objPtr->m_bWantsDestroy == false)
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_staticColCache.insert(std::make_pair(layer, result));
		return m_staticColCache[layer];
	}
	else
		return iter->second;
	/*return cpplinq::from_iterators(this->m_staticColliders.begin(), this->m_staticColliders.end())
		>> cpplinq::where([&](Collider* objPtr)
	{
		if (objPtr->GetGameObject()->GetLayer() & layer && objPtr->GetActive())
			return true;
		else
			return false;
	}) >> cpplinq::to_vector();*/
}

std::vector<class Collider*> HyEngine::Scene::GetMultipurposeColliderAll(UINT layer)
{
	auto& iter = m_multipurposeColCache.find(layer);
	if (m_multipurposeColCache.end() == iter)
	{
		auto& result = cpplinq::from_iterators(this->m_multipurposeColliders.begin(), this->m_multipurposeColliders.end())
			>> cpplinq::where([&](Collider* objPtr)
		{
			if (objPtr->GetGameObject()->GetLayer() & layer && objPtr->GetActive() && objPtr->m_bWantsDestroy == false)
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_multipurposeColCache.insert(std::make_pair(layer, result));
		return m_multipurposeColCache[layer];
	}
	else
		return iter->second;
/*
	return cpplinq::from_iterators(this->m_multipurposeColliders.begin(), this->m_multipurposeColliders.end())
		>> cpplinq::where([&](Collider* objPtr)
	{
		if (objPtr->GetGameObject()->GetLayer() & layer && objPtr->GetActive())
			return true;
		else
			return false;
	}) >> cpplinq::to_vector();*/
}

NavMesh * HyEngine::Scene::GetNavMesh(int index)
{
	assert(index < m_navMeshs.size());
	assert(index >= 0);
	return m_navMeshs[index];
}

const std::vector<class NavMesh*> HyEngine::Scene::GetNavMeshAll()
{
	return m_navMeshs;
}

std::vector<GameObject*>& HyEngine::Scene::GetMeshObjectAll(UINT layer)
{
	auto& iter = m_meshObjCache.find(layer);
	if (m_meshObjCache.end() == iter)
	{
		auto& result = cpplinq::from_iterators(m_meshObjects.begin(), m_meshObjects.end())
			>> cpplinq::where([&](GameObject* obj)
		{
			if (obj->GetLayer() & layer && obj->GetActive())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		m_meshObjCache.insert(std::make_pair(layer, result));
		return m_meshObjCache[layer];
	}
	else
		iter->second;

	//std::vector<GameObject*> objVec;
	//for (auto& obj : m_meshObjects)
	//{
	//	if (obj->GetLayer() & layer)
	//	{
	//		objVec.emplace_back(obj);
	//	}
	//}
	//return objVec;
}

GameObject * HyEngine::Scene::GetUIObject(std::wstring name)
{
	for (auto& obj : m_uiObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	return nullptr;
}

GameObject * HyEngine::Scene::GetPlayer()
{
	assert(m_pPlayer != nullptr);
	return m_pPlayer;
}

Skybox * HyEngine::Scene::GetSkybox()
{
	return m_pSkybox;
}

Camera * HyEngine::Scene::GetSelectedCamera() const
{
	return m_pSelectedCamera;
}

Light * HyEngine::Scene::GetGlobalLight() const
{
	return m_pGlobalLight;
}


