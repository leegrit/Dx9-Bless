#include "StandardEngineFramework.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ILight.h"
#include "Constants.h"
#include "ObjectContainer.h"
#include "DeferredQuad.h"
#include "Light.h"
#include "PathManager.h"
#include "Skybox.h"
#include "VertexTypes.h"
#include "DebugMRTQuad.h"
#include "DynamicMesh.h"

void HyEngine::Renderer::Setup()
{
	/* Render Target Settings */
	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
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
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pAlbedoRTTexture
	);
	m_pAlbedoRTTexture->GetSurfaceLevel(0, &m_pAlbedoRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pNormalRTTexture
	);
	m_pNormalRTTexture->GetSurfaceLevel(0, &m_pNormalRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
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
			0,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_R16F,
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
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_R16F,
		D3DPOOL_DEFAULT,
		&m_pSoftShadowOriginRTTexture
	);
	m_pSoftShadowOriginRTTexture->GetSurfaceLevel(0, &m_pSoftShadowOriginRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_R16F,
		D3DPOOL_DEFAULT,
		&m_pSoftShadowBlurXRTTexture
	);
	m_pSoftShadowBlurXRTTexture->GetSurfaceLevel(0, &m_pSoftShadowBlurXRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_R16F,
		D3DPOOL_DEFAULT,
		&m_pSoftShadowRTTexture
	);
	m_pSoftShadowRTTexture->GetSurfaceLevel(0, &m_pSoftShadowRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pLightIntensityRTTexture
	);
	m_pLightIntensityRTTexture->GetSurfaceLevel(0, &m_pLightIntensityRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pAmbientIntensityRTTexture
	);
	m_pAmbientIntensityRTTexture->GetSurfaceLevel(0, &m_pAmbientIntensityRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pSpecularIntensityRTTexture
	);
	m_pSpecularIntensityRTTexture->GetSurfaceLevel(0, &m_pSpecularIntensityRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pScreenTexture
	);
	m_pScreenTexture->GetSurfaceLevel(0, &m_pScreenSurface);


	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pVtxNormalRTTexture
	);
	m_pVtxNormalRTTexture->GetSurfaceLevel(0, &m_pVtxNormalRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pEffectMaskRTTexture
	);
	m_pEffectMaskRTTexture->GetSurfaceLevel(0, &m_pEffectMaskRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pEffectParamRTTexture
	);
	m_pEffectParamRTTexture->GetSurfaceLevel(0, &m_pEffectParamRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pRimLightColorRTTexture
	);
	m_pRimLightColorRTTexture->GetSurfaceLevel(0, &m_pRimLightColorRTSurface);


	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pRimLightRTTexture
	);
	m_pRimLightRTTexture->GetSurfaceLevel(0, &m_pRimLightRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pBrightnessTexture
	);
	m_pBrightnessTexture->GetSurfaceLevel(0, &m_pBrightnessSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pBloomRTTexture
	);
	m_pBloomRTTexture->GetSurfaceLevel(0, &m_pBloomRTSurface);


	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pPostRenderRTTexture
	);
	m_pPostRenderRTTexture->GetSurfaceLevel(0, &m_pPostRenderRTSurface);


	D3DXCreateTexture
	(
		DEVICE,
		WinMaxWidth,
		WinMaxHeight,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&m_pStashRTTexture
	);
	m_pStashRTTexture->GetSurfaceLevel(0, &m_pStashRTSurface);

	m_pResultScreen = new DeferredQuad();

	/* GBuffer Group */
	m_pDepthRTQuad = new DebugMRTQuad(0, 0, 150, 150);
	m_pAlbedoRTQuad = new DebugMRTQuad(0, 150, 150, 150);
	m_pNormalRTQuad = new DebugMRTQuad(0, 300, 150, 150);
	m_pSpecularRTQuad = new DebugMRTQuad(0, 450, 150, 150);

	/* Effect Buffer Group */
	m_pVtxNormalQuad = new DebugMRTQuad(150, 0, 150, 150);
	m_pEffectMaskQuad = new DebugMRTQuad(150, 150, 150, 150);
	m_pEffectParamQuad = new DebugMRTQuad(150, 300, 150, 150);
	m_pRimLightColorQuad = new  DebugMRTQuad(150, 450, 150, 150);

	/* Shadow Group */
	m_pCascadeShadowQuad0 = new DebugMRTQuad(300, 0, 150, 150);
	m_pCascadeShadowQuad1 = new DebugMRTQuad(300, 150, 150, 150);
	m_pShadowOriginQuad = new DebugMRTQuad(300, 300, 150, 150);
	m_pShadowBlurQuad = new DebugMRTQuad(300, 450, 150, 150);

	/* Light Group */
	m_pLightIntensityQuad = new DebugMRTQuad(450, 0, 150, 150);
	m_pAmbientIntensityQuad = new DebugMRTQuad(450, 150, 150, 150);
	m_pSpecularIntensityQuad = new DebugMRTQuad(450, 300, 150, 150);
	m_pRimLightQuad = new DebugMRTQuad(450, 450, 150, 150);

	/* Post Render Group */
	//m_pRimLightQuad = new DebugMRTQuad(600, 0, 150, 150);
	m_pBrightnessQuad = new DebugMRTQuad(600, 0, 150, 150);
	m_pBloomQuad = new DebugMRTQuad(600, 150, 150, 150);


	m_bSetup = true;
}

void HyEngine::Renderer::SetupOcclusion()
{
	/* Create the query */
	DEVICE->CreateQuery(D3DQUERYTYPE_OCCLUSION, &m_pQuery);

	/* Get the display mode to obtain the format */
	D3DDISPLAYMODE mode;
	DEVICE->GetDisplayMode(0, &mode);

	HRESULT hr = D3DXCreateTexture
	(
		DEVICE,
		320, // WinMaxWidth
		240, // WinMaxHeight
		1,
		D3DUSAGE_RENDERTARGET,
		mode.Format,
		D3DPOOL_DEFAULT,
		&m_pOcclusionTexture
	);
	assert(SUCCEEDED(hr));

	/* Obtain the surface */
	D3DSURFACE_DESC desc;
	m_pOcclusionTexture->GetSurfaceLevel(0, &m_pOcclusionSurface);
	m_pOcclusionSurface->GetDesc(&desc);

	/* Create the render to surface */
	hr = D3DXCreateRenderToSurface
	(
		DEVICE,
		desc.Width,
		desc.Height,
		desc.Format,
		TRUE,
		D3DFMT_D16,
		&m_pOcclusionRender
	);
	assert(SUCCEEDED(hr));


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

	/* Light */
	SAFE_RELEASE(m_pLightIntensityRTTexture);
	SAFE_RELEASE(m_pLightIntensityRTSurface);
	SAFE_RELEASE(m_pAmbientIntensityRTTexture);
	SAFE_RELEASE(m_pAmbientIntensityRTSurface);
	SAFE_RELEASE(m_pSpecularIntensityRTTexture);
	SAFE_RELEASE(m_pSpecularIntensityRTSurface);

	/* Stash */
	SAFE_RELEASE(m_pStashRTTexture);
	SAFE_RELEASE(m_pStashRTSurface);

	SAFE_DELETE(m_pResultScreen);

	/* Occlusion Query */
	SAFE_RELEASE(m_pQuery);
	SAFE_RELEASE(m_pOcclusionRender);
	SAFE_RELEASE(m_pOcclusionSurface);
	SAFE_RELEASE(m_pOcclusionTexture);

}

