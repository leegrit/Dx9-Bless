#include "stdafx.h"
#include "GainSkillNoticeUI.h"
#include "PathManager.h"
#include "Client_Events.h"
#include "SoundManager.h"

GainSkillNoticeUI::GainSkillNoticeUI(Scene * pScene)
	: GameObject(ERenderType::None, pScene, nullptr, L"GainSkillNoticeUI")
{
	EventDispatcher::AddEventListener(GameEvent::GainSkill, "GainSkillNoticeUI",
		std::bind(&GainSkillNoticeUI::OnGainSkill, this, placeholders::_1));

}

GainSkillNoticeUI::~GainSkillNoticeUI()
{
	EventDispatcher::RemoveEventListener(GameEvent::GainSkill, "GainskillNoticeUI");
}

void GainSkillNoticeUI::Render()
{
}

void GainSkillNoticeUI::Update()
{
	m_pBackground->SetActive(false);
	m_pIcon->SetActive(false);

	if (m_bGainSkill == false)
		return;

	m_pBackground->SetActive(true);
	m_pIcon->SetActive(true);

	m_elapsed += TIMER->getDeltaTime();
	if (m_elapsed > m_delay)
	{
		m_pBackground->SetActive(false);
		m_pIcon->SetActive(false);

		m_elapsed = 0;
		m_bGainSkill = false;
	}
	else if (m_elapsed <= m_fadeInTime)
	{
		float alpha = m_elapsed / m_fadeInTime;

		m_pBackground->SetAlpha(alpha);
		m_pIcon->SetActive(alpha);

		ENGINE->DrawText(m_renderFont.c_str(), D3DXVECTOR3(432, 217, 0), D3DXVECTOR3(2, 2, 2), D3DXCOLOR(m_color.r, m_color.g, m_color.b, alpha));

	}
	else if (m_elapsed >= m_delay - m_fadeOutTime)
	{
		float alpha = (m_delay - m_elapsed) / m_fadeOutTime;

		m_pBackground->SetAlpha(alpha);
		m_pIcon->SetAlpha(alpha);
		ENGINE->DrawText(m_renderFont.c_str(), D3DXVECTOR3(432, 217, 0), D3DXVECTOR3(2, 2, 2), D3DXCOLOR(m_color.r, m_color.g, m_color.b, alpha));

	}
	else
	{
		m_pBackground->SetAlpha(1);
		m_pIcon->SetAlpha(1);
		ENGINE->DrawText(m_renderFont.c_str(), D3DXVECTOR3(432, 217, 0), D3DXVECTOR3(2, 2, 2), D3DXCOLOR(m_color.r, m_color.g, m_color.b, 1));

	}
}

void GainSkillNoticeUI::OnGainSkill(void * value)
{
	m_bGainSkill = true;

	int skillIndex = *static_cast<int*>(value);
	// 2레벨이 되었습니다.

	std::wstring message;

	switch (skillIndex)
	{
	case 0 :
		message = L"가드";
		break;
	default:
		assert(false);
		break;
	}

	message = message + L" 스킬을 획득하였습니다.";
	m_renderFont = message;

	SoundDesc desc;
	desc.channelMode = FMOD_LOOP_OFF;
	desc.volumeType = EVolumeTYPE::AbsoluteVolume;
	desc.volume = 0.7f;
	SOUND->PlaySound("GainSkillSound", L"GetSkill.mp3", desc);
}

void GainSkillNoticeUI::Initialize()
{
	m_pBackground = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/BLUINoticeBoard_I1_0.png",
		D3DXVECTOR3(0, 144, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1028, 60, 1), L"LevelUpBackground");
	m_pIcon = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/BLUINoticeBoard_IB_2.png",
		D3DXVECTOR3(-194.4, 137.6, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 120, 1), L"GainSkillIcon");

	float r = (float)191 / 255;
	float g = 1;
	float b = 0;
	m_color = D3DXCOLOR(r, g, b, 1);
}

GainSkillNoticeUI * GainSkillNoticeUI::Create(Scene * pScene)
{
	GainSkillNoticeUI * obj = new GainSkillNoticeUI(pScene);
	obj->Initialize();
	return obj;
}
