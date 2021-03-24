#include "StandardEngineFramework.h"
#include "UIElement.h"
#include "Scene.h"
#include "VertexTypes.h"
#include "IndexTypes.h"

using namespace HyEngine;

UIElement::UIElement(Scene* scene, std::wstring ImagePath, const Vector3 & position, const Quaternion & rotation, const Vector3 & scale)
	:m_ImagePath(ImagePath)
{
	//m_pTransform = new Transform(position, rotation, scale);
}

HyEngine::UIElement::UIElement(const UIElement & other)
{
}

HRESULT UIElement::Initialize()
{
	// UI 이미지 로드
	if (FAILED(D3DXCreateTextureFromFile(DEVICE, m_ImagePath.c_str(), &m_pTexture)))
		return E_FAIL;

	HRESULT hr;

	hr = DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	assert(SUCCEEDED(hr));
	hr = DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	assert(SUCCEEDED(hr));
	hr = DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	assert(SUCCEEDED(hr));

	hr = DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	assert(SUCCEEDED(hr));
	hr = DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	assert(SUCCEEDED(hr));


#pragma region IndexVertexBuffer
	m_vertexSize = sizeof(TextureVertex);
	m_vertexCount = 4;
	m_triCount = 2;

	m_indexSize = sizeof(Index16);

	hr = DEVICE->CreateVertexBuffer
	(
		m_vertexCount * m_vertexSize,
		D3DUSAGE_WRITEONLY,
		TextureVertex::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		nullptr
	);
	assert(SUCCEEDED(hr));

	hr = DEVICE->CreateIndexBuffer
	(
		m_triCount * m_indexSize,
		D3DUSAGE_WRITEONLY,
		Index16::FMT,
		D3DPOOL_MANAGED,
		&m_pIndexBuffer,
		nullptr
	);
	assert(SUCCEEDED(hr));

	TextureVertex* vertices = nullptr;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].x = -0.5f * m_pTransform->m_scale.x() + m_pTransform->m_position.x();
	vertices[0].y = 0.5f* m_pTransform->m_scale.y() + m_pTransform->m_position.y();
	vertices[0].z = 0.f * m_pTransform->m_scale.z() + m_pTransform->m_position.z();
	vertices[0].u = 0.f;
	vertices[0].v = 0.f;

	vertices[1].x = 0.5f* m_pTransform->m_scale.x() + m_pTransform->m_position.x();
	vertices[1].y = 0.5f* m_pTransform->m_scale.y() + m_pTransform->m_position.y();
	vertices[1].z = 0.f* m_pTransform->m_scale.z() + m_pTransform->m_position.z();
	vertices[1].u = 1.f;
	vertices[1].v = 0.f;

	vertices[2].x = 0.5f* m_pTransform->m_scale.x() + m_pTransform->m_position.x();
	vertices[2].y = -0.5f* m_pTransform->m_scale.y() + m_pTransform->m_position.y();
	vertices[2].z = 0.f* m_pTransform->m_scale.z() + m_pTransform->m_position.z();
	vertices[2].u = 1.f;
	vertices[2].v = 1.f;

	vertices[3].x = -0.5f* m_pTransform->m_scale.x() + m_pTransform->m_position.x();
	vertices[3].y = -0.5f* m_pTransform->m_scale.y() + m_pTransform->m_position.y();
	vertices[3].z = 0.f* m_pTransform->m_scale.z() + m_pTransform->m_position.z();
	vertices[3].u = 0.f;
	vertices[3].v = 1.f;

	m_pVertexBuffer->Unlock();

	Index16* indices = nullptr;

	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	indices[0]._1 = 0;
	indices[0]._2 = 1;
	indices[0]._3 = 2;

	indices[1]._1 = 0;
	indices[1]._2 = 2;
	indices[1]._3 = 3;

	m_pIndexBuffer->Unlock();
#pragma endregion
	return S_OK;
}

void UIElement::Update()
{
}

void UIElement::Render()
{		
	HRESULT hr;
	D3DXMATRIX matView;

	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0, 0, -1),
		&D3DXVECTOR3(0, 0, 0),
		&Vector3::Up);
	DEVICE->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matProj;
	D3DXMatrixOrthoLH(&matProj,
		WinMaxWidth,
		WinMaxHeight,
		0.f,
		100.f);

	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);

	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	hr = DEVICE->SetStreamSource(0, m_pVertexBuffer, 0, m_vertexSize);
	assert(SUCCEEDED(hr));

	hr = DEVICE->SetFVF(TextureVertex::FVF);
	assert(SUCCEEDED(hr));

	hr = DEVICE->SetTexture(0, m_pTexture);
	assert(SUCCEEDED(hr));

	hr = DEVICE->SetIndices(m_pIndexBuffer);
	assert(SUCCEEDED(hr));

	hr = DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vertexCount, 0, m_triCount);
	assert(SUCCEEDED(hr));
}


UIElement * UIElement::Create(Scene* scene,
	std::wstring ImagePath,
	const Vector3 & position,
	const Quaternion & rotation,
	const Vector3 & scale)
{
	UIElement* pInstance = new UIElement(scene, ImagePath, position, rotation, scale);
	HRESULT hResult = pInstance->Initialize();
	if (FAILED(hResult))
		SAFE_DELETE(pInstance);
	assert(SUCCEEDED(hResult));
	return pInstance;
}

void UIElement::Free()
{
	SAFE_DELETE(m_pTransform);
	SAFE_DELETE(m_pVertexBuffer);
	SAFE_DELETE(m_pIndexBuffer);
	SAFE_DELETE(m_pTexture);
}

