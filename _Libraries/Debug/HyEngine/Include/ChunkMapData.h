#pragma once
#include "HierarchyData.h"
namespace HyEngine
{
	class HierarchyData;
	class ChunkMapData
	{
	public :
		int group;
		int mapCount;
		std::vector<std::shared_ptr<HierarchyData>> hierarchies;
	};
}

