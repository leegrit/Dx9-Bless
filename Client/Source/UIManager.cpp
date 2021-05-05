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
#include "FadeInOut.h"
#include "ProgressBar.h"
#include "LevelUpNoticeUI.h"
#include "DamageFontScatter.h"
#include "TargetingArrow.h"
#include "TargetingCircle.h"
#include "Enemy.h"
#include "EnemyScreenHPBar.h"
#include "CollectProgressBar.h"



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
	m_pFadeInOut->FadeIn([]() {});
	for (auto& ui : m_staticUIList)
	{
		ui->SetActive(false);
	}
}

void UIManager::OnQuestDialogEnd(void *)
{
	m_pFadeInOut->FadeIn([]() {}, 0.5f);
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

	m_pWarpPanel = UIPanel::Create(m_pScene, PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_1.png", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 100, 1), L"TalkPanel");
	m_pWarpPanel->SetActive(false);

	m_pCollectPanel = UIPanel::Create(m_pScene, PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_1.png", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 100, 1), L"TalkPanel");
	m_pCollectPanel->SetActive(false);

	m_pCollectProgressBar = CollectProgressBar::Create(m_pScene, L"CollectProgressBar");
	m_pCollectProgressBar->Hide();

	m_pFadeInOut = FadeInOut::Create(m_pScene);
	m_pFadeInOut->SetActive(false);

	m_pDamageFontScatter = DamageFontScatter::Create(m_pScene, L"DamageFontScatter");

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

	m_pLevelUpNoticeUI = LevelUpNoticeUI::Create(m_pScene, L"LevelUpNoticeUI");

	/* For Battle UI */
	m_pTargetingCircle = TargetingCircle::Create(m_pScene, L"TargetingCircle");
	m_pTargetingCircle->m_pTransform->SetScale(3, 3, 1);
	m_pTargetingArrow = TargetingArrow::Create(m_pScene, L"TargetingArrow");
	m_pTargetingArrow->m_pTransform->SetScale(10, 10, 1);

	m_pEnemyScreenHPBar = EnemyScreenHPBar::Create(m_pScene, L"EnemyScreenHPBar");
	m_pEnemyScreenHPBar->Hide();

	/* For Static UI */
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/ClassMark_0.png", D3DXVECTOR3(0, -312.8, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(80, 80, 1), L"1"));
	//m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/PortraitCircle/PortraitCircle_0.png", D3DXVECTOR3(0, -291, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(160, 160, 1), L"2"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_4.png", D3DXVECTOR3(-258, -341, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(45, 45, 1), L"3"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_0.png", D3DXVECTOR3(-210, -341, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(45, 45, 1), L"4"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_1.png", D3DXVECTOR3(-162, -341, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(45, 45, 1), L"5"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_2.png", D3DXVECTOR3(-114, -341, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(45, 45, 1), L"6"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_3.png", D3DXVECTOR3(114, -341, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(45, 45, 1), L"7"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_5.png", D3DXVECTOR3(162, -341, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(45, 45, 1), L"8"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_6.png", D3DXVECTOR3(210, -341, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(45, 45, 1), L"9"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/SkillIcon/Lups/Lups_7.png", D3DXVECTOR3(258, -341, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(45, 45, 1), L"11"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_0.png", D3DXVECTOR3(-235, -308.4, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(350, 15, 1), L"PlayerHP_Back"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_0.png", D3DXVECTOR3(235, -308, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(350, 15, 1), L"PlayerMP_Back"));
	m_staticUIList.emplace_back(ProgressBar::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_1.png", D3DXVECTOR3(-235.2, -308, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(286, 6.5, 1), L"PlayerHP_Fill"));
	m_staticUIList.emplace_back(ProgressBar::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/StatusGauge_2.png", D3DXVECTOR3(235.2, -308, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(286, 6.5, 1), L"PlayerMP_Fill"));
	/* exp */
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_2.png", D3DXVECTOR3(-462, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"44"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_3.png", D3DXVECTOR3(-361, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"55"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_3.png", D3DXVECTOR3(-261, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"55"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_3.png", D3DXVECTOR3(-161, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"55"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_3.png", D3DXVECTOR3(-61, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"55"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_3.png", D3DXVECTOR3(39, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"55"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_3.png", D3DXVECTOR3(139, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"55"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_3.png", D3DXVECTOR3(239, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"55"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_3.png", D3DXVECTOR3(339, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"55"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_3.png", D3DXVECTOR3(439, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"55"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_3.png", D3DXVECTOR3(539, -373, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 10, 1), L"55"));
	/* exp fill */
	m_staticUIList.emplace_back(ProgressBar::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIEXPBar_I3_5.png", D3DXVECTOR3(13.2, -372.6, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1000, 1.2, 1), L"PlayerExp_Fill"));
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

UIElement * UIManager::GetStaticUI(std::wstring name)
{
	for (auto& ui : m_staticUIList)
	{
		if (ui->CompareName(name))
			return ui;
	}
	return nullptr;
}

void UIManager::ShowTalkInteractPanel()
{
	m_pTalkPanel->SetActive(true);
}

void UIManager::HideTalkInteractPanel()
{
	m_pTalkPanel->SetActive(false);
}

void UIManager::ShowWarpInteractPanel()
{
	m_pWarpPanel->SetActive(true);
}

void UIManager::HideWarpInteractPanel()
{
	m_pWarpPanel->SetActive(false);
}

void UIManager::ShowCollectInteractPanel()
{
	m_pCollectPanel->SetActive(true);
}

void UIManager::HideCollectInteractPanel()
{
	m_pCollectPanel->SetActive(false);
}

void UIManager::ShowCollectProgressBar(float amount)
{
	m_pCollectProgressBar->Show(amount);
}

void UIManager::HideCollectProgressBar()
{
	m_pCollectProgressBar->Hide();
}

void UIManager::PushDamageFont(float damage, bool isPlayer, bool isCritical, D3DXVECTOR3 center)
{
	m_pDamageFontScatter->PushDamageFunt(damage, isPlayer, isCritical, center);
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

void UIManager::OnFocusChanged(GameObject * pFocusedTarget)
{
	Enemy* pEnemy = static_cast<Enemy*>(pFocusedTarget);
	assert(pEnemy);
	m_pTargetingArrow->Focus(pFocusedTarget, pEnemy->GetFocusUIOffset());
	m_pTargetingCircle->Focus(pFocusedTarget, pEnemy->GetFocusUIOffset());

	m_pEnemyScreenHPBar->Show(pFocusedTarget);
}

void UIManager::OnFocusAgain(GameObject* pFocusedTarget)
{
	m_pEnemyScreenHPBar->Show(pFocusedTarget);

}

void UIManager::OnFocusLost()
{
	m_pTargetingArrow->LostFocus();
	m_pTargetingCircle->LostFocus();

	m_pEnemyScreenHPBar->Hide();
}
