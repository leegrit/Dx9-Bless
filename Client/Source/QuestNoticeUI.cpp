#include "stdafx.h"
#include "QuestNoticeUI.h"
#include "PathManager.h"



QuestNoticeUI::QuestNoticeUI(Scene * pScene, std::wstring name)
	:GameObject(ERenderType::None, pScene,nullptr, name)
{

}

void QuestNoticeUI::Render()
{
	assert(false);
}

void QuestNoticeUI::Update()
{
	m_pBackground->SetActive(false);
	m_pArrowLeft->SetActive(false);
	m_pArrowRight->SetActive(false);
	m_pMainClearIcon->SetActive(false);
	m_pSubClearIcon->SetActive(false);

	if (m_notices.empty())
		return;

	QuestNoticeDesc notice = m_notices.front();

	m_pBackground->SetActive(true);
	m_pArrowLeft->SetActive(true);
	m_pArrowRight->SetActive(true);
	if(notice.type == EQuestNoticeType::MainQuestCompletelyClear)
		m_pMainClearIcon->SetActive(true);
	if(notice.type == EQuestNoticeType::SubQuestCompletelyClear)
		m_pSubClearIcon->SetActive(true);

	m_elapsed += TIMER->getDeltaTime();
	if (m_elapsed > m_delay)
	{
		m_pBackground->SetActive(false);
		m_pArrowLeft->SetActive(false);
		m_pArrowRight->SetActive(false);
		m_pMainClearIcon->SetActive(false);
		m_pSubClearIcon->SetActive(false);

		m_elapsed = 0;
		m_notices.pop();
	}
	else if(m_elapsed <= 0.2f)
	{
		float alpha  = m_elapsed / m_fadeInTime;
		
		m_pBackground->SetAlpha(alpha);
		m_pArrowLeft->SetAlpha(alpha);
		m_pArrowRight->SetAlpha(alpha);
		m_pMainClearIcon->SetAlpha(alpha);
		m_pSubClearIcon->SetAlpha(alpha);
	}
	else if (m_elapsed >= m_delay - m_fadeOutTime)
	{
		float alpha = (m_delay - m_elapsed) / m_fadeOutTime;


		m_pBackground->SetAlpha(alpha);
		m_pArrowLeft->SetAlpha(alpha);
		m_pArrowRight->SetAlpha(alpha);
		m_pMainClearIcon->SetAlpha(alpha);
		m_pSubClearIcon->SetAlpha(alpha);
	}
	else
	{

		m_pBackground->SetAlpha(1);
		m_pArrowLeft->SetAlpha(1);
		m_pArrowRight->SetAlpha(1);
		m_pMainClearIcon->SetAlpha(1);
		m_pSubClearIcon->SetAlpha(1);
	}
}

void QuestNoticeUI::Initialize()
{
	m_pBackground = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/BLUINoticeBoard_I1_0.png",
		D3DXVECTOR3(0, -140, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1028, 150, 1), L"QuestNoticeBackground");
	m_pArrowLeft = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/BLUINoticeBoard_IB_9.png",
		D3DXVECTOR3(-244, -168, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(60, 25, 1), L"QuestNoticeArrowLeft");
	m_pArrowRight = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/BLUINoticeBoard_IB_8.png",
		D3DXVECTOR3(244, -168, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(60, 25, 1), L"QuestNoticeArrowRight");
	m_pMainClearIcon = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/BLUINoticeBoard_IB_12.png",
		D3DXVECTOR3(0, -50, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(120, 120, 1), L"QuestNoticeMainClearIcon");
	m_pSubClearIcon = UIPanel::Create(GetScene(), PATH->AssetsPathW() + L"UI/BLUINoticeBoard_IB_6.png",
		D3DXVECTOR3(0, -56, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 120, 1), L"QuestNoticeSubClearIcon");
}

void QuestNoticeUI::PushQuestNotice(std::wstring questName, EQuestNoticeType type)
{
	QuestNoticeDesc desc;
	desc.questName = questName;
	desc.type = type;

	m_notices.push(desc);
}

QuestNoticeUI * QuestNoticeUI::Create(Scene * pScene, std::wstring name)
{
	QuestNoticeUI * ui = new QuestNoticeUI(pScene, name);
	ui->Initialize();
	return ui;
}
