#include "stdafx.h"
#include "UIManager.h"
#include "PathManager.h"
#include "QuestDialogUI.h"
#include "Quest.h"
#include "Client_Events.h"
#include "UIPanel.h"
#include "GameScene.h"
#include "QuestManager.h"
#include "QuestGuideUI.h"
#include "QuestNoticeUI.h"


UIManager::UIManager(GameScene* pScene)
	:m_pScene(pScene)
{
	EventDispatcher::AddEventListener(QuestEvent::QuestDialogOpen, "UIManager",
		std::bind(&UIManager::OnQuestDialogOpen, this, placeholders::_1));
	EventDispatcher::AddEventListener(QuestEvent::QuestDialogEnd, "UIManager",
		std::bind(&UIManager::OnQuestDialogEnd, this, placeholders::_1));

	EventDispatcher::AddEventListener(QuestEvent::QuestAccept, "UIManager",
		std::bind(&UIManager::OnAcceptQuest, this, placeholders::_1));
	EventDispatcher::AddEventListener(QuestEvent::QuestCompletelyClear, "UIManager",
		std::bind(&UIManager::OnCompletelyClearQuest, this, placeholders::_1));
}


UIManager::~UIManager()
{
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogOpen, "UIManager");
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogEnd, "UIManager");

	EventDispatcher::RemoveEventListener(QuestEvent::QuestAccept, "UIManager");
	EventDispatcher::RemoveEventListener(QuestEvent::QuestCompletelyClear, "UIManager");
}

void UIManager::OnQuestDialogOpen(void *)
{
	for (auto& ui : m_staticUIList)
	{
		ui->SetActive(false);
	}
}

void UIManager::OnQuestDialogEnd(void *)
{
	for (auto& ui : m_staticUIList)
	{
		ui->SetActive(true);
	}

	m_pQuestDialogUI->HideDialog();
	m_pDialogChoiceUI->SetActive(false);
	m_pDialogChoiceIconUI->SetActive(false);

	m_pDialogCancleUI->SetActive(false);
	m_pDialogCancleIconUI->SetActive(false);

}

