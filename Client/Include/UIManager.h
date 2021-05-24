#pragma once
#include "Client_Enumerators.h"
#include "ItemInfo.h"

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
	void OnInventoryUIOpen(void*);
	void OnInventoryUIClose(void*);
	
	void OnEquipmentUIOpen(void*);
	void OnEquipmentUIClose(void*);

	void OnShopUIOpen(void*);
	void OnShopUIClose(void*);

public :
	void OnAddItem(void*);
	void OnBuyItem(void*);
	void OnInvalidTarget(void*);
	void OnInvalidCoolTime(void*);

public :
	void OnBeginCinematic(void*);
	void OnEndCinematic(void*);
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

	void ShowSpoilsUI(ItemInfo itemInfo);
	void HideSpoilsUI();


	void PushDamageFont(float damage, bool isPlayer, bool isCritical, D3DXVECTOR3 center);
	void PushDamageFontForPlayer(float damage, bool isCritical, bool isGaurd, D3DXVECTOR3 center);

	void PushStateFont(std::wstring font, D3DXVECTOR3 center);

public : /* For Mouse */
	void ShowMouseCursor();
	void HideMouseCursor();
	void ShowCrossHair();
	void HideCrossHair();

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
	std::vector<GameObject*> m_skillList;
	std::vector<GameObject*> m_itemList;

	class ItemQuickSlotUI* m_pQuickSlotUI;
	class BuffSlotUI * m_pBuffSlotUI;
private : /* Interacive UI */
	UIElement* m_pTalkPanel = nullptr;
	UIElement* m_pPickUpPanel = nullptr;
	UIElement* m_pWarpPanel = nullptr;
	UIElement* m_pCollectPanel = nullptr;

	FadeInOut* m_pFadeInOut = nullptr;

	class CollectProgressBar * m_pCollectProgressBar = nullptr;

	class DamageFontScatter * m_pDamageFontScatter = nullptr;
	class StateFontScatter * m_pStateFontScatter = nullptr;

	class SummonProgressBar * m_pSummonProgressBar = nullptr;

	class SpoilsUI* m_pSpoilsUI = nullptr;

private :
	class MouseCursorUI * m_pMouseCursorUI = nullptr;
	UIPanel* m_pCrossHairUI = nullptr;

private : /* For Quest */
	class QuestDialogUI* m_pQuestDialogUI = nullptr;
	// 나중에 버튼으로 수정할것
	 Button* m_pDialogChoiceUI = nullptr;
	class UIPanel* m_pDialogChoiceIconUI = nullptr;

	 Button * m_pDialogCancleUI = nullptr;
	class UIPanel * m_pDialogCancleIconUI = nullptr;

	bool m_bDialogChoice = false;

	class Quest* m_pAcceptedMainQuest = nullptr;
	std::vector<Quest*> m_acceptedSubQuests;
	const float m_acceptedQuestUIOffset = 98;
	const int m_guideMax = 5;
	class QuestGuideUI* m_pMainQuestGuideUI = nullptr;
	std::vector<class QuestGuideUI*> m_subQuestGuideUIList;

	class QuestNoticeUI * m_pQuestNoticeUI = nullptr;

	class LevelUpNoticeUI* m_pLevelUpNoticeUI = nullptr;

	class GainSkillNoticeUI* m_pGainSkillNoticeUI = nullptr;

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

