#pragma once
#include "IUserInterface.h"
#include "ISkybox.h"
#include "ILight.h"
#include "Object.h"
#include "GameObject.h"


namespace HyEngine
{

	class GameObject;
	class Camera;
	class ENGINE_DLL Scene
	{
		friend class Object;
		friend class GameObject;

	protected:
		virtual void Update() = 0;

		// LOAD / UNLOAD
		virtual void Load() = 0;
		virtual void Unload() = 0;
		
	

	public:
		// LoadAsync 함수는 thread에서 들어온다.
		// 콜백 함수는 자원을 로드할 때마다 호출해줘야하며
		// 인자는 로드한 리소스 수, 로드해야하는 리소스 총량 
		virtual void LoadAsync(std::function<void(int, int)> onProgress) = 0;
		/*
			Scene에서 UI, Light, Skybox를 그린다.
			Engine에서 Debug를 그린다.
			GameObject에서 각종 오브젝트를 그린다.
		*/

	
	private :

		// Scene을 상속받은 Scene클래스에선
		// UI, Light, Skybox를 Add 해주기만 하면
		// 알아서 동작한다.
		//void RenderOpaqueMesh(class Renderer* renderer) const;
		//void RenderAlphaMesh(class Renderer* renderer) const;
		void RenderMesh() const;
		//void RenderTexture(class Renderer* renderer) const;
		//void RenderAlphaTexture(class Renderer* renderer) const;
		void RenderTexture() const;
		//void RenderCollider(class Renderer* renderer) const;
		void RenderCollider() const;
		//void RenderUI(class Renderer* renderer) const;
		void RenderUI() ;
		//void RenderSkybox(class Renderer* renderer) const ;
		void RenderSkybox() const;
		//void RenderParticle() const;
		void RenderParticle() const;

		void UpdateGameObject();
		void UpdateUI();
		void UpdateCollider();
		void UpdateParticle();

		void LateUpdateGameObject();

		void CheckWantDestroy();

		void CollisionCalculate();

	public:
		explicit Scene();
		virtual ~Scene();

		/*
			CORE INTERFACE
		*/
		void LoadScene();
		void UnloadScene();
		virtual void LateLoadScene() {}
		void UpdateScene();
		void RenderScene(class Renderer * renderer);

		void ViewFrustumCull();
		/*
			Object Setter
		*/

		//void AddOpaqueObject(class GameObject* obj);
		//void AddAlphaObject(class GameObject* obj);
		void AddMeshObject(class GameObject* obj);
		void AddTextureObject(class GameObject* obj);
		//void AddAlphaTextureObject(class GameObject* obj);
		void AddInvisibleObject(class GameObject* obj);
		//void AddUserInterface(class IUserInterface* ui);
		void AddUIObject(class GameObject* obj);
		//void AddLight(int lightIndex, D3DLIGHT9 light);
		void AddCamera(std::wstring tag, class Camera* camera);
		void AddDynamicCollider(class Collider* collider);
		void AddStaticCollider(class Collider* collider);
		void AddMultipurposeCollider(class Collider* collider);
		void AddParticleSystem(class ParticleSystem* particleSystem);
		void SetPlayer(std::wstring playerName);
		void SetSkybox(class Skybox* skybox);
		void SetGlobalLight(class Light* light);
		
		bool SelectCamera(std::wstring name);

		/*
		 해당 오브젝트가 어떤 종류에 속할 지 모를 떄 
		 전체적으로 검색합니다.
		 전체를 검사하는 만큼 속도가 느려질 수 있으니
		 가능하면 GetOpaqueObject, GetAlphgaObject 등 다른 함수를
		 사용해야합니다.
		*/
		GameObject* GetGameObject(std::wstring name);
		GameObject * GetMeshObject(std::wstring name);
		std::vector<class GameObject*>& GetMeshObjectAll();
		// 잦은 호출의 경우 layer를 통한 탐색을 권장합니다.
		std::vector<GameObject*>& GetMeshObjectAll(UINT layer);
		std::vector<GameObject*> GetMeshObjectAll(std::function<bool(GameObject*)> condition);
		GameObject* GetTextureObject(std::wstring name);
		std::vector<class GameObject*>& GetTextureObjectAll();
		std::vector<GameObject*>& GetTextureObjectAll(UINT layer);
		GameObject* GetInvisibleObject(std::wstring name);
		std::vector<class GameObject*>& GetInvisibleObjectAll();
		std::vector<class GameObject*>& GetInvisibleObjectAll(UINT layer);

		std::vector<class Collider*>& GetDynamicColliderAll();
		std::vector<class Collider*>& GetStaticColliderAll();
		std::vector<class Collider*>& GetMultipurposeColliderAll();
		std::vector<class Collider*> GetDynamicColliderAll(UINT layer);
		std::vector<class Collider*> GetStaticColliderAll(UINT layer);
		std::vector<class Collider*> GetMultipurposeColliderAll(UINT layer);
	


		GameObject* GetUIObject(std::wstring name);
		GameObject* GetPlayer();
		Skybox* GetSkybox();
		Camera* GetSelectedCamera() const;

		class Light* GetGlobalLight() const;
	private:
		// TODO : 



		// 각각의 Cache들을 통해 
		// 한 프레임에 여러곳에서 탐색을 요구했을 때 
		// 한번의 검색으로 모두 원하는 값을 참조값으로 받을 수 있게 한다.
		// 단 Layer를 통한 탐색이여야한다.

		// Visible Objects
		// only mesh
		std::vector<GameObject* > m_meshObjects;
		std::unordered_map<UINT, std::vector<GameObject*>> m_meshObjCache;

		// only texture
		std::vector<GameObject*> m_textureObjects;
		std::unordered_map<UINT, std::vector<GameObject*>> m_textureObjCache;

		// Invisible Objects
		std::vector<GameObject* > m_invisibleObjects;
		std::unordered_map<UINT, std::vector<GameObject*>> m_invisibleObjCache;
		// UI Objects
		//std::vector<IUserInterface*> m_uiObjects;
		std::vector<class GameObject*> m_uiObjects;
		std::unordered_map<UINT, std::vector<GameObject*>> m_uiObjCache;
		// lights
		//std::vector<std::pair<int, D3DLIGHT9>> m_lights;
		// cameras
		std::unordered_map<std::wstring, class Camera*> m_cameras;
		Camera* m_pSelectedCamera;
		// colliders
		std::vector<class Collider*> m_dynamicColliders;
		std::unordered_map<UINT, std::vector<Collider*>> m_dynamicColCache;
		std::vector<class Collider*> m_staticColliders;
		std::unordered_map<UINT, std::vector<Collider*>> m_staticColCache;
		std::vector<class Collider*> m_multipurposeColliders;
		std::unordered_map<UINT, std::vector<Collider*>> m_multipurposeColCache;
		std::vector<class ParticleSystem* > m_particleSystems;
		class Skybox* m_pSkybox;
		GameObject* m_pPlayer = nullptr;

		class Light* m_pGlobalLight;



		/*
			삭제 로직을 담는 함수.
			Update돌아가는 도중 삭제할 수 없기 때문에
			임시로 m_removeFunctions에 담아
			모든 Update, LateUpdate를 끝마친 후 모든 제거함수를 호출해준다.
		*/
		std::vector<std::function<void()>> m_removeFunctions;


	};

}