void HyEngine::Renderer::ClearBackBuffer()
{
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
}

void HyEngine::Renderer::ClearStashSurface()
{
	DEVICE->ColorFill(m_pStashRTSurface, NULL, 0x00000000);
}

void HyEngine::Renderer::ClearSurface()
{
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET, 0x00000000, 1.0f, 0);
}

void HyEngine::Renderer::ClearDepth()
{
	DEVICE->Clear(0, 0, D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
}

void HyEngine::Renderer::OcclusionCull(Scene* scene)
{
	//auto& objects = scene->GetObjectContainer()->GetRenderableOpaqueAll();
	auto& objects = m_renderableOpaque;
	// TODO : 나중에 미리 로드했다가 사용하는 방식으로 변경
	ID3DXEffect * pShader = nullptr;
	if (IS_EDITOR)
		EDIT_ENGINE->TryGetShader(L"OcclusionQuery", &pShader);
	else
		ENGINE->TryGetShader(L"OcclusionQuery", &pShader);

	/* First, Render every object's boundingMesh */
	for(int i = 0; i < objects.size(); i++)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(objects[i]);
		if (mesh == nullptr)
			continue;

		pShader->SetTechnique("OcclusionQuery");
		pShader->Begin(0, 0);
		{
			pShader->BeginPass(0);
			mesh->RenderBoundingMesh(pShader);
			pShader->EndPass();
		}
		pShader->End();
	}

	/* Now, Render each boundingMesh again, except this time, count how many pixels are visible */ 
	/* By using an occlusion query. We are guaranteed to get the right amoung, */
	/* Since all the bounding mesh have already been rendered */
	for (int i = 0; i < objects.size(); i++)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(objects[i]);
		if (mesh == nullptr)
			continue;

		/* Start Query */
		m_pQuery->Issue(D3DISSUE_BEGIN);

		/* Render */
		pShader->SetTechnique("OcclusionQuery");
		pShader->Begin(0, 0);
		{
			pShader->BeginPass(0);
			mesh->RenderBoundingMesh(pShader);
			pShader->EndPass();
		}
		pShader->End();

		/* End the query, get the data */
		m_pQuery->Issue(D3DISSUE_END);

		/* Loop until the data becomes available */
		DWORD pixelsVisible = 0;

		while (m_pQuery->GetData((void*)&pixelsVisible,
			sizeof(DWORD), D3DGETDATA_FLUSH) == S_FALSE)
		{
			if (pixelsVisible == 0)
			{
				int a = 0;
				/* No pixels visible, do not render */
				//mesh->OcclusionCulled(true);
			}
			else
			{
				int a = 0;

				/* Pixel visible, render */
				//mesh->OcclusionCulled(false);
			}
		}

	}

}

void HyEngine::Renderer::OcclusionBegin()
{
	HRESULT hr;
	hr = m_pOcclusionRender->BeginScene(m_pOcclusionSurface, NULL);
	assert(SUCCEEDED(hr));

	DEVICE->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
}

void HyEngine::Renderer::OcclusionEnd()
{
	m_pOcclusionRender->EndScene(0);

	//D3DXSaveSurfaceToFile(L"buffer.bmp", D3DXIFF_BMP, m_pOcclusionSurface, NULL, NULL);
	
}

void HyEngine::Renderer::Render(Scene * scene)
{
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	//* For shadowMap */
	PreparePipeline(scene);

	//* For opaque objects with light */
	DeferredPipeline(scene);


	//* For alpha object without light */
	ForwardPipeline(scene);

	//* For PostRendering */
	PostRenderPipeline(scene);

	if(m_isDebugRender)
		DebugPipeline();
}

void Renderer::RenderBegin()
{
	DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, m_clearColor, 1.f, 0);
	DEVICE->BeginScene();
	EventDispatcher::TriggerEvent(RenderEvent::RenderBegin);

	if (IS_EDITOR)
	{
		m_renderableOpaque = EDIT_SCENE->GetObjectContainer()->GetRenderableOpaqueAll();
	}
	else
	{
		m_renderableOpaque = SCENE->GetObjectContainer()->GetRenderableOpaqueAll();
	}
}

void Renderer::RenderEnd()
{
	EventDispatcher::TriggerEvent(RenderEvent::RenderEnd);
	DEVICE->EndScene();
	DEVICE->Present(nullptr, nullptr, g_hWnd, nullptr);

	//D3DXSaveTextureToFile(L"AlbedoMap.bmp", D3DXIFF_BMP, m_pAlbedoRTTexture, NULL);
	/*D3DXSaveTextureToFile(L"AlbedoMap.bmp", D3DXIFF_BMP, m_pAlbedoRTTexture, NULL);
	D3DXSaveSurfaceToFile(L"ResultMap.bmp", D3DXIFF_BMP, m_pOriginSurface, NULL, NULL);*/
	//D3DXSaveTextureToFile(L"AlbedoMap.bmp", D3DXIFF_BMP, m_pAlbedoRTTexture, NULL);
	//D3DXSaveTextureToFile(L"AlbedoMap.bmp", D3DXIFF_BMP, m_pAlbedoRTTexture, NULL);
	//D3DXSaveTextureToFile(L"Stash.bmp", D3DXIFF_BMP, m_pStashRTTexture, NULL);
	//D3DXSaveTextureToFile(L"ShadowMap.bmp", D3DXIFF_BMP, m_pSoftShadowOriginRTTexture, NULL);
	/*for (int i = 0; i < 4; i++)
	{
		std::wstring test = L"Cascade" + to_wstring(i);

		D3DXSaveTextureToFile((test + L".bmp").c_str(), D3DXIFF_BMP, m_pShadowRTTexture[i], NULL);
	}*/
}

void HyEngine::Renderer::ShowDebugMRT()
{
	m_isDebugRender = true;
}

void HyEngine::Renderer::HideDebugMRT()
{
	m_isDebugRender = false;
}

void HyEngine::Renderer::SetLutFilter(IDirect3DTexture9 * pLutFilterTexture)
{
	m_pLutFilterTexture = pLutFilterTexture;
}

