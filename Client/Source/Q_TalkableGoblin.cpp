#include "stdafx.h"
#include "Q_TalkableGoblin.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "QuestManager.h"


Q_TalkableGoblin::Q_TalkableGoblin()
	: CombatQuest()
{
}


Q_TalkableGoblin::~Q_TalkableGoblin()
{
}

void Q_TalkableGoblin::Initialize()
{
	CombatQuest::Initialize
	(
		L"���ϴ� ���",
		L"��� ������ óġ�϶�",
		{
			L"��... �������� �����ּ��� ! ",
			L"��.. ������ \n���� �츮 ������ �̷��� ȣ�������� �ʾҴµ�",
			L"����� ������ �ٲ�鼭 �ٵ� �̻��������", 
			L"������ �� �����Ű���?"
		},
		{
			L"������!",
			L"�׷����� ������ ���� ����� ã�°Ű�����",
			L"�� ��ó�� ������ �� �� �ִ� Ű�� ������־��"
			L"��� Ű�� ��� ������ �Ա��� ������ ����� �ϼ���Ű�� \n�� �� �����ſ���"
		},
		{
			L"�˾Ҵ�"
		},
		{
			L"�˾Ҵ�"
		},
		EQuestImportance::Sub,
		[&]() ->bool
	{
		GameScene *pScene = static_cast<GameScene*>(SCENE);
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"���� ����");
		if (pQuest->IsCompletelyFinished() == true)
			return true;
		else
			return false;
	},
		[]()
	{
		float exp = 800;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"GoblinNPC",
		L"GoblinNPC",
		1,
		L"HGoblin"
		);
}
