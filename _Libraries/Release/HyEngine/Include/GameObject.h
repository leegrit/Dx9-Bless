#pragma once
#include "Object.h"
#include "IRenderable.h"


namespace HyEngine
{
	class Component;
	class ENGINE_DLL GameObject abstract: public Object
	{
	protected:
		explicit GameObject(ERenderType renderType, class Scene* scene, GameObject* parent, const std::wstring& tag);
		/*explicit GameObject(ERenderType renderType, class Scene* scene, GameObject* parent, const std::wstring& tag,
			const Vector3& originPos,
			const Quaternion& originRot,
			const Vector3& originScale);*/
		virtual ~GameObject();

	public:
		virtual void Render();
		virtual void Update();
		virtual void OnEnable() {}
		virtual void OnDisable() {}
		void LateUpdate();

		bool CompareTag(std::wstring tag);
		std::wstring GetTag()const;
		inline ERenderType GetRenderType()const { return m_renderType; }

		inline Component* AddComponent(Component* component)
		{
			m_components.emplace_back(component);
			return component;
		}

		template <typename Type>
		Type* GetComponent()
		{
			for (auto& component : m_components)
			{
				Type* comp = dynamic_cast<Type*>(component);
				if (comp != nullptr)
					return comp;
			}
			return nullptr;
		}

		template <typename Type>
		std::vector<class Component* > GetComponents()
		{
			std::vector<component*> comVec;
			for (auto& component : m_components)
			{
				Type* comp = dynamic_cast<Type*> (component);
				if (comp != nullptr)
					comVec.push_back(comp);
			}
			return comVec;
		}

		void SetActive(bool active);
		inline bool GetActive() const { return m_bActiveSelf; }

		// Gets the component of the specified type, if it exists.
		template <typename T>
		bool TryGetComponent(_Out_ Component** result)
		{
			for (auto& component : m_components)
			{
				T * comp = dynamic_cast<T*>(component);
				if (comp != nullptr)
				{
					result = comp;
					return true;
				}
			}
			return false;


		}


		inline void SetScene(class Scene* scene)
		{
			if (m_pScene == nullptr)
				m_pScene = scene;
			else
				assert(false);
		}

		void SetTag(std::wstring tag);
		
		inline void SetLayer(UINT layer) { m_layer = layer; }
		inline UINT GetLayer() { return m_layer; }
		inline int GetRenderQueue() { return m_renderQueue; }
		inline void SetRenderQueue(int renderQueue) { m_renderQueue = renderQueue; }
		void SetEditID(int editID);
		int GetEditID() const;
		inline void AddChild(GameObject* obj)
		{
			m_pChilds.push_back(obj);
		}
		inline void RemoveChild(GameObject* obj)
		{
			for (auto& child : m_pChilds)
			{
				if (child == obj)
				{
					m_pChilds.remove(obj);
					return;
				}
			}
		}

		GameObject* GetParent() const;
		Scene* GetScene() const;
		// ----------------------------------------------------------
		// STATIC METHODS
		// ---------------------------------------------------------------

		inline void SetViewFrustumCulled(bool result) { m_bViewFrustumCulled = result; }
		inline bool GetViewFrustumCulled() const { return m_bViewFrustumCulled; }


		// --------------------------------------------------------------
		// DATA
		// --------------------------------------------------------------
		void InsertGameData(class GameObjectData* data);
		void InsertMeshData(class MeshData* data);
		void InsertCellData(class CellData* data);
		void InsertTerrainData(class TerrainData* data);

		virtual void UpdatedData(EDataType dataType) {};
		EStaticType GetStaticType() const;
	public:
		class Transform* m_pTransform;

	private:
		// --------------------------------------
		// PROPERTIES
		// --------------------------------------

		bool m_bActiveSelf;

		bool m_bViewFrustumCulled; // ±âº»°ª false
		//TODO : Layer m_layer;
		// TODO : Scene m_scene;
		std::wstring m_tag;

		UINT m_layer;
		//Scene that the GameObject is part of.
		class Scene* m_pScene = nullptr;
		GameObject* m_pParent = nullptr;
		std::list<GameObject* > m_pChilds;

		ERenderType m_renderType;

		std::vector<class Component* > m_components;

		std::vector<std::function<void()>> m_removeFunctions;


		EStaticType m_staticType;
		// only editor
		int m_editID;

		int m_renderQueue = 3000;
	protected: /* Hierarchy Data */
		class GameObjectData* m_pGameObjectData = nullptr;
		class MeshData* m_pMeshData = nullptr;
		class CellData* m_pCellData = nullptr;
		class TerrainData* m_pTerrainData = nullptr;
	};
}