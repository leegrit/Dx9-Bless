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

		m_damageFonts[i].m_elapsed += TIMER->getDeltaTime();// *m_speed;
		if (m_damageFonts[i].isCritical)
		{
			// critical animation

			if (m_damageFonts[i].dir == D3DXVECTOR3(0, 0, 0))
			{
				D3DXVECTOR3 min = D3DXVECTOR3(-1, -1, -1);
				D3DXVECTOR3 max = D3DXVECTOR3(1, 1, 1);
				DxHelper::GetRandomVector(&m_damageFonts[i].dir, &min, &max);

			}
			if (m_damageFonts[i].m_elapsed <= (m_delay * 0.1f))
			{
				float size = MathUtils::lerp(4.0f, 0.5f, (m_damageFonts[i].m_elapsed - (m_delay * 0.1f)) / ((m_delay * 0.2f) - (m_delay * 0.1f)));

				m_damageFonts[i].size = size;
			}
			else if (m_damageFonts[i].m_elapsed > (m_delay * 0.1f) &&
				m_damageFonts[i].m_elapsed <= (m_delay * 0.3f))
			{
				float size = MathUtils::lerp(0.5f, 2.0f, (m_damageFonts[i].m_elapsed - (m_delay * 0.1f)) / ((m_delay * 0.3f) - (m_delay * 0.1f)));
				m_damageFonts[i].size = size;
			}
			else if (m_damageFonts[i].m_elapsed > (m_delay * 0.3f))
			{
				m_damageFonts[i].position += m_damageFonts[i].dir * m_damageFonts[i].speed * TIMER->getDeltaTime();
			}
		}
		else if (m_damageFonts[i].isCritical == false)
		{
			if (m_damageFonts[i].dir == D3DXVECTOR3(0, 0, 0))
			{
				D3DXVECTOR3 min = D3DXVECTOR3(-1, -1, -1);
				D3DXVECTOR3 max = D3DXVECTOR3(1, 1, 1);
				DxHelper::GetRandomVector(&m_damageFonts[i].dir, &min, &max);

			}
			if (m_damageFonts[i].m_elapsed <= (m_delay * 0.1f))
			{
				float size = MathUtils::lerp(2.0f, 1.0f, (m_damageFonts[i].m_elapsed - (m_delay * 0.1f)) / ((m_delay * 0.2f) - (m_delay * 0.1f)));

				m_damageFonts[i].size = size;
			}
			else if (m_damageFonts[i].m_elapsed > (m_delay * 0.1f) &&
				m_damageFonts[i].m_elapsed <= (m_delay * 0.3f))
			{
				float size = MathUtils::lerp(1.0f, 1.5f, (m_damageFonts[i].m_elapsed - (m_delay * 0.1f)) / ((m_delay * 0.3f) - (m_delay * 0.1f)));
				m_damageFonts[i].size = size;
			}
			else if (m_damageFonts[i].m_elapsed > (m_delay * 0.3f))
			{
				m_damageFonts[i].position += m_damageFonts[i].dir * m_damageFonts[i].speed * TIMER->getDeltaTime();
			}
		}
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

				ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(m_damageFonts[i].size, m_damageFonts[i].size, m_damageFonts[i].size), D3DXCOLOR(1, 0, 0,alpha));
			}
			else
			{
				if (m_damageFonts[i].isCritical)
				{
					FontDesc fontDesc;
					fontDesc.text = m_damageFonts[i].font.c_str();
					fontDesc.position = m_damageFonts[i].position;
					fontDesc.scale = D3DXVECTOR3(2.05, 2.05, 2.05);
					fontDesc.rect;
					SetRect(&fontDesc.rect, -400, -20, 400, 20);
					fontDesc.format = DT_CENTER | DT_VCENTER;
					fontDesc.textColor = D3DXCOLOR(1, 0, 0, alpha);
					//ENGINE->DrawTextInWorld(fontDesc);
					fontDesc.scale = D3DXVECTOR3(m_damageFonts[i].size, m_damageFonts[i].size, m_damageFonts[i].size);
					fontDesc.textColor = D3DXCOLOR(1, 0.3f, 0, alpha);
					ENGINE->DrawTextInWorld(fontDesc);
				}
				else
				{
					ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(m_damageFonts[i].size, m_damageFonts[i].size, m_damageFonts[i].size), D3DXCOLOR(1, 1, 1, alpha));
				}
				
			}
		}
		else if (m_damageFonts[i].m_elapsed >= m_delay - m_fadeOutTime)
		{
			float alpha = (m_delay - m_damageFonts[i].m_elapsed) / m_fadeOutTime;

			if (m_damageFonts[i].isPlayer)
			{

				ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(m_damageFonts[i].size, m_damageFonts[i].size, m_damageFonts[i].size), D3DXCOLOR(1, 0, 0, alpha));
			}
			else
			{
				std::cout << "Font ALpha : " << alpha << std::endl;
				if (m_damageFonts[i].isCritical)
				{
					FontDesc fontDesc;
					fontDesc.text = m_damageFonts[i].font.c_str();
					fontDesc.position = m_damageFonts[i].position;
					fontDesc.scale = D3DXVECTOR3(2.05, 2.05, 2.05);
					fontDesc.rect;
					SetRect(&fontDesc.rect, -400, -20, 400, 20);
					fontDesc.format = DT_CENTER | DT_VCENTER;
					fontDesc.textColor = D3DXCOLOR(1, 0, 0, alpha);
					//ENGINE->DrawTextInWorld(fontDesc);
					fontDesc.scale = D3DXVECTOR3(m_damageFonts[i].size, m_damageFonts[i].size, m_damageFonts[i].size);
					fontDesc.textColor = D3DXCOLOR(1, 0.3f, 0, alpha);
					ENGINE->DrawTextInWorld(fontDesc);

				}
				else
				{
					ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(m_damageFonts[i].size, m_damageFonts[i].size, m_damageFonts[i].size), D3DXCOLOR(1, 1, 1, alpha));
				}
			}
		}
		else
		{
			if (m_damageFonts[i].isPlayer)
			{

				ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(m_damageFonts[i].size, m_damageFonts[i].size, m_damageFonts[i].size), D3DXCOLOR(1, 0, 0, 1));
			}
			else
			{
				if (m_damageFonts[i].isCritical)
				{
					FontDesc fontDesc;
					fontDesc.text = m_damageFonts[i].font.c_str();
					fontDesc.position = m_damageFonts[i].position;
					fontDesc.scale = D3DXVECTOR3(2.05, 2.05, 2.05);
					fontDesc.rect;
					SetRect(&fontDesc.rect, -400, -20, 400, 20);
					fontDesc.format = DT_CENTER | DT_VCENTER;
					fontDesc.textColor = D3DXCOLOR(1, 0, 0, 1);
					//ENGINE->DrawTextInWorld(fontDesc);
					fontDesc.scale = D3DXVECTOR3(m_damageFonts[i].size, m_damageFonts[i].size, m_damageFonts[i].size);
					fontDesc.textColor = D3DXCOLOR(1, 0.3f, 0, 1);
					ENGINE->DrawTextInWorld(fontDesc);

				}
				else
				{
					ENGINE->DrawTextInWorld(m_damageFonts[i].font.c_str(), m_damageFonts[i].position, D3DXVECTOR3(m_damageFonts[i].size, m_damageFonts[i].size, m_damageFonts[i].size), D3DXCOLOR(1, 1, 1, 1));
				}
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
	//desc.isCritical = true;

	if (desc.isCritical)
	{
		desc.font = L"Ä¡¸íÅ¸ " + desc.font;
	}

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
