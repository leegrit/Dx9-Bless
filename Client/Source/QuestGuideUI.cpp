#include "stdafx.h"
#include "QuestGuideUI.h"
#include "PathManager.h"

QuestGuideUI::QuestGuideUI(Scene * pScene, std::wstring name)
	: UIElement(pScene, name)
{

}

QuestGuideUI::~QuestGuideUI()
{
}


void QuestGuideUI::Initialize(EQuestImportance questImportance)
{
	m_pHeadline = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/BLUINoticeBoard_I1_0.png",
		D3DXVECTOR3(396, 182, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(200, 20, 1), L"QuestGuide_Headline");
	m_pHeadline->SetActive(false);

	if (questImportance == EQuestImportance::Main)
	{
		m_pIcon = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/StatusGauge_4.png",
			D3DXVECTOR3(309, 182, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"QuestGuide_Icon");
	}
	else
	{
		m_pIcon = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/quest mark_question mark5_12.png",
			D3DXVECTOR3(309, 182, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"QuestGuide_Icon");
	}
	
	m_pIcon->SetActive(false);
}

void QuestGuideUI::Render()
{
	
}

void QuestGuideUI::ShowGuideUI(std::wstring questName, std::wstring questContent, float yOffset)
{
	D3DXVECTOR3 originPos = m_pHeadline->m_pTransform->m_position.operator D3DXVECTOR3();
	m_pHeadline->m_pTransform->SetPosition(D3DXVECTOR3(originPos.x, m_yOrigin + yOffset, 0));
	m_pHeadline->SetActive(true);

	originPos = m_pIcon->m_pTransform->m_position.operator D3DXVECTOR3();
	m_pIcon->m_pTransform->SetPosition(D3DXVECTOR3(originPos.x, m_yOrigin + yOffset, 0));
	m_pIcon->SetActive(true);

	m_questName = questName;
	m_questContent = questContent;

	ENGINE->DrawText(m_questName.c_str(), D3DXVECTOR3(820, (WinMaxHeight * 0.5f) - m_yOrigin , 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
	ENGINE->DrawText(m_questContent.c_str(), D3DXVECTOR3(820, (WinMaxHeight * 0.5f) - m_yOrigin  + 20, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

}

void QuestGuideUI::HideGuideUI()
{
	m_pHeadline->SetActive(false);
	m_pIcon->SetActive(false);
}

QuestGuideUI * QuestGuideUI::Create(Scene * pScene, EQuestImportance questImportance, std::wstring name)
{
	QuestGuideUI * ui = new QuestGuideUI(pScene, name);
	ui->Initialize(questImportance);
	return ui;
}
