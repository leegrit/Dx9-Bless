#pragma once
#include "Quest.h"

enum class ECollectType
{
	// 같은종류 여러번 수집
	Single,
	// 다른종류 하나씩 수집
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
	// 모아야하는 개수
	std::vector<int> m_collectCount;
	// 현재 모은 개수
	std::vector<int> m_collectedCount;

	// 모아야하는 오브젝트 이름
	std::vector<std::wstring> m_collectObjNames;
};

