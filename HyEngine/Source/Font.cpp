#include "StandardEngineFramework.h"
#include "Font.h"

HyEngine::Font::Font(Scene * pScene, FontDesc desc)
	: GameObject(ERenderType::RenderAlpha, pScene, nullptr, L"Font")
{
	// ¹Ì±¸Çö
	assert(false);
	m_desc = desc;
}

HyEngine::Font::~Font()
{
}

void HyEngine::Font::Initialize()
{
	if (m_desc.fontSpace == EFontSpace::World)
	{

	}
	else if(m_desc.fontSpace == EFontSpace::Screen)
	{

	}
}

void HyEngine::Font::Render()
{
	switch (m_desc.fontSpace)
	{
	case EFontSpace::Screen:
		
		break;
	case EFontSpace::World:
		D3DXVECTOR3 camPos = CAMERA->m_pTransform->m_position;
		float dist = D3DXVec3Length(&(camPos - m_desc.position));
		if (dist >= 250)
			return;
		D3DXVECTOR3 resultPos;
		D3DXMATRIX resultMat;
		D3DXMATRIX worldMat;
		D3DXMATRIX posMat;
		D3DXMATRIX scaleMat;

		D3DXMATRIX viewMat = SCENE->GetSelectedCamera()->GetViewMatrix();
		D3DXMATRIX projMat = SCENE->GetSelectedCamera()->GetProjectionMatrix();


		//position.x -= m_size.x * 0.5f;
		D3DXMatrixTranslation(&posMat, m_desc.position.x, m_desc.position.y, m_desc.position.z);
		D3DXMatrixScaling(&scaleMat, m_desc.scale.x, m_desc.scale.y, 1);
		worldMat = scaleMat * posMat;
		D3DVIEWPORT9 viewPort;
		DEVICE->GetViewport(&viewPort);

		D3DXMATRIX identity;
		D3DXMatrixIdentity(&identity);
		D3DXVec3Project(&resultPos, &D3DXVECTOR3(0, 0, 0), &viewPort, &projMat, &viewMat, &worldMat);


		D3DXMatrixTranslation(&posMat, resultPos.x, resultPos.y, resultPos.z);
		D3DXMatrixScaling(&scaleMat, m_desc.scale.x, m_desc.scale.y, m_desc.scale.z);
		m_desc.matTrans = scaleMat * posMat;
		DIRECT_SPRITE->SetTransform(&m_desc.matTrans);
		DIRECT_FONT->DrawTextW(DIRECT_SPRITE, m_desc.text, lstrlen(m_desc.text), &m_desc.rect, m_desc.format, m_desc.textColor);
		break;
	}
}

void HyEngine::Font::Update()
{
}

void HyEngine::Font::SetDesc(FontDesc desc)
{
	m_desc = desc;
}

Font * HyEngine::Font::Create(Scene * pScene, FontDesc desc)
{
	Font* pFont = new Font(pScene, desc);
	pFont->Initialize();
	return pFont;
}
