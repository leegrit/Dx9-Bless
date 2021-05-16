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
		virtual void PostRender(ID3DXEffect* pEffect) {}
		// 단순하게 정점 그리는 내용만 호출하는 함수
		virtual void DrawPrimitive(ID3DXEffect* pShader) {}
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
		virtual void SetActive(bool active) override;
		virtual bool GetActive() const override;
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

		bool IsRenderEffect();
		bool IsRenderEffect(DWORD renderEffectOption);
		DWORD GetRenderEffectOption();
		void SetRenderEffectOption(DWORD RenderEffectOption);

		float GetRimWidth();
		void SetRimWidth(float rimWidth);

		D3DXCOLOR GetRimColor();
		void SetRimColor(D3DXCOLOR color);

	public :
		virtual D3DXMATRIX GetWorldMatrix();
		// ----------------------------------------------------------
		// STATIC METHODS
		// ---------------------------------------------------------------

		inline void SetViewFrustumCulled(bool result) { m_bViewFrustumCulled = result; }
		inline bool GetViewFrustumCulled() const { return m_bViewFrustumCulled; }
		inline void SetCullable(bool bCullable) { m_bCullable = bCullable; }
		inline bool GetCullable() { return m_bCullable; }

		// --------------------------------------------------------------
		// DATA
		// --------------------------------------------------------------
		void InsertGameData(class GameObjectData* data);
		void InsertMeshData(class MeshData* data);
		void InsertCellData(class CellData* data);
		void InsertTerrainData(class TerrainData* data);
		void InsertLightData(class LightData* data);
		void InsertEffectData(class EffectData* data);
		void InsertUIData(class UIData* data);

		virtual void UpdatedData(EDataType dataType) {};
		EStaticType GetStaticType() const;
	public:
		class Transform* m_pTransform;

	private:
		// --------------------------------------
		// PROPERTIES
		// --------------------------------------

		bool m_bViewFrustumCulled; // 기본값 false
		bool m_bCullable = true; // 기본값 true
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

		DWORD m_RenderEffectOption = RenderEffectOption::None;
		EStaticType m_staticType;
		// only editor
		int m_editID;

		int m_renderQueue = 3000;

	private :/* For PostRender */
		float m_rimWidth = 0;
		D3DXCOLOR m_rimColor = D3DXCOLOR(1, 1, 1, 1);

	protected: /* Hierarchy Data */
		class GameObjectData* m_pGameObjectData = nullptr;
		class MeshData* m_pMeshData = nullptr;
		class CellData* m_pCellData = nullptr;
		class TerrainData* m_pTerrainData = nullptr;
		class LightData* m_pLightData = nullptr;
		class EffectData* m_pEffectData = nullptr;
		class UIData* m_pUIData = nullptr;
	};
}