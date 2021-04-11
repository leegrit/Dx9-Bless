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

	for (int i = 0; i < NUM_CASCADEDES; i++)
	{
		D3DXCreateTexture
		(
			DEVICE,
			WinMaxWidth,
			WinMaxHeight,
			D3DX_DEFAULT,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A32B32G32R32F,
			D3DPOOL_DEFAULT,
			&m_pShadowRTTexture[i]
		);
		m_pShadowRTTexture[i]->GetSurfaceLevel(0, &m_pShadowRTSurface[i]);
	}
	

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pSoftShadowOriginRTTexture
	);
	m_pSoftShadowOriginRTTexture->GetSurfaceLevel(0, &m_pSoftShadowOriginRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pSoftShadowBlurXRTTexture
	);
	m_pSoftShadowBlurXRTTexture->GetSurfaceLevel(0, &m_pSoftShadowBlurXRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pSoftShadowRTTexture
	);
	m_pSoftShadowRTTexture->GetSurfaceLevel(0, &m_pSoftShadowRTSurface);

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

	/* ShadowMap */
	for (int i = 0; i < NUM_CASCADEDES; i++)
	{
		SAFE_RELEASE(m_pShadowRTTexture[i]);
		SAFE_RELEASE(m_pShadowRTSurface[i]);
	}

	/* SoftShadowMap */
	SAFE_RELEASE(m_pSoftShadowOriginRTTexture);
	SAFE_RELEASE(m_pSoftShadowOriginRTSurface);
	SAFE_RELEASE(m_pSoftShadowBlurXRTTexture);
	SAFE_RELEASE(m_pSoftShadowBlurXRTSurface);
	SAFE_RELEASE(m_pSoftShadowRTTexture);
	SAFE_RELEASE(m_pSoftShadowRTSurface);

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
	GetOriginMRT();

	/* For shadowMap */
	PreparePipeline(scene);

	/* For opaque objects with light */
	DeferredPipeline(scene);

	/* For alpha object without light */
	ForwardPipeline(scene);
}

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

void HyEngine::Renderer::PreparePipeline(Scene * scene)
{
	/* Create CascadeShadow Map  */
	for (int i = 0; i < NUM_CASCADEDES; i++)
	{
		SetShadowMapMRT(i);
		ClearBackBuffer();
		ShadowPass(scene, i);
	}

	SetOriginMRT();
}

