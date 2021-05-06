#include "stdafx.h"
#include "Q_PrepareForMission.h"
#include "Client_Events.h"
Q_PrepareForMission::Q_PrepareForMission()
	: Quest()
{
}

Q_PrepareForMission::~Q_PrepareForMission()
{
}

float Q_PrepareForMission::GetCurProgress()
{
	return 1;
}

bool Q_PrepareForMission::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_PrepareForMission::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_PrepareForMission::Initialize()
{
	Quest::Initialize
	(
		L"�ӹ��� ���� �غ�",
		L"����3�� �޼��Ͻÿ�",
		{
			L"�������ܿ� �°� ȯ���� ����",
			L"��ħ �߿Ծ� ���� �Ƹ��� ���ۿ��� �������̶�� �ϴ±�",
			L"� �غ� ��ġ�� �ٽ� ���ɵ���"
		},
		{
			L"���� �������"
		},
		{
			L"�˰ڽ��ϴ�."
		},
		{
			L"�˰ڽ��ϴ�"
		},
		EQuestImportance::Main,
		[]() {return true; }, // ÷���� ����
		[]()
	{
		float exp = 200;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Hieracon_Cora",
		L"Hieracon_Cora"
		);
}
