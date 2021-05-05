#include "stdafx.h"
#include "Q_CollectKey.h"
#include "GameScene.h"
#include "QuestManager.h"
#include "Client_Events.h"

Q_CollectKey::Q_CollectKey()
	: CollectQuest()
{
}

Q_CollectKey::~Q_CollectKey()
{
}

void Q_CollectKey::Initialize()
{
	std::vector<int> collectCount={ 1, 1, 1 };
	std::vector<std::wstring > collectNames = { L"TEMP01", L"TEMP02", L"TEMP03" };
	CollectQuest::Initialize
	(
		L"���� ����",
		L"���� ���忡 �ʿ��� Ű�� ��ƶ�",
		{
			L"������ ���� ����� �˾Ƴ´ٰ�?",
			L"... �׷��� ���� Ű�� ��ƿ�����"
		},
		{
			L"�����ߴ� \n�ٷ� ���״� �غ� ������ ���������"
		},
		{
			L"�˰ڽ��ϴ�."
		},
		{
			L"�˰ڽ��ϴ�."
		},
		EQuestImportance::Main,
		[&]() ->bool
	{
		GameScene *pScene = static_cast<GameScene*>(SCENE);
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"���ϴ� ���");
		if (pQuest->IsCompletelyFinished() == true)
			return true;
		else
			return false;
	},
		[]()
	{
		float exp = 900;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Leoni",
		L"Leoni",
		ECollectType::Multiple,
		collectCount,
		collectNames
		);
}
