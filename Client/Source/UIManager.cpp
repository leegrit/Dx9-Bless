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
#include "InventoryUI.h"
#include "EquipmentUI.h"
#include "Button.h"
#include "GeneralStoreUI.h"
#include "EquipShopUI.h"
#include "NotifyUI.h"
#include "SummonProgressBar.h"



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

	EventDispatcher::AddEventListener(GameEvent::AddItemToInventory, "UIManager",
		std::bind(&UIManager::OnAddItem, this, placeholders::_1));
	EventDispatcher::AddEventListener(GameEvent::BuyItem, "UIManager",
		std::bind(&UIManager::OnBuyItem, this, placeholders::_1));
	EventDispatcher::AddEventListener(GameEvent::InvalidCoolTime, "UIManager",
		std::bind(&UIManager::OnInvalidCoolTime, this, placeholders::_1));
	EventDispatcher::AddEventListener(GameEvent::InvalidTarget, "UIManager",
		std::bind(&UIManager::OnInvalidTarget, this, placeholders::_1));
}


UIManager::~UIManager()
{
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogOpen, "UIManager");
	EventDispatcher::RemoveEventListener(QuestEvent::QuestDialogEnd, "UIManager");

	EventDispatcher::RemoveEventListener(QuestEvent::QuestAccept, "UIManager");
	EventDispatcher::RemoveEventListener(QuestEvent::QuestCompletelyClear, "UIManager");

	EventDispatcher::RemoveEventListener(GameEvent::AddItemToInventory, "UIManager");
	EventDispatcher::RemoveEventListener(GameEvent::BuyItem, "UIManager");
	EventDispatcher::RemoveEventListener(GameEvent::InvalidCoolTime, "UIManager");
	EventDispatcher::RemoveEventListener(GameEvent::InvalidTarget, "UIManager");

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

	m_bDialogChoice = false;

	m_pQuestDialogUI->HideDialog();
	m_pDialogChoiceUI->SetActive(false);
	m_pDialogChoiceIconUI->SetActive(false);

	m_pDialogCancleUI->SetActive(false);
	m_pDialogCancleIconUI->SetActive(false);

}

void UIManager::OnAddItem(void *)
{
	// 이건 제외
	//m_pNotifyUI->PushNotify(ENotifyType::GetItemNotify);
}

void UIManager::OnBuyItem(void *)
{
	m_pNotifyUI->PushNotify(ENotifyType::BuyItemNotify);
}

void UIManager::OnInvalidTarget(void *)
{
	m_pNotifyUI->PushNotify(ENotifyType::InvalidTarget);
}

void UIManager::OnInvalidCoolTime(void *)
{
	m_pNotifyUI->PushNotify(ENotifyType::InvalidCoolTime);
}

