#include "stdafx.h"
#include "Q_AttackToGoblin.h"
#include "Client_Events.h"
#include "GameScene.h"
#include "QuestManager.h"

Q_AttackToGoblin::Q_AttackToGoblin()
	: CombatQuest()
{
}

Q_AttackToGoblin::~Q_AttackToGoblin()
{
}

void Q_AttackToGoblin::Initialize()
{
	CombatQuest::Initialize
	(
		L"��� ��ġ",
		L"��� 10���� ��ġ",
		{
			L"�̰� ����� ����� ȣ�����̱� \n ������� ���� �Ҿ���\n�̾������� �ڳ׵� ���� �ο���߰ھ�",
			L"�� �� �ְڳ�?",
			L"���� ���� ���δ� �ο�� �����״� ��� ����������"
		},
		{
			L"�����߾� �ؾ��� ����"
		},
		{
			L"�˰ڽ��ϴ�"
		},
		{
			L"�˰ڽ��Ѵ�"
		},
		EQuestImportance::Main,
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
		float exp = 400;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Leoni",
		L"Leoni",
		10,
		L"Goblin"
		);
}
