#pragma once
#include "Client_Enumerators.h"

class Quest 
{
public:
	Quest();
	virtual ~Quest() = default;

	//////////////////////////////////////////////////////////////////////////
	// INITIALIZER
	//////////////////////////////////////////////////////////////////////////
public :
	void Initialize
	(
		std::wstring questName,
		std::wstring questContent,
		std::vector<std::wstring> acceptDialogs,
		std::vector<std::wstring> finishDialogs,
		std::wstring playerAcceptDialog,
		std::wstring playerFinishDialog,
		EQuestImportance questImportance,
		std::function<bool()> openCondition,
		std::function<void()> onFinished,
		std::wstring senderName,
		std::wstring rewardProvider
	);

	//////////////////////////////////////////////////////////////////////////
	// PURE
	//////////////////////////////////////////////////////////////////////////
public :
	// 현재 진행상황 퍼센티지
	virtual float GetCurProgress() PURE; 
	// 퀘스트 클리어했는지
	virtual bool IsFinish() PURE;
	// 퀘스트 목표 오브젝트 목록 (아이콘 띄워줘야한다.)
	virtual std::vector<GameObject*> GetTargets() PURE;

	//////////////////////////////////////////////////////////////////////////
	// GETTER
	//////////////////////////////////////////////////////////////////////////
public:
	int GetAcceptDialogCount();
	int GetFinishDialogCount();
	EQuestState GetQuestState();
	int GetQuestIndex();
	GameObject* GetRewardProvider();
	EQuestImportance GetQuestImportance();
	std::wstring GetDialog(int index, EQuestDialogType dialogType);
	std::wstring GetQuestName() const;
	std::wstring GetQuestContent() const;

	//////////////////////////////////////////////////////////////////////////
	// SETTER
	//////////////////////////////////////////////////////////////////////////
public :
	void SetQuestState(EQuestState state);

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	bool IsOpen();
	// 완료 대화까지 마치면 호출
	// 여기서 보상도 적용해준다, 콜백함수 활용해서
	void CompletelyFinished();


	virtual void LinkObject();
	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	int m_index;
	// 퀘스트 이름
	std::wstring m_questName;
	// 퀘스트 내용
	std::wstring m_questContent;
	// 수락 대화들
	std::vector<std::wstring > m_acceptDialogs;
	// 완료 대화들
	std::vector<std::wstring> m_finishDialogs;

	int m_acceptDialogIndex = 0;
	int m_finishDialogIndex = 0;

	// 수락 텍스트
	std::wstring m_playerAcceptDialog;
	// 완료시 나오는 플레이어 텍스트
	std::wstring m_playerFinishDialog;

	EQuestImportance m_questImportance;
	EQuestState m_questState; 
	
	// 퀘스트 오픈 조건
	std::function<bool()> m_openCondition;

	// 보상을 적용하는 함수 
	std::function<void()> m_onFinished;

	std::wstring m_senderName;
	GameObject* m_pSender = nullptr;
	// 퀘스트가 완료되었을 때 보상을 전달하는 역할을 하는 오브젝트
	std::wstring m_rewardProviderName;
	GameObject* m_pRewardProvider = nullptr;

	// 퀘스트 목표 (적, NPC)
	//std::vector<GameObject* > m_targets;

};

