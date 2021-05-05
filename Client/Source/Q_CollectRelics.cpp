#include "stdafx.h"
#include "Q_CollectRelics.h"
#include "GameScene.h"
#include "QuestManager.h"
#include "Client_Events.h"
Q_CollectRelics::Q_CollectRelics()
	: CollectQuest()
{
}

Q_CollectRelics::~Q_CollectRelics()
{
}

void Q_CollectRelics::Initialize()
{
	std::vector<int> collectCount = {1, 1};
	std::vector<std::wstring> collectNames = { L"Statue01", L"Statue02" };
	CollectQuest::Initialize
	(
		L"���� ����",
		L"����� ������ �����϶�",
		{
			L"�� ���̱��� \n ��ħ �ϼ��� �ʿ��ϴ� ���Դϴ�.",
			L"�� ��ó �������� �����Ͽ� ������ �����ֽʽÿ�"
		},
		{
			L"�����մϴ�",
			L"�Ʊ� �ڶ� ���ϰ� ã�°Ű����� �ѹ� �����ʼ�"
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
		Quest * pQuest = pScene->GetQuestManager()->GetQuest(L"ù �̼�");
		if (pQuest->IsCompletelyFinished() == true)
			return true;
		else
			return false;
	}, 
		[]()
	{
		float exp = 300;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Guido",
		L"Guido",
		ECollectType::Multiple,
		collectCount,
		collectNames
		);
}