void HyEngine::Renderer::DeferredPipeline(Scene* scene)
{
	SetGBufferMRT();
	ClearBackBuffer();

	/* Render For GBuffer */
	GeometryPass(scene);

	/* Create Soft ShadowMap */
	// SoftShadow Origin
	SetSoftShadowOriginMRT();
	SoftShadowPass(scene);
	// SoftShadow Blur
	SetSoftShadowMRT();
	SoftShadowBlurPass(scene);

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
	auto& list = scene->GetObjectContainer()->GetRenderableAlphaAll();
	if (list.size() == 0) return;
	for (auto& alpha : list)
	{
		alpha->Render();
	}
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

void HyEngine::Renderer::SetOriginMRT()
{
	DEVICE->SetRenderTarget(0, m_pOriginSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}

void HyEngine::Renderer::SetShadowMapMRT(int cascadeIndex)
{
	DEVICE->SetRenderTarget(0, m_pShadowRTSurface[cascadeIndex]);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);

}

void HyEngine::Renderer::GetOriginMRT()
{
	/* Get Origin */
	DEVICE->GetRenderTarget(0, &m_pOriginSurface);
}

void HyEngine::Renderer::SetSoftShadowOriginMRT()
{
	DEVICE->SetRenderTarget(0, m_pSoftShadowOriginRTSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}

void HyEngine::Renderer::SetSoftShadowBlurXMRT()
{
	/* ����� */
	assert(false);
}

void HyEngine::Renderer::SetSoftShadowMRT()
{
	DEVICE->SetRenderTarget(0, m_pSoftShadowRTSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}

void HyEngine::Renderer::GeometryPass(Scene * scene)
{
	auto& list = scene->GetObjectContainer()->GetRenderableOpaqueAll();
	if (list.size() == 0) return;
	for (auto& opaque : list)
	{
		opaque->Render();
	}

}

void HyEngine::Renderer::AmbientPass(Scene * scene)
{
	/* �ӽ� ������ */
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
	auto& list = scene->GetObjectContainer()->GetRenderableLightAll();
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

		/* �׽�Ʈ�� */
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

		if (light->Type() == ELightType::DIRECTIONAL)
		{
			/* For CascadeShadowMapping */
			pShader->SetMatrixArray("LightViewMatrix", m_lightViewMat, NUM_CASCADEDES);
			pShader->SetMatrixArray("LightProjMatrix", m_lightProjMat, NUM_CASCADEDES);
		}

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

		/* For CascadeShadowMapping */
		if (NUM_CASCADEDES > 0)
		{
			D3DXHANDLE shadowMapHandler0 = pShader->GetParameterByName(0, "ShadowDepthTex0");
			pShader->SetTexture(shadowMapHandler0, m_pShadowRTTexture[0]);
		}
		if (NUM_CASCADEDES > 1)
		{
			D3DXHANDLE shadowMapHandler1 = pShader->GetParameterByName(0, "ShadowDepthTex1");
			pShader->SetTexture(shadowMapHandler1, m_pShadowRTTexture[1]);
		}
		if (NUM_CASCADEDES > 2)
		{
			D3DXHANDLE shadowMapHandler2 = pShader->GetParameterByName(0, "ShadowDepthTex2");
			pShader->SetTexture(shadowMapHandler2, m_pShadowRTTexture[2]);
		}
		if (NUM_CASCADEDES > 3)
		{
			D3DXHANDLE shadowMapHandler3 = pShader->GetParameterByName(0, "ShadowDepthTex3");
			pShader->SetTexture(shadowMapHandler3, m_pShadowRTTexture[3]);
		}


		D3DXHANDLE softShadowHandler = pShader->GetParameterByName(0, "SoftShadowTex");
		pShader->SetTexture(softShadowHandler, m_pSoftShadowRTTexture);
		

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


		/* �׽�Ʈ�� */
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

void HyEngine::Renderer::ShadowPass(Scene * scene, int cascadeIndex)
{
	auto& list = scene->GetObjectContainer()->GetRenderableOpaqueAll();
	if (list.size() == 0) return;

	/* shader load */
	ID3DXEffect* pShader = nullptr;
#ifndef _EDITOR
	ENGINE->TryGetShader(L"ShadowMap", &pShader);
#else 
	EDIT_ENGINE->TryGetShader(L"ShadowMap", &pShader);
#endif 

	/* Get Selected Cam */
	Camera* pSelectedCam = nullptr;
	pSelectedCam = scene->GetSelectedCamera();
	assert(pSelectedCam);

	/* Find Directional Light */
	// Shadow�� directional�� ������ �޴´�.
	Light* directionalLight = nullptr;
	auto& lights = scene->GetObjectContainer()->GetRenderableLightAll();
	for (auto& light : lights)
	{
		if (light->Type() == ELightType::DIRECTIONAL)
		{
			directionalLight = light;
			break;
		}
	}
	if (directionalLight == nullptr)
		return;


	/* Calculate Cascades algorithm */
#pragma region Cascade ShadowMapping Algorithm
	int numCascades = 4; // 4�� ���� 
						 /* cascadedEnds[NUM_CASCADES + 1] = {0.0f, 0.2f, 0.4f, 1.0f} */
	float cascadedEnds[4 + 1] = { 0.0f, 0.05f, 0.1f, 0.2f, 1.0f };

	D3DXVECTOR3 frustumCorners[8] =
	{
		D3DXVECTOR3(-1.0f,  1.0f, 0.0f),
		D3DXVECTOR3(1.0f,  1.0f, 0.0f),
		D3DXVECTOR3(1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(-1.0f,  1.0f,  1.0f),
		D3DXVECTOR3(1.0f,  1.0f,  1.0f),
		D3DXVECTOR3(1.0f, -1.0f,  1.0f),
		D3DXVECTOR3(-1.0f, -1.0f,  1.0f)
	};

	/* Calculate inverse view projection */
	D3DXMATRIX viewMatInv;
	D3DXMATRIX projMatInv;

	D3DXMatrixInverse(&viewMatInv, NULL, &pSelectedCam->GetViewMatrix());
	D3DXMatrixInverse(&projMatInv, NULL, &pSelectedCam->GetProjectionMatrix());

	/* Convert NDC -> World Space */
	for (UINT i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(&frustumCorners[i], &frustumCorners[i], &projMatInv);
		D3DXVec3TransformCoord(&frustumCorners[i], &frustumCorners[i], &viewMatInv);
	}

	/* Unit Cube�� �� �ڳ� ��ġ�� Slice�� �°� ���� */
	// �ӽ÷� �Ѱ��� cascade�� ����
	for (int i = 0; i < 4; i++)
	{
		D3DXVECTOR3 cornerRay = frustumCorners[i + 4] - frustumCorners[i];
		D3DXVECTOR3 nearCornerRay = cornerRay * cascadedEnds[cascadeIndex];
		D3DXVECTOR3 farCornerRay = cornerRay * cascadedEnds[cascadeIndex + 1];
		frustumCorners[i + 4] = frustumCorners[i] + farCornerRay;
		frustumCorners[i] = frustumCorners[i] + nearCornerRay;
	}

	/* Calculate Center of view frustum */
	D3DXVECTOR3 frustumCenter = D3DXVECTOR3(0, 0, 0);
	for (int i = 0; i < 8; i++)
	{
		frustumCenter += frustumCorners[i];
	}
	frustumCenter *= (1.0f / 8.0f);

	/* Calculate radius of the bound sphere of the view frustum */
	float sphereRadius = 0.0f;
	for (int i = 0; i < 8; i++)
	{
		float dist = D3DXVec3Length(&(frustumCorners[i] - frustumCenter));
		sphereRadius = std::max(sphereRadius, dist);
	}

	// Calculate AABB with the radius of the bound spherer
	D3DXVECTOR3 mins = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	D3DXVECTOR3 maxes = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	sphereRadius = std::ceil(sphereRadius * 16.0f) / 16.0f;
	maxes = D3DXVECTOR3(sphereRadius, sphereRadius, sphereRadius);
	mins = -maxes;

	// Calculate the Scale of aabb
	D3DXVECTOR3 cascadedExtents = maxes - mins;

	/* Calcualte the ShadowMap Position */
	// frustum �߽ɿ��� light �ݴ�������� min.z��ŭ �̵�
	D3DXVECTOR3 normalizedDirection;
	D3DXVec3Normalize(&normalizedDirection, &directionalLight->Direction());
	D3DXVECTOR3 shadowCameraPos = frustumCenter - normalizedDirection * std::fabs(mins.z);

	D3DXMATRIX lightViewMatrix;
	D3DXMATRIX lightProjMatrix;

	/* Light View Matrix */
	D3DXMatrixLookAtLH(&lightViewMatrix,
		&shadowCameraPos,
		&frustumCenter,
		&Vector3::Up);

	D3DXMatrixOrthoOffCenterLH(&lightProjMatrix, mins.x, maxes.x, mins.y, maxes.y, 1, cascadedExtents.z);


	m_lightViewMat[cascadeIndex] = lightViewMatrix;
	m_lightProjMat[cascadeIndex] = lightProjMatrix;

#pragma endregion

	for (auto& opaque : list)
	{
		pShader->SetValue("WorldMatrix", &opaque->m_pTransform->GetWorldMatrix(), sizeof(opaque->m_pTransform->GetWorldMatrix()));


		pShader->SetValue("LightViewMatrix", &m_lightViewMat[cascadeIndex], sizeof(m_lightViewMat[cascadeIndex]));
		pShader->SetValue("LightProjMatrix", &m_lightProjMat[cascadeIndex], sizeof(m_lightProjMat[cascadeIndex]));

		pShader->SetTechnique("ShadowMap");
		pShader->Begin(0, 0);
		{
			pShader->BeginPass(0);
			opaque->DrawPrimitive();
			pShader->EndPass();

		}
		pShader->End();

	}
}

void HyEngine::Renderer::SoftShadowPass(Scene * scene)
{
	/* Find Directional Light */
	Light* directionalLight = nullptr;
	for(auto& light : scene->GetObjectContainer()->GetRenderableLightAll())
	{
		if (light->Type() == ELightType::DIRECTIONAL)
		{
			directionalLight = light;
			break;
		}
	}
	if (directionalLight == nullptr)
		return;


	/* World, View, Porj */
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	/* Camera Matrix Inverse */
	D3DXMATRIX viewMatrixInv;
	D3DXMATRIX projMatrixInv;

	/* Set Matrices */
	D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 1000);
	D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
	D3DXMatrixIdentity(&viewMatrix);


	/* Set Stream */
	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
	DEVICE->SetIndices(m_pResultScreen->_ib);

	/* Shader Load */
	ID3DXEffect* pShader = nullptr;

#ifdef _EDITOR
	EDIT_ENGINE->TryGetShader(L"SoftShadowMapping", &pShader);
#else
	ENGINE->TryGetShader(L"SoftShadowMapping", &pShader);
#endif
	assert(pShader);

	Camera* selectedCam = scene->GetSelectedCamera();
	assert(selectedCam);

	D3DXMatrixInverse(&viewMatrixInv, NULL, &selectedCam->GetViewMatrix());
	D3DXMatrixInverse(&projMatrixInv, NULL, &selectedCam->GetProjectionMatrix());

	/* Set Matrix to shader */
	pShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	pShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	pShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));

	pShader->SetValue("ViewMatrixInv", &viewMatrixInv, sizeof(viewMatrixInv));
	pShader->SetValue("ProjMatrixInv", &projMatrixInv, sizeof(projMatrixInv));

	pShader->SetMatrixArray("LightViewMatrix", m_lightViewMat, NUM_CASCADEDES);
	pShader->SetMatrixArray("LightProjMatrix", m_lightProjMat, NUM_CASCADEDES);


	/* Set GBuffer */
	D3DXHANDLE depthHandle = pShader->GetParameterByName(0, "DepthTex");
	pShader->SetTexture(depthHandle, m_pDepthRTTexture);

	D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
	pShader->SetTexture(albedoHandle, m_pAlbedoRTTexture);

	D3DXHANDLE normalHandle = pShader->GetParameterByName(0, "NormalTex");
	pShader->SetTexture(normalHandle, m_pNormalRTTexture);

	D3DXHANDLE specularHandle = pShader->GetParameterByName(0, "SpecularTex");
	pShader->SetTexture(specularHandle, m_pSpecularRTTexture);

	/* For CascadeShadowMapping */
	if (NUM_CASCADEDES > 0)
	{
		D3DXHANDLE shadowMapHandler0 = pShader->GetParameterByName(0, "ShadowDepthTex0");
		pShader->SetTexture(shadowMapHandler0, m_pShadowRTTexture[0]);
	}
	if (NUM_CASCADEDES > 1)
	{
		D3DXHANDLE shadowMapHandler1 = pShader->GetParameterByName(0, "ShadowDepthTex1");
		pShader->SetTexture(shadowMapHandler1, m_pShadowRTTexture[1]);
	}
	if (NUM_CASCADEDES > 2)
	{
		D3DXHANDLE shadowMapHandler2 = pShader->GetParameterByName(0, "ShadowDepthTex2");
		pShader->SetTexture(shadowMapHandler2, m_pShadowRTTexture[2]);
	}
	if (NUM_CASCADEDES > 3)
	{
		D3DXHANDLE shadowMapHandler3 = pShader->GetParameterByName(0, "ShadowDepthTex3");
		pShader->SetTexture(shadowMapHandler3, m_pShadowRTTexture[3]);
	}
	pShader->SetTechnique("SoftShadowMapping");
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
}

void HyEngine::Renderer::SoftShadowBlurPass(Scene * scene)
{
	/* Set Stream */
	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
	DEVICE->SetIndices(m_pResultScreen->_ib);

	/* Shader Load */
	ID3DXEffect* pShader = nullptr;

#ifdef _EDITOR
	EDIT_ENGINE->TryGetShader(L"Blur", &pShader);
#else
	ENGINE->TryGetShader(L"Blur", &pShader);
#endif
	assert(pShader);

	/* World, View, Porj */
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;
	
	/* Set Matrices */
	D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 1000);
	D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
	D3DXMatrixIdentity(&viewMatrix);

	/* Set Matrix to shader */
	pShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	pShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	pShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));

	/* Set SourceSize */
	D3DXVECTOR2 sourceSize = D3DXVECTOR2(WinMaxWidth, WinMaxHeight);
	pShader->SetValue("SourceSize", &sourceSize, sizeof(sourceSize));
	
	/* Set Source */
	D3DXHANDLE sourceHandle = pShader->GetParameterByName(0, "SourceTex");
	pShader->SetTexture(sourceHandle, m_pSoftShadowOriginRTTexture);

	pShader->SetTechnique("Blur");
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

