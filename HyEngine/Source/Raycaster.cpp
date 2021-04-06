#include "StandardEngineFramework.h"
#include "Raycaster.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "ObjectContainer.h"

bool HyEngine::Raycaster::Raycast(D3DXVECTOR3 origin, D3DXVECTOR3 direction, RaycastHit *& result)
{
	Scene* currentScene = SCENE;
	assert(currentScene != nullptr);

	Ray ray;
	ray.origin = origin;
	ray.direction = direction;
	result = nullptr;

	std::vector<Collider*>& dynamicColliders = currentScene->GetObjectContainer()->GetDynamicColliderAll();
	std::vector<Collider*>& staticColliders = currentScene->GetObjectContainer()->GetStaticColliderAll();
	std::vector<Collider*>& multipurposeColliders = currentScene->GetObjectContainer()->GetMultipurposeColliderAll();

	auto& dynamics = cpplinq::from_iterators(dynamicColliders.begin(), dynamicColliders.end())
		>> cpplinq::where([&](const Collider* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->m_bWantsDestroy == true)
			return false;
		return true;
	}) >> cpplinq::to_vector();


	auto& statics = cpplinq::from_iterators(staticColliders.begin(), staticColliders.end())
		>> cpplinq::where([&](const Collider* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->m_bWantsDestroy == true)
			return false;
		return true;
	}) >> cpplinq::to_vector();

	auto& multi = cpplinq::from_iterators(multipurposeColliders.begin(), multipurposeColliders.end())
		>> cpplinq::where([&](const Collider* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->m_bWantsDestroy == true)
			return false;
		return true;
	}) >> cpplinq::to_vector();

	bool isSucceeded = false;
	for (auto& col : dynamics)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}
	for (auto& col : statics)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}
	for (auto& col : multi)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}

	return false;
}

bool HyEngine::Raycaster::Raycast(Ray ray, RaycastHit *& result)
{
	Scene* currentScene = ENGINE->GetActiveScene();
	assert(currentScene != nullptr);

	result = nullptr;

	std::vector<Collider*>& dynamicColliders = currentScene->GetObjectContainer()->GetDynamicColliderAll();
	std::vector<Collider*>& staticColliders = currentScene->GetObjectContainer()->GetStaticColliderAll();
	std::vector<Collider*>& multipurposeColliders = currentScene->GetObjectContainer()->GetMultipurposeColliderAll();

	auto& dynamics = cpplinq::from_iterators(dynamicColliders.begin(), dynamicColliders.end())
		>> cpplinq::where([&](const Collider* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->m_bWantsDestroy == true)
			return false;
		return true;
	}) >> cpplinq::to_vector();


	auto& statics = cpplinq::from_iterators(staticColliders.begin(), staticColliders.end())
		>> cpplinq::where([&](const Collider* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->m_bWantsDestroy == true)
			return false;
		return true;
	}) >> cpplinq::to_vector();

	auto& multi = cpplinq::from_iterators(multipurposeColliders.begin(), multipurposeColliders.end())
		>> cpplinq::where([&](const Collider* obj)
	{
		if (obj->GetActive() == false)
			return false;
		if (obj->m_bWantsDestroy == true)
			return false;
		return true;
	}) >> cpplinq::to_vector();

	bool isSucceeded = false;
	for (auto& col : dynamics)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}
	for (auto& col : statics)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}
	for (auto& col : multi)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}

	return false;
}

bool HyEngine::Raycaster::Raycast(D3DXVECTOR3 origin, D3DXVECTOR3 direction, UINT layer, RaycastHit *& result)
{
	Scene* currentScene = SCENE;
	assert(currentScene != nullptr);

	Ray ray;
	ray.origin = origin;
	ray.direction = direction;
	result = nullptr;

	std::vector<Collider*> dynamicColliders = currentScene->GetObjectContainer()->GetDynamicColliderAll(layer);
	std::vector<Collider*> staticColliders = currentScene->GetObjectContainer()->GetStaticColliderAll(layer);
	std::vector<Collider*> multipurposeColliders = currentScene->GetObjectContainer()->GetMultipurposeColliderAll(layer);

	bool isSucceeded = false;
	for (auto& col : dynamicColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}
	for (auto& col : staticColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}
	for (auto& col : multipurposeColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}

	return false;
}

