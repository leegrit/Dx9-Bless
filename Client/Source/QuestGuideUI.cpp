#include "stdafx.h"
#include "QuestGuideUI.h"
#include "PathManager.h"
#include "ProgressBar.h"

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

	m_pFillBack = UIPanel::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/EnemyHPBack.png",
		D3DXVECTOR3(381, 117, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(100, 5, 1),
		L"QuestGuideUI_FillBack");
	m_pFillBack->SetActive(false);

	m_pFill = ProgressBar::Create(GetScene(),
		PATH->AssetsPathW() + L"UI/StatusGauge_2.png",
		D3DXVECTOR3(381, 117, 0),
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(100, 5, 1),
		L"QuestGuideUI_Fill");
	m_pFill->SetActive(false);
	
	m_pIcon->SetActive(false);
}

void QuestGuideUI::Render()
{
	
}

void QuestGuideUI::ShowGuideUI(std::wstring questName, std::wstring questContent, float yOffset, float progress)
{
	D3DXVECTOR3 originPos = m_pHeadline->m_pTransform->m_position.operator D3DXVECTOR3();
	m_pHeadline->m_pTransform->SetPosition(D3DXVECTOR3(originPos.x, m_yOrigin - yOffset, 0));
	m_pHeadline->SetActive(true);

	originPos = m_pIcon->m_pTransform->m_position.operator D3DXVECTOR3();
	m_pIcon->m_pTransform->SetPosition(D3DXVECTOR3(originPos.x, m_yOrigin - yOffset, 0));
	m_pIcon->SetActive(true);

	m_questName = questName;
	m_questContent = questContent;

	ENGINE->DrawText(m_questName.c_str(), D3DXVECTOR3(847, m_yFontTitleOri + yOffset, 0), D3DXVECTOR3(0.8, 0.8, 0.8), D3DXCOLOR(1, 1, 1, 1));
	ENGINE->DrawText(m_questContent.c_str(), D3DXVECTOR3(847, m_yFontContentOri + yOffset, 0), D3DXVECTOR3(0.8, 0.8, 0.8), D3DXCOLOR(1, 1, 1, 1));

	if (progress != -1)
	{
		m_pFillBack->SetActive(true);
		m_pFill->SetActive(true);
		m_pFill->SetAmount(progress);

		m_pFillBack->m_pTransform->SetPosition(D3DXVECTOR3(381, m_yFillOrigin - yOffset, 0));
		m_pFill->m_pTransform->SetPosition(D3DXVECTOR3(381, m_yFillOrigin - yOffset, 0));

	}

}

void QuestGuideUI::HideGuideUI()
{
	m_pHeadline->SetActive(false);
	m_pIcon->SetActive(false);

	m_pFill->SetActive(false);
	m_pFillBack->SetActive(false);
}

QuestGuideUI * QuestGuideUI::Create(Scene * pScene, EQuestImportance questImportance, std::wstring name)
{
	QuestGuideUI * ui = new QuestGuideUI(pScene, name);
	ui->Initialize(questImportance);
	return ui;
}
