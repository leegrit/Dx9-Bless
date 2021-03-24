#include "StandardEngineFramework.h"
#include "UIButton.h"
#include "TextureQuad.h"
#include "UpdateDispatcher.h"

using namespace HyEngine;

HyEngine::UIButton::UIButton(Scene * scene, std::wstring imageFilePath, const Vector3 position, const Quaternion rotation, const Vector3 scale, std::wstring tag)
	: UIElement(scene, imageFilePath, position, rotation, scale, tag)
{
}

HyEngine::UIButton::~UIButton()
{
}

void HyEngine::UIButton::Initialize()
{
	UIElement::Initialize();


}

void HyEngine::UIButton::Render()
{
	UIElement::Render();

	/*DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		0, 0, m_pTextureQuad->GetVertexCount(),
		0,
		m_pTextureQuad->GetPrimitiveCount());*/
}

void HyEngine::UIButton::Update()
{
	Vector3 mousePos = MOUSE->GetPosition();
	mousePos.x() -= WinMaxWidth * 0.5f;
	mousePos.y() -= WinMaxHeight * 0.5f;
	const Vector3& position = m_pTransform->m_position;
	const Vector3& scale = m_pTransform->m_scale;
	Vector3 leftTop;
	leftTop.x() = position.x() - scale.x() * 0.5f;
	leftTop.y() = position.y() + scale.y() * 0.5f;

	Vector3 rightDown;
	rightDown.x() = position.x() + scale.x() * 0.5f;
	rightDown.y() = position.y() - scale.y() * 0.5f;

	if (leftTop.x() > mousePos.x() ||
		leftTop.y() < mousePos.y() ||
		rightDown.x() < mousePos.x() ||
		rightDown.y() > mousePos.y())
	{
		if (m_isCollision)
		{
			if (m_buttonEvents[(int)EButtonEvent::ButtonCollisionExit])
				m_buttonEvents[(int)EButtonEvent::ButtonCollisionExit]();
		}
		return;
	}
	// collision

	if (m_isCollision)
	{
		if(m_buttonEvents[(int)EButtonEvent::ButtonCollisionStay])
			m_buttonEvents[(int)EButtonEvent::ButtonCollisionStay]();
		OnCollisionStayWithMouse();
	}
	else
	{
		m_isCollision = true;
		if(m_buttonEvents[(int)EButtonEvent::ButtonCollisionEnter])
			m_buttonEvents[(int)EButtonEvent::ButtonCollisionEnter]();
	}

	if (MOUSE->Down(0))
	{
		if (m_buttonEvents[(int)EButtonEvent::ButtonDown])
			m_buttonEvents[(int)EButtonEvent::ButtonDown]();
		OnButtonDown();
	}
	if (MOUSE->Up(0))
	{
		if (m_buttonEvents[(int)EButtonEvent::ButtonUp])
			m_buttonEvents[(int)EButtonEvent::ButtonUp]();
		OnButtonUp();
	}
	if (MOUSE->Press(0))
	{
		if (m_buttonEvents[(int)EButtonEvent::ButtonPress])
			m_buttonEvents[(int)EButtonEvent::ButtonPress]();
	}


}

void HyEngine::UIButton::SetButtonEvent(EButtonEvent eventType, std::function<void()> event)
{
	m_buttonEvents[(int)eventType] = event;
}

void HyEngine::UIButton::OnButtonDown()
{

}

void HyEngine::UIButton::OnButtonUp()
{
}

void HyEngine::UIButton::OnCollisionStayWithMouse()
{
}

void HyEngine::UIButton::DrawButton()
{

}
