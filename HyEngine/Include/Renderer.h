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
		void SetLightMRT();
		void SetOriginMRT();

		void GeometryPass(Scene* scene);
		void AmbientPass(Scene* scene);
		void LightPass(Scene* scene);


		//////////////////////////////////////////////////////////////////////////
		// FORWARD VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private:



		//////////////////////////////////////////////////////////////////////////
		// DEFERRED VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private: /* RenderTarget Textures*/
		IDirect3DTexture9 * m_pDepthRTTexture = nullptr;
		IDirect3DTexture9 * m_pAlbedoRTTexture = nullptr;
		IDirect3DTexture9 * m_pNormalRTTexture = nullptr;

	private: /* RenderTarget Surfaces */
		IDirect3DSurface9 * m_pDepthRTSurface = nullptr;
		IDirect3DSurface9 * m_pAlbedoRTSurface = nullptr;
		IDirect3DSurface9 * m_pNormalRTSurface = nullptr;

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


		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHODES
		//////////////////////////////////////////////////////////////////////////
	public:
		static Renderer* Create();
		static void Release(Renderer* pRenderer);
	};

}