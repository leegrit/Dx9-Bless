#include "stdafx.h"
#include "CollectQuest.h"
#include "Client_Events.h"

CollectQuest::CollectQuest()
	: Quest()
{
	EventDispatcher::AddEventListener(QuestEvent::CollectQuestObject, std::to_string(GetQuestIndex()),
		std::bind(&CollectQuest::OnCollectObject, this, placeholders::_1));
}

CollectQuest::~CollectQuest()
{
	EventDispatcher::RemoveEventListener(QuestEvent::CollectQuestObject, std::to_string(GetQuestIndex()));

}

void CollectQuest::Initialize(std::wstring questName, std::wstring questContent, std::vector<std::wstring> acceptDialogs, std::vector<std::wstring> finishDialogs, std::wstring playerAcceptDialog, std::wstring playerFinishDialog, EQuestImportance questImportance, std::function<bool()> openCondition, std::function<void()> onFinished, std::wstring senderName, std::wstring rewardProviderName, ECollectType collectType, std::vector<int> collectCount, std::vector<std::wstring> collectTargetNames)
{
	Quest::Initialize
	(
		questName,
		questContent,
		acceptDialogs,
		finishDialogs,
		playerAcceptDialog,
		playerFinishDialog,
		questImportance,
		openCondition,
		onFinished,
		senderName,
		rewardProviderName
	);
	m_collectCount = collectCount;
	m_collectedCount.clear();
	for (int i = 0; i < m_collectCount.size(); i++)
	{
		m_collectedCount.push_back(0);
	}
	m_collectObjNames = collectTargetNames;
}

float CollectQuest::GetCurProgress()
{
	int collectCount = 0;
	int collectedCount = 0;
	for (int i = 0; i < m_collectCount.size(); i++)
	{
		collectCount += m_collectCount[i];
	}
	for (int i = 0; i < m_collectedCount.size(); i++)
	{
		collectedCount += m_collectedCount[i];
	}
	return (float)collectedCount / collectCount;
}


bool CollectQuest::IsFinish()
{
	int collectCount = 0;
	int collectedCount = 0;
	for (int i = 0; i < m_collectCount.size(); i++)
	{
		collectCount += m_collectCount[i];
	}
	for (int i = 0; i < m_collectedCount.size(); i++)
	{
		collectedCount += m_collectedCount[i];
	}
	return collectedCount >= collectCount;
}

std::vector<GameObject*> CollectQuest::GetTargets()
{
	return std::vector<GameObject*>();
}

void CollectQuest::LinkObject()
{
	Quest::LinkObject();
}

void CollectQuest::OnCollectObject(void *arg)
{
	GameObject * obj = static_cast<GameObject*>(arg);
	for (int i = 0; i < m_collectObjNames.size(); i++)
	{
		if (m_collectObjNames[i].compare(obj->GetName()) == 0)
		{
			if (m_collectedCount[i] < m_collectCount[i])
			{
				m_collectedCount[i]++;
			}
		}
	}
}
