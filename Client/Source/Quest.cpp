#include "stdafx.h"
#include "Quest.h"

Quest::Quest()
{
	m_index = UIDGen::Get()->GetUID();
}

void Quest::Initialize
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
	GameObject * pSender, 
	GameObject * pRewardProvider
)
{
	m_questName = questName;
	m_questContent = questContent;
	m_acceptDialogs = acceptDialogs;
	m_finishDialogs = finishDialogs;
	m_playerAcceptDialog = playerAcceptDialog;
	m_questImportance = questImportance;
	m_openCondition = openCondition;
	m_onFinished = onFinished;
	m_pSender = pSender;
	m_pRewardProvider = pRewardProvider;
	m_questState = EQuestState::NotOpen; // default
}

int Quest::GetAcceptDialogCount()
{
	return m_acceptDialogs.size();
}

int Quest::GetFinishDialogCount()
{
	return m_finishDialogs.size();
}

EQuestState Quest::GetQuestState()
{
	return m_questState;
}

int Quest::GetQuestIndex()
{
	return m_index;
}

GameObject * Quest::GetRewardProvider()
{
	return m_pRewardProvider;
}

EQuestImportance Quest::GetQuestImportance()
{
	return m_questImportance;
}

std::wstring Quest::GetDialog(int index, EQuestDialogType dialogType)
{
	switch (dialogType)
	{
	case EQuestDialogType::AcceptDialog:
		assert(index < m_acceptDialogs.size() );
		return m_acceptDialogs[index];
		break;
	case EQuestDialogType::FinishDialog:
		assert(index < m_finishDialogs.size());
		return m_finishDialogs[index];
		break;
	default:
		assert(false);
		break;
	}
}

std::wstring Quest::GetQuestName() const
{
	return m_questName;
}

std::wstring Quest::GetQuestContent() const
{
	return m_questContent;
}

void Quest::SetQuestState(EQuestState state)
{
	m_questState = state;
}

bool Quest::IsOpen()
{
	return m_openCondition();
}

void Quest::CompletelyFinished()
{
	m_onFinished();
}
