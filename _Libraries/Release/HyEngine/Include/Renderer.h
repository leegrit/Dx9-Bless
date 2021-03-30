#pragma once

#include "IRenderable.h"

namespace HyEngine
{
	/*
	Renderer는 Render관련 모든 기능을 수행한다.
	*/
	class ENGINE_DLL Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Render(IRenderable * renderable);
		void RenderList(std::vector<IRenderable* > renderables);

		void RenderBegin();
		void RenderEnd();


		// default setter 
		void SetOpaqueContext();

		void SetAlphaContext();
		
		void SetEnableLight(std::vector<std::pair<int, D3DLIGHT9>> lights);
		void SetEnableLight();
		void SetDisableLight(std::vector<std::pair<int, D3DLIGHT9>> lights);
		void SetDisableLight();
		void EnableUIContext();
		void DisableUIContext();

		void BeginRenderEvent(std::wstring message);
		void EndRenderEvent(std::wstring message);

	private :
		D3DXCOLOR m_clearColor = 0xff555566;

		D3DXMATRIX m_identityMat;
		D3DXMATRIX m_orthoMat;
		//D3DXCOLOR clearColor = D3DCOLOR_ARGB(255, 255, 0, 0);
		D3DMATERIAL9 m_material;
		D3DLIGHT9 m_light;
	};

}