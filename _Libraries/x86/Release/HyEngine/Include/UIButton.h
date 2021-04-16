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
		// ui�� ������Ʈ�� ���� ������ ���� Update�� ȣ�������ʴ´�.
		// ���� ������ ������.
		// ���⼭ ��ư ���� �̺�Ʈ ������
		virtual void Update() final;

		void SetButtonEvent(EButtonEvent eventType, std::function<void()> event);
	protected :
		/*virtual void OnButtonDown();
		virtual void OnButtonUp();
		virtual void OnButtonPress();
		virtual void OnCollisionEnterWithMouse();
		virtual void OnCollisionStayWithMouse();
		virtual void OnCollisionExitWithMouse();*/

		// ����� ���� ������
		virtual void OnButtonDown();// ��ư ������ �� ���׼�
		virtual void OnButtonUp(); // ��ư �ö� �� ���׼�
		virtual void OnCollisionStayWithMouse(); // ���콺 ��ư ���� �ö� �� ���׼�

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