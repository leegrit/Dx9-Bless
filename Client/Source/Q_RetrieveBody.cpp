#include "stdafx.h"
#include "Q_RetrieveBody.h"
#include "GameScene.h"
#include "QuestManager.h"
#include "Client_Events.h"

Q_RetrieveBody::Q_RetrieveBody()
	: CollectQuest()
{
}


Q_RetrieveBody::~Q_RetrieveBody()
{
}

void Q_RetrieveBody::Initialize()
{
	std::vector<int> collectCount = { 5 };
	std::vector<std::wstring> collectNames = {L"Dead_Soldier"};
	CollectQuest::Initialize
	(
		L"��ü ȸ��",
		L"���� ȸ������ ���� ������ ��ü�� ȸ���϶�",
		{
			L"�̹� �ӹ����� �������� ���ذ� �Ǳ�",
			L"���� ȸ������ ���� ��ü�� ȸ�����ְ�"
		},
		{
			L"����"
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
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"��� ��ġ");
		if (pQuest->IsCompletelyFinished() == true)
			return true;
		else
			return false;
	},
		[]()
	{
		float exp = 400;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Leoni",
		L"Leoni",
		ECollectType::Single,
		collectCount,
		collectNames
		);
}
