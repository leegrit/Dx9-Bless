#include "stdafx.h"
#include "QuestManager.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "Client_Enumerators.h"
#include "Quest.h"
#include "UIManager.h"
#include "Character.h"



QuestManager::QuestManager(Scene * pScene)
{
	m_pScene = dynamic_cast<GameScene*>(pScene);
	assert(m_pScene);
}

QuestManager::~QuestManager()
{
}

void QuestManager::OnQuestAccepted(void *)
{

}

void QuestManager::OnQuestCompletelyClear(void *)
{
	// ������ ����Ʈ ������� ��Ͽ��� ���������
}

void QuestManager::Initialize()
{

}

void QuestManager::Update()
{
	//////////////////////////////////////////////////////////////////////////
	// FOR QUEST OPEN
	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < m_quests.size(); i++)
	{
		if (m_quests[i]->GetQuestState() == EQuestState::NotOpen)
		{
			if (m_quests[i]->IsOpen() == true)
			{
				m_quests[i]->SetQuestState(EQuestState::Open);
			}
		}

	}


	//////////////////////////////////////////////////////////////////////////
	// FOR QUEST DIALOG
	//////////////////////////////////////////////////////////////////////////
	/* ����Ʈ ��ȭ���϶��� ���� */
	if (m_bOpenQuestDialog)
	{
		if (KEYBOARD->Down(VK_ESCAPE))
		{
			int index = m_pOpenQuestDialog->GetQuestIndex();

			// ��ȭ ����
			EventDispatcher::TriggerEvent(QuestEvent::QuestDialogEnd, (void*)&index);
			m_bOpenQuestDialog = false;
			m_pOpenQuestDialog = nullptr;
			m_dialogIndex = 0;
			m_dialogCount = 0;
		}

		if (KEYBOARD->Down(VK_SPACE) || KEYBOARD->Down(VK_RETURN))
		{
			// ���� dialog
			if (m_dialogIndex < m_dialogCount)
			{
				m_pScene->GetUIManager()->ShowQuestDialogUI(m_pOpenQuestDialog, m_dialogIndex, m_questDialogType);
				m_dialogIndex++;
			}
			else
			{
				m_pScene->GetUIManager()->ShowDialogChoiceButton(m_pOpenQuestDialog, m_questDialogType, [&]()
				{
					int index = m_pOpenQuestDialog->GetQuestIndex();

					if (m_questDialogType == EQuestDialogType::AcceptDialog)
					{
						/* Accept */
						EventDispatcher::TriggerEvent(QuestEvent::QuestAccept, (void*)&index);
						m_acceptedQuests.push_back(m_pOpenQuestDialog);
						/* targets�� �ش� ����Ʈ ǥ�� �޾��ֱ� */
						for (auto& target : m_pOpenQuestDialog->GetTargets())
						{
							Character * questTarget = dynamic_cast<Character*>(target);
							assert(questTarget);

							questTarget->ShowQuestMark(m_pOpenQuestDialog);
						}
					}
					if (m_questDialogType == EQuestDialogType::FinishDialog)
					{
						/* Completely Clear */
						EventDispatcher::TriggerEvent(QuestEvent::QuestCompletelyClear, (void*)&index);
						for (int i = 0; i < m_acceptedQuests.size(); i++)
						{
							if (m_pOpenQuestDialog == m_acceptedQuests[i])
							{	
								m_acceptedQuests.erase(m_acceptedQuests.begin() + i);
								break;
							}
						}
						Character* rewardProvider = dynamic_cast<Character*>(m_pOpenQuestDialog->GetRewardProvider());
						assert(rewardProvider);

						rewardProvider->RemoveQuestFinishMark(m_pOpenQuestDialog);
					}
					

					/* ��ȭ ���� */
					EventDispatcher::TriggerEvent(QuestEvent::QuestDialogEnd, (void*)&index);
					m_bOpenQuestDialog = false;
					m_pOpenQuestDialog = nullptr;
					m_dialogIndex = 0;
					m_dialogCount = 0;
				});
			}
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	// FOR ACCEPTED QUEST
	//////////////////////////////////////////////////////////////////////////
	for(int i = 0; i < m_acceptedQuests.size(); i++)
	{
		// �Ҵ緮 ä�� ����Ʈ���� 
		// Progress�� ��� ȣ�����ش�.
		// ������� ���� ���� ���� ����Ʈ�� ������ ��Ͽ� ����
		m_pScene->GetUIManager()->ProgressQuest(m_acceptedQuests[i], m_acceptedQuests[i]->GetCurProgress());


		int questIndex = m_acceptedQuests[i]->GetQuestIndex();
		if (m_acceptedQuests[i]->IsFinish())
		{
			EventDispatcher::TriggerEvent(QuestEvent::QuestFinish, (void*)&questIndex);
			/* targets�� �ش� ����Ʈ ǥ�� �������ֱ� */
			for (auto& target : m_acceptedQuests[i]->GetTargets())
			{
				Character * questTarget = dynamic_cast<Character*>(target);
				assert(questTarget);

				questTarget->RemoveQuestMark(m_acceptedQuests[i]);
			}

			Character* rewardProvider = dynamic_cast<Character*>(m_acceptedQuests[i]->GetRewardProvider());
			assert(rewardProvider);

			rewardProvider->ShowQuestFinishMark(m_acceptedQuests[i]);


			m_acceptedQuests.erase(m_acceptedQuests.begin() + i);
			i--;
			continue;
		}

		

	}
}

void QuestManager::AddQuest(Quest * pQuest)
{
	if (pQuest->GetQuestState() == EQuestState::Clear)
		return;

	m_quests.push_back(pQuest);

	if (pQuest->GetQuestState() == EQuestState::Accepted)
	{
		m_acceptedQuests.push_back(pQuest);
	}
}

Quest* QuestManager::GetQuest(int index)
{
	for (auto quest : m_quests)
	{
		if (quest->GetQuestIndex() == index)
			return quest;
	}
	return nullptr;
}

void QuestManager::ShowQuestDialog(NonePlayer * pSender, Quest * pQuest)
{
	EventDispatcher::TriggerEvent(QuestEvent::QuestDialogOpen, nullptr);
	m_pOpenQuestDialog = pQuest;
	m_bOpenQuestDialog = true;
	m_dialogIndex = 0;

	if (m_pOpenQuestDialog->IsFinish())
	{
		m_questDialogType = EQuestDialogType::FinishDialog;
		m_dialogCount = m_pOpenQuestDialog->GetFinishDialogCount();
	}
	else
	{
		m_questDialogType = EQuestDialogType::AcceptDialog;
		m_dialogCount = m_pOpenQuestDialog->GetAcceptDialogCount();
	}
	m_pScene->GetUIManager()->ShowQuestDialogUI(m_pOpenQuestDialog, m_dialogIndex, m_questDialogType);
	m_dialogIndex++;
}
