#pragma once
#include "ISkybox.h"
#include "ILight.h"
#include "Object.h"
#include "GameObject.h"


namespace HyEngine
{

	class GameObject;
	class Collider;
	class Camera;
	class NavMesh;
	class Light;
	class Skybox;
	class ENGINE_DLL Scene
	{
		friend class Object;
		friend class GameObject;
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	public:
		explicit Scene();
		virtual ~Scene();

		//////////////////////////////////////////////////////////////////////////
		// FOR INHERITED
		//////////////////////////////////////////////////////////////////////////
	protected:
		virtual void Update() = 0;
		virtual void Load() = 0;
		virtual void Unload() = 0;
	public:
		// LoadAsync 함수는 thread에서 들어온다.
		// 콜백 함수는 자원을 로드할 때마다 호출해줘야하며
		// 인자는 로드한 리소스 수, 로드해야하는 리소스 총량 
		virtual void LoadAsync(std::function<void(int, int)> onProgress) = 0;

	
		//////////////////////////////////////////////////////////////////////////
		// LOAD & UNLOAD
		//////////////////////////////////////////////////////////////////////////
	public :
		void LoadScene();
		void UnloadScene();
		virtual void LateLoadScene() {}

		//////////////////////////////////////////////////////////////////////////
		// UPDATE & RENDER
		//////////////////////////////////////////////////////////////////////////
	public :
		void UpdateScene();
		void RenderScene(class Renderer * renderer);
		virtual void RenderGUI();

		//////////////////////////////////////////////////////////////////////////
		// SETTER
		//////////////////////////////////////////////////////////////////////////
	public:
		bool SelectCamera(std::wstring name);
		void SetSkybox(Skybox* skybox);

		//////////////////////////////////////////////////////////////////////////
		// GETTER
		//////////////////////////////////////////////////////////////////////////
	public :
		Camera* GetSelectedCamera() const;
		Skybox* GetSkybox() const;
		class ObjectContainer* GetObjectContainer() const;

		//////////////////////////////////////////////////////////////////////////
		// FOR CULLING
		//////////////////////////////////////////////////////////////////////////
	public :
		void ViewFrustumCull();

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private:
		Camera* m_pSelectedCamera = nullptr;
		Skybox* m_pSkybox = nullptr;
		class ObjectContainer * m_pObjectContainer = nullptr;
		class CollisionCalculator * m_pCollisionCalculator = nullptr;

	};

}
