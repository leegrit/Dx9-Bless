#pragma once
#include "UIElement.h"

namespace HyEngine
{
	class ENGINE_DLL ProgressBar : public UIElement
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit ProgressBar(Scene* pScene, std::wstring name,
			std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);
		virtual ~ProgressBar();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Initialize() override;
		virtual void Render() override;
		virtual void Update() override;

		//////////////////////////////////////////////////////////////////////////
		// PUBLIC METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		void SetAmount(float amount);

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private : /* For Render */
		ID3DXEffect* m_pEffect = nullptr;
		class TextureQuad * m_pTextureQuad = nullptr;
		IDirect3DTexture9* m_pTexture = nullptr;

	private : /* For ProgressBar */
		float m_amount = 1;

		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		static ProgressBar* Create(Scene * pScene, 
			std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, std::wstring name);


	};
}

