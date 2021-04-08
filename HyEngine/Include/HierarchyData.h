#pragma once


namespace HyEngine
{

	class HierarchyData
	{
	public :
		HierarchyData();
		~HierarchyData();
		class GameObjectData * gameObjectData;
		class MeshData * meshData;
		class MapData* mapData;
		class NavMeshData* navMeshData;
		class EffectData* effectData;
		std::vector<class CellData*> cells;
	};

}
