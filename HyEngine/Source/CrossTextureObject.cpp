#include "StandardEngineFramework.h"
#include "CrossTextureObject.h"
#include "CrossTextureQuad.h"
#include "TextureLoader.h"

using namespace HyEngine;

HyEngine::CrossTextureObject::CrossTextureObject(Scene * scene, GameObject * parent, const std::wstring & textureFilePath, const std::wstring & name)
	: GameObject(ERenderType::RenderTexture, scene,parent, name)
{
	m_pTexture = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(textureFilePath));
}

void HyEngine::CrossTextureObject::Initialize()
{
	m_pTextureQuad = Geometry::CreateGeometry<CrossTextureQuad>(nullptr);
	D3DXCreateEffectFromFile(DEVICE, L"../_Shaders/TextureShader.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);
}

void HyEngine::CrossTextureObject::Render()
{
	GameObject::Render();

	DEVICE->SetStreamSource(0, m_pTextureQuad->GetVertexBuffer(), 0, m_pTextureQuad->GetVertexSize());
	DEVICE->SetVertexDeclaration(m_pTextureQuad->GetDeclare());
	DEVICE->SetIndices(m_pTextureQuad->GetIndexBuffer());

	m_pEffect->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(D3DXMATRIX));
	m_pEffect->SetValue("ViewMatrix", &CAMERA->GetViewMatrix(), sizeof(D3DXMATRIX));
	m_pEffect->SetValue("ProjMatrix", &CAMERA->GetProjectionMatrix(), sizeof(D3DXMATRIX));


	D3DXHANDLE imageHandle = m_pEffect->GetParameterByName(0, "ImageTex");
	m_pEffect->SetTexture(imageHandle, m_pTexture.get());
}

void HyEngine::CrossTextureObject::Draw(std::string techniqueName)
{
	m_pEffect->SetTechnique(techniqueName.c_str());
	m_pEffect->Begin(0, 0);
	m_pEffect->BeginPass(0);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pTextureQuad->GetVertexCount(), 0, m_pTextureQuad->GetPrimitiveCount());
	m_pEffect->EndPass();
	m_pEffect->End();
}
