#include "StandardEngineFramework.h"
#include "HierarchyData.h"
#include "GameObjectData.h"
#include "MeshData.h"
#include "CellData.h"
#include "MapData.h"
#include "NavMeshData.h"
#include "EffectData.h"
#include "TerrainData.h"
#include "LightData.h"


GameObjectData * gameObjectData;
MeshData * meshData;
MapData* mapData;
NavMeshData* navMeshData;
EffectData* effectData;
std::vector<CellData*> cells;
HyEngine::HierarchyData::HierarchyData()
{
	gameObjectData = new GameObjectData();
	meshData = new MeshData();
	mapData = new MapData();
	navMeshData = new NavMeshData();
	terrainData = new TerrainData();
	lightData = new LightData();
	effectData = new EffectData();
}

HyEngine::HierarchyData::~HierarchyData()
{
	SAFE_DELETE(gameObjectData);
	SAFE_DELETE(meshData);
	SAFE_DELETE(mapData);
	SAFE_DELETE(navMeshData);
	SAFE_DELETE(terrainData);
	SAFE_DELETE(lightData);
	SAFE_DELETE(effectData);
	for (auto& cell : cells)
	{
		SAFE_DELETE(cell);
	}
	cells.clear();
}
