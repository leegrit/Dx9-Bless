#include "StandardEngineFramework.h"
#include "Button.h"
#include "TextureQuad.h"
#include "TextureLoader.h"
HyEngine::Button::Button(Scene * pScene, std::wstring name, std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
	: UIElement(pScene, name)
{
	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);
	ENGINE->TryGetShader(L"UIPanel", &m_pEffect);
	assert(m_pEffect);
	m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(imageFilePath);

	m_pTransform->SetPosition(position);
	m_pTransform->m_rotationEuler = rotation;
	m_pTransform->SetScale(scale);
}

HyEngine::Button::~Button()
{
}

void HyEngine::Button::Initialize()
{
	UIElement::Initialize();

}

void HyEngine::Button::Render()
{
	UIElement::Render();

	m_pEffect->SetMatrix("WorldMatrix", &m_pTransform->GetWorldMatrix());
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetOrthoMatrix());

	D3DXHANDLE diffuseHandler = m_pEffect->GetParameterByName(0, "AlbedoTex");
	m_pEffect->SetTexture(diffuseHandler, m_pTexture);

	m_pEffect->SetTechnique("UIPanel");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);

		DEVICE->SetStreamSource(0, m_pTextureQuad->GetVertexBuffer(), 0, m_pTextureQuad->GetVertexSize());
		DEVICE->SetVertexDeclaration(m_pTextureQuad->GetDeclare());
		DEVICE->SetIndices(m_pTextureQuad->GetIndexBuffer());
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pTextureQuad->GetVertexCount(), 0, m_pTextureQuad->GetPrimitiveCount());

		m_pEffect->EndPass();
	}
	m_pEffect->End();
}

void HyEngine::Button::Update()
{
	UIElement::Update();

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
			m_isCollision = false;
			if (m_buttonEvents[(int)EButtonEvent::ButtonCollisionExit])
				m_buttonEvents[(int)EButtonEvent::ButtonCollisionExit]();
		}
		return;
	}
	// collision

	if (m_isCollision)
	{
		if (m_buttonEvents[(int)EButtonEvent::ButtonCollisionStay])
			m_buttonEvents[(int)EButtonEvent::ButtonCollisionStay]();
		OnCollisionStayWithMouse();
	}
	else
	{
		m_isCollision = true;
		if (m_buttonEvents[(int)EButtonEvent::ButtonCollisionEnter])
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

void HyEngine::Button::OnButtonDown()
{
}

void HyEngine::Button::OnButtonUp()
{
}

void HyEngine::Button::OnCollisionStayWithMouse()
{
}

void HyEngine::Button::SetButtonEvent(EButtonEvent eventType, std::function<void()> event)
{
	m_buttonEvents[(int)eventType] = event;
}

Button * HyEngine::Button::Create(Scene * pScene, std::wstring name, std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
	Button * button = new Button(pScene, name, imageFilePath, position, rotation, scale);
	button->Initialize();
	return button;
}
