#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class ENGINE_DLL ZTextureObject abstract : public GameObject
	{
	protected:
		explicit ZTextureObject(class Scene* scene, GameObject* parent, ERenderType renderType, const std::wstring& textureFilePath ,const std::wstring& tag);
		virtual ~ZTextureObject() = default;

	public:

		// Inherited via GameObject
		virtual void Initialize();
		virtual void Render() override;

		void Draw(std::string techniqueName);

	protected:
		class ZTextureQuad* m_pTextureQuad = nullptr;
		std::shared_ptr<IDirect3DTexture9> m_pTexture = nullptr;

		LPD3DXEFFECT m_pEffect = nullptr;
	};

}