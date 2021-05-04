#pragma once

#include "UIElement.h"

namespace HyEngine
{
	class ENGINE_DLL Button : public UIElement
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit Button(Scene* pScene, std::wstring name, 
			std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);
		virtual ~Button();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public:
		virtual void Initialize() override;
		virtual void Render() override;
		virtual void Update() override;
		
		//////////////////////////////////////////////////////////////////////////
		// CALLBACk
		//////////////////////////////////////////////////////////////////////////
	protected :
		virtual void OnButtonDown();
		virtual void OnButtonUp();
		//virtual void OnButtonPress();
		virtual void OnCollisionStayWithMouse(); // 마우스 버튼 위에 올라갈 때 리액션



		//////////////////////////////////////////////////////////////////////////
		// PUBLIC METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		void SetButtonEvent(EButtonEvent eventType, std::function<void()> event);
		

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private : /* For Render */
		ID3DXEffect* m_pEffect = nullptr;
		class TextureQuad* m_pTextureQuad = nullptr;
		IDirect3DTexture9* m_pTexture = nullptr;
	private : /* For Event */
		std::vector<std::function<void()>> m_buttonEvents=
		{
			std::function<void()>(),
			std::function<void()>(),
			std::function<void()>(),
			std::function<void()>(),
			std::function<void()>(),
			std::function<void()>()
		};
		bool m_isCollision = false;

		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		static Button *Create(Scene* pScene, std::wstring name,
			std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);

	};
}