void HyEngine::Renderer::PreparePipeline(Scene * scene)
{
	GetOriginMRT();

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

	/* For Skybox */
	if (scene->GetSkybox() != nullptr)
		scene->GetSkybox()->Render();

	/* Render For GBuffer */
	GeometryPass(scene);

	SetEffectBufferMRT();
	ClearSurface();
	EffectPass(scene);

	/* Create Soft ShadowMap */
	// SoftShadow Origin
	SetSoftShadowOriginMRT();
	SoftShadowPass(scene);
	// SoftShadow Blur
	SetSoftShadowMRT();
	SoftShadowBlurPass(scene);

	//SetOriginMRT();
	SetLightMRT();
	ClearSurface();
	/* Render For Backbuffer */
	LightPass(scene);

	/* Final Blend */
	SetOriginMRT();
	BlendPass();
}

void HyEngine::Renderer::ForwardPipeline(Scene* scene)
{
	SetOriginMRT();
	/* Render Alpha */
	auto& list = scene->GetObjectContainer()->GetRenderableAlphaAll();
	if (list.size() == 0) return;

	std::sort(list.begin(), list.end(), [](GameObject* l, GameObject*r)->bool
	{
		return l->GetRenderQueue() > r->GetRenderQueue();
	});


	for (auto& alpha : list)
	{
		alpha->Render();
	}

	/* Render Collider */
#ifdef _DEBUG
	if (IS_CLIENT)
	{
		bool bRender = ENGINE->CheckRenderOption(RenderOptions::RenderCollider);
		if (bRender == false)
			return;
	}
	auto& colliders = scene->GetObjectContainer()->GetRenderableColliderAll();
	for (auto& collider : colliders)
	{
		collider->Render();
	}
#endif
}

void HyEngine::Renderer::PostRenderPipeline(Scene * scene)
{
	if (IS_CLIENT)
	{
		bool bRender = ENGINE->CheckRenderOption(RenderOptions::RenderPostEffect);
		if (bRender == false)
			return;
	}
	ClearStashSurface();
	DEVICE->StretchRect(m_pOriginSurface, NULL, m_pScreenSurface, NULL, D3DTEXF_NONE);



	/* Post Render Buffer */
	/*SetPRBufferMRT();
	ClearSurface();
	PRBufferPass(scene);*/

	/* Rim Light */
	/*SetRimLightMRT();
	ClearSurface();
	RimLightPass();*/

	/* Brightness */
	SetBrightnessMRT();
	ClearSurface();
	BrightnessPass();

	/* BloomPass */
	SetBloomMRT();
	ClearSurface();
	BloomPass();

	/* Post Render */
	SetPostRenderMRT();
	PostRenderPass();

	
}

