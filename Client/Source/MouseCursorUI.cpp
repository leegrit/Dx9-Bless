#include "stdafx.h"
#include "MouseCursorUI.h"
#include "Geometry.h"
#include "MouseQuad.h"
#include "PathManager.h"

MouseCursorUI::MouseCursorUI(Scene * pScene)
	: UIElement(pScene, L"MouseCursor")
{

}

MouseCursorUI::~MouseCursorUI()
{
}

void MouseCursorUI::Initialize(std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
	UIElement::Initialize();
	m_pTextureQuad = Geometry::CreateGeometry<MouseQuad>(nullptr);
	m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(imageFilePath);
	m_pTransform->m_position = position;
	m_pTransform->m_rotationEuler = rotation;
	m_pTransform->m_scale = scale;
		ENGINE->TryGetShader(L"UIPanel", &m_pEffect);
	assert(m_pEffect);


}

void MouseCursorUI::Render()
{
	UIElement::Render();

	/* Get Selected Cam */
	Camera* pSelectedCamera = nullptr;
	pSelectedCamera = GetScene()->GetSelectedCamera();
	assert(pSelectedCamera);

	m_pEffect->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
	m_pEffect->SetValue("ProjMatrix", &pSelectedCamera->GetOrthoMatrix(), sizeof(pSelectedCamera->GetOrthoMatrix()));

	/* Set albedo */
	D3DXHANDLE albedoHandle = m_pEffect->GetParameterByName(0, "AlbedoTex");
	m_pEffect->SetTexture(albedoHandle, m_pTexture);


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

void MouseCursorUI::Update()
{
	D3DXVECTOR3 pos = MOUSE->GetPosition();
	m_pTransform->m_position = pos - D3DXVECTOR3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f,0);
}

MouseCursorUI * MouseCursorUI::Create(Scene * scene, std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
	MouseCursorUI * ui = new MouseCursorUI(scene);
	ui->Initialize(imageFilePath, position, rotation, scale);
	return ui;
}
