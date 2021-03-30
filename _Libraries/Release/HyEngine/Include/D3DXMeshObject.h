#pragma once
#include "GameObject.h"


namespace HyEngine
{
	class ENGINE_DLL D3DXMeshObject abstract : public GameObject
	{
	protected :
		explicit D3DXMeshObject(class Scene* scene,
			GameObject* parent,
			ED3DXMeshType meshType,
			const std::wstring& name);

		virtual ~D3DXMeshObject();

	public :
		virtual void Initialize();
		virtual void Render() override;

	protected :
		void Draw();

	protected :
		ID3DXMesh* m_pMesh = nullptr;

	};
}