void HyEngine::Renderer::DebugPipeline()
{
	m_debugQuads.clear();
	m_debugTextures.clear();

	m_debugQuads.push_back(m_pDepthRTQuad);
	m_debugQuads.push_back(m_pAlbedoRTQuad);
	m_debugQuads.push_back(m_pNormalRTQuad);
	m_debugQuads.push_back(m_pSpecularRTQuad);

	m_debugQuads.push_back(m_pVtxNormalQuad);
	m_debugQuads.push_back(m_pEffectMaskQuad);
	m_debugQuads.push_back(m_pEffectParamQuad);
	m_debugQuads.push_back(m_pRimLightColorQuad);

	m_debugQuads.push_back(m_pCascadeShadowQuad0);
	m_debugQuads.push_back(m_pCascadeShadowQuad1);
	m_debugQuads.push_back(m_pShadowOriginQuad);
	m_debugQuads.push_back(m_pShadowBlurQuad);

	m_debugQuads.push_back(m_pLightIntensityQuad);
	m_debugQuads.push_back(m_pAmbientIntensityQuad);
	m_debugQuads.push_back(m_pSpecularIntensityQuad);
	m_debugQuads.push_back(m_pRimLightQuad);

	m_debugQuads.push_back(m_pBrightnessQuad);
	m_debugQuads.push_back(m_pBloomQuad);

	m_debugTextures.push_back(m_pDepthRTTexture);
	m_debugTextures.push_back(m_pAlbedoRTTexture);
	m_debugTextures.push_back(m_pNormalRTTexture);
	m_debugTextures.push_back(m_pSpecularRTTexture);

	m_debugTextures.push_back(m_pVtxNormalRTTexture);
	m_debugTextures.push_back(m_pEffectMaskRTTexture);
	m_debugTextures.push_back(m_pEffectParamRTTexture);
	m_debugTextures.push_back(m_pRimLightColorRTTexture);

	m_debugTextures.push_back(m_pShadowRTTexture[0]);
	m_debugTextures.push_back(m_pShadowRTTexture[1]);
	m_debugTextures.push_back(m_pSoftShadowOriginRTTexture);
	m_debugTextures.push_back(m_pSoftShadowRTTexture);

	m_debugTextures.push_back(m_pLightIntensityRTTexture);
	m_debugTextures.push_back(m_pAmbientIntensityRTTexture);
	m_debugTextures.push_back(m_pSpecularIntensityRTTexture);
	m_debugTextures.push_back(m_pRimLightRTTexture);

	m_debugTextures.push_back(m_pBrightnessTexture);
	m_debugTextures.push_back(m_pBloomRTTexture);

	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"DebugMRT", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"DebugMRT", &pShader);
	assert(pShader);

	assert(m_debugQuads.size() == m_debugTextures.size());
	for (UINT i = 0; i < m_debugQuads.size(); i++)
	{
		DEVICE->SetStreamSource(0, m_debugQuads[i]->_vb, 0, m_debugQuads[i]->vertexSize);
		DEVICE->SetFVF(VTXSCREEN::FVF);
		//DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
		DEVICE->SetIndices(m_debugQuads[i]->_ib);

		D3DXHANDLE renderTargetHandle = pShader->GetParameterByName(0, "RenderTargetTex");
		pShader->SetTexture(renderTargetHandle, m_debugTextures[i]);

		pShader->SetTechnique("DebugMRT");
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

void HyEngine::Renderer::SetEffectBufferMRT()
{
	DEVICE->SetRenderTarget(0, m_pVtxNormalRTSurface);
	DEVICE->SetRenderTarget(1, m_pEffectMaskRTSurface);
	DEVICE->SetRenderTarget(2, m_pEffectParamRTSurface);
	DEVICE->SetRenderTarget(3, m_pRimLightColorRTSurface);
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
	/* 지우기 */
	assert(false);
}

void HyEngine::Renderer::SetSoftShadowMRT()
{
	DEVICE->SetRenderTarget(0, m_pSoftShadowRTSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}

void HyEngine::Renderer::SetLightMRT()
{
	DEVICE->SetRenderTarget(0, m_pLightIntensityRTSurface);
	DEVICE->SetRenderTarget(1, m_pAmbientIntensityRTSurface);
	DEVICE->SetRenderTarget(2, m_pSpecularIntensityRTSurface);
	DEVICE->SetRenderTarget(3, m_pRimLightRTSurface);
}

void HyEngine::Renderer::SetPRBufferMRT()
{
	DEVICE->SetRenderTarget(0, m_pVtxNormalRTSurface);
	DEVICE->SetRenderTarget(1, m_pEffectMaskRTSurface);
	DEVICE->SetRenderTarget(2, m_pEffectParamRTSurface);
	DEVICE->SetRenderTarget(3, m_pBloomRTSurface);
}

void HyEngine::Renderer::SetPostRenderMRT()
{
	DEVICE->SetRenderTarget(0, m_pOriginSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}

void HyEngine::Renderer::SetRimLightMRT()
{
	DEVICE->SetRenderTarget(0, m_pRimLightRTSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}

void HyEngine::Renderer::SetBrightnessMRT()
{
	DEVICE->SetRenderTarget(0, m_pBrightnessSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}

void HyEngine::Renderer::SetBloomMRT()
{
	DEVICE->SetRenderTarget(0, m_pBloomRTSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}

void HyEngine::Renderer::GeometryPass(Scene * scene)
{
	//auto& list = scene->GetObjectContainer()->GetRenderableOpaqueAll();
	/* 
	여기서 Dynamic과 Static이 분리될것
	Static은 Instancing을 통해 같은 종류끼리 묶어서 
	drawcall을 줄인다.
	*/
	/*
	auto& staticMeshes = scene->GetObjectContainer()->GetStaticMeshAll();
	auto& renderableStatic = cpplinq::from_iterators(staticMeshes.begin(), staticMeshes.end())
		>> cpplinq::where([&](GameObject* obj)
	{
		if (obj->GetActive() == false) return false;
		if (obj->m_bWantsDestroy == true) return false;
		if (obj->GetViewFrustumCulled() == true) return false;
		return true;
	}) >> cpplinq::to_vector();
	std::cout << "Renderable Count : " << renderableStatic.size() << std::endl;
	for (auto& staticMesh : renderableStatic)
	{
		Mesh* mesh = static_cast<Mesh*>(staticMesh);
		mesh->Render();

	}
	auto& dynamicMeshes = scene->GetObjectContainer()->GetDynamicMeshAll();
	for (auto& dynamicMesh : dynamicMeshes)
	{
		Mesh* mesh = static_cast<Mesh*>(dynamicMesh);
		mesh->Render();

	}*/
	auto& list = m_renderableOpaque;
	//auto& list = scene->GetObjectContainer()->GetStaticMeshAll();
#ifdef _DEBUG
	//std::cout << "Renderable Count : " << list.size() << std::endl;
#endif
	if (list.size() == 0) return;
	for (auto& opaque : list)
	{
		//if (opaque->GetActive() == false) continue;
		//if (opaque->GetViewFrustumCulled() == true) continue;
		//Mesh* mesh = dynamic_cast<Mesh*>(opaque);
		/*if (mesh != nullptr && mesh->IsOcclusionCulled() == true)
		{
			continue;
		}*/
		opaque->Render();
	}

}

void HyEngine::Renderer::EffectPass(Scene * scene)
{
	ID3DXEffect* pEffect = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"EffectBuffer", &pEffect);
	else
		EDIT_ENGINE->TryGetShader(L"EffectBuffer", &pEffect);
	assert(pEffect);

	auto& opaquelist = m_renderableOpaque;
	for (auto& opaque : opaquelist)
	{
		if (opaque->IsRenderEffect() == false)
			continue;

		/* For Rim Light */
		bool isRimLight = opaque->IsRenderEffect(RenderEffectOption::RimLight) ? true : false;
		if (isRimLight == true)
			pEffect->SetInt("RimLightFactor", 1);
		else
			pEffect->SetInt("RimLightFactor", 0);
		//pEffect->SetBool("IsRimLight", isRimLight);
		pEffect->SetFloat("RimLightWidth", opaque->GetRimWidth());

		pEffect->SetValue("RimLightColor", &opaque->GetRimColor(), sizeof(opaque->GetRimColor()));

		pEffect->SetMatrix("WorldMatrix", &opaque->GetWorldMatrix());
		if (IS_CLIENT)
		{
			pEffect->SetMatrix("ViewMatrix", &CAMERA->GetViewMatrix());
			pEffect->SetMatrix("ProjMatrix", &CAMERA->GetProjectionMatrix());
		}
		else if (IS_EDITOR)
		{
			pEffect->SetMatrix("ViewMatrix", &EDIT_CAMERA->GetViewMatrix());
			pEffect->SetMatrix("ProjMatrix", &EDIT_CAMERA->GetProjectionMatrix());
		}
		DynamicMesh * pDynamicMesh = dynamic_cast<DynamicMesh*>(opaque);
		if (pDynamicMesh && pDynamicMesh->GetSkinningType() == ESkinningType::HardwareSkinning)
		{
			pEffect->SetTechnique("EffectBuffer_Skinned");
		}
		else
			pEffect->SetTechnique("EffectBuffer");
		pEffect->Begin(0, 0);
		{
			pEffect->BeginPass(0);


			opaque->DrawPrimitive(pEffect);
			pEffect->EndPass();
		}
		pEffect->End();
	}

	auto& alphaList = scene->GetObjectContainer()->GetRenderableAlphaAll();
	for (auto& alpha : alphaList)
	{
		if (alpha->IsRenderEffect() == false)
			continue;

		/* For Rim Light */
		bool isRimLight = alpha->IsRenderEffect(RenderEffectOption::RimLight) ? true : false;
		if (isRimLight == true)
			pEffect->SetInt("RimLightFactor", 1);
		else
			pEffect->SetInt("RimLightFactor", 0);
		pEffect->SetBool("IsRimLight", isRimLight);
		pEffect->SetFloat("RimLightWidth", alpha->GetRimWidth());

		pEffect->SetValue("RimLightColor", &alpha->GetRimColor(), sizeof(alpha->GetRimColor()));

		pEffect->SetMatrix("WorldMatrix", &alpha->GetWorldMatrix());
		if (IS_CLIENT)
		{
			pEffect->SetMatrix("ViewMatrix", &CAMERA->GetViewMatrix());
			pEffect->SetMatrix("ProjMatrix", &CAMERA->GetProjectionMatrix());
		}
		else if (IS_EDITOR)
		{
			pEffect->SetMatrix("ViewMatrix", &EDIT_CAMERA->GetViewMatrix());
			pEffect->SetMatrix("ProjMatrix", &EDIT_CAMERA->GetProjectionMatrix());
		}
		pEffect->SetTechnique("EffectBuffer");
		pEffect->Begin(0, 0);
		{
			pEffect->BeginPass(0);


			alpha->DrawPrimitive(pEffect);
			pEffect->EndPass();
		}
		pEffect->End();

	}
}

void HyEngine::Renderer::AmbientPass(Scene * scene)
{
	/* 임시 데이터 */
	float ambientFactor = 0.4f;// 0.5f;

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	D3DXMATRIX viewMatrixInv;
	D3DXMATRIX projMatrixInv;

	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
	DEVICE->SetIndices(m_pResultScreen->_ib);

	D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 10);
	//D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
	D3DXMatrixIdentity(&viewMatrix);

	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"Ambient", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"Ambient", &pShader);
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
	DEVICE->StretchRect(m_pOriginSurface, NULL, m_pStashRTSurface, NULL,D3DTEXF_NONE/*D3DTEXF_POINT*/);
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
		DEVICE->SetFVF(VTXSCREEN::FVF);
		//DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
		DEVICE->SetIndices(m_pResultScreen->_ib);

		//D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 1000);
		//D3DXMatrixIdentity(&worldMatrix);
		//D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
		D3DXMatrixIdentity(&projMatrix);
		D3DXMatrixIdentity(&worldMatrix);

		D3DXMatrixIdentity(&viewMatrix);


		/* shader load */
		ID3DXEffect* pShader = nullptr;

		/* 테스트용 */
		if (light->Type() == ELightType::POINT)
		{
			if (IS_CLIENT)
			{
				bool bRender = ENGINE->CheckRenderOption(RenderOptions::RenderLight);
				if (bRender == false)
					continue;
			}

			if (ENGINE)
				ENGINE->TryGetShader(L"PointLight", &pShader);
			else
				EDIT_ENGINE->TryGetShader(L"PointLight", &pShader);
		}
		else if (light->Type() == ELightType::DIRECTIONAL)
		{
			if (ENGINE)
				ENGINE->TryGetShader(L"DirectionalLight", &pShader);
			else
				EDIT_ENGINE->TryGetShader(L"DirectionalLight", &pShader);
		}
		else if (light->Type() == ELightType::SPOT)
		{
			if (IS_CLIENT)
			{
				bool bRender = ENGINE->CheckRenderOption(RenderOptions::RenderLight);
				if (bRender == false)
					continue;
			}

			if (ENGINE)
				ENGINE->TryGetShader(L"SpotLight", &pShader);
			else
				EDIT_ENGINE->TryGetShader(L"SpotLight", &pShader);
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

		if (light->Type() == ELightType::DIRECTIONAL)
		{
			D3DXHANDLE vtxNormalHandle = pShader->GetParameterByName(0, "VtxNormalTex");
			pShader->SetTexture(vtxNormalHandle, m_pVtxNormalRTTexture);

			D3DXHANDLE effectMaskHandle = pShader->GetParameterByName(0, "EffectMaskTex");
			pShader->SetTexture(effectMaskHandle, m_pEffectMaskRTTexture);

			D3DXHANDLE effectParamHandle = pShader->GetParameterByName(0, "EffectParamTex");
			pShader->SetTexture(effectParamHandle, m_pEffectParamRTTexture);
		
			D3DXHANDLE rimLightColorHandle = pShader->GetParameterByName(0, "RimLightColorTex");
			pShader->SetTexture(rimLightColorHandle, m_pRimLightColorRTTexture);
		}

		/* For CascadeShadowMapping */
		/*if (NUM_CASCADEDES > 0)
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
		}*/


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
		//DEVICE->StretchRect(m_pLightRTSurface, NULL, m_pStashRTSurface,NULL, D3DTEXF_NONE/* NULL,D3DTEXF_POINT*//*  D3DTEXF_NONE*/);
	}
}

void HyEngine::Renderer::ShadowPass(Scene * scene, int cascadeIndex)
{
	if (IS_CLIENT)
	{
		bool bRender = ENGINE->CheckRenderOption(RenderOptions::RenderShadow);
		if (bRender == false)
			return;
	}

	/* shader load */
	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"ShadowMap", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"ShadowMap", &pShader);

	/* Get Selected Cam */
	Camera* pSelectedCam = nullptr;
	pSelectedCam = scene->GetSelectedCamera();
	assert(pSelectedCam);

	/* Find Directional Light */
	// Shadow는 directional만 영향을 받는다.
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
	int numCascades = 4; // 4개 분할 
						 /* cascadedEnds[NUM_CASCADES + 1] = {0.0f, 0.2f, 0.4f, 1.0f} */
	//float cascadedEnds[NUM_CASCADEDES + 1] = { 0.0f, 0.1f, 0.3f, 0.6f, 1.0f };
	//float cascadedEnds[NUM_CASCADEDES + 1] = { 0.0f, 0.4f, 0.25f, 0.5f, 1.0f };
	//float cascadedEnds[NUM_CASCADEDES + 1] = { 0.0f, 0.5f,  1.0f };
	//float cascadedEnds[NUM_CASCADEDES + 1] = { 0.0f, 0.05f, 0.1f, 0.2f, 1.0f };
	//float cascadedEnds[NUM_CASCADEDES + 1] = { 0.0f, 0.4f, 1.0f};//, 1.0f }; origin
	float cascadedEnds[NUM_CASCADEDES + 1] = { 0.0f, 0.4f, 1.0f };
	//float cascadedEnds[NUM_CASCADEDES + 1] = { 0.0f, 0.2f };// , 0.1f, 0.15f, 0.2f
//};//, 0.2f, 1.0f };
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

	/* Unit Cube의 각 코너 위치를 Slice에 맞게 설정 */
	// 임시로 한개의 cascade만 생성
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
	sphereRadius = D3DXVec3Length(&(frustumCorners[0] - frustumCenter));
	float maxRadius = D3DXVec3Length(&(frustumCorners[4] - frustumCenter));
	/*for (int i = 0; i < 8; i++)
	{
		float dist = D3DXVec3Length(&(frustumCorners[i] - frustumCenter));
		sphereRadius = std::max(sphereRadius, dist);
	}*/

	// Calculate AABB with the radius of the bound spherer
	D3DXVECTOR3 mins = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	D3DXVECTOR3 maxes = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	sphereRadius = std::ceil(sphereRadius * 16.0f) / 16.0f;
	maxes = D3DXVECTOR3(sphereRadius, sphereRadius, sphereRadius);
	mins = -maxes;

	// Calculate the Scale of aabb
	//D3DXVECTOR3 cascadedExtents = max - min.z;

	/* Calcualte the ShadowMap Position */
	// frustum 중심에서 light 반대방향으로 min.z만큼 이동
	D3DXVECTOR3 normalizedDirection;
	D3DXVec3Normalize(&normalizedDirection, &directionalLight->Direction());
	D3DXVECTOR3 shadowCameraPos = frustumCenter - normalizedDirection * std::fabs(700/*mins.z*/);

	D3DXMATRIX lightViewMatrix;
	D3DXMATRIX lightProjMatrix;

	/* Light View Matrix */
	D3DXMatrixLookAtLH(&lightViewMatrix,
		&shadowCameraPos,
		&frustumCenter,
		&Vector3::Up);

	D3DXMatrixOrthoOffCenterLH(&lightProjMatrix, mins.x, maxes.x, mins.y, maxes.y, 0, 1500/*maxRadius + maxRadius*/);


	m_lightViewMat[cascadeIndex] = lightViewMatrix;
	m_lightProjMat[cascadeIndex] = lightProjMatrix;

#pragma endregion

	//pSelectedCam->BeginFrustumCull(lightViewMatrix, lightProjMatrix);

	auto& list = scene->GetObjectContainer()->GetRenderableOpaqueAll();
	if (list.size() == 0) return;

	for (auto& opaque : list)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(opaque);
		if (mesh != nullptr && mesh->IsOcclusionCulled() == true)
		{
			continue;
		}
		//bool culled = pSelectedCam->FrustumCulling(opaque);
		//if (culled) continue;

		pShader->SetValue("WorldMatrix", &opaque->m_pTransform->GetWorldMatrix(), sizeof(opaque->m_pTransform->GetWorldMatrix()));


		pShader->SetValue("LightViewMatrix", &m_lightViewMat[cascadeIndex], sizeof(m_lightViewMat[cascadeIndex]));
		pShader->SetValue("LightProjMatrix", &m_lightProjMat[cascadeIndex], sizeof(m_lightProjMat[cascadeIndex]));
		pShader->SetBool("IsSkinnedMesh", false);
		pShader->SetBool("IsMasked", false);
		pShader->SetTechnique("ShadowMap");
		pShader->Begin(0, 0);
		{
			pShader->BeginPass(0);
			opaque->DrawPrimitive(pShader);
			pShader->EndPass();

		}
		pShader->End();

	}
	
	//pSelectedCam->EndFrustumCull();
}

void HyEngine::Renderer::SoftShadowPass(Scene * scene)
{
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET, 0xffffffff, 1.0f, 0);
	if (IS_CLIENT)
	{
		bool bRender = ENGINE->CheckRenderOption(RenderOptions::RenderShadow);
		if (bRender == false)
			return;
	}

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
	//D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 100);
	////D3DXMatrixIdentity(&worldMatrix);
	//D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
	D3DXMatrixIdentity(&projMatrix);
	D3DXMatrixIdentity(&worldMatrix);

	D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixIdentity(&viewMatrix);


	/* Set Stream */
	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetFVF(VTXSCREEN::FVF);
	//DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
	DEVICE->SetIndices(m_pResultScreen->_ib);

	/* Shader Load */
	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"SoftShadowMapping", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"SoftShadowMapping", &pShader);
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


	/* Shadow Map Sort */
	// 카메라 방향벡터와 광원의 방향을 내적해서
	// 양수면 그대로, 음수면 순서 거꾸로

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	D3DXMATRIX viewInv = selectedCam->GetViewMatrix();
	D3DXMatrixInverse(&viewInv, NULL, &viewInv);
	identity = identity * viewInv;
	D3DXVECTOR3 camDir;
	memcpy(&camDir, &identity.m[2][0], sizeof(D3DXVECTOR3));
	//D3DXVECTOR3 temp2 = D3DXVECTOR3(0, 0, 0);

	camDir.y = 0;
	D3DXVec3Normalize(&camDir, &camDir);
	
	//D3DXVec3Normalize(&camDir, &camDir);
	D3DXVECTOR3 lightDir = directionalLight->Direction();
	lightDir.y = 0;
	//D3DXVec3TransformNormal(&lightDir, &lightDir, &viewInv);
	////lightDir.y = 0;
	D3DXVec3Normalize(&lightDir, &lightDir);
	float temp = D3DXVec3Dot(&camDir, &lightDir);
	//std::cout << "Test : " << temp << std::endl;
	bool isReverse = false;
	/*if (temp > 0)
		isReverse = false;
	else
		isReverse = true;*/

	D3DXMATRIX lightViewMat[NUM_CASCADEDES];
	D3DXMATRIX lightProjMat[NUM_CASCADEDES];

	if (isReverse)
	{
		for (int i = 0; i < NUM_CASCADEDES; i++)
		{
			lightViewMat[i] = m_lightViewMat[NUM_CASCADEDES - 1 - i];
			lightProjMat[i] = m_lightProjMat[NUM_CASCADEDES - 1 - i];
		}
	}
	else
	{
		for (int i = 0; i < NUM_CASCADEDES; i++)
		{
			lightViewMat[i] = m_lightViewMat[i];
			lightProjMat[i] = m_lightProjMat[i];
		}
	}


	pShader->SetMatrixArray("LightViewMatrix", lightViewMat, NUM_CASCADEDES);
	pShader->SetMatrixArray("LightProjMatrix", lightProjMat, NUM_CASCADEDES);

	

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
		if (isReverse)
		{
			D3DXHANDLE shadowMapHandler0 = pShader->GetParameterByName(0, "ShadowDepthTex0");
			pShader->SetTexture(shadowMapHandler0, m_pShadowRTTexture[NUM_CASCADEDES - 1]);
		}
		else
		{
			D3DXHANDLE shadowMapHandler0 = pShader->GetParameterByName(0, "ShadowDepthTex0");
			pShader->SetTexture(shadowMapHandler0, m_pShadowRTTexture[0]);
		}
	}
	if (NUM_CASCADEDES > 1)
	{
		if (isReverse)
		{
			D3DXHANDLE shadowMapHandler1 = pShader->GetParameterByName(0, "ShadowDepthTex1");
			pShader->SetTexture(shadowMapHandler1, m_pShadowRTTexture[NUM_CASCADEDES - 2]);
		}
		else
		{
			D3DXHANDLE shadowMapHandler1 = pShader->GetParameterByName(0, "ShadowDepthTex1");
			pShader->SetTexture(shadowMapHandler1, m_pShadowRTTexture[1]);
		}
	}
	if (NUM_CASCADEDES > 2)
	{
		if (isReverse)
		{
			D3DXHANDLE shadowMapHandler2 = pShader->GetParameterByName(0, "ShadowDepthTex2");
			pShader->SetTexture(shadowMapHandler2, m_pShadowRTTexture[NUM_CASCADEDES - 3]);
		}
		else
		{
			D3DXHANDLE shadowMapHandler2 = pShader->GetParameterByName(0, "ShadowDepthTex2");
			pShader->SetTexture(shadowMapHandler2, m_pShadowRTTexture[2]);
		}
	}
	/*if (NUM_CASCADEDES > 3)
	{
		D3DXHANDLE shadowMapHandler3 = pShader->GetParameterByName(0, z"ShadowDepthTex3");
		if(isReverse)
			pShader->SetTexture(shadowMapHandler3, m_pShadowRTTexture[(NUM_CASCADEDES - 1) - 3]);
		else
			pShader->SetTexture(shadowMapHandler3, m_pShadowRTTexture[3]);
	}*/
	pShader->SetTechnique("SoftShadowMapping");
	pShader->Begin(0, 0);
	{
		for (int i = 0; i < NUM_CASCADEDES; i++)
		{
			pShader->BeginPass(i);
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
	}
	pShader->End();
}

