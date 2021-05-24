#include "stdafx.h"
#include "PlayerBuffInfo.h"
#include "Client_Events.h"
PlayerBuffInfo::PlayerBuffInfo()
{
	buffDescs.reserve(10);
}
void PlayerBuffInfo::AddBuff(BuffDesc desc)
{

	for (int i = 0; i < buffDescs.size(); i++)
	{
		if (buffDescs[i].key.compare(desc.key) == 0)
		{
			buffDescs[i] = desc;

			EventDispatcher::TriggerEvent(GameEvent::BeginLastingBuff, &desc);
			return;
		}
	}

	buffDescs.push_back(desc);

	EventDispatcher::TriggerEvent(GameEvent::BeginLastingBuff, &desc);
}

void PlayerBuffInfo::RemoveBuff(BuffDesc desc)
{
	EventDispatcher::TriggerEvent(GameEvent::EndLastingBuff, &desc);

	for (int i = 0; i < buffDescs.size(); i++)
	{
		if (buffDescs[i].key.compare(desc.key) == 0)
		{
			buffDescs.erase(buffDescs.begin() + i);
			i--;
			return;
		}
	}
}

float PlayerBuffInfo::GetBuffAtk()
{
	float acc = 0;
	for (auto desc : buffDescs)
	{
		acc += desc.addAtk;
	}
	return acc;
}

float PlayerBuffInfo::GetBuffDef()
{
	float acc = 0;
	for (auto desc : buffDescs)
	{
		acc += desc.addDef;
	}
	return acc;
}

float PlayerBuffInfo::GetBuffMoveSpd()
{
	float acc = 0;
	for (auto desc : buffDescs)
	{
		acc += desc.addMoveSpd;
	}
	return acc;
}

float PlayerBuffInfo::GetBuffAtkSpd()
{
	float acc = 0;
	for (auto desc : buffDescs)
	{
		acc += desc.addAtkSpd;
	}
	return acc;
}
