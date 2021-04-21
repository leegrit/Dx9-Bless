#pragma once
#include "GameObject.h"
using namespace HyEngine;

	class ENGINE_DLL DebugGround : public HyEngine::GameObject
	{
	private:
		explicit DebugGround(class Scene* scene, GameObject* parent);
	private:
		virtual ~DebugGround() = default;

	public:
		static DebugGround* Create(Scene* scene, GameObject* parent)
		{
			DebugGround * obj = new DebugGround(scene, parent);
			obj->Initialize();
			return obj;
		}

		virtual void Render() override;

	private:
		void Initialize();
	private:
		IDirect3DVertexBuffer9 * m_pVertexBuffer = nullptr;
		IDirect3DIndexBuffer9 * m_pIndexBuffer = nullptr;

		int m_xCount = 100;
		int m_zCount = 100;
		int m_spacing = 10;

		int m_vertexSize;
		int m_vertexCount;
		int m_triCount;

		int m_indexSize;


	};
