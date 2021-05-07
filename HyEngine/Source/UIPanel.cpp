#include "StandardEngineFramework.h"
#include "UIPanel.h"
#include "Geometry.h"
#include "TextureQuad.h"
#include "UIData.h"
#include "PathManager.h"


HyEngine::UIPanel::UIPanel(Scene * scene, GameObject * parent, int editID)
	: UIElement(scene, parent, editID)
{
	m_alpha = 1;
}

HyEngine::UIPanel::UIPanel(Scene * scene, std::wstring name)
	: UIElement(scene, name)
{
	m_alpha = 1;
}

HyEngine::UIPanel::~UIPanel()
{

}

void HyEngine::UIPanel::Initialize()
{
	UIElement::Initialize();
	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);
	if (IS_EDITOR)
	{
		EDIT_ENGINE->TryGetShader(L"UIPanel", &m_pShader);
	}
	else
		ENGINE->TryGetShader(L"UIPanel", &m_pShader);
	assert(m_pShader);
}

void HyEngine::UIPanel::Initialize(std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
	UIElement::Initialize();

	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);

	m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(imageFilePath);

	m_pTransform->m_position = position;
	m_pTransform->m_rotationEuler = rotation;
	m_pTransform->m_scale = scale;
	
	if (IS_EDITOR)
	{
		EDIT_ENGINE->TryGetShader(L"UIPanel", &m_pShader);
	}
	else
		ENGINE->TryGetShader(L"UIPanel", &m_pShader);
	assert(m_pShader);
}


void HyEngine::UIPanel::Render()
{
	UIElement::Render();

	assert(m_pShader);

	/* Get Selected Cam */
	Camera* pSelectedCamera = nullptr;
	pSelectedCamera = GetScene()->GetSelectedCamera();
	assert(pSelectedCamera);

	m_pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
	m_pShader->SetValue("ProjMatrix", &pSelectedCamera->GetOrthoMatrix(), sizeof(pSelectedCamera->GetOrthoMatrix()));

	m_pShader->SetFloat("Alpha", m_alpha);

	/* Set albedo */
	D3DXHANDLE albedoHandle = m_pShader->GetParameterByName(0, "AlbedoTex");
	m_pShader->SetTexture(albedoHandle, m_pTexture);


	m_pShader->SetTechnique("UIPanel");
	m_pShader->Begin(0, 0);
	{
		m_pShader->BeginPass(0);

		DEVICE->SetStreamSource(0, m_pTextureQuad->GetVertexBuffer(), 0, m_pTextureQuad->GetVertexSize());
		DEVICE->SetVertexDeclaration(m_pTextureQuad->GetDeclare());
		DEVICE->SetIndices(m_pTextureQuad->GetIndexBuffer());
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pTextureQuad->GetVertexCount(), 0, m_pTextureQuad->GetPrimitiveCount());

		m_pShader->EndPass();
	}
	m_pShader->End();
}

void HyEngine::UIPanel::UpdatedData(EDataType dataType)
{
	UIElement::UpdatedData(dataType);

	if (dataType != EDataType::UIData) return;
	std::wstring textureFilePath = CString::CharToWstring(m_pUIData->textureFilePath);

	m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(PATH->ResourcesPathW() + textureFilePath);

}

void HyEngine::UIPanel::SetAlpha(float alpha)
{
	m_alpha = alpha;
}

void HyEngine::UIPanel::SetTexture(std::wstring filePath)
{
	m_pTexture = (IDirect3DTexture9*)TextureLoader::GetTexture(filePath);
}

UIPanel * HyEngine::UIPanel::Create(Scene * scene, GameObject * parent, int editID)
{
	UIPanel * ui = new UIPanel(scene, parent, editID);
	ui->Initialize();
	return ui;
}

UIPanel * HyEngine::UIPanel::Create(Scene * scene, std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, std::wstring name)
{
	UIPanel * ui = new UIPanel(scene, name);
	ui->Initialize(imageFilePath, position, rotation, scale);
	return ui;
}
