#pragma once
#include "GameObject.h"

namespace HyEngine
{

	class ENGINE_DLL MeshObject abstract : public GameObject
	{
	protected:
		explicit MeshObject(class Scene* scene,
			GameObject* parent,
			ERenderType renderType,
			const std::wstring& meshFilePath,
			const std::wstring& baseTexturePath,
			const std::wstring& normalTexturePath,
			const std::wstring& emissionTexturePath,
			const std::wstring& tag
			);
		explicit MeshObject(class Scene* scene,
			GameObject* parent,
			ERenderType renderType,
			const std::wstring& meshFilePath,
			const std::wstring& baseTexturePath,
			const std::wstring& normalTexturePath,
			const std::wstring& tag
		);
		explicit MeshObject(class Scene* scene,
			GameObject* parent,
			ERenderType renderType,
			const std::wstring& meshFilePath,
			const std::wstring& baseTexturePath,
			const std::wstring& tag
		);
		explicit MeshObject(class Scene* scene,
			GameObject* parent,
			ERenderType renderType,
			const std::wstring& meshFilePath,
			D3DXCOLOR color,
			const std::wstring& tag
		);
		explicit MeshObject(class Scene* scene,
			GameObject* parent,
			ED3DXMeshType meshType,
			D3DXCOLOR color,
			const std::wstring& name);
		virtual ~MeshObject();

	public:
		virtual void Initialize();
		virtual void Render() override;

		float GetRadius();
		void SetDissolveAmount(float amount);
		float GetDissolveAmount() const;
		void SetFringeAmount(float amount);
		float GetFringeAmount() const;
	protected:
		void Draw(std::string techniqueName);

	protected:
		IDirect3DTexture9* m_pBaseTex = nullptr;
		IDirect3DTexture9* m_pBumpTex = nullptr;
		IDirect3DTexture9*m_pEmission = nullptr;
		IDirect3DTexture9* m_pDissolveMap = nullptr;
		std::shared_ptr< Mesh>m_pMesh = nullptr;
		ID3DXMesh * m_pDxMesh = nullptr;
		D3DXCOLOR m_color;

		LPD3DXEFFECT m_pEffect = nullptr;

		float m_dissolveAmount = 0;
		float m_fringeAmount = 0;
	};
}
