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
		void ClearLightSurface();
		
	public : /* For Occlusion Query */
		void OcclusionCull(Scene* scene);
		void OcclusionBegin();
		void OcclusionEnd();

	public: /* For Render */
		void Render(Scene* scene);
		void RenderBegin();
		void RenderEnd();

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

	private :
		void GeometryPass(Scene* scene);
		void AmbientPass(Scene* scene);
		void LightPass(Scene* scene);
		void ShadowPass(Scene * scene, int casecadeIndex);
		void SoftShadowPass(Scene* scene);
		void SoftShadowBlurPass(Scene* scene);
		void LinearFilterPass();
		void LutFilterPass();
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
		IDirect3DTexture9* m_pLightRTTexture = nullptr;
		IDirect3DSurface9* m_pLightRTSurface = nullptr;

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

		std::vector<GameObject*> m_renderableOpaque;

		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHODES
		//////////////////////////////////////////////////////////////////////////
	public:
		static Renderer* Create();
		static void Release(Renderer* pRenderer);
	};

}