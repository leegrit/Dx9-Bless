#include "stdafx.h"
#include "DamageFontScatter.h"

DamageFontScatter::DamageFontScatter(Scene * pScene, std::wstring name)
	: GameObject(ERenderType::None, pScene, nullptr, name)
{

}

DamageFontScatter::~DamageFontScatter()
{	

}

void DamageFontScatter::Render()
{
	assert(false);
}

void DamageFontScatter::Update()
{
	for (int i = 0; i < m_damageFonts.size(); i++)
	{

		m_damageFonts[i].m_elapsed += TIMER->getDeltaTime() * m_speed;
		if (m_damageFonts[i].m_elapsed >= m_delay)
		{
			m_damageFonts.erase(m_damageFonts.begin() + i);
			i--;
			continue;
		}
		else if (m_damageFonts[i].m_elapsed <= m_fadeInTime)
		{
			float alpha = m_damageFonts[i].m_elapsed / m_fadeInTime;
			if (m_damageFonts[i].isPlayer)
			{

				ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(2, 2, 2), D3DXCOLOR(1, 0, 0,alpha));
			}
			else
			{
				ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(2, 2, 2), D3DXCOLOR(1, 1, 1, alpha));
			}
		}
		else if (m_damageFonts[i].m_elapsed >= m_delay - m_fadeOutTime)
		{
			float alpha = (m_delay - m_damageFonts[i].m_elapsed) / m_fadeOutTime;

			if (m_damageFonts[i].isPlayer)
			{

				ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(2, 2, 2), D3DXCOLOR(1, 0, 0, alpha));
			}
			else
			{
				ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(2, 2, 2), D3DXCOLOR(1, 1, 1, alpha));
			}
		}
		else
		{
			if (m_damageFonts[i].isPlayer)
			{

				ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(2, 2, 2), D3DXCOLOR(1, 0, 0, 1));
			}
			else
			{
				ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(2, 2, 2), D3DXCOLOR(1, 1, 1, 1));
			}
		}




	}
}

void DamageFontScatter::Initialize()
{

}

void DamageFontScatter::PushDamageFunt(float damage, bool isPlayer, bool isCritical, D3DXVECTOR3 center)
{
	DamageFontDesc desc;
	
	desc.font = std::to_wstring((int)damage);
	if (isPlayer == true)
	{
		desc.font = L"-" + desc.font;
	}
	desc.isPlayer = isPlayer;
	desc.isCritical = isCritical;
	
	D3DXVECTOR3 min = center - D3DXVECTOR3(m_radius, m_radius, m_radius);
	D3DXVECTOR3 max = center + D3DXVECTOR3(m_radius, m_radius, m_radius);
	DxHelper::GetRandomVector(&desc.position,
		&min,
		&max);
	
	desc.m_elapsed = 0;

	m_damageFonts.push_back(desc);
}

DamageFontScatter * DamageFontScatter::Create(Scene * pScene, std::wstring name)
{
	DamageFontScatter* obj = new DamageFontScatter(pScene, name);
	obj->Initialize();
	return obj;
}
