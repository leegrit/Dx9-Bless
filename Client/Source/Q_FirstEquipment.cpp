#include "stdafx.h"
#include "Q_FirstEquipment.h"
#include "Client_Events.h"

Q_FirstEquipment::Q_FirstEquipment()
	: Quest()
{
}

Q_FirstEquipment::~Q_FirstEquipment()
{
}

float Q_FirstEquipment::GetCurProgress()
{
	return 1;
}

bool Q_FirstEquipment::IsFinish()
{
	return IsAccepted();
}

std::vector<GameObject*> Q_FirstEquipment::GetTargets()
{
	return std::vector<GameObject*>();
}

void Q_FirstEquipment::Initialize()
{
	Quest::Initialize
	(
		L"ù ���",
		L"���������� ���⸦ ���� �� �����϶�",
		{
			L"���� ��� �װ� ����?",
			L"���������� ����� ��������� �ʰھ�"
		},
		{
			L"�׷� �ڰ�� ������ �������"
		},
		{
			L"�˰ڽ��ϴ�."
		},
		{
			L"�˰ڽ��ϴ�"
		},
		EQuestImportance::Sub,
		[]() {return true; }, // ÷���� ����
		[]()
	{
		float exp = 300;
		EventDispatcher::TriggerEvent(GameEvent::SendExp, (void*)&exp);
	}, // ���� ���� 
		L"Bran",
		L"Bran"
		);
}
