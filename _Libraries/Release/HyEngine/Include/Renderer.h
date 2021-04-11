#pragma once

#include "IRenderable.h"

/* For Cascade Shadow */
#define NUM_CASCADEDES 4

namespace HyEngine
{
	/*
	Renderer는 Render관련 모든 기능을 수행한다.
	*/
	class ENGINE_DLL Renderer
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTUR & DESTRUCTOR 
		//////////////////////////////////////////////////////////////////////////
	private:
		Renderer() = default;
		~Renderer() = default;

	public:
		void Setup();
		void Cleanup();
		void ClearBackBuffer();
		void ClearStashSurface();

	public: /* For Render */
		void Render(Scene* scene);
		void RenderBegin();
		void RenderEnd();

		//////////////////////////////////////////////////////////////////////////
		// PIPELINES
		//////////////////////////////////////////////////////////////////////////
	private:
		/* For ShaderMap */
		void PreparePipeline(Scene* scene);
		/* For Lights */
		void DeferredPipeline(Scene* scene);
		/* For Alpha */
		void ForwardPipeline(Scene* scene);



		//////////////////////////////////////////////////////////////////////////
		// DEFERRED METHODES
		//////////////////////////////////////////////////////////////////////////
	private:
		/* For Multi Render Target */
		void SetGBufferMRT();
		void SetOriginMRT();
		void SetShadowMapMRT(int cascadeIndex);
		void GetOriginMRT();
		/* For SoftShadow */
		void SetSoftShadowOriginMRT();
		void SetSoftShadowBlurXMRT();
		void SetSoftShadowMRT();

	private :
		void GeometryPass(Scene* scene);
		void AmbientPass(Scene* scene);
		void LightPass(Scene* scene);
		void ShadowPass(Scene * scene, int casecadeIndex);
		void SoftShadowPass(Scene* scene);
		void SoftShadowBlurPass(Scene* scene);

		//////////////////////////////////////////////////////////////////////////
		// FORWARD VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private:



		//////////////////////////////////////////////////////////////////////////
		// DEFERRED VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private: /* RenderTarget Textures*/
		// depth : rgb에 emissive.rgb, a에 depth값이 저장된다.
		IDirect3DTexture9 * m_pDepthRTTexture = nullptr;
		IDirect3DTexture9 * m_pAlbedoRTTexture = nullptr;
		IDirect3DTexture9 * m_pNormalRTTexture = nullptr;
		IDirect3DTexture9 * m_pSpecularRTTexture = nullptr;
		IDirect3DTexture9 * m_pShadowRTTexture[NUM_CASCADEDES] = {nullptr};

	private: /* RenderTarget Surfaces */
		IDirect3DSurface9 * m_pDepthRTSurface = nullptr;
		IDirect3DSurface9 * m_pAlbedoRTSurface = nullptr;
		IDirect3DSurface9 * m_pNormalRTSurface = nullptr;
		IDirect3DSurface9 * m_pSpecularRTSurface = nullptr;
		IDirect3DSurface9 * m_pShadowRTSurface[NUM_CASCADEDES] = { nullptr };

	private : /* For SoftShadow */
		IDirect3DTexture9 * m_pSoftShadowOriginRTTexture = nullptr;
		IDirect3DSurface9 * m_pSoftShadowOriginRTSurface = nullptr;
		IDirect3DTexture9 * m_pSoftShadowBlurXRTTexture = nullptr;
		IDirect3DSurface9 * m_pSoftShadowBlurXRTSurface = nullptr;
		/* SoftShadow result map */
		IDirect3DTexture9 * m_pSoftShadowRTTexture = nullptr;
		IDirect3DSurface9 * m_pSoftShadowRTSurface = nullptr;

	private: /* For Stash */
		IDirect3DTexture9 * m_pStashRTTexture = nullptr;
		IDirect3DSurface9 * m_pStashRTSurface = nullptr;

	private: /* For Original Surface */
		IDirect3DSurface9 * m_pOriginSurface = nullptr;

	private :
		class DeferredQuad * m_pResultScreen = nullptr;

		//////////////////////////////////////////////////////////////////////////
		// RENDERER VARIABLES 
		//////////////////////////////////////////////////////////////////////////
	private:
		bool m_bSetup = false;
		D3DXCOLOR m_clearColor = 0xff555566;
		/* For Shadow */
		D3DXMATRIX m_lightViewMat[NUM_CASCADEDES];
		D3DXMATRIX m_lightProjMat[NUM_CASCADEDES];


		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHODES
		//////////////////////////////////////////////////////////////////////////
	public:
		static Renderer* Create();
		static void Release(Renderer* pRenderer);
	};

}