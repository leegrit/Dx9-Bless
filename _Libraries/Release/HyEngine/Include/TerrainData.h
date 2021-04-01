#pragma once

namespace HyEngine
{
#pragma pack(push, 1)
	struct TerrainData
	{
		unsigned int vertexCountX;
		unsigned int vertexCountZ;
		float vertexInterval;
		char diffuseFilePath[256];
		char normalFilePath[256];
	};
#pragma pack(pop)
}