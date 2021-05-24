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
	/* 플레이어 스킬로 인한 버프 */
	bool bBuff = false;


	float buffAtk;
	float buffDef;
	float buffMoveSpd;
	float buffAtkSpd;

public:
	void AddBuff(BuffDesc desc);
	void RemoveBuff(BuffDesc desc);

	float GetBuffAtk();
	float GetBuffDef();
	float GetBuffMoveSpd();
	float GetBuffAtkSpd();

	std::vector<BuffDesc> buffDescs;
};

