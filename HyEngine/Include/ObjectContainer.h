#pragma once

namespace HyEngine
{
	class GameObject;
	class Collider;
	class Camera;
	class NavMesh;
	class Light;
	class Skybox;
	class ENGINE_DLL ObjectContainer
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	public:
		ObjectContainer();
		~ObjectContainer();

	public:
		void SeperateContainers();

	public:
		void ClearGarbage();
		void ClearAll();
		void ClearCache();


		//////////////////////////////////////////////////////////////////////////
		// ADD
		//////////////////////////////////////////////////////////////////////////
	public: /* For Game Object */
		void AddOpaqueObject(GameObject* obj);
		void AddAlphaObject(GameObject* obj);
		void AddInvisibleObject(GameObject* obj);

	public: /* For Collider */
		void AddDynamicCollider(Collider* col);
		void AddStaticCollider(Collider* col);
		void AddMultipurposeCollider(Collider* col);

	public: /* ETC */
		void AddLight(Light* light);

		//////////////////////////////////////////////////////////////////////////
		// SETTER
		//////////////////////////////////////////////////////////////////////////
	public:
		void SetSkybox(Skybox* skybox);

		//////////////////////////////////////////////////////////////////////////
		// GETTER
		//////////////////////////////////////////////////////////////////////////
	public: /* Getter for single object */
		bool TryGetGameObject(std::wstring name, _Out_ GameObject** outObj);
		bool TryGetOpaqueObject(std::wstring name, _Out_ GameObject** outObj);
		bool TryGetAlphaObject(std::wstring name, _Out_ GameObject** outObj);
		bool TryGetInvisibleObject(std::wstring name, _Out_ GameObject** outObj);


		Skybox* GetSkybox() const;

	public: /* Getter for all objects */
		std::vector<GameObject*> GetGameObjectAll();
		std::vector<GameObject*>& GetOpaqueObjectAll();
		std::vector<GameObject*> GetRenderableOpaqueAll();
		std::vector<GameObject*>& GetAlphaObjectAll();
		std::vector<GameObject*> GetRenderableAlphaAll();
		std::vector<GameObject*>& GetInvisibleObjectAll();

		std::vector<Collider*> GetRenderableColliderAll();
		std::vector<Collider*>& GetDynamicColliderAll();
		std::vector<Collider*>& GetStaticColliderAll();
		std::vector<Collider*>& GetMultipurposeColliderAll();

		std::vector<Light*>& GetLightAll();
		std::vector<Light*> GetRenderableLightAll();

	public : /* Getter for Seperated Object */
		std::vector<GameObject*>& GetStaticMeshAll();
		std::vector<GameObject*>& GetDynamicMeshAll();
		std::vector<GameObject*>& GetUIElementAll();
		std::vector<GameObject*>& GetEffectAll();

	public: /* Getter for all objects within layer */
		std::vector<GameObject*>& GetOpaqueObjectAll(UINT layer);
		std::vector<GameObject*>& GetAlphaObjectAll(UINT layer);
		std::vector<GameObject*>& GetInvisibleObjectAll(UINT layer);

		std::vector<Collider*>& GetDynamicColliderAll(UINT layer);
		std::vector<Collider*>& GetStaticColliderAll(UINT layer);
		std::vector<Collider*>& GetMultipurposeColliderAll(UINT layer);

	private :
		

		//////////////////////////////////////////////////////////////////////////
		// OBJECT CONTAINERS
		//////////////////////////////////////////////////////////////////////////
	private:
		/* Opaque was rendered Diferred pipeline with light */
		std::vector<GameObject*> m_opaqueObjects;
		/* Alpha was rendered forward pipeline without light */
		std::vector<GameObject*> m_alphaObjects;
		/* Invisible is not rendered */
		std::vector<GameObject*> m_invisibleObjects;

	private: /* For Collider */
		std::vector<Collider*> m_dynamicColliders;
		std::vector<Collider*> m_staticColliders;
		std::vector<Collider*> m_multipurposeColliders;

	private: /* Particles */

	private: /* ETC */
		std::unordered_map<std::wstring, Camera*> m_cameras;
		std::vector<Light*> m_lights;
		Skybox* m_pSkybox;

		// StaticMesh
		// DynamicMesh
	private :
		/* Seperated Objects */
		std::vector<GameObject*> m_staticMeshes;
		std::vector<GameObject*> m_dynamicMeshes;
		std::vector<GameObject*> m_uiElements;
		std::vector<GameObject*> m_effects;

		// 오브젝트 내역이 변경되었을 때(ex 오브젝트 생성, 삭제)
		bool m_bDirtyFlag = false;
		bool m_bObjectDestroyed = false;

	private: /* For Cache */
		std::unordered_map<UINT, std::vector<GameObject*>> m_opaqueCache;
		std::unordered_map<UINT, std::vector<GameObject*>> m_alphaCache;
		std::unordered_map<UINT, std::vector<GameObject*>> m_invisibleCache;

		std::unordered_map<UINT, std::vector<Collider*>> m_dynamicCache;
		std::unordered_map<UINT, std::vector<Collider*>> m_staticCache;
		std::unordered_map<UINT, std::vector<Collider*>> m_multipurposeCache;

	};
}