#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class TestMesh : public GameObject
	{
	protected:
		explicit TestMesh(class Scene* scene, GameObject* parent);
		virtual ~TestMesh();

	public:
		virtual void Initialize();
		virtual void Render() override;
	public:
		static TestMesh* Create(Scene* scene, GameObject* parent)
		{
			//assert(false);
			TestMesh* obj = new TestMesh(scene, parent);
			obj->Initialize();
			
			obj->m_bInit = true;
			return obj;
		}
		class HyEngine::SphereCollider *m_pCollider;
	private:
		std::shared_ptr<IDirect3DTexture9> m_pBaseTex = nullptr;
		std::shared_ptr<IDirect3DTexture9> m_pBumpTex = nullptr;
		std::shared_ptr<IDirect3DTexture9> m_pEmission = nullptr;
		std::shared_ptr<Mesh> m_pMesh = nullptr;

		bool m_bInit = false;
	};

}