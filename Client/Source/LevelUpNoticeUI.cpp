#include "stdafx.h"
#include "LevelUpNoticeUI.h"
#include "PathManager.h"
#include "Client_Events.h"
LevelUpNoticeUI::LevelUpNoticeUI(Scene * pScene, std::wstring name)
	: GameObject( ERenderType::None, pScene, nullptr, name)
{
	EventDispatcher::AddEventListener(GameEvent::LevelUp, std::to_string(GetInstanceID()),
		std::bind(&LevelUpNoticeUI::OnLevelUp, this, placeholders::_1));
}

LevelUpNoticeUI::~LevelUpNoticeUI()
{
	EventDispatcher::RemoveEventListener(GameEvent::LevelUp, std::to_string(GetInstanceID()));
}

void LevelUpNoticeUI::Render()
{
}

void LevelUpNoticeUI::Update()
{
	m_pBackground->SetActive(false);
	m_pIcon->SetActive(false);

	if (m_bLevelUp == false)
		return;

	m_pBackground->SetActive(true);
	m_pIcon->SetActive(true);

	m_elapsed += TIMER->getDeltaTime();
	if (m_elapsed > m_delay)
	{
		m_pBackground->SetActive(false);
		m_pIcon->SetActive(false);

		m_elapsed = 0;
		m_bLevelUp = false;
	}
	else if (m_elapsed <= m_fadeInTime)
	{
		float alpha = m_elapsed / m_fadeInTime;

		m_pBackground->SetAlpha(alpha);
		m_pIcon->SetActive(alpha);

		ENGINE->DrawText(m_renderFont.c_str(), D3DXVECTOR3(400, 300, 0), D3DXVECTOR3(2, 2, 2), D3DXCOLOR(1, 1, 1, alpha));

	}
	else if (m_elapsed >= m_delay - m_fadeOutTime)
	{
		float alpha = (m_delay - m_elapsed) / m_fadeOutTime;

		m_pBackground->SetAlpha(alpha);
		m_pIcon->SetAlpha(alpha);
		ENGINE->DrawText(m_renderFont.c_str(), D3DXVECTOR3(400, 300, 0), D3DXVECTOR3(2, 2, 2), D3DXCOLOR(1, 1, 1, alpha));

	}
	else
	{
		m_pBackground->SetAlpha(1);
		m_pIcon->SetAlpha(1);
		ENGINE->DrawText(m_renderFont.c_str(), D3DXVECTOR3(400, 300, 0), D3DXVECTOR3(2, 2, 2), D3DXCOLOR(1, 1, 1, 1));

	}
}

void LevelUpNoticeUI::OnLevelUp(void* value)
{
	m_bLevelUp = true;

	int level = *static_cast<int*>(value);
	// 2레벨이 되었습니다.
	
	std::wstring message;
	message = std::to_wstring(level);
	message = message + L"레벨이 되었습니다.";
	m_renderFont = message;
}

void LevelUpNoticeUI::Initialize()
{
	m_pBackground = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/BLUINoticeBoard_I1_0.png",
		D3DXVECTOR3(0, 144, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1028, 60, 1), L"LevelUpBackground");
	m_pIcon = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/BLUINoticeBoard_IB_1.png",
		D3DXVECTOR3(-194.4, 137.6, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(190, 120, 1), L"LevelUpIcon");
}

LevelUpNoticeUI * LevelUpNoticeUI::Create(Scene * pScene, std::wstring name)
{
	LevelUpNoticeUI * obj = new LevelUpNoticeUI(pScene, name);
	obj->Initialize();
	return obj;
}
