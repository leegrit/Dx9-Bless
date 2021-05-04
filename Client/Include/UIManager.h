#pragma once
#include "Client_Enumerators.h"

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

	void PushDamageFont(float damage, bool isPlayer, bool isCritical, D3DXVECTOR3 center);


public : /* For Quest */
	void ShowQuestDialogUI(class Quest* pQuest, int dialogIndex, EQuestDialogType questDialogType);
	void ShowDialogChoiceButton(class Quest* pQuest, EQuestDialogType questDialogType, std::function<void()> onClick);
	void ProgressQuest(class Quest* pQuest, float progressRate);
	void OnAcceptQuest(void*);
	void OnCompletelyClearQuest(void*);


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

	FadeInOut* m_pFadeInOut = nullptr;

	class DamageFontScatter * m_pDamageFontScatter = nullptr;

private : /* For Quest */
	class QuestDialogUI* m_pQuestDialogUI = nullptr;
	// 나중에 버튼으로 수정할것
	class UIPanel* m_pDialogChoiceUI = nullptr;
	class UIPanel* m_pDialogChoiceIconUI = nullptr;

	class UIPanel * m_pDialogCancleUI = nullptr;
	class UIPanel * m_pDialogCancleIconUI = nullptr;

	class Quest* m_pAcceptedMainQuest = nullptr;
	std::vector<Quest*> m_acceptedSubQuests;
	const float m_acceptedQuestUIOffset = 50;
	const int m_guideMax = 5;
	class QuestGuideUI* m_pMainQuestGuideUI = nullptr;
	std::vector<class QuestGuideUI*> m_subQuestGuideUIList;

	class QuestNoticeUI * m_pQuestNoticeUI = nullptr;

	class LevelUpNoticeUI* m_pLevelUpNoticeUI = nullptr;

};