void UIManager::Initialize()
{

	m_pTalkPanel = UIPanel::Create(m_pScene,PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_9.png", D3DXVECTOR3(277, -138, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(60, 60, 1), L"TalkPanel");
	m_pTalkPanel->SetActive(false);

	m_pWarpPanel = UIPanel::Create(m_pScene, PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_9.png", D3DXVECTOR3(277, -138, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(60, 60, 1), L"TalkPanel");
	m_pWarpPanel->SetActive(false);

	m_pCollectPanel = UIPanel::Create(m_pScene, PATH->AssetsPathW() + L"UI/BLUIEquip_I4F_9.png", D3DXVECTOR3(277, -138, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(60, 60, 1), L"TalkPanel");
	m_pCollectPanel->SetActive(false);

	m_pCollectProgressBar = CollectProgressBar::Create(m_pScene, L"CollectProgressBar");
	m_pCollectProgressBar->Hide();

	m_pSummonProgressBar = SummonProgressBar::Create(m_pScene, L"SummonProgressBar");
	m_pSummonProgressBar->Hide();

	m_pFadeInOut = FadeInOut::Create(m_pScene);
	m_pFadeInOut->SetActive(false);

	m_pDamageFontScatter = DamageFontScatter::Create(m_pScene, L"DamageFontScatter");

	m_pQuestDialogUI = QuestDialogUI::Create(m_pScene, PATH->AssetsPathW() + L"UI/BLUILooting_I4_0.png", D3DXVECTOR3(0, -260, 0), D3DXVECTOR3(WinMaxWidth, 250, 1), L"QuestDialogUI");
	m_pQuestDialogUI->SetActive(false);

	m_pDialogChoiceUI = Button::Create(m_pScene, L"DialogChoice", PATH->AssetsPathW() + L"UI/BLUITalk_I15_2.png", D3DXVECTOR3(342, -139, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(300, 40, 1));
	m_pDialogChoiceUI->SetActive(false);
	m_pDialogChoiceIconUI = UIPanel::Create(m_pScene, PATH->AssetsPathW() + L"UI/StatusGauge_4.png", D3DXVECTOR3(243, -138, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(25, 35, 1), L"DialogChoiceIcon");
	m_pDialogChoiceIconUI->SetActive(false);

	m_pDialogCancleUI = Button::Create(m_pScene, L"DialogCancle", PATH->AssetsPathW() + L"UI/BLUITalk_I15_2.png", D3DXVECTOR3(342, -99, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(300, 40, 1));
	m_pDialogCancleUI->SetActive(false);
	m_pDialogCancleIconUI = UIPanel::Create(m_pScene, PATH->AssetsPathW() + L"UI/BLUITalk_I15_1.png", D3DXVECTOR3(243, -101, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(25, 25, 1), L"DialogCancleIcon");
	m_pDialogCancleIconUI->SetActive(false);


	m_pInventoryUI = InventoryUI::Create(m_pScene, L"InventoryUI");
	m_pInventoryUI->Hide();

	m_pEquipmentUI = EquipmentUI::Create(m_pScene, L"EquipmentUI");
	m_pEquipmentUI->Hide();

	/* For Shop Ui */
	m_pEquipShopUI = EquipShopUI::Create(m_pScene, L"EquipShopUI");
	m_pEquipShopUI->Hide();

	m_pGeneralStoreUI = GeneralStoreUI::Create(m_pScene, L"GeneralStoreUI");
	m_pGeneralStoreUI->Hide();

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

	/* For Notify */
	m_pNotifyUI = NotifyUI::Create(m_pScene, L"NotifyUI");

	//////////////////////////////////////////////////////////////////////////
	// STATIC UI
	//////////////////////////////////////////////////////////////////////////
	/* For Opener */
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_53.png", D3DXVECTOR3(-480, 352, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_43.png", D3DXVECTOR3(-480 + 50, 352, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_60.png", D3DXVECTOR3(-480 + 100, 352, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_19.png", D3DXVECTOR3(-480 + 150, 352, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_49.png", D3DXVECTOR3(-480 + 200, 352, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_51.png", D3DXVECTOR3(-480 + 250, 352, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));

	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_48.png", D3DXVECTOR3(-480, 352 - 50, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_57.png", D3DXVECTOR3(-480 + 50, 352 - 50, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_39.png", D3DXVECTOR3(-480 + 100, 352 - 50, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_52.png", D3DXVECTOR3(-480 + 150, 352 - 50, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_32.png", D3DXVECTOR3(-480 + 200, 352 - 50, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	m_staticUIList.emplace_back(UIPanel::Create(m_pScene, PATH->ResourcesPathW() + L"Assets/UI/BLUIOpener_I3_33.png", D3DXVECTOR3(-480 + 250, 352 - 50, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(35, 35, 1), L"1"));
	/* For Player HP */
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
	// FOR INVENTORY
	//////////////////////////////////////////////////////////////////////////
	//if (KEYBOARD->Down('I'))
	//{
	//	if (m_pInventoryUI->IsShow())
	//	{
	//		// 이미 열려있는데 I를 누르면 닫는다.
	//		m_pInventoryUI->Hide();
	//	}
	//	else
	//	{
	//		m_pInventoryUI->Show();
	//	}
	//}

	//////////////////////////////////////////////////////////////////////////
	// FOR QUEST 
	//////////////////////////////////////////////////////////////////////////
	if (m_pAcceptedMainQuest)
	{
		m_pMainQuestGuideUI->ShowGuideUI(m_pAcceptedMainQuest->GetQuestName(), m_pAcceptedMainQuest->GetQuestContent(), 0, m_pAcceptedMainQuest->GetCurProgress());
	}
	for (auto& subGuide : m_subQuestGuideUIList)
	{
		subGuide->HideGuideUI();
	}
	for (int i = 0; i < m_acceptedSubQuests.size() && i < m_guideMax; i++)
	{
		m_subQuestGuideUIList[i]->ShowGuideUI(m_acceptedSubQuests[i]->GetQuestName(), m_acceptedSubQuests[i]->GetQuestContent(), (i + 1)* m_acceptedQuestUIOffset, m_acceptedSubQuests[i]->GetCurProgress());
	}

	//////////////////////////////////////////////////////////////////////////
	// DIALOGE CHOICE FONT
	//////////////////////////////////////////////////////////////////////////
	if (m_bDialogChoice)
	{
		ENGINE->DrawText(L"알겠습니다.", D3DXVECTOR3(778, 512, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

		ENGINE->DrawText(L"싫습니다.", D3DXVECTOR3(778, 473, 0), D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1));

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

void UIManager::ShowSummonProgressBar(float amount)
{
	m_pSummonProgressBar->Show(amount);
}

void UIManager::HideSummonProgressBar()
{
	m_pSummonProgressBar->Hide();
}

void UIManager::ToggleInventoryUI()
{
	if (m_pInventoryUI->IsShow())
	{
		// 이미 열려있는데 I를 누르면 닫는다.
		m_pInventoryUI->Hide();
	}
	else
	{
		m_pInventoryUI->Show();
	}
}

InventoryUI * UIManager::GetInventoryUI() const
{
	return m_pInventoryUI;
}

void UIManager::ToggleEquipmentUI()
{
	if (m_pEquipmentUI->IsShow())
	{
		// 이미 열려있는데 I를 누르면 닫는다.
		m_pEquipmentUI->Hide();
	}
	else
	{
		m_pEquipmentUI->Show();
	}
}

EquipmentUI * UIManager::GetEquipmentUI() const
{
	return m_pEquipmentUI;
}

void UIManager::ShowEquipShopUI()
{
	m_pEquipShopUI->Show();
}

void UIManager::HideEquipShopUI()
{
	m_pEquipShopUI->Hide();
}

void UIManager::ShowGeneralStoreUI()
{
	m_pGeneralStoreUI->Show();
}

void UIManager::HideGeneralStoreUI()
{
	m_pGeneralStoreUI->Hide();
}

void UIManager::PushDamageFont(float damage, bool isPlayer, bool isCritical, D3DXVECTOR3 center)
{
	m_pDamageFontScatter->PushDamageFunt(damage, isPlayer, isCritical, center);
}

void UIManager::ShowQuestDialogUI(Quest * pQuest, int dialogIndex, EQuestDialogType questDialogType)
{
	m_pQuestDialogUI->ShowDialog(pQuest->GetSenderName(), pQuest->GetDialog(dialogIndex, questDialogType));
}

void UIManager::ShowDialogChoiceButton(Quest * pQuest, EQuestDialogType questDialogType, std::function<void()> onClick)
{
	m_bDialogChoice = true;
	// 나중에 버튼으로 수정
	m_pDialogChoiceUI->SetActive(true);
	m_pDialogChoiceIconUI->SetActive(true);
	m_pDialogCancleUI->SetActive(true);
	m_pDialogCancleIconUI->SetActive(true);
	m_pDialogChoiceUI->SetButtonEvent(EButtonEvent::ButtonUp, [=]() 
	{
		onClick();
	});
	/*if (KEYBOARD->Down(VK_RETURN))
	{
		onClick();
	}*/
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

	if (m_pAcceptedMainQuest != nullptr && m_pAcceptedMainQuest->GetQuestIndex() == index)
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
	m_pTargetingArrow->LostFocus();
	m_pTargetingArrow->Focus(pFocusedTarget, pEnemy->GetFocusUIOffset());
	m_pTargetingCircle->LostFocus();
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
