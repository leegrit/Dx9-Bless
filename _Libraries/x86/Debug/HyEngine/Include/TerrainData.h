#pragma once

namespace HyEngine
{
#pragma pack(push, 1)
	struct TerrainData
	{
		int vertexCountX;
		int vertexCountZ;
		float textureCountX;
		float textureCountZ;
		float vertexInterval;
		char diffuseFilePath[256];
		char normalFilePath[256];
	};
#pragma pack(pop)
}