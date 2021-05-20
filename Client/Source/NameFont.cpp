#include "StandardEngineFramework.h"
#include "NameFont.h"
#include "Font.h"


void NameFont::Initialize(std::wstring text, GameObject * pOwner, D3DXVECTOR2 size, D3DXVECTOR3 offset, float centerOffset, D3DXCOLOR color)
{
	m_text = text;
	m_pOwner = pOwner;
	m_offset = offset;
	m_size = size;
	m_color = color;
	m_centerOffset = centerOffset;

	/*FontDesc desc;
	desc.text = text.c_str();
	desc.position = D3DXVECTOR3(0, 0, 0);
	desc.format = DT_CENTER | DT_BOTTOM;
	RECT rt;
	SetRect(&rt, -100, 40, 100, 0);
	desc.rect = rt;
	desc.scale = D3DXVECTOR3(1, 1, 1);
	desc.textColor = D3DXCOLOR(1, 1, 1, 1);
	m_pFont =  Font::Create(SCENE, desc);*/
}

void NameFont::RenderFont()
{
	D3DXVECTOR3 resultPos;
	D3DXMATRIX resultMat;
	D3DXMATRIX worldMat;
	D3DXMATRIX posMat;
	D3DXMATRIX scaleMat;
	
	D3DXMATRIX viewMat = SCENE->GetSelectedCamera()->GetViewMatrix();
	D3DXMATRIX projMat = SCENE->GetSelectedCamera()->GetProjectionMatrix();
	//D3DXMATRIX projMat;
	//D3DXMatrixOrthoOffCenterLH(&projMat, 0, WinMaxWidth, 0,  WinMaxHeight, 0, 1000);

	D3DXVECTOR3 position = m_pOwner->m_pTransform->CalcOffset(m_offset);
	
	
	//position.x -= m_size.x * 0.5f;
	/*D3DXMatrixTranslation(&posMat, position.x, position.y, position.z);
	D3DXMatrixScaling(&scaleMat, m_size.x, m_size.y, 1);
	worldMat = scaleMat * posMat;
	D3DVIEWPORT9 viewPort;
	DEVICE->GetViewport(&viewPort);

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	D3DXVec3Project(&resultPos, &D3DXVECTOR3(0, 0, 0), &viewPort, &projMat, &viewMat, &worldMat);
*/

	//resultPos.x += m_centerOffset;

	/*FontDesc desc;
	desc.fontSpace = EFontSpace::World;
	desc.text = m_text.c_str();
	desc.position = m_pOwner->m_pTransform->CalcOffset(m_offset);
	desc.format = DT_CENTER | DT_BOTTOM;
	RECT rt;
	SetRect(&rt, -100, 40, 100, 0);
	desc.rect = rt;
	desc.scale = D3DXVECTOR3(1, 1, 1);
	desc.textColor = D3DXCOLOR(1, 1, 1, 1);
	m_pFont->SetDesc(desc);*/

	ENGINE->DrawTextInWorld(m_text.c_str(), position, D3DXVECTOR3(m_size.x, m_size.y, 1), m_color);


	//ENGINE->DrawText(m_text.c_str(), resultPos, D3DXVECTOR3(m_size.x, m_size.y, 1), m_color);
}

void NameFont::SetOffset(D3DXVECTOR3 offset)
{
	m_offset = offset;
}

void NameFont::SetCenterOffset(float centerOffset)
{
	m_centerOffset = centerOffset;
}
