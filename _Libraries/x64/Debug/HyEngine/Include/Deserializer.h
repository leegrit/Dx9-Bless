#pragma once
namespace HyEngine
{
	class HierarchyData;
	class ChunkMapData;
	class ENGINE_DLL Deserializer
	{
	public :
		static shared_ptr<HierarchyData> Deserialize(std::wstring jsonPath);
		static shared_ptr<ChunkMapData>  MapDeserialize(std::wstring jsonPath);
	private :

	};

}