bool HyEngine::Raycaster::Raycast(Ray ray, UINT layer, RaycastHit *& result)
{
	Scene* currentScene = ENGINE->GetActiveScene();
	assert(currentScene != nullptr);

	result = nullptr;

	std::vector<Collider*> dynamicColliders = currentScene->GetObjectContainer()->GetDynamicColliderAll(layer);
	std::vector<Collider*> staticColliders = currentScene->GetObjectContainer()->GetStaticColliderAll(layer);
	std::vector<Collider*> multipurposeColliders = currentScene->GetObjectContainer()->GetMultipurposeColliderAll(layer);

	bool isSucceeded = false;
	for (auto& col : dynamicColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}
	for (auto& col : staticColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}
	for (auto& col : multipurposeColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}

	return false;
}

bool HyEngine::Raycaster::Raycast(D3DXVECTOR3 origin, D3DXVECTOR3 direction, UINT layer, EColliderType colliderType, RaycastHit *& result)
{
	Scene* currentScene = SCENE;
	assert(currentScene != nullptr);

	Ray ray;
	ray.origin = origin;
	ray.direction = direction;
	result = nullptr;
	std::vector<Collider*> colliders;
	switch (colliderType)
	{
	case EColliderType::Static:
		colliders = currentScene->GetObjectContainer()->GetStaticColliderAll(layer);
		break;
	case EColliderType::Dynamic:
		colliders = currentScene->GetObjectContainer()->GetDynamicColliderAll(layer);
		break;
	case EColliderType::Multipurpose:
		colliders = currentScene->GetObjectContainer()->GetMultipurposeColliderAll(layer);
		break;
	default:
		assert(false);
		break;
	}
	bool isSucceeded = false;
	for (auto& col : colliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}

	return false;
}

bool HyEngine::Raycaster::Raycast(Ray ray, UINT layer, EColliderType colliderType, RaycastHit *& result)
{
	Scene* currentScene = ENGINE->GetActiveScene();
	assert(currentScene != nullptr);

	result = nullptr;

	std::vector<Collider*> colliders;
	switch (colliderType)
	{
	case EColliderType::Static:
		colliders = currentScene->GetObjectContainer()->GetStaticColliderAll(layer);
		break;
	case EColliderType::Dynamic:
		colliders = currentScene->GetObjectContainer()->GetDynamicColliderAll(layer);
		break;
	case EColliderType::Multipurpose:
		colliders = currentScene->GetObjectContainer()->GetMultipurposeColliderAll(layer);
		break;
	default:
		assert(false);
		break;
	}
	bool isSucceeded = false;
	for (auto& col : colliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			result = new RaycastHit(col);
			return true;
		}
	}

	return false;
}

std::vector<RaycastHit*> HyEngine::Raycaster::RaycastHitAll(D3DXVECTOR3 origin, D3DXVECTOR3 direction)
{
	Scene* currentScene = SCENE;
	assert(currentScene != nullptr);

	Ray ray;
	ray.origin = origin;
	ray.direction = direction;
	//result = nullptr;
	std::vector<RaycastHit*> results;

	std::vector<Collider*>& dynamicColliders = currentScene->GetObjectContainer()->GetDynamicColliderAll();
	std::vector<Collider*>& staticColliders = currentScene->GetObjectContainer()->GetStaticColliderAll();
	std::vector<Collider*>& multipurposeColliders = currentScene->GetObjectContainer()->GetMultipurposeColliderAll();


	bool isSucceeded = false;
	for (auto& col : dynamicColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			results.emplace_back(new RaycastHit(col));
		}
		
	}
	for (auto& col : staticColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			results.emplace_back(new RaycastHit(col));
		//	return true;
		}
	}
	for (auto& col : multipurposeColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			results.emplace_back(new RaycastHit(col));
			//	return true;
		}
	}
	return results;
}

std::vector<RaycastHit*> HyEngine::Raycaster::RaycastHitAll(Ray ray)
{
	return RaycastHitAll(ray.origin, ray.direction);
}

