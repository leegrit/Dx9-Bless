#include "StandardEngineFramework.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ILight.h"
#include "Constants.h"
using namespace HyEngine;

Renderer::Renderer()
{
	D3DXMatrixIdentity(&m_identityMat);
	D3DXMatrixOrthoLH(&m_orthoMat,
		WinMaxWidth,
		WinMaxHeight,
		0.f,
		100.f);

	m_material = WHITE_MTRL;
	m_light = InitDirectionalLight(&D3DXVECTOR3(5, -5, 5), WHITE);

}


Renderer::~Renderer()
{
}

void Renderer::Render(IRenderable * renderable)
{
	renderable->Render();
}

void Renderer::RenderList(std::vector<IRenderable*> renderables)
{
	for (auto& renderable : renderables)
	{
		renderable->Render();
	}
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


void Renderer::SetOpaqueContext()
{
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void Renderer::SetAlphaContext()
{
	/*DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 1);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);*/

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 1); // 알파 기준 설정
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // 알파 테스팅 수행
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
}

void HyEngine::Renderer::SetEnableLight(std::vector<std::pair<int, D3DLIGHT9>> lights)
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	for (auto& light : lights)
	{
		// 여기서 계속 set 안해도 될거같음
		DEVICE->SetLight(light.first, &light.second);
		DEVICE->LightEnable(light.first, TRUE);
	}
}

void HyEngine::Renderer::SetEnableLight()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	DEVICE->SetLight(0, &m_light);
	DEVICE->LightEnable(0, TRUE);

	// 임시
	DEVICE->SetMaterial(&m_material);
}

void HyEngine::Renderer::SetDisableLight(std::vector<std::pair<int, D3DLIGHT9>> lights)
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	//DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	//DEVICE->SetRenderState(D3DRS_SPECULARENABLE, FALSE);

	for (auto& light : lights)
	{
		//DEVICE->SetLight(light.first, &light.second);
		DEVICE->LightEnable(light.first, FALSE);
	}
}

void HyEngine::Renderer::SetDisableLight()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	DEVICE->LightEnable(0, FALSE);
	DEVICE->SetMaterial(nullptr);
}

void HyEngine::Renderer::EnableUIContext()
{
	DEVICE->SetTransform(D3DTS_VIEW, &m_identityMat);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_orthoMat);
}

void HyEngine::Renderer::DisableUIContext()
{
	DEVICE->SetTransform(D3DTS_VIEW, &CAMERA->GetViewMatrix());
	DEVICE->SetTransform(D3DTS_PROJECTION, &CAMERA->GetProjectionMatrix());
}

void Renderer::BeginRenderEvent(std::wstring message)
{
}

void Renderer::EndRenderEvent(std::wstring message)
{
}
