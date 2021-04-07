#include "StandardEngineFramework.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ILight.h"
#include "Constants.h"
#include "ObjectContainer.h"
#include "DeferredQuad.h"
#include "Light.h"
#include "PathManager.h"


void HyEngine::Renderer::Setup()
{
	/* Render Target Settings */
	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A32B32G32R32F,
		D3DPOOL_DEFAULT,
		&m_pDepthRTTexture
	);
	m_pDepthRTTexture->GetSurfaceLevel(0, &m_pDepthRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pAlbedoRTTexture
	);
	m_pAlbedoRTTexture->GetSurfaceLevel(0, &m_pAlbedoRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pNormalRTTexture
	);
	m_pNormalRTTexture->GetSurfaceLevel(0, &m_pNormalRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pSpecularRTTexture
	);
	m_pSpecularRTTexture->GetSurfaceLevel(0, &m_pSpecularRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pStashRTTexture
	);
	m_pStashRTTexture->GetSurfaceLevel(0, &m_pStashRTSurface);

	m_pResultScreen = new DeferredQuad();

	m_bSetup = true;
}

void HyEngine::Renderer::Cleanup()
{
	/* Depth */
	SAFE_RELEASE(m_pDepthRTTexture);
	SAFE_RELEASE(m_pDepthRTSurface);
	/* Albedo */
	SAFE_RELEASE(m_pAlbedoRTTexture);
	SAFE_RELEASE(m_pAlbedoRTSurface);
	/* Normal */
	SAFE_RELEASE(m_pNormalRTTexture);
	SAFE_RELEASE(m_pNormalRTSurface);
	/* Specular */
	SAFE_RELEASE(m_pSpecularRTTexture);
	SAFE_RELEASE(m_pSpecularRTSurface);
	/* Stash */
	SAFE_RELEASE(m_pStashRTTexture);
	SAFE_RELEASE(m_pStashRTSurface);

	SAFE_DELETE(m_pResultScreen);
}

void HyEngine::Renderer::ClearBackBuffer()
{
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
}

void HyEngine::Renderer::ClearStashSurface()
{
	DEVICE->ColorFill(m_pStashRTSurface, NULL, 0x00000000);
}

void HyEngine::Renderer::Render(Scene * scene)
{
	/* For opaque objects with light */
	DeferredPipeline(scene);

	/* For alpha object without light */
	ForwardPipeline(scene);}

void Renderer::RenderBegin()
{
	DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, m_clearColor, 1.f, 0);
	DEVICE->BeginScene();


}

void Renderer::RenderEnd()
{

	DEVICE->EndScene();
	DEVICE->Present(nullptr, nullptr, g_hWnd, nullptr);
}

void HyEngine::Renderer::DeferredPipeline(Scene* scene)
{
	SetGBufferMRT();
	ClearBackBuffer();

	/* Render For GBuffer */
	GeometryPass(scene);

	SetOriginMRT();
	ClearStashSurface();
	
	/* Ambient Pass */
	AmbientPass(scene);

	/* Render For Backbuffer */
	LightPass(scene);


}

void HyEngine::Renderer::ForwardPipeline(Scene* scene)
{
	/* Render Alpha */
}

void HyEngine::Renderer::SetGBufferMRT()
{
	/* Get Origin */
	DEVICE->GetRenderTarget(0, &m_pOriginSurface);

	/* Set Multi Render Targets */
	DEVICE->SetRenderTarget(0, m_pDepthRTSurface);
	DEVICE->SetRenderTarget(1, m_pAlbedoRTSurface);
	DEVICE->SetRenderTarget(2, m_pNormalRTSurface);
	DEVICE->SetRenderTarget(3, m_pSpecularRTSurface);
}

void HyEngine::Renderer::SetLightMRT()
{
}

void HyEngine::Renderer::SetOriginMRT()
{
	DEVICE->SetRenderTarget(0, m_pOriginSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
	DEVICE->SetRenderTarget(4, NULL);
}

void HyEngine::Renderer::GeometryPass(Scene * scene)
{
	auto& list = scene->GetObjectContainer()->GetOpaqueObjectAll();
	if (list.size() == 0) return;
	for (auto& opaque : list)
	{
		opaque->Render();
	}

}

void HyEngine::Renderer::AmbientPass(Scene * scene)
{
	/* 임시 데이터 */
	float ambientFactor = 0.1f;

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	D3DXMATRIX viewMatrixInv;
	D3DXMATRIX projMatrixInv;

	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
	DEVICE->SetIndices(m_pResultScreen->_ib);

	D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 1000);
	D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
	D3DXMatrixIdentity(&viewMatrix);

	ID3DXEffect* pShader = nullptr;
#ifndef _EDITOR
	ENGINE->TryGetShader(L"Ambient", &pShader);
#else
	EDIT_ENGINE->TryGetShader(L"Ambient", &pShader);
#endif
	assert(pShader);

	pShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	pShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	pShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
	

	/* Albedo */
	D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
	pShader->SetTexture(albedoHandle, m_pAlbedoRTTexture);

	pShader->SetValue("AmbientFactor", &ambientFactor, sizeof(ambientFactor));

	pShader->SetTechnique("AmbientLight");
	pShader->Begin(0, 0);
	{
		pShader->BeginPass(0);
		DEVICE->DrawIndexedPrimitive
		(
			D3DPT_TRIANGLELIST,
			0,
			0,
			4,
			0,
			2
		);
		pShader->EndPass();
	}
	pShader->End();
	DEVICE->StretchRect(m_pOriginSurface, NULL, m_pStashRTSurface, NULL, D3DTEXF_NONE);
}

