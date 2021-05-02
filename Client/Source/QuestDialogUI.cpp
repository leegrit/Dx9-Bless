#include "stdafx.h"
#include "QuestDialogUI.h"

#include "TextureQuad.h"


QuestDialogUI::QuestDialogUI(Scene * pScene, std::wstring name)
	: UIElement(pScene, name)
{

}

QuestDialogUI::~QuestDialogUI()
{
}

void QuestDialogUI::Initialize(std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
	UIElement::Initialize();

	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);

	m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(imageFilePath);

	m_pTransform->m_position = position;
	m_pTransform->m_rotationEuler = rotation;
	m_pTransform->m_scale = scale;

	ENGINE->TryGetShader(L"UIPanel", &m_pEffect);
	assert(m_pEffect);
}

void QuestDialogUI::Render()
{
	UIElement::Render();

	/* For Font */
	ENGINE->DrawTextW(m_dialogText.c_str(), D3DXVECTOR3(0, 500, 0),D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));


	m_pEffect->SetMatrix("WorldMatrix", &m_pTransform->GetWorldMatrix());
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetOrthoMatrix());

	/* Set Diffuse */
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

void QuestDialogUI::ShowDialog(std::wstring message)
{
	m_dialogText = message;
	SetActive(true);
}

void QuestDialogUI::HideDialog()
{
	SetActive(false);
}

QuestDialogUI * QuestDialogUI::Create(Scene * pScene, std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 scale, std::wstring name)
{
	QuestDialogUI * ui = new QuestDialogUI(pScene, name);
	ui->Initialize(imageFilePath, position, D3DXVECTOR3(0, 0, 0), scale);
	return ui;
}
