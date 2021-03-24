#pragma once
#include "EditData.h"

namespace Editor
{
#pragma pack(push, 1)
	struct MeshData// : public EditData
	{
		//virtual ~MeshData() = default;
		int index;
		char meshFilePath[256];
		char diffuseTexturePath[256];
	};
#pragma pack(pop)
}
