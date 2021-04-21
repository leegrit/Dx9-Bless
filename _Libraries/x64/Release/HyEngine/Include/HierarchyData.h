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
		class TerrainData* terrainData;
		class LightData* lightData;
		class EffectData* effectData;
		class UIData* uiData;
		std::vector<class CellData*> cells;
	};

}
