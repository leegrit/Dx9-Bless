#include "stdafx.h"
#include "Q_NewSkill.h"
#include "Client_Events.h"

Q_NewSkill::Q_NewSkill()
	: Quest()
{
}

Q_NewSkill::~Q_NewSkill()
{
}

float Q_NewSkill::GetCurProgress()
{
	return 1;
}

bool Q_NewSkill::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_NewSkill::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_NewSkill::Initialize()
{
	Quest::Initialize
	(
		L"���ο� ���� ���",
		L"��� ������ �о��",
		{
			L"���� ����� ���� �ͳ�? \n�� ������� �����̶�� �Ѵ�. ",
			L"�� ���� ����� ���� �ͳ� ����. \n�׷��ٸ� ��� ������ ���� ���� ���� ����",
			L"�׷����� �ʵ� ��� ������ �ϳ� �޾����ٵ�?",
			L"����, �׷� �� ��� ������ �а� �� ���� ����� �������� �� \n������ �ִٸ� ����� �ݹ� ���� �����ž�"
		},
		{
			L"�ο� �� ������ ����� Ȱ���ϸ� ���� ���� ������ ��������"
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
		L"Elroy",
		L"Elroy"
		);
}