std::vector<RaycastHit*> HyEngine::Raycaster::RaycastHitAll(D3DXVECTOR3 origin, D3DXVECTOR3 direction, UINT layer)
{
	Scene* currentScene = SCENE;
	assert(currentScene != nullptr);

	Ray ray;
	ray.origin = origin;
	ray.direction = direction;
	//result = nullptr;
	std::vector<RaycastHit*> results;

	std::vector<Collider*> dynamicColliders = currentScene->GetObjectContainer()->GetDynamicColliderAll(layer);
	std::vector<Collider*> staticColliders = currentScene->GetObjectContainer()->GetStaticColliderAll(layer);
	std::vector<Collider*> multipurposeColliders = currentScene->GetObjectContainer()->GetMultipurposeColliderAll(layer);


	bool isSucceeded = false;
	for (auto& col : dynamicColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			results.emplace_back(new RaycastHit(col));
		}

	}
	for (auto& col : staticColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			results.emplace_back(new RaycastHit(col));
			//	return true;
		}
	}
	for (auto& col : multipurposeColliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			results.emplace_back(new RaycastHit(col));
			//	return true;
		}
	}
	return results;
}

std::vector<RaycastHit*> HyEngine::Raycaster::RaycastHitAll(Ray ray, UINT layer)
{
	return RaycastHitAll(ray.origin, ray.direction, layer);
}

std::vector<RaycastHit*> HyEngine::Raycaster::RaycastHitAll(D3DXVECTOR3 origin, D3DXVECTOR3 direction, UINT layer, EColliderType colliderType)
{
	Scene* currentScene = SCENE;
	assert(currentScene != nullptr);

	Ray ray;
	ray.origin = origin;
	ray.direction = direction;
	//result = nullptr;
	std::vector<RaycastHit*> results;

	std::vector<Collider*> colliders;
	switch (colliderType)
	{
	case EColliderType::Static:
		colliders = currentScene->GetObjectContainer()->GetStaticColliderAll(layer);
		break;
	case EColliderType::Dynamic:
		colliders = currentScene->GetObjectContainer()->GetDynamicColliderAll(layer);
		break;
	case EColliderType::Multipurpose:
		colliders = currentScene->GetObjectContainer()->GetMultipurposeColliderAll(layer);
		break;
	default:
		assert(false);
		break;
	}

	bool isSucceeded = false;
	for (auto& col : colliders)
	{
		isSucceeded = CollisionCalculate(ray, col);
		if (isSucceeded)
		{
			results.emplace_back(new RaycastHit(col));
		}

	}

	return results;
}

std::vector<RaycastHit*> HyEngine::Raycaster::RaycastHitAll(Ray ray, UINT layer, EColliderType colliderType)
{
	return RaycastHitAll(ray.origin, ray.direction, layer, colliderType);
}

bool HyEngine::Raycaster::CollisionCalculate(Ray ray, Collider * collider)
{
	switch (collider->GetColliderShape())
	{
	case EColliderShape::Sphere:
		return CalcToSphere(ray, dynamic_cast<SphereCollider*>(collider));
	}
	// 예외 
	assert(false);
	return false;
}

bool HyEngine::Raycaster::CalcToSphere(Ray ray, SphereCollider * sphere)
{
	D3DXMATRIX worldMatInv;
	D3DXVECTOR3 q, v;
	float qq, vv, rr, qv; 
	
	D3DXMatrixInverse(&worldMatInv, NULL, &sphere->GetTransform()->GetWorldMatrix()); // 구의 역행렬
	D3DXVec3TransformCoord(&q, &ray.origin, &worldMatInv); // 반직선을 구공간으로 옮긴다.
	D3DXVec3TransformNormal(&v, &ray.direction, &worldMatInv); // 반직선을 구공간으로 옮긴다.

	qq = D3DXVec3Dot(&q, &q);
	vv = D3DXVec3Dot(&v, &v);
	qv = D3DXVec3Dot(&q, &v);
	rr = (float)sphere->GetRadius() * sphere->GetRadius();

	return qv * qv - vv * (qq - rr) >= 0;
	
}
