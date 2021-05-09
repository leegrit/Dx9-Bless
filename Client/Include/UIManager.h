#pragma once
#include "Client_Enumerators.h"

namespace HyEngine
{
	class ProgressBar;
	class Button;
}

class Quest;
class FadeInOut;
class UIManager
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
public:
	UIManager(class GameScene* pScene);
	~UIManager();
	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
public : /* For Quest */
	void OnQuestDialogOpen(void*);
	void OnQuestDialogEnd(void*);

public :
	void OnAddItem(void*);
	void OnBuyItem(void*);
	void OnInvalidTarget(void*);
	void OnInvalidCoolTime(void*);
	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void Initialize();
	void Update();

public : /* For StaticUI */
	UIElement* GetStaticUI(std::wstring name);
	//void AddStaticUI(UIElement* pUIElement);


public : /* For Interact */
	void ShowTalkInteractPanel();
	void HideTalkInteractPanel();

	void ShowWarpInteractPanel();
	void HideWarpInteractPanel();

	void ShowCollectInteractPanel();
	void HideCollectInteractPanel();

	void ShowCollectProgressBar(float amount);
	void HideCollectProgressBar();

	void ShowSummonProgressBar(float amount);
	void HideSummonProgressBar();
	
	void ToggleInventoryUI();
	class InventoryUI* GetInventoryUI() const;
	void ToggleEquipmentUI();
	class EquipmentUI* GetEquipmentUI() const;

	void ShowEquipShopUI();
	void HideEquipShopUI();
	void ShowGeneralStoreUI();
	void HideGeneralStoreUI();

	void PushDamageFont(float damage, bool isPlayer, bool isCritical, D3DXVECTOR3 center);


public : /* For Quest */
	void ShowQuestDialogUI(class Quest* pQuest, int dialogIndex, EQuestDialogType questDialogType);
	void ShowDialogChoiceButton(class Quest* pQuest, EQuestDialogType questDialogType, std::function<void()> onClick);
	void ProgressQuest(class Quest* pQuest, float progressRate);
	void OnAcceptQuest(void*);
	void OnCompletelyClearQuest(void*);

public : /* For Battle */
	void OnFocusChanged(GameObject* pFocusedTarget);
	void OnFocusAgain(GameObject* pFocusedTarget);
	void OnFocusLost();

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	class GameScene* m_pScene = nullptr;

private : /* Static UI */
	std::vector<UIElement*> m_staticUIList;

private : /* Interacive UI */
	UIElement* m_pTalkPanel = nullptr;
	UIElement* m_pPickUpPanel = nullptr;
	UIElement* m_pWarpPanel = nullptr;
	UIElement* m_pCollectPanel = nullptr;

	FadeInOut* m_pFadeInOut = nullptr;

	class CollectProgressBar * m_pCollectProgressBar = nullptr;

	class DamageFontScatter * m_pDamageFontScatter = nullptr;

	class SummonProgressBar * m_pSummonProgressBar = nullptr;

private : /* For Quest */
	class QuestDialogUI* m_pQuestDialogUI = nullptr;
	// 나중에 버튼으로 수정할것
	 Button* m_pDialogChoiceUI = nullptr;
	class UIPanel* m_pDialogChoiceIconUI = nullptr;

	 Button * m_pDialogCancleUI = nullptr;
	class UIPanel * m_pDialogCancleIconUI = nullptr;

	class Quest* m_pAcceptedMainQuest = nullptr;
	std::vector<Quest*> m_acceptedSubQuests;
	const float m_acceptedQuestUIOffset = 98;
	const int m_guideMax = 5;
	class QuestGuideUI* m_pMainQuestGuideUI = nullptr;
	std::vector<class QuestGuideUI*> m_subQuestGuideUIList;

	class QuestNoticeUI * m_pQuestNoticeUI = nullptr;

	class LevelUpNoticeUI* m_pLevelUpNoticeUI = nullptr;

private :
	class InventoryUI* m_pInventoryUI = nullptr;
	class EquipmentUI* m_pEquipmentUI = nullptr;

private :/* For Shop Ui */
	class EquipShopUI* m_pEquipShopUI = nullptr;
	class GeneralStoreUI* m_pGeneralStoreUI = nullptr;

private : /* For Battle */
	class TargetingCircle* m_pTargetingCircle = nullptr;
	class TargetingArrow* m_pTargetingArrow = nullptr;
	class EnemyScreenHPBar* m_pEnemyScreenHPBar = nullptr;

private : /* For Notify */
	class NotifyUI * m_pNotifyUI = nullptr;
};

