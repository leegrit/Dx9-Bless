#include "stdafx.h"
#include "Q_BreadShuttle.h"
#include "Client_Events.h"

Q_BreadShuttle::Q_BreadShuttle()
	: Quest()
{
}

Q_BreadShuttle::~Q_BreadShuttle()
{
}

float Q_BreadShuttle::GetCurProgress()
{
	return 1;
}

bool Q_BreadShuttle::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_BreadShuttle::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_BreadShuttle::Initialize()
{
	Quest::Initialize
	(
		L"�� ��Ʋ",
		L"���� ���� �� ��տ��� �����϶�",
		{
			L"������ ���ε� �����ΰ�?",
			L"���� �ɺθ� �� ���ָ� ������ ��������"
		},
		{
			L"���� ���� ����, ������ �� ������ �ɰž�"
		},
		{
			L"�˰ڽ��ϴ�."
		},
		{
			L"�˰ڽ��ϴ�."
		},
		EQuestImportance::Sub,
		[]() {return true; }, // ÷���� ����
		[]()
	{
		float exp = 200;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Samson",
		L"Samson"
		);
}
