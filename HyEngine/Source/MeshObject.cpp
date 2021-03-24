#include "StandardEngineFramework.h"
#include "MeshObject.h"
#include "TextureLoader.h"
#include "MeshLoader.h"
#include "CString.h"
#include "Light.h"
#include "VertexTypes.h"


using namespace HyEngine;

HyEngine::MeshObject::MeshObject(Scene * scene, GameObject * parent, ERenderType renderType, const std::wstring & meshFilePath, const std::wstring & baseTexturePath, const std::wstring & normalTexturePath, const std::wstring & emissionTexturePath, const std::wstring & tag)
	: GameObject(renderType, scene, parent, tag)
{
	m_pBaseTex = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(baseTexturePath));
	m_pBumpTex = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(normalTexturePath));
	m_pEmission = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(emissionTexturePath));
#ifdef TEST_MODE
	m_pMesh = MeshLoader::GetMesh("../Resources/Cube.obj");
#else
	m_pMesh = MeshLoader::GetMesh(CString::ToString(meshFilePath));
#endif
}

HyEngine::MeshObject::MeshObject(Scene * scene, GameObject * parent, ERenderType renderType, const std::wstring & meshFilePath, const std::wstring & baseTexturePath, const std::wstring & normalTexturePath, const std::wstring & tag)
	: GameObject(renderType, scene, parent, tag)
{
	m_pBaseTex = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(baseTexturePath));
	m_pBumpTex = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(normalTexturePath));
	m_pEmission = nullptr;
#ifdef TEST_MODE
	m_pMesh = MeshLoader::GetMesh("../Resources/Cube.obj");
#else
	m_pMesh = MeshLoader::GetMesh(CString::ToString(meshFilePath));
#endif
}

HyEngine::MeshObject::MeshObject(Scene * scene, GameObject * parent, ERenderType renderType, const std::wstring & meshFilePath, const std::wstring & baseTexturePath, const std::wstring & tag)
	: GameObject(renderType, scene, parent, tag)
{
	m_pBaseTex = std::static_pointer_cast<IDirect3DTexture9>(TextureLoader::GetTexture(baseTexturePath));
	m_pBumpTex = nullptr;
	m_pEmission = nullptr;
#ifdef TEST_MODE
	m_pMesh = MeshLoader::GetMesh("../Resources/Cube.obj");
#else
	m_pMesh = MeshLoader::GetMesh(CString::ToString(meshFilePath));
#endif
}

HyEngine::MeshObject::MeshObject(Scene * scene, GameObject * parent, ERenderType renderType, const std::wstring & meshFilePath, D3DXCOLOR color, const std::wstring & tag)
	: GameObject(renderType, scene, parent, tag),
	m_color(color)
{
	m_pBaseTex = nullptr;
	m_pBumpTex = nullptr;
	m_pEmission = nullptr;
#ifdef TEST_MODE
	m_pMesh = MeshLoader::GetMesh("../Resources/Cube.obj");
#else
	m_pMesh = MeshLoader::GetMesh(CString::ToString(meshFilePath));
#endif
}

HyEngine::MeshObject::MeshObject(Scene * scene, GameObject * parent, ED3DXMeshType meshType, D3DXCOLOR color, const std::wstring & name)
	:GameObject(ERenderType::RenderMesh, scene, parent, name),
	m_color(color)
{
#ifdef TEST_MODE
	m_pMesh = MeshLoader::GetMesh("../Resources/Cube.obj");
#else
	switch (meshType)
	{
	case ED3DXMeshType::Box:
		D3DXCreateBox
		(
			DEVICE,
			2.0f, // width
			2.0f, // height
			2.0f, // depth
			&m_pDxMesh,
			0
		);
		break;
	case ED3DXMeshType::Torus:
		D3DXCreateTorus(
			DEVICE,
			0.2f, // inner radius
			3.2f, // outer radius
			20,   // sides
			20,   // rings
			&m_pDxMesh,
			0);

		break;
	case ED3DXMeshType::Cylinder:
		D3DXCreateCylinder
		(
			DEVICE,
			1.0f, // radius at negative z end
			1.0f, // radius at positive z end
			3.0f, // length of cylinder
			10, // slices
			10, // stacks
			&m_pDxMesh,
			0
		);
		break;
	case ED3DXMeshType::Sphere:
		D3DXCreateSphere(
			DEVICE,
			1.0f, // radius
			10,   // slices
			10,   // stacks
			&m_pDxMesh,
			0);
		break;
	default:
		break;
	}
#endif
}

HyEngine::MeshObject::~MeshObject()
{
	if (m_pMesh)
		m_pMesh.reset();
	if (m_pBaseTex)
		m_pBaseTex.reset();
	if (m_pBumpTex)
		m_pBumpTex.reset();
	if (m_pEmission)
		m_pEmission.reset();
}

