#include "StandardEngineFramework.h"
#include "Skybox.h"
#include "Transform.h"
#include "VertexTypes.h"
#include "IndexTypes.h"
#include "TextureLoader.h"

HyEngine::Skybox::Skybox(Camera * camera, std::wstring cubeTexPath)
{
	/*if (FAILED(D3DXCreateCubeTextureFromFile(DEVICE, cubeTexPath.c_str(), &m_pTexture)))
		assert(m_pTexture);*/
	m_pTexture = std::static_pointer_cast<IDirect3DCubeTexture9>(TextureLoader::GetCubeTexture(cubeTexPath));
	assert(m_pTexture);
	m_pCamera = camera;
	m_pTransform = new Transform(nullptr);
}

HyEngine::Skybox::~Skybox()
{
}

void HyEngine::Skybox::Initialize()
{
	m_isInit = true;

	// 렌더순서 바꾼후 사이즈 줄여야됨
	m_pTransform->SetScale(Vector3(100, 100.f, 100.f));

	HRESULT hr;

	m_vertexCount = 8;
	m_vertexSize = sizeof(TextureCubeVertex);
	m_vertexFVF = TextureCubeVertex::FVF;
	m_indexCount = 12;
	m_primitiveCount = m_indexCount;

	hr = DEVICE->CreateVertexBuffer
	(
		m_vertexCount * m_vertexSize,
		D3DUSAGE_DYNAMIC,
		m_vertexFVF,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		0
	);
	assert(SUCCEEDED(hr));

	TextureCubeVertex* vertices = LockVertices();
	{
		vertices[0] = TextureCubeVertex(-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f);
		vertices[1] = TextureCubeVertex(0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f);
		vertices[2] = TextureCubeVertex(0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f);
		vertices[3] = TextureCubeVertex(-0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f);

		vertices[4] = TextureCubeVertex(-0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f);
		vertices[5] = TextureCubeVertex(0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
		vertices[6] = TextureCubeVertex(0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f);
		vertices[7] = TextureCubeVertex(-0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f);
	}
	UnlockVertices();

	hr = DEVICE->CreateIndexBuffer
	(
		m_primitiveCount * sizeof(Index16),
		D3DUSAGE_DYNAMIC,
		Index16::FMT,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		nullptr
	);
	assert(SUCCEEDED(hr));

	Index16* indices = LockIndices();
	{
		// +x
		indices[0]._1 = 1;
		indices[0]._2 = 5;
		indices[0]._3 = 6;

		indices[1]._1 = 1;
		indices[1]._2 = 6;
		indices[1]._3 = 2;

		// -x
		indices[2]._1 = 4;
		indices[2]._2 = 0;
		indices[2]._3 = 3;

		indices[3]._1 = 4;
		indices[3]._2 = 3;
		indices[3]._3 = 7;

		// +y
		indices[4]._1 = 4;
		indices[4]._2 = 5;
		indices[4]._3 = 1;

		indices[5]._1 = 4;
		indices[5]._2 = 1;
		indices[5]._3 = 0;

		// -y
		indices[6]._1 = 6;
		indices[6]._2 = 7;
		indices[6]._3 = 3;

		indices[7]._1 = 6;
		indices[7]._2 = 3;
		indices[7]._3 = 2;

		// +z
		indices[8]._1 = 5;
		indices[8]._2 = 4;
		indices[8]._3 = 7;

		indices[9]._1 = 5;
		indices[9]._2 = 7;
		indices[9]._3 = 6;

		// -z
		indices[10]._1 = 0;
		indices[10]._2 = 1;
		indices[10]._3 = 2;

		indices[11]._1 = 0;
		indices[11]._2 = 2;
		indices[11]._3 = 3;
	}
	UnlockIndices();
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = (D3DXCOLOR)D3DCOLOR_XRGB(255, 255, 255);
	m_light.Specular = (D3DXCOLOR)D3DCOLOR_XRGB(255, 255, 255) * 0.3f;
	m_light.Ambient = (D3DXCOLOR)D3DCOLOR_XRGB(255, 255, 255) * 0.6f;
	m_light.Direction = D3DXVECTOR3(0.707f, -0.707f, 0.707f);
}

void HyEngine::Skybox::Update()
{
	assert(m_isInit);
	/*if (m_pCamera == nullptr)
		m_pCamera = SCENE->GetSelectedCamera();
	
	assert(m_pCamera != nullptr);*/
	m_pTransform->SetPosition(SCENE->GetSelectedCamera()->m_pTransform->m_position);
}

void HyEngine::Skybox::Render()
{
	assert(m_isInit);

	DEVICE->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	DEVICE->SetStreamSource(0, m_pVertexBuffer, 0, m_vertexSize);
	DEVICE->SetFVF(TextureCubeVertex::FVF);

	DEVICE->SetIndices(m_pIndexBuffer);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetLight(0, &m_light);//임시
	BOOL lightEnable;
	DEVICE->GetLightEnable(0, &lightEnable);
	DEVICE->LightEnable(0, TRUE);//임시

	DEVICE->SetTexture(0, m_pTexture.get());

	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vertexCount, 0, m_primitiveCount);

	DEVICE->LightEnable(0, lightEnable);//임시
										//DEVICE->SetLight(0, NULL); //임시
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

TextureCubeVertex * HyEngine::Skybox::LockVertices()
{
	assert(m_pVertexBuffer != nullptr);
	TextureCubeVertex* vertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	return vertices;
}

void HyEngine::Skybox::UnlockVertices()
{
	m_pVertexBuffer->Unlock();
}

Index16 * HyEngine::Skybox::LockIndices()
{
	assert(m_pIndexBuffer != nullptr);
	Index16* indices;
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	return indices;
}

void HyEngine::Skybox::UnlockIndices()
{
	m_pIndexBuffer->Unlock();
}
