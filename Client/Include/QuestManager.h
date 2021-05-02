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
	/* 보상까지 받고 완전 끝 */
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
	// 여기 변수들은 대화가 끝나면 초기상태로 초기화 해준다.
	// 퀘스트 대화중인지 확인
	bool m_bOpenQuestDialog = false;
	Quest* m_pOpenQuestDialog = nullptr;
	int m_dialogIndex = 0;
	int m_dialogCount = 0;
	EQuestDialogType m_questDialogType;

private : /* For Accepted Quest */
	std::vector<Quest*> m_acceptedQuests;


};