void HyEngine::Renderer::SoftShadowBlurPass(Scene * scene)
{

	/* Set Stream */
	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetFVF(VTXSCREEN::FVF);
	//DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
	DEVICE->SetIndices(m_pResultScreen->_ib);

	/* Shader Load */
	ID3DXEffect* pShader = nullptr;

	if (ENGINE)
		ENGINE->TryGetShader(L"Blur", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"Blur", &pShader);

	assert(pShader);

	/* World, View, Porj */
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;
	
	/* Set Matrices */
	//D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 1000);
	////D3DXMatrixIdentity(&worldMatrix);
	//D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
	//D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixIdentity(&projMatrix);
	D3DXMatrixIdentity(&worldMatrix);

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

void HyEngine::Renderer::LinearFilterPass()
{
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetFVF(VTXSCREEN::FVF);
	//DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
	DEVICE->SetIndices(m_pResultScreen->_ib);


	D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 1000);
	D3DXMatrixIdentity(&worldMatrix);
	//D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
	D3DXMatrixIdentity(&viewMatrix);

	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"LinearFilter", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"LinearFilter", &pShader);
	assert(pShader);

	pShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	pShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	pShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));


	/* Albedo */
	D3DXHANDLE stashHandle = pShader->GetParameterByName(0, "StashTex");
	pShader->SetTexture(stashHandle, m_pStashRTTexture);


	pShader->SetTechnique("LinearFilter");
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
	//DEVICE->StretchRect(m_pOriginSurface, NULL, m_pStashRTSurface, NULL, D3DTEXF_NONE);
}

