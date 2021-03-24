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
		// LoadAsync �Լ��� thread���� ���´�.
		// �ݹ� �Լ��� �ڿ��� �ε��� ������ ȣ��������ϸ�
		// ���ڴ� �ε��� ���ҽ� ��, �ε��ؾ��ϴ� ���ҽ� �ѷ� 
		virtual void LoadAsync(std::function<void(int, int)> onProgress) = 0;
		/*
			Scene���� UI, Light, Skybox�� �׸���.
			Engine���� Debug�� �׸���.
			GameObject���� ���� ������Ʈ�� �׸���.
		*/

	
	private :

		// Scene�� ��ӹ��� SceneŬ��������
		// UI, Light, Skybox�� Add ���ֱ⸸ �ϸ�
		// �˾Ƽ� �����Ѵ�.
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
		 �ش� ������Ʈ�� � ������ ���� �� �� �� 
		 ��ü������ �˻��մϴ�.
		 ��ü�� �˻��ϴ� ��ŭ �ӵ��� ������ �� ������
		 �����ϸ� GetOpaqueObject, GetAlphgaObject �� �ٸ� �Լ���
		 ����ؾ��մϴ�.
		*/
		GameObject* GetGameObject(std::wstring name);
		GameObject * GetMeshObject(std::wstring name);
		std::vector<class GameObject*>& GetMeshObjectAll();
		// ���� ȣ���� ��� layer�� ���� Ž���� �����մϴ�.
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



		// ������ Cache���� ���� 
		// �� �����ӿ� ���������� Ž���� �䱸���� �� 
		// �ѹ��� �˻����� ��� ���ϴ� ���� ���������� ���� �� �ְ� �Ѵ�.
		// �� Layer�� ���� Ž���̿����Ѵ�.

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
			���� ������ ��� �Լ�.
			Update���ư��� ���� ������ �� ���� ������
			�ӽ÷� m_removeFunctions�� ���
			��� Update, LateUpdate�� ����ģ �� ��� �����Լ��� ȣ�����ش�.
		*/
		std::vector<std::function<void()>> m_removeFunctions;


	};

}