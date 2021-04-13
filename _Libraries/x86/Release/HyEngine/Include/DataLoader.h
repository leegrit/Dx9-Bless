#pragma once
#include "Deserializer.h"
namespace HyEngine
{
	class ENGINE_DLL DataLoader
	{
	public :
		static std::shared_ptr<HierarchyData> GetData(std::wstring filePath)
		{
			auto& iter = dataMap.find(filePath);
			if (dataMap.end() == iter)
			{
				std::shared_ptr<HierarchyData> data = Deserializer::Deserialize(filePath);
				dataMap.insert(std::make_pair(filePath, data));
			}
			return dataMap[filePath];
		}

	private :
		static std::unordered_map<std::wstring, std::shared_ptr<HierarchyData> > dataMap;
	};
}

