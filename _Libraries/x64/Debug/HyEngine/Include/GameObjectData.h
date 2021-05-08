#pragma once
#include "EditData.h"
#include "TransformData.h"

namespace HyEngine
{
#pragma pack(push,1)
	struct GameObjectData// : public EditData
	{
		GameObjectData();
		//virtual ~GameObjectData() = default;	
		int index;
		char name[256];
		char tag[256];
		int layer;
		int staticType;
		TransformData transform;
	};
#pragma pack(pop)
}