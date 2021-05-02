#pragma once
#include "Client_Enumerators.h"

class QuestManager
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
public:
	QuestManager(Scene* pScene);
	~QuestManager();

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
public :
	void OnQuestAccepted(void*);
	/* ������� �ް� ���� �� */
	void OnQuestCompletelyClear(void*);

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	void Initialize();
	void Update();

	void AddQuest(class Quest* pQuest);
	class Quest* GetQuest(int index);


	void ShowQuestDialog(class NonePlayer* pSender, class Quest * pQuest);


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private :
	class GameScene * m_pScene = nullptr;

private : /* For All Quest */
	std::vector<Quest*> m_quests;

private : /* For Quest Dialog */
	// ���� �������� ��ȭ�� ������ �ʱ���·� �ʱ�ȭ ���ش�.
	// ����Ʈ ��ȭ������ Ȯ��
	bool m_bOpenQuestDialog = false;
	Quest* m_pOpenQuestDialog = nullptr;
	int m_dialogIndex = 0;
	int m_dialogCount = 0;
	EQuestDialogType m_questDialogType;

private : /* For Accepted Quest */
	std::vector<Quest*> m_acceptedQuests;


};