void HyEngine::Renderer::LightPass(Scene * scene)
{
	auto& list = scene->GetObjectContainer()->GetLightAll();
	if (list.size() == 0) return;
	for (auto& light : list)
	{
		/* world, view, projection */
		D3DXMATRIX worldMatrix;
		D3DXMATRIX viewMatrix;
		D3DXMATRIX projMatrix;
	
		/* inverse */
		D3DXMATRIX viewMatrixInv;
		D3DXMATRIX projMatrixInv;

		DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
		DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
		DEVICE->SetIndices(m_pResultScreen->_ib);

		D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 1000);
		D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
		D3DXMatrixIdentity(&viewMatrix);

		/* shader load */
		ID3DXEffect* pShader = nullptr;

		/* 테스트용 */
		if (light->Type() == ELightType::POINT)
		{
#ifndef _EDITOR
			ENGINE->TryGetShader(L"PointLight", &pShader);
#else 
			EDIT_ENGINE->TryGetShader(L"PointLight", &pShader);
#endif 
		}
		else if (light->Type() == ELightType::DIRECTIONAL)
		{
#ifndef _EDITOR
			ENGINE->TryGetShader(L"DirectionalLight", &pShader);
#else
			EDIT_ENGINE->TryGetShader(L"DirectionalLight", &pShader);
#endif
		}
		else if (light->Type() == ELightType::SPOT)
		{
#ifndef _EDITOR
			ENGINE->TryGetShader(L"SpotLight", &pShader);
#else
			EDIT_ENGINE->TryGetShader(L"SpotLight", &pShader);
#endif
		}

		assert(pShader);
	
		pShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
		pShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
		pShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));

		Camera* selectedCam = scene->GetSelectedCamera();
		assert(selectedCam);

		float farPlane = selectedCam->GetFar();
		pShader->SetValue("Far", &farPlane, sizeof(selectedCam->GetFar()));

		D3DXMatrixInverse(&viewMatrixInv, NULL, &selectedCam->GetViewMatrix());
		D3DXMatrixInverse(&projMatrixInv, NULL, &selectedCam->GetProjectionMatrix());

		pShader->SetValue("ViewMatrixInv", &viewMatrixInv, sizeof(viewMatrixInv));
		pShader->SetValue("ProjMatrixInv", &projMatrixInv, sizeof(projMatrixInv));

		/* Set GBuffer */
		D3DXHANDLE depthHandle = pShader->GetParameterByName(0, "DepthTex");
		pShader->SetTexture(depthHandle, m_pDepthRTTexture);

		D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
		pShader->SetTexture(albedoHandle, m_pAlbedoRTTexture);

		D3DXHANDLE normalHandle = pShader->GetParameterByName(0, "NormalTex");
		pShader->SetTexture(normalHandle, m_pNormalRTTexture);

		D3DXHANDLE specularHandle = pShader->GetParameterByName(0, "SpecularTex");
		pShader->SetTexture(specularHandle, m_pSpecularRTTexture);

		D3DXHANDLE stashHandle = pShader->GetParameterByName(0, "StashTex");
		pShader->SetTexture(stashHandle, m_pStashRTTexture);

		pShader->SetValue("EyePosition", &selectedCam->GetPosition(), sizeof(selectedCam->GetPosition()));
		pShader->SetValue("Direction", &light->Direction(), sizeof(light->Direction()));
		pShader->SetValue("Position", &light->Position(), sizeof(light->Position()));
		pShader->SetValue("Ambient", &light->Ambient(), sizeof(light->Ambient()));
		pShader->SetValue("AmbientIntensity", &light->AmbientIntensity(), sizeof(light->AmbientIntensity()));
		pShader->SetValue("Diffuse", &light->Diffuse(), sizeof(light->Diffuse()));
		pShader->SetValue("DiffuseIntensity", &light->DiffuseIntensity(), sizeof(light->DiffuseIntensity()));
		pShader->SetValue("Specular", &light->Specular(), sizeof(light->Specular()));
		pShader->SetValue("SpecularIntensity", &light->SpecularIntensity(), sizeof(light->SpecularIntensity()));
		pShader->SetValue("SpecularPower", &light->SpecularPower(), sizeof(light->SpecularPower()));
		pShader->SetValue("Range", &light->Range(), sizeof(light->Range()));
		pShader->SetValue("Cone", &light->Cone(), sizeof(light->Cone()));
		pShader->SetValue("Constant", &light->Constant(), sizeof(light->Constant()));
		pShader->SetValue("Linear", &light->Linear(), sizeof(light->Linear()));
		pShader->SetValue("Quadratic", &light->Quadratic(), sizeof(light->Quadratic()));


		/* 테스트용 */
		if (light->Type() == ELightType::POINT)
			pShader->SetTechnique("PointLight");
		else if (light->Type() == ELightType::DIRECTIONAL)
			pShader->SetTechnique("DirectionalLight");
		else if (light->Type() == ELightType::SPOT)
			pShader->SetTechnique("SpotLight");

		pShader->Begin(0, 0);
		{
			pShader->BeginPass(0);
			DEVICE->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLELIST,
				0,
				0,
				4,
				0,
				2
			);
			pShader->EndPass();
		}
		pShader->End();
		DEVICE->StretchRect(m_pOriginSurface, NULL, m_pStashRTSurface, NULL, D3DTEXF_NONE);
	}
}

Renderer * HyEngine::Renderer::Create()
{
	Renderer* pRenderer = new Renderer();
	pRenderer->Setup();
	return pRenderer;
}

void HyEngine::Renderer::Release(Renderer * pRenderer)
{
	pRenderer->Cleanup();
	SAFE_DELETE(pRenderer);
}