void HyEngine::MeshObject::Initialize()
{
	D3DXCreateEffectFromFile(DEVICE, L"../_Shaders/MeshShader.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);

	//m_pBaseTex = TextureLoader::GetTexture(baseTexturePath);
	//m_pDissolveMap = (IDirect3DTexture9*)TextureLoader::GetTexture(L"../Resources/Effects/dissolveMap.jpg");
}

void HyEngine::MeshObject::Render()
{
	if (m_pMesh)
	{
		DEVICE->SetStreamSource(0, m_pMesh->GetVertexBuffer(), 0, m_pMesh->GetVertexSize());
		DEVICE->SetVertexDeclaration(m_pMesh->GetDeclare());
		DEVICE->SetIndices(m_pMesh->GetIndexBuffer());
	}
	Light* pGlobalLight = GetScene()->GetGlobalLight();
	assert(pGlobalLight->Type() == ELightType::DIRECTIONAL);
	m_pEffect->SetValue("LightDirection", &pGlobalLight->Direction(), sizeof(pGlobalLight->Direction()));
	m_pEffect->SetValue("Ambient", &pGlobalLight->Ambient(), sizeof(pGlobalLight->Ambient()));
	m_pEffect->SetValue("AmbientIntensity", &pGlobalLight->AmbientIntensity(), sizeof(pGlobalLight->AmbientIntensity()));
	m_pEffect->SetValue("Diffuse", &pGlobalLight->Diffuse(), sizeof(pGlobalLight->Diffuse()));
	m_pEffect->SetValue("DiffuseIntensity", &pGlobalLight->DiffuseIntensity(), sizeof(pGlobalLight->DiffuseIntensity()));
	m_pEffect->SetValue("Specular", &pGlobalLight->Specular(), sizeof(pGlobalLight->Specular()));
	m_pEffect->SetValue("SpecularIntensity", &pGlobalLight->SpecularIntensity(), sizeof(pGlobalLight->SpecularIntensity()));
	m_pEffect->SetValue("SpecularPower", &pGlobalLight->SpecularPower(), sizeof(pGlobalLight->SpecularPower()));

	m_pEffect->SetValue("DissolveAmount", &m_dissolveAmount, sizeof(m_dissolveAmount));
	m_pEffect->SetValue("FringeAmount", &m_fringeAmount, sizeof(m_fringeAmount));

	m_pEffect->SetValue("Color", &m_color, sizeof(m_color));
	
	m_pEffect->SetValue("CameraPosition", &GetScene()->GetSelectedCamera()->GetPosition(), sizeof(CAMERA->GetPosition()));
	
	m_pEffect->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(D3DXMATRIX));
	m_pEffect->SetValue("ViewMatrix", &GetScene()->GetSelectedCamera()->GetViewMatrix(), sizeof(D3DXMATRIX));
	m_pEffect->SetValue("ProjMatrix", &GetScene()->GetSelectedCamera()->GetProjectionMatrix(), sizeof(D3DXMATRIX));


	if (m_pBaseTex)
	{
		D3DXHANDLE baseHandle = m_pEffect->GetParameterByName(0, "BaseMap");
		m_pEffect->SetTexture(baseHandle, m_pBaseTex.get());
	}
	if (m_pBumpTex)
	{
		D3DXHANDLE bumpHandle = m_pEffect->GetParameterByName(0, "BumpMap");
		m_pEffect->SetTexture(bumpHandle, m_pBumpTex.get());
	}
	if (m_pEmission)
	{
		D3DXHANDLE emissionHandle = m_pEffect->GetParameterByName(0, "EmissionMap");
		m_pEffect->SetTexture(emissionHandle, m_pEmission.get());
	}
	if (m_pDissolveMap)
	{
		D3DXHANDLE dissolveHandle = m_pEffect->GetParameterByName(0, "DissolveMap");
		m_pEffect->SetTexture(dissolveHandle, m_pDissolveMap.get());
	}
}

float HyEngine::MeshObject::GetRadius()
{
	if (m_pMesh)
	{
		return m_pMesh->GetRadius();
	}
	if (m_pDxMesh)
	{
		// ±âº»°ª
		return 1;
	}
	return 1;
}

void HyEngine::MeshObject::SetDissolveAmount(float amount)
{
	assert(amount <= 1 && amount >= 0);

	m_dissolveAmount = amount;
}

float HyEngine::MeshObject::GetDissolveAmount() const
{
	return m_dissolveAmount;
}

void HyEngine::MeshObject::SetFringeAmount(float amount)
{
	m_fringeAmount = amount;
}

float HyEngine::MeshObject::GetFringeAmount() const
{
	return m_fringeAmount;
}

void HyEngine::MeshObject::Draw(std::string techniqueName)
{
	m_pEffect->SetTechnique(techniqueName.c_str());
	m_pEffect->Begin(0, 0);
	m_pEffect->BeginPass(0);
	if(m_pDxMesh)
		m_pDxMesh->DrawSubset(0);
	else if(m_pMesh)
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pMesh->GetVertexCount(), 0, m_pMesh->GetPrimitiveCount());
	m_pEffect->EndPass();
	m_pEffect->End();
}
