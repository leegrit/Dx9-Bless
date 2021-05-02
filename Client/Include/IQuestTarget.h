#pragma once

class IQuestTarget
{
public:
	virtual void ShowQuestMark(class Quest* pQuest) PURE;
	virtual void RemoveQuestMark(class Quest* pQuest) PURE;
	virtual void ShowQuestFinishMark(class Quest* pQuest) PURE;
	virtual void RemoveQuestFinishMark(class Quest* pQuest) PURE;
};

