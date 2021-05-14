#pragma once

#include "IRenderable.h"

/* For Cascade Shadow */
// MAX = 4
#define NUM_CASCADEDES 2

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
		
		//////////////////////////////////////////////////////////////////////////
		// SETUP
		//////////////////////////////////////////////////////////////////////////
	private :
		void Setup();
		void SetupOcclusion();

	public:
		void Cleanup();
		void ClearBackBuffer();
		void ClearStashSurface();
		void ClearSurface();
		void ClearDepth();
		
	public : /* For Occlusion Query */
		void OcclusionCull(Scene* scene);
		void OcclusionBegin();
		void OcclusionEnd();

	public: /* For Render */
		void Render(Scene* scene);
		void RenderBegin();
		void RenderEnd();

		void ShowDebugMRT();
		void HideDebugMRT();

	public : /* For Filter */
		void SetLutFilter(IDirect3DTexture9* pLutFilterTexture);

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
		/* For PostRender */
		void PostRenderPipeline(Scene* scene);

		void DebugPipeline();


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
		void SetLightMRT(); // 음영 렌더타깃
		void SetPRBufferMRT(); // 후처리 준비
		void SetPostRenderMRT(); // 후처리 렌더타겟
		void SetRimLightMRT();
		void SetBrightnessMRT();
		void SetBloomMRT();

	private :
		void GeometryPass(Scene* scene);
		void AmbientPass(Scene* scene);
		void LightPass(Scene* scene);
		void ShadowPass(Scene * scene, int casecadeIndex);
		void SoftShadowPass(Scene* scene);
		void SoftShadowBlurPass(Scene* scene);
		void LinearFilterPass();
		void LutFilterPass();
		void PRBufferPass(Scene * pScene);
		void RimLightPass();
		void BrightnessPass();
		void BloomPass();
		void PostRenderPass();
		void BlendPass(); // 최종 합산 pass

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private: /* For LUT Filter */
		IDirect3DTexture9* m_pLutFilterTexture;

		//////////////////////////////////////////////////////////////////////////
		// OCCLUSION QUERY VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private:
		IDirect3DQuery9* m_pQuery = nullptr;
		ID3DXRenderToSurface * m_pOcclusionRender; // Occlusion's render to surface
		IDirect3DSurface9* m_pOcclusionSurface; // Occlusion's surface that is uses
		IDirect3DTexture9 * m_pOcclusionTexture; 

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

	private: /* For Light Map */
		IDirect3DTexture9* m_pLightIntensityRTTexture = nullptr;
		IDirect3DSurface9* m_pLightIntensityRTSurface = nullptr;

		IDirect3DTexture9* m_pAmbientIntensityRTTexture = nullptr;
		IDirect3DSurface9* m_pAmbientIntensityRTSurface = nullptr;

		IDirect3DTexture9* m_pSpecularIntensityRTTexture = nullptr;
		IDirect3DSurface9* m_pSpecularIntensityRTSurface = nullptr;

	private: /* For Stash */
		IDirect3DTexture9 * m_pStashRTTexture = nullptr;
		IDirect3DSurface9 * m_pStashRTSurface = nullptr;

	private : /* For Post Render Buffer */
		IDirect3DTexture9 * m_pVtxNormalRTTexture = nullptr;
		IDirect3DSurface9 * m_pVtxNormalRTSurface = nullptr;

		IDirect3DTexture9 * m_pEffectMaskRTTexture = nullptr;
		IDirect3DSurface9 * m_pEffectMaskRTSurface = nullptr;

		IDirect3DTexture9 * m_pEffectParamRTTexture = nullptr;
		IDirect3DSurface9 * m_pEffectParamRTSurface = nullptr;

	private : /* For Post Render */
		IDirect3DTexture9 * m_pRimLightRTTexture = nullptr;
		IDirect3DSurface9 * m_pRimLightRTSurface = nullptr;

		IDirect3DTexture9 * m_pBrightnessTexture = nullptr;
		IDirect3DSurface9 * m_pBrightnessSurface = nullptr;

		IDirect3DTexture9 * m_pBloomRTTexture = nullptr;
		IDirect3DSurface9 * m_pBloomRTSurface = nullptr;

	private : /* For Post Render */
		IDirect3DTexture9* m_pPostRenderRTTexture = nullptr;
		IDirect3DSurface9* m_pPostRenderRTSurface = nullptr;

	private : 
		IDirect3DTexture9* m_pScreenTexture = nullptr;
		IDirect3DSurface9* m_pScreenSurface = nullptr;

	private: /* For Original Surface */
		IDirect3DSurface9 * m_pOriginSurface = nullptr;

	private :
		class DeferredQuad * m_pResultScreen = nullptr;

	private : /* For Debug MRT Quad */
		class DebugMRTQuad * m_pDepthRTQuad = nullptr;
		class DebugMRTQuad * m_pAlbedoRTQuad = nullptr;
		class DebugMRTQuad * m_pNormalRTQuad = nullptr;
		class DebugMRTQuad * m_pSpecularRTQuad = nullptr;

		class DebugMRTQuad * m_pCascadeShadowQuad0 = nullptr;
		class DebugMRTQuad * m_pCascadeShadowQuad1 = nullptr;
		class DebugMRTQuad * m_pShadowOriginQuad = nullptr;
		class DebugMRTQuad * m_pShadowBlurQuad = nullptr;

		class DebugMRTQuad * m_pLightIntensityQuad = nullptr;
		class DebugMRTQuad * m_pAmbientIntensityQuad = nullptr;
		class DebugMRTQuad * m_pSpecularIntensityQuad = nullptr;

		class DebugMRTQuad * m_pVtxNormalQuad = nullptr;
		class DebugMRTQuad * m_pEffectMaskQuad = nullptr;
		class DebugMRTQuad * m_pEffectParamQuad = nullptr;

		class DebugMRTQuad * m_pRimLightQuad = nullptr;
		class DebugMRTQuad * m_pBrightnessQuad = nullptr;
		class DebugMRTQuad * m_pBloomQuad = nullptr;

		class DebugMRTQuad * m_pPostRenderQuad = nullptr;

		std::vector<DebugMRTQuad*> m_debugQuads;
		std::vector<IDirect3DTexture9*> m_debugTextures;

		bool m_isDebugRender = false;
		//////////////////////////////////////////////////////////////////////////
		// RENDERER VARIABLES 
		//////////////////////////////////////////////////////////////////////////
	private:
		bool m_bSetup = false;
		D3DXCOLOR m_clearColor = 0xff555566;
		/* For Shadow */
		D3DXMATRIX m_lightViewMat[NUM_CASCADEDES];
		D3DXMATRIX m_lightProjMat[NUM_CASCADEDES];

		std::vector<GameObject*> m_renderableOpaque;

		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHODES
		//////////////////////////////////////////////////////////////////////////
	public:
		static Renderer* Create();
		static void Release(Renderer* pRenderer);
	};

}