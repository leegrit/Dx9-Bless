#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class ENGINE_DLL Texture abstract : public GameObject
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit Texture(Scene* pScene, GameObject* pParent, std::wstring name);
		virtual ~Texture() = default;

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Render();
		virtual void Update();
		virtual void OnEnable();
		virtual void OnDisable();

	public:
		virtual void Initialize();
		void SetDiffuseTexture(std::wstring diffusePath);
		void SetAlphaMaskTexture(std::wstring alphaMaskPath);

	protected:
		class TextureQuad* m_pTextureQuad = nullptr;
		IDirect3DTexture9 * m_pDiffuse = nullptr;
		IDirect3DTexture9 * m_pAlphaMask = nullptr;

		ID3DXEffect* m_pEffect = nullptr;
	};

}