void HyEngine::Renderer::LutFilterPass()
{
	if (m_pLutFilterTexture == nullptr)
		return;

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetFVF(VTXSCREEN::FVF);
	//DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
	DEVICE->SetIndices(m_pResultScreen->_ib);


	//D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 1000);
	D3DXMatrixIdentity(&projMatrix);
	D3DXMatrixIdentity(&worldMatrix);
	//D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
	D3DXMatrixIdentity(&viewMatrix);

	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"LUTFilter", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"LUTFilter", &pShader);
	assert(pShader);

	pShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	pShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	pShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));

	DEVICE->StretchRect(m_pOriginSurface, NULL, m_pStashRTSurface, NULL, D3DTEXF_LINEAR/* NULL,D3DTEXF_POINT*//*  D3DTEXF_NONE*/);


	/* Albedo */
	D3DXHANDLE stashHandle = pShader->GetParameterByName(0, "ScreenTex");
	pShader->SetTexture(stashHandle, m_pStashRTTexture);

	D3DXHANDLE lutFilterHandle = pShader->GetParameterByName(0, "LutTex");
	pShader->SetTexture(lutFilterHandle, m_pLutFilterTexture);


	pShader->SetTechnique("LutFilter");
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

void HyEngine::Renderer::PRBufferPass(Scene * pScene)
{
	//ID3DXEffect* pEffect = nullptr;
	//if (ENGINE)
	//	ENGINE->TryGetShader(L"PRBuffer", &pEffect);
	//else
	//	EDIT_ENGINE->TryGetShader(L"PRBuffer", &pEffect);
	//assert(pEffect);

	//auto& opaquelist = m_renderableOpaque;
	//for (auto& opaque : opaquelist)
	//{
	//	if (opaque->IsPostRender() == false)
	//		continue;

	//	/* For Rim Light */
	//	bool isRimLight = opaque->IsPostRender(RenderEffectOption::RimLight) ? true : false;
	//	if (isRimLight == true)
	//		pEffect->SetInt("RimLightFactor", 1);
	//	else
	//		pEffect->SetInt("RimLightFactor", 0);
	//	pEffect->SetBool("IsRimLight", isRimLight);
	//	pEffect->SetFloat("RimLightWidth", opaque->GetRimWidth());

	//	///* For Bloom */
	//	//bool isBloom = opaque->IsPostRender(RenderEffectOption::Bloom) ? true : false;
	//	//if (isBloom == true)
	//	//	pEffect->SetInt("BloomFactor", 1);
	//	//else
	//	//	pEffect->SetInt("BloomFactor", 0);


	//	//Mesh* mesh = dynamic_cast<Mesh*>(opaque);
	//	opaque->PostRender(pEffect);
	//}

	//auto& alphaList = pScene->GetObjectContainer()->GetRenderableAlphaAll();
	//for (auto& alpha : alphaList)
	//{
	//	if (alpha->IsPostRender() == false)
	//		continue;

	//	/* For Rim Light */
	//	bool isRimLight = alpha->IsPostRender(RenderEffectOption::RimLight) ? true : false;
	//	if (isRimLight == true)
	//		pEffect->SetInt("RimLightFactor", 1);
	//	else
	//		pEffect->SetInt("RimLightFactor", 0);
	//	pEffect->SetBool("IsRimLight", isRimLight);
	//	pEffect->SetFloat("RimLightWidth", alpha->GetRimWidth());


	//	///* For Bloom */
	//	//bool isBloom = alpha->IsPostRender(RenderEffectOption::Bloom) ? true : false;
	//	//if (isBloom == true)
	//	//	pEffect->SetInt("BloomFactor", 1);
	//	//else
	//	//	pEffect->SetInt("BloomFactor", 0);


	//	alpha->PostRender(pEffect);
	//}
}

