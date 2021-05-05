#pragma once
#include "Quest.h"

enum class ECollectType
{
	// �������� ������ ����
	Single,
	// �ٸ����� �ϳ��� ����
	Multiple,
};
class CollectQuest : public Quest
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
public :
	CollectQuest();
	virtual ~CollectQuest();

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
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
		std::wstring rewardProviderName,
		ECollectType collectType,
		std::vector<int> collectCount,
		std::vector<std::wstring> collectTargetName
	);

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual float GetCurProgress() override;
	virtual bool IsFinish() override;
	virtual std::vector<GameObject*> GetTargets() override;
	virtual void LinkObject() override;

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
public :
	void OnCollectObject(void*);

private :
	// ��ƾ��ϴ� ����
	std::vector<int> m_collectCount;
	// ���� ���� ����
	std::vector<int> m_collectedCount;

	// ��ƾ��ϴ� ������Ʈ �̸�
	std::vector<std::wstring> m_collectObjNames;
};

