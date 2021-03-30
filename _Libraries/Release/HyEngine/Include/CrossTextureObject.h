#pragma once
#include "GameObject.h"

namespace HyEngine
{

	class ENGINE_DLL CrossTextureObject abstract : public GameObject
	{
	protected :
		explicit CrossTextureObject(class Scene* scene, GameObject* parent,const std::wstring& textureFilePath, const std::wstring& name);
		virtual ~CrossTextureObject() = default;

	public :
		virtual void Initialize();
		virtual void Render() override;

		void Draw(std::string techniqueName);

	protected :
		class CrossTextureQuad* m_pTextureQuad = nullptr;
		std::shared_ptr<IDirect3DTexture9> m_pTexture = nullptr;

		LPD3DXEFFECT m_pEffect = nullptr;
	};
}
