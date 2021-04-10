#pragma once

#include "IRenderable.h"

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
		void SetPrepareMRT();
		void SetGBufferMRT();
		void SetOriginMRT();

		void GeometryPass(Scene* scene);
		void AmbientPass(Scene* scene);
		void LightPass(Scene* scene);
		void ShadowPass(Scene * scene);

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
		IDirect3DTexture9 * m_pShadowRTTexture = nullptr;

	private: /* RenderTarget Surfaces */
		IDirect3DSurface9 * m_pDepthRTSurface = nullptr;
		IDirect3DSurface9 * m_pAlbedoRTSurface = nullptr;
		IDirect3DSurface9 * m_pNormalRTSurface = nullptr;
		IDirect3DSurface9 * m_pSpecularRTSurface = nullptr;
		IDirect3DSurface9 * m_pShadowRTSurface = nullptr;

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
		D3DXMATRIX m_lightViewMat;
		D3DXMATRIX m_lightProjMat;


		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHODES
		//////////////////////////////////////////////////////////////////////////
	public:
		static Renderer* Create();
		static void Release(Renderer* pRenderer);
	};

}