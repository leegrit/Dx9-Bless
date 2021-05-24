#include "stdafx.h"
#include "Q_FirstMission.h"
#include "Client_Events.h"

Q_FirstMission::Q_FirstMission()
	:Quest()
{
}

Q_FirstMission::~Q_FirstMission()
{
}

void Q_FirstMission::Initialize()
{
	Quest::Initialize
	(
		L"ù �̼�",
		L"�ڶ󿡰� ���� �ɾ��",
		{
			L"�츮�� �ӹ��� �ֺ� ����, ������ ��� Ž���ϴ� ���̴�.",
			L"�ϼ��� ���ڸ��� ��а� ���⼭ ������߰ڴ�.",
			L"���� �غ� �Ǹ� �ٽ� ���ϵ���"
		},
		{
			L"����, �켱 ������ �������� ��Ƹ����� ���� ������"
		},
		{
			L"�˰ڽ��ϴ�."
		},
		{
			L"���� �غ� ���Ǿ����ϴ�."
		},
		EQuestImportance::Main,
		[]() {return true; }, // ÷���� ����
		[]()
	{
		float exp = 200;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Leoni",
		L"Leoni"
		);
}

float Q_FirstMission::GetCurProgress()
{
	return -1;
}

bool Q_FirstMission::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_FirstMission::GetTargets()
{
	return std::vector<GameObject*>();
}