void UIManager::Initialize()
{

	m_pTalkPanel = UIPanel::Create(m_pScene,PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_1.png", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 100, 1), L"TalkPanel");
	m_pTalkPanel->SetActive(false);

	m_pQuestDialogUI = QuestDialogUI::Create(m_pScene, PATH->AssetsPathW() + L"UI/BLUILooting_I4_0.png", D3DXVECTOR3(0, -260, 0), D3DXVECTOR3(WinMaxWidth, 250, 1), L"QuestDialogUI");
	m_pQuestDialogUI->SetActive(false);

	m_pDialogChoiceUI = UIPanel::Create(m_pScene, PATH->AssetsPathW() + L"UI/BLUITalk_I15_2.png", D3DXVECTOR3(287, -139, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(400, 50, 1), L"DialogChoice");
	m_pDialogChoiceUI->SetActive(false);
	m_pDialogChoiceIconUI = UIPanel::Create(m_pScene, PATH->AssetsPathW() + L"UI/StatusGauge_4.png", D3DXVECTOR3(148, -132, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(33, 44, 1), L"DialogChoiceIcon");
	m_pDialogChoiceIconUI->SetActive(false);

	m_pDialogCancleUI = UIPanel::Create(m_pScene, PATH->AssetsPathW() + L"UI/BLUITalk_I15_2.png", D3DXVECTOR3(287, -73, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(400, 50, 1), L"DialogCancle");
	m_pDialogCancleUI->SetActive(false);
	m_pDialogCancleIconUI = UIPanel::Create(m_pScene, PATH->AssetsPathW() + L"UI/BLUITalk_I15_1.png", D3DXVECTOR3(151, -75, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(25, 25, 1), L"DialogCancleIcon");
	m_pDialogCancleIconUI->SetActive(false);


	/* For QuestGuideUI */
	m_pMainQuestGuideUI = QuestGuideUI::Create(m_pScene, EQuestImportance::Main, L"MainQuestGuide");
	for (int i = 0; i < m_guideMax; i++)
	{
		m_subQuestGuideUIList.emplace_back(QuestGuideUI::Create(m_pScene, EQuestImportance::Sub, L"SubQuestGuide"));
	}

	/* For QuestNoticeUI */
	m_pQuestNoticeUI = QuestNoticeUI::Create(m_pScene, L"QuestNoticeUI");


	/* For Static UI */
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/ClassMark_0.png", D3DXVECTOR3(0, -276, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(120, 120, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/PortraitCircle/PortraitCircle_0.png", D3DXVECTOR3(0, -291, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(160, 160, 1), L"2"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_4.png", D3DXVECTOR3(-368, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"3"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_0.png", D3DXVECTOR3(-295.2, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"4"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_1.png", D3DXVECTOR3(-222, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"5"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_2.png", D3DXVECTOR3(-150.4, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"6"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_3.png", D3DXVECTOR3(150.4, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"7"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_5.png", D3DXVECTOR3(222, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"8"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_6.png", D3DXVECTOR3(295.2, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"9"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_7.png", D3DXVECTOR3(368, -325, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(70, 70, 1), L"11"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_0.png", D3DXVECTOR3(-276, -266, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(400, 20, 1), L"22"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_0.png", D3DXVECTOR3(276, -266, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(400, 20, 1), L"33"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_1.png", D3DXVECTOR3(-276, -265, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(325, 10, 1), L"44"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_2.png", D3DXVECTOR3(276, -265, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(325, 10, 1), L"55"));

}

void UIManager::Update()
{
	//////////////////////////////////////////////////////////////////////////
	// FOR QUEST 
	//////////////////////////////////////////////////////////////////////////
	if (m_pAcceptedMainQuest)
	{
		m_pMainQuestGuideUI->ShowGuideUI(m_pAcceptedMainQuest->GetQuestName(), m_pAcceptedMainQuest->GetQuestContent(), 0);
	}
	for (auto& subGuide : m_subQuestGuideUIList)
	{
		subGuide->HideGuideUI();
	}
	for (int i = 0; i < m_acceptedSubQuests.size() && i < m_guideMax; i++)
	{
		m_subQuestGuideUIList[i]->ShowGuideUI(m_acceptedSubQuests[i]->GetQuestName(), m_acceptedSubQuests[i]->GetQuestContent(), (i + 1)* m_acceptedQuestUIOffset);
	}

}

void UIManager::ShowTalkInteractPanel()
{
	m_pTalkPanel->SetActive(true);
}

void UIManager::HideTalkInteractPanel()
{
	m_pTalkPanel->SetActive(false);
}

void UIManager::ShowQuestDialogUI(Quest * pQuest, int dialogIndex, EQuestDialogType questDialogType)
{
	m_pQuestDialogUI->ShowDialog(pQuest->GetDialog(dialogIndex, questDialogType));
}

void UIManager::ShowDialogChoiceButton(Quest * pQuest, EQuestDialogType questDialogType, std::function<void()> onClick)
{
	// 나중에 버튼으로 수정
	m_pDialogChoiceUI->SetActive(true);
	m_pDialogChoiceIconUI->SetActive(true);
	m_pDialogCancleUI->SetActive(true);
	m_pDialogCancleIconUI->SetActive(true);
	if (KEYBOARD->Down(VK_RETURN))
	{
		onClick();
	}
}

void UIManager::ProgressQuest(Quest * pQuest, float progressRate)
{
}

void UIManager::OnAcceptQuest(void * questIndex)
{
	int index = *(static_cast<int*>(questIndex));
    Quest* quest = m_pScene->GetQuestManager()->GetQuest(index);

	if (quest->GetQuestImportance() == EQuestImportance::Main)
	{
		m_pAcceptedMainQuest = quest;
		m_pQuestNoticeUI->PushQuestNotice(quest->GetQuestName(), EQuestNoticeType::MainQuestAccept);
	}
	else if (quest->GetQuestImportance() == EQuestImportance::Sub)
	{
		m_acceptedSubQuests.push_back(quest);
		m_pQuestNoticeUI->PushQuestNotice(quest->GetQuestName(), EQuestNoticeType::SubQuestAccept);
	}
}

void UIManager::OnCompletelyClearQuest(void * questIndex)
{
	int index = *(static_cast<int*>(questIndex));

	if (m_pAcceptedMainQuest->GetQuestIndex() == index)
	{
		m_pQuestNoticeUI->PushQuestNotice(m_pAcceptedMainQuest->GetQuestName(), EQuestNoticeType::MainQuestCompletelyClear);
		m_pAcceptedMainQuest = nullptr;
		m_pMainQuestGuideUI->HideGuideUI();
		return;
	}
	else
	{
		for (int i = 0; i < m_acceptedSubQuests.size(); i++)
		{
			if (m_acceptedSubQuests[i]->GetQuestIndex() == index)
			{
				m_pQuestNoticeUI->PushQuestNotice(m_acceptedSubQuests[i]->GetQuestName(), EQuestNoticeType::SubQuestCompletelyClear);
				m_acceptedSubQuests.erase(m_acceptedSubQuests.begin() + i);
				
				return;
			}
		}
	}
}
