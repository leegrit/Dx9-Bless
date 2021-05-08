#pragma once
#include "Ray.h"
#include "RaycastHit.h"


namespace HyEngine
{
	class ENGINE_DLL Raycaster
	{
	public :
		// TODO : layer mask 추가하기
		bool Raycast(D3DXVECTOR3 origin, D3DXVECTOR3 direction, _Out_ RaycastHit*& result);
		bool Raycast(Ray ray, _Out_ RaycastHit*& result);
		bool Raycast(D3DXVECTOR3 origin, D3DXVECTOR3 direction, UINT layer, _Out_ RaycastHit*& result);
		bool Raycast(Ray ray, UINT layer, _Out_ RaycastHit*& result);
		bool Raycast(D3DXVECTOR3 origin, D3DXVECTOR3 direction, UINT layer, EColliderType colliderType, _Out_ RaycastHit*& result);
		bool Raycast(Ray ray, UINT layer, EColliderType colliderType, _Out_ RaycastHit*& result);
		std::vector<RaycastHit*> RaycastHitAll(D3DXVECTOR3 origin, D3DXVECTOR3 direction);
		std::vector<RaycastHit*> RaycastHitAll(Ray ray);
		std::vector<RaycastHit*> RaycastHitAll(D3DXVECTOR3 origin, D3DXVECTOR3 direction, UINT layer);
		std::vector<RaycastHit*> RaycastHitAll(Ray ray, UINT layer);
		std::vector<RaycastHit*> RaycastHitAll(D3DXVECTOR3 origin, D3DXVECTOR3 direction, UINT layer, EColliderType colliderType);
		std::vector<RaycastHit*> RaycastHitAll(Ray ray, UINT layer, EColliderType colliderType);

	private :
		bool CollisionCalculate(Ray ray, class Collider* collider);
		bool CalcToSphere(Ray ray, class SphereCollider* sphere);
	};
}