void HyEngine::Renderer::RimLightPass()
{
	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetFVF(VTXSCREEN::FVF);
	DEVICE->SetIndices(m_pResultScreen->_ib);

	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"RimLight", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"RimLight", &pShader);
	assert(pShader);

	D3DXMATRIX viewMatrixInv;
	D3DXMATRIX projMatrixInv;

	if (IS_CLIENT)
	{
		D3DXMatrixInverse(&viewMatrixInv, NULL, &CAMERA->GetViewMatrix());
		D3DXMatrixInverse(&projMatrixInv, NULL, &CAMERA->GetProjectionMatrix());
	}
	else if (IS_EDITOR)
	{
		D3DXMatrixInverse(&viewMatrixInv, NULL, &EDIT_CAMERA->GetViewMatrix());
		D3DXMatrixInverse(&projMatrixInv, NULL, &EDIT_CAMERA->GetProjectionMatrix());
	}

	pShader->SetValue("ViewMatrixInv", &viewMatrixInv, sizeof(viewMatrixInv));
	pShader->SetValue("ProjMatrixInv", &projMatrixInv, sizeof(projMatrixInv));

	if (IS_CLIENT)
	{
		pShader->SetValue("EyePosition", &CAMERA->m_pTransform->m_position, sizeof(CAMERA->m_pTransform->m_position));
	}
	if(IS_EDITOR)
	{
		pShader->SetValue("EyePosition", &EDIT_CAMERA->m_pTransform->m_position, sizeof(EDIT_CAMERA->m_pTransform->m_position));
	}

	/* DepthTex */
	D3DXHANDLE depthHandle = pShader->GetParameterByName(0, "DepthTex");
	pShader->SetTexture(depthHandle, m_pDepthRTTexture);

	/* VtxNormalTex */
	D3DXHANDLE vtxNormalHandle = pShader->GetParameterByName(0, "VtxNormalTex");
	pShader->SetTexture(vtxNormalHandle, m_pVtxNormalRTTexture);

	/* EffectMaskTex */
	D3DXHANDLE effectMaskHandle = pShader->GetParameterByName(0, "EffectMaskTex");
	pShader->SetTexture(effectMaskHandle, m_pEffectMaskRTTexture);

	/* EffectParamTex */
	D3DXHANDLE effectParamHandle = pShader->GetParameterByName(0, "EffectParamTex");
	pShader->SetTexture(effectParamHandle, m_pEffectParamRTTexture);

	/* LightIntensityTex */
	D3DXHANDLE lightIntensityHandle = pShader->GetParameterByName(0, "LightIntensityTex");
	pShader->SetTexture(lightIntensityHandle, m_pLightIntensityRTTexture);

	pShader->SetTechnique("RimLight");
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

