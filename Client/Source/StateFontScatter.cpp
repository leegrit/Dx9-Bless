#include "stdafx.h"
#include "StateFontScatter.h"

StateFontScatter::StateFontScatter(Scene * pScene)
	: GameObject(ERenderType::None, pScene, nullptr, L"StateFontScatter")
{

}

StateFontScatter::~StateFontScatter()
{
}

void StateFontScatter::Render()
{
}

void StateFontScatter::Update()
{
	for (int i = 0; i < m_stateFonts.size(); i++)
	{

		m_stateFonts[i].m_elapsed += TIMER->getDeltaTime();// *m_speed;
		
		if (m_stateFonts[i].dir == D3DXVECTOR3(0, 0, 0))
		{
			//m_stateFonts[i].dir = D3DXVECTOR3(0, 1, 0);
			D3DXVECTOR3 min = D3DXVECTOR3(-1, -1, -1);
			D3DXVECTOR3 max = D3DXVECTOR3(1, 1, 1);
			DxHelper::GetRandomVector(&m_stateFonts[i].dir, &min, &max);

		}
		if (m_stateFonts[i].m_elapsed <= (m_delay * 0.1f))
		{
			float size = MathUtils::lerp(2.0f, 1.0f, (m_stateFonts[i].m_elapsed - (m_delay * 0.1f)) / ((m_delay * 0.2f) - (m_delay * 0.1f)));

			m_stateFonts[i].size = size;
		}
		else if (m_stateFonts[i].m_elapsed > (m_delay * 0.1f) &&
			m_stateFonts[i].m_elapsed <= (m_delay * 0.3f))
		{
			float size = MathUtils::lerp(1.0f, 1.5f, (m_stateFonts[i].m_elapsed - (m_delay * 0.1f)) / ((m_delay * 0.3f) - (m_delay * 0.1f)));
			m_stateFonts[i].size = size;
		}
		else if (m_stateFonts[i].m_elapsed > (m_delay * 0.3f))
		{
			m_stateFonts[i].position += m_stateFonts[i].dir * m_stateFonts[i].speed * TIMER->getDeltaTime();
		}

		if (m_stateFonts[i].m_elapsed >= m_delay)
		{
			m_stateFonts.erase(m_stateFonts.begin() + i);
			i--;
			continue;
		}
		else if (m_stateFonts[i].m_elapsed <= m_fadeInTime)
		{
			float alpha = m_stateFonts[i].m_elapsed / m_fadeInTime;

			ENGINE->DrawTextInWorld(m_stateFonts[i].font.c_str(), m_stateFonts[i].position, D3DXVECTOR3(m_stateFonts[i].size, m_stateFonts[i].size, m_stateFonts[i].size), D3DXCOLOR(1, 0.2f, 0.2f, alpha));



		}
		else if (m_stateFonts[i].m_elapsed >= m_delay - m_fadeOutTime)
		{
			float alpha = (m_delay - m_stateFonts[i].m_elapsed) / m_fadeOutTime;

			ENGINE->DrawTextInWorld(m_stateFonts[i].font.c_str(), m_stateFonts[i].position, D3DXVECTOR3(m_stateFonts[i].size, m_stateFonts[i].size, m_stateFonts[i].size), D3DXCOLOR(1, 0.2f, 0.2f, alpha));


		}
		else
		{
			ENGINE->DrawTextInWorld(m_stateFonts[i].font.c_str(), m_stateFonts[i].position, D3DXVECTOR3(m_stateFonts[i].size, m_stateFonts[i].size, m_stateFonts[i].size), D3DXCOLOR(1, 0.2f, 0.2f, 1));


		}




	}
}

void StateFontScatter::Initialize()
{
}

void StateFontScatter::PushStateFont(std::wstring font, D3DXVECTOR3 center)
{
	StateFontDesc desc;
	desc.font = font;

	D3DXVECTOR3 min = center - D3DXVECTOR3(m_radius, m_radius, m_radius);
	D3DXVECTOR3 max = center + D3DXVECTOR3(m_radius, m_radius, m_radius);
	DxHelper::GetRandomVector(&desc.position,
		&min,
		&max);

	desc.m_elapsed = 0;
	m_stateFonts.push_back(desc);
}

StateFontScatter * StateFontScatter::Create(Scene * pScene)
{
	StateFontScatter* obj = new StateFontScatter(pScene);
	obj->Initialize();
	return obj;
}
