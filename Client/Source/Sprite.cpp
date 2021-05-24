#include "stdafx.h"
#include "Sprite.h"
#include "SpriteLoader.h"
#include "Geometry.h"
#include "TextureQuad.h"
#include "Helper.h"


using namespace HyEngine;

Sprite::Sprite(Scene * pScene, std::wstring name, std::wstring spriteFolderPath, ELoopType loopType, float frameCount, float speed)
	: GameObject(ERenderType::RenderAlpha, pScene, nullptr,name)
{
	m_curFrame = 0;
	m_endFrame = frameCount;
	m_frameSpeed = speed;
	m_loopType = loopType;
	std::wstring path = spriteFolderPath + L"/%d.png";
	m_path = path;
	SpriteLoader::InsertTexture(path, path, frameCount);
}

Sprite::~Sprite()
{
}

void Sprite::Initialize()
{
	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);

	ENGINE->TryGetShader(L"Texture", &m_pEffect);

	m_pTexture = SpriteLoader::GetSprite(m_path, m_curFrame);


}

void Sprite::Render()
{
	GameObject::Render();

	D3DXMATRIX worldMat = Helper::GetWorldToBillboard
	(
		m_pTransform->m_position.operator D3DXVECTOR3(),
		m_pTransform->m_rotationEuler.operator D3DXVECTOR3(),
		m_pTransform->m_scale.operator D3DXVECTOR3(),
		CAMERA->GetViewMatrix()
	);
	m_pEffect->SetMatrix("WorldMatrix", &worldMat);
	m_pEffect->SetMatrix("ViewMatrix", &CAMERA->GetViewMatrix());
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetProjectionMatrix());

	D3DXHANDLE diffuseHandle = m_pEffect->GetParameterByName(0, "DiffuseTex");
	m_pEffect->SetTexture(diffuseHandle, m_pTexture);

	m_pEffect->SetTechnique("Texture");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);

		DEVICE->SetStreamSource(0, m_pTextureQuad->GetVertexBuffer(), 0, m_pTextureQuad->GetVertexSize());
		DEVICE->SetVertexDeclaration(m_pTextureQuad->GetDeclare());
		DEVICE->SetIndices(m_pTextureQuad->GetIndexBuffer());
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pTextureQuad->GetVertexCount(), 0, m_pTextureQuad->GetPrimitiveCount());

		m_pEffect->EndPass();
	}
	m_pEffect->End();

	

}

void Sprite::Update()
{
	GameObject::Update();

	if (m_curFrame >= m_endFrame)
	{
		switch (m_loopType)
		{
		case ELoopType::Default :
			m_curFrame = 0;
			SetActive(false);
			break;
		case ELoopType::Loop:
			m_curFrame = 0;
			break;
		case ELoopType::Infinity:
			return;
		default : 
			assert(false);
			break;
		}
	}

	if (m_curFrame < m_endFrame)
		m_curFrame += TIMER->getDeltaTime() * m_frameSpeed;
	if (m_curFrame < m_endFrame)
		m_pTexture = SpriteLoader::GetSprite(m_path, (int)m_curFrame);
}

void Sprite::PlayAnimation()
{
	SetActive(true);
	m_curFrame = 0;
}

Sprite * Sprite::Create(Scene * pScene, std::wstring name, std::wstring spritePath, ELoopType loopType, float frameCount, float speed)
{
	Sprite * obj = new Sprite(pScene, name, spritePath, loopType, frameCount, speed);
	obj->Initialize();
	return obj;
}
