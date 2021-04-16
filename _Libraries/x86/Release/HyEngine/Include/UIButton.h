#pragma once

#include "UIElement.h"

namespace HyEngine
{
	class ENGINE_DLL UIButton abstract: public UIElement
	{
	protected :
		explicit UIButton(class Scene* scene,
			std::wstring imageFilePath,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring tag);
		virtual ~UIButton();

	public :
		virtual void Initialize() override;
		virtual void Render() override;
		// ui는 컴포넌트가 없기 때문에 상위 Update를 호출하지않는다.
		// 본인 로직만 수행함.
		// 여기서 버튼 관련 이벤트 보내줌
		virtual void Update() final;

		void SetButtonEvent(EButtonEvent eventType, std::function<void()> event);
	protected :
		/*virtual void OnButtonDown();
		virtual void OnButtonUp();
		virtual void OnButtonPress();
		virtual void OnCollisionEnterWithMouse();
		virtual void OnCollisionStayWithMouse();
		virtual void OnCollisionExitWithMouse();*/

		// 상속을 통해 재정의
		virtual void OnButtonDown();// 버튼 내려갈 때 리액션
		virtual void OnButtonUp(); // 버튼 올라갈 때 리액션
		virtual void OnCollisionStayWithMouse(); // 마우스 버튼 위에 올라갈 때 리액션

	private :
		std::vector<std::function<void()>> m_buttonEvents =
		{
			std::function<void()>(),
			std::function<void()>(),
			std::function<void()>(),
			std::function<void()>(),
			std::function<void()>(),
			std::function<void()>()
		};
		/*std::function<void()> m_onButtonDown;
		std::function<void()> m_onButtonUp;
		std::function<void()> m_onButtonPress;
		std::function<void()> m_onCollisionEnterWithMouse;
		std::function<void()> m_onCollisionStayWithMouse;
		std::function<void()> m_onCollisionEnterWithMouse;*/

		bool m_isCollision = false;
	public :
	private :
		void DrawButton();
	/*	static UIButton* Create
		(
			Scene* scene,
			std::wstring imageFilePath,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring tag)
		{
			UIButton* button = new UIButton(scene, imageFilePath, position, rotation, scale, tag);
			button->Initialize();
			return button;
		}*/

	};

}