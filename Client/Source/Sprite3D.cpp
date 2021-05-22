#include "stdafx.h"
#include "Sprite3D.h"
#include "SpriteLoader.h"
#include "Geometry.h"
#include "TextureQuad.h"
#include "Helper.h"


Sprite3D::Sprite3D(Scene * pScene, std::wstring name, std::wstring spritePath, ELoopType loopType, float frameCount, float speed)
	: GameObject(ERenderType::RenderAlpha, pScene, nullptr, name)
{
	m_curFrame = 0;
	m_endFrame = frameCount;
	m_frameSpeed = speed;
	m_loopType = loopType;
	std::wstring path = spritePath + L"/%d.png";
	m_path = path;
	SpriteLoader::InsertTexture(path, path, frameCount);
}

Sprite3D::~Sprite3D()
{
}

void Sprite3D::Initialize()
{
	m_pTextureQuad = Geometry::CreateGeometry<TextureQuad>(nullptr);
	ENGINE->TryGetShader(L"Texture", &m_pEffect);

	m_pTexture = SpriteLoader::GetSprite(m_path, m_curFrame);
}

void Sprite3D::Render()
{
	GameObject::Render();

	{
		D3DXMATRIX worldMat = GetWorldMatrix();

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
	{
		D3DXMATRIX worldMat;

		D3DXMATRIX matScale;
		D3DXMATRIX matRot;
		D3DXMATRIX matPos;

		D3DXMatrixScaling(&matScale, m_pTransform->m_scale.x(), m_pTransform->m_scale.y(), m_pTransform->m_scale.z());
		D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(m_pTransform->m_rotationEuler.y() + 90), D3DXToRadian(m_pTransform->m_rotationEuler.x()), D3DXToRadian(m_pTransform->m_rotationEuler.z()));
		D3DXMatrixTranslation(&matPos, m_pTransform->m_position.x(), m_pTransform->m_position.y(), m_pTransform->m_position.z());

		worldMat = matScale * matRot * matPos;


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
}

void Sprite3D::Update()
{
	GameObject::Update();

	if (m_curFrame >= m_endFrame)
	{
		switch (m_loopType)
		{
		case ELoopType::Default:
			m_curFrame = 0;
			SetActive(false);
			break;
		case ELoopType::Loop:
			m_curFrame = 0;
			break;
		default:
			assert(false);
			break;
		}
	}

	if (m_curFrame < m_endFrame)
		m_curFrame += TIMER->getDeltaTime() * m_frameSpeed;
	if (m_curFrame < m_endFrame)
		m_pTexture = SpriteLoader::GetSprite(m_path, (int)m_curFrame);
}

void Sprite3D::PlayAnimation()
{
	SetActive(true);
	m_curFrame = 0;
}

Sprite3D * Sprite3D::Create(Scene * pScene, std::wstring name, std::wstring spritePath, ELoopType loopType, float frameCount, float speed)
{
	Sprite3D * obj = new Sprite3D(pScene, name, spritePath, loopType, frameCount, speed);
	obj->Initialize();
	return obj;
}
