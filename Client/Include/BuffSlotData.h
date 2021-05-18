#pragma once
#include "ScriptableData.h"

struct BuffSlotInfo
{
	std::wstring imagePath;
};

class BuffSlotData : public ScriptableData
{
public:
	BuffSlotData();

	bool Push();

};