void HyEngine::Renderer::BrightnessPass()
{
	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetFVF(VTXSCREEN::FVF);
	DEVICE->SetIndices(m_pResultScreen->_ib);

	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"Brightness", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"Brightness", &pShader);
	assert(pShader);

	/* DepthTex */
	D3DXHANDLE screenHandle = pShader->GetParameterByName(0, "ScreenTex");
	pShader->SetTexture(screenHandle, m_pScreenTexture);

	pShader->SetTechnique("Brightness");
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

void HyEngine::Renderer::BloomPass()
{
	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetFVF(VTXSCREEN::FVF);
	DEVICE->SetIndices(m_pResultScreen->_ib);

	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"Bloom", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"Bloom", &pShader);
	assert(pShader);

	/* DepthTex */
	D3DXHANDLE sourceHandle = pShader->GetParameterByName(0, "SourceTex");
	pShader->SetTexture(sourceHandle, m_pBrightnessTexture);

	pShader->SetTechnique("Bloom");
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

void HyEngine::Renderer::PostRenderPass()
{
	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetFVF(VTXSCREEN::FVF);
	DEVICE->SetIndices(m_pResultScreen->_ib);

	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"PostRender", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"PostRender", &pShader);
	assert(pShader);

	/* RimLight */
	//D3DXHANDLE rimLightHandle = pShader->GetParameterByName(0, "RimLightTex");
	//pShader->SetTexture(rimLightHandle, m_pRimLightRTTexture);
	
	/* Bloom */
	D3DXHANDLE bloomHandle = pShader->GetParameterByName(0, "BloomTex");
	pShader->SetTexture(bloomHandle, m_pBloomRTTexture);

	

	pShader->SetTechnique("PostRender");
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

void HyEngine::Renderer::BlendPass()
{
	

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	DEVICE->SetStreamSource(0, m_pResultScreen->_vb, 0, m_pResultScreen->vertexSize);
	DEVICE->SetFVF(VTXSCREEN::FVF);
	//DEVICE->SetVertexDeclaration(m_pResultScreen->m_pDeclare);
	DEVICE->SetIndices(m_pResultScreen->_ib);


	//D3DXMatrixOrthoLH(&projMatrix, WinMaxWidth, WinMaxHeight, 0, 1000);
	D3DXMatrixIdentity(&projMatrix);
	D3DXMatrixIdentity(&worldMatrix);
	//D3DXMatrixScaling(&worldMatrix, WinMaxWidth, WinMaxHeight, 1);
	D3DXMatrixIdentity(&viewMatrix);

	ID3DXEffect* pShader = nullptr;
	if (ENGINE)
		ENGINE->TryGetShader(L"DeferredBlend", &pShader);
	else
		EDIT_ENGINE->TryGetShader(L"DeferredBlend", &pShader);
	assert(pShader);

	pShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	pShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	pShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));

	DEVICE->StretchRect(m_pOriginSurface, NULL, m_pStashRTSurface, NULL, D3DTEXF_LINEAR/* NULL,D3DTEXF_POINT*//*  D3DTEXF_NONE*/);


	/* Albedo */
	D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
	pShader->SetTexture(albedoHandle, m_pAlbedoRTTexture);

	/* Light */
	D3DXHANDLE lightIntensityHandle = pShader->GetParameterByName(0, "LightIntensityTex");
	pShader->SetTexture(lightIntensityHandle, m_pLightIntensityRTTexture);

	D3DXHANDLE ambientIntensityHandle = pShader->GetParameterByName(0, "AmbientIntensityTex");
	pShader->SetTexture(ambientIntensityHandle, m_pAmbientIntensityRTTexture);

	D3DXHANDLE specularIntensityHandle = pShader->GetParameterByName(0, "SpecularIntensityTex");
	pShader->SetTexture(specularIntensityHandle, m_pSpecularIntensityRTTexture);

	/* Post Render */
	D3DXHANDLE rimLightHandle = pShader->GetParameterByName(0, "RimLightTex");
	pShader->SetTexture(rimLightHandle, m_pRimLightRTTexture);


	D3DXHANDLE lutFilterHandle = pShader->GetParameterByName(0, "LutTex");
	pShader->SetTexture(lutFilterHandle, m_pLutFilterTexture);


	if (m_pLutFilterTexture)
	{
		pShader->SetTechnique("DeferredBlendWithLUTFilter");
	}
	else
	{
		pShader->SetTechnique("DeferredBlend");
	}
	
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
	pRenderer->SetupOcclusion();
	return pRenderer;
}

void HyEngine::Renderer::Release(Renderer * pRenderer)
{
	pRenderer->Cleanup();
	SAFE_DELETE(pRenderer);
}

