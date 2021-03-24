#pragma once
#include "VectorData.h"

namespace Editor
{
#pragma pack(push, 1)
	struct TransformData
	{
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
	};
#pragma pack(pop)
}