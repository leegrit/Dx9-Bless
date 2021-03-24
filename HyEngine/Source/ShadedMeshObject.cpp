#include "StandardEngineFramework.h"
#include "ShadedMeshObject.h"
//#include "BumpMesh.h"
#include "Mesh.h"
#include "TextureLoader.h"
#include "MeshLoader.h"
#include "CString.h"



using namespace HyEngine;

HyEngine::ShadedMeshObject::ShadedMeshObject(Scene * scene, GameObject * parent, ERenderType renderType, const std::wstring & meshFilePath, const std::wstring & baseTexturePath, const std::wstring & normalTexturePath,
	const std::wstring& emissionTexturePath, const std::wstring & tag)
	: GameObject(renderType, scene, parent, tag)
{
	m_pBaseTex = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(baseTexturePath));
	m_pBumpTex = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(normalTexturePath));
	m_pEmission = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(emissionTexturePath));
	m_pMesh = MeshLoader::GetMesh(CString::ToString(meshFilePath));

}

HyEngine::ShadedMeshObject::~ShadedMeshObject()
{

}

void HyEngine::ShadedMeshObject::Initialize()
{
	HRESULT hr = 0;
	
	D3DXCreateEffectFromFile(DEVICE, L"../_Shaders/BumpMapping.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);

}

void HyEngine::ShadedMeshObject::Render()
{
	DEVICE->SetStreamSource(0, m_pMesh->GetVertexBuffer(), 0, m_pMesh->GetVertexSize());
	DEVICE->SetVertexDeclaration(m_pMesh->GetDeclare());
	DEVICE->SetIndices(m_pMesh->GetIndexBuffer());

	
	D3DXVECTOR4 lightPosition(-500, 500, 0, 1);
	m_pEffect->SetValue("LightPosition", &lightPosition, sizeof(lightPosition));
	m_pEffect->SetValue("EyePosition", &CAMERA->m_pTransform->m_position, sizeof(CAMERA->m_pTransform->m_position));
	//m_pEffect->SetValue("EyePosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));

	m_pEffect->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(D3DXMATRIX));
	m_pEffect->SetValue("ViewMatrix", &CAMERA->GetViewMatrix(), sizeof(D3DXMATRIX));
	m_pEffect->SetValue("ProjMatrix", &CAMERA->GetProjectionMatrix(), sizeof(D3DXMATRIX));
	
	
	D3DXVECTOR4 ambient(1, 1, 1, 1);
	//D3DXVECTOR4 specular(1.f, 1.f, 1.f, 1.f);
	D3DXVECTOR4 specular(1.f, 1.f, 1.f, 1.f);

	D3DXVECTOR4 diffuse(1.f, 1.f, 1.f, 1.f);
	float specularPower = 1.0f;

	m_pEffect->SetValue("Ambient", &ambient, sizeof(ambient));
	m_pEffect->SetValue("Specular", &specular, sizeof(specular));
	m_pEffect->SetValue("Diffuse", &diffuse, sizeof(diffuse));
	m_pEffect->SetValue("SpecularPower", &specularPower, sizeof(specularPower));

	DEVICE->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	DEVICE->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	DEVICE->SetTexture(0, m_pBaseTex.get());
	DEVICE->SetTexture(1, m_pBumpTex.get());
	DEVICE->SetTexture(2, m_pEmission.get());

	m_pEffect->SetTechnique("Default_Technique");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);
			DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pMesh->GetVertexCount(), 0, m_pMesh->GetPrimitiveCount());
		m_pEffect->EndPass();

	}
	m_pEffect->End();

}

void HyEngine::ShadedMeshObject::Draw()
{
	assert(false);
	m_pEffect->SetTechnique("Default_Technique");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pMesh->GetVertexCount(), 0, m_pMesh->GetPrimitiveCount());
		m_pEffect->EndPass();

	}
	m_pEffect->End();
}
