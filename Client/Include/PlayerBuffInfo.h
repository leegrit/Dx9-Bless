#pragma once
#include "ScriptableData.h"

struct BuffDesc
{
	std::wstring key = L"";
	std::wstring imagePath =L"";
	float elapsed = 0;
	float duration = 0;

	float addAtk = 0;
	float addDef = 0;
	float addMoveSpd = 0;
	float addAtkSpd = 0;
};


using namespace HyEngine;
class PlayerBuffInfo : public ScriptableData
{
public :
	PlayerBuffInfo();
	/* �÷��̾� ��ų�� ���� ���� */
	bool bBuff = false;


	float buffAtk;
	float buffDef;
	float buffMoveSpd;
	float buffAtkSpd;

public:
	void AddBuff(BuffDesc desc);
	void RemoveBuff(BuffDesc desc);

	std::vector<BuffDesc> buffDescs;
};

