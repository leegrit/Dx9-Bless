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
	// ���� �����Ȳ �ۼ�Ƽ��
	virtual float GetCurProgress() PURE; 
	// ����Ʈ Ŭ�����ߴ���
	virtual bool IsFinish() PURE;
	// ����Ʈ ��ǥ ������Ʈ ��� (������ �������Ѵ�.)
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
	// �Ϸ� ��ȭ���� ��ġ�� ȣ��
	// ���⼭ ���� �������ش�, �ݹ��Լ� Ȱ���ؼ�
	void CompletelyFinished();


	virtual void LinkObject();
	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	int m_index;
	// ����Ʈ �̸�
	std::wstring m_questName;
	// ����Ʈ ����
	std::wstring m_questContent;
	// ���� ��ȭ��
	std::vector<std::wstring > m_acceptDialogs;
	// �Ϸ� ��ȭ��
	std::vector<std::wstring> m_finishDialogs;

	int m_acceptDialogIndex = 0;
	int m_finishDialogIndex = 0;

	// ���� �ؽ�Ʈ
	std::wstring m_playerAcceptDialog;
	// �Ϸ�� ������ �÷��̾� �ؽ�Ʈ
	std::wstring m_playerFinishDialog;

	EQuestImportance m_questImportance;
	EQuestState m_questState; 
	
	// ����Ʈ ���� ����
	std::function<bool()> m_openCondition;

	// ������ �����ϴ� �Լ� 
	std::function<void()> m_onFinished;

	std::wstring m_senderName;
	GameObject* m_pSender = nullptr;
	// ����Ʈ�� �Ϸ�Ǿ��� �� ������ �����ϴ� ������ �ϴ� ������Ʈ
	std::wstring m_rewardProviderName;
	GameObject* m_pRewardProvider = nullptr;

	// ����Ʈ ��ǥ (��, NPC)
	//std::vector<GameObject* > m_targets;

};

