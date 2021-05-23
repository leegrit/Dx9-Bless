#include "stdafx.h"
#include "Quest.h"
#include "ObjectContainer.h"
#include "NonePlayer.h"
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
	std::wstring senderName,
	std::wstring rewardProvider
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
	m_senderName = senderName;
	m_rewardProviderName = rewardProvider;
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

std::wstring Quest::GetSenderName()
{
	NonePlayer* pNonePlayer = static_cast<NonePlayer*>(m_pSender);
	assert(pNonePlayer);
	return pNonePlayer->GetOnlyCharacterName();
}

void Quest::SetQuestState(EQuestState state)
{
	m_questState = state;
}

bool Quest::IsOpen()
{
	return m_openCondition();
}

bool Quest::IsAccepted()
{
	return m_bAccepted;
}

void Quest::CompletelyFinished()
{
	m_bCompletelyFinish = true;
	m_onFinished();
}

bool Quest::IsCompletelyFinished()
{
	return m_bCompletelyFinish;
}

void Quest::Accept()
{
	OnAccept();
	m_bAccepted = true;
}

void Quest::LinkObject()
{
	bool isExist = SCENE->GetObjectContainer()->TryGetDynamicMeshObject(m_senderName, &m_pSender);
	if (isExist == false)
		return;
	isExist = SCENE->GetObjectContainer()->TryGetDynamicMeshObject(m_rewardProviderName, &m_pRewardProvider);
	assert(isExist);

	NonePlayer* npc = dynamic_cast<NonePlayer*>(m_pSender);
	assert(npc);
	npc->AddQuest(this);
}
