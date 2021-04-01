#include "StandardEngineFramework.h"
#include "Deserializer.h"
#include "JsonHelper.h"
#include "HierarchyData.h"
#include "GameObjectData.h"
#include "MeshData.h"
#include "MapData.h"
#include "NavMeshData.h"
#include "CellData.h"
#include "ChunkMapData.h"

shared_ptr<HierarchyData> HyEngine::Deserializer::Deserialize(std::wstring jsonPath)
{
	Json::Value root;
	Json::ReadData(jsonPath, &root);

	shared_ptr<HierarchyData> result = std::make_shared<HierarchyData>();
// 	result->gameObjectData = new GameObjectData();
// 	result->meshData = new MeshData();
// 	result->mapData = new MapData();
// 	result->navMeshData = new NavMeshData();

	//Json::Value hierarchyDataJson = root["Hierarchy"];

	/* For GameObjectData */
	Json::Value gameObjectDataJson = root[JsonKey::GameObjectData];
	Json::Value transformDataJson = gameObjectDataJson[JsonKey::Transform];
	Json::Value positionDataJson = transformDataJson[JsonKey::Position];
	Json::Value rotationDataJson = transformDataJson[JsonKey::Rotation];
	Json::Value scaleDataJson = transformDataJson[JsonKey::Scale];

	Json::GetValue(gameObjectDataJson, JsonKey::Index, result->gameObjectData->index);
	Json::GetValue(gameObjectDataJson, JsonKey::Name, result->gameObjectData->name, 256);
	Json::GetValue(gameObjectDataJson, JsonKey::Tag, result->gameObjectData->tag, 256);
	Json::GetValue(gameObjectDataJson, JsonKey::Layer, result->gameObjectData->layer);
	Json::GetValue(gameObjectDataJson, JsonKey::StaticType, result->gameObjectData->staticType);
	Json::GetValue(transformDataJson, JsonKey::Position, result->gameObjectData->transform.position); // TEST
	Json::GetValue(transformDataJson, JsonKey::Rotation, result->gameObjectData->transform.rotation);
	Json::GetValue(transformDataJson, JsonKey::Scale, result->gameObjectData->transform.scale);


	/* For MeshData */
	Json::Value meshDataJson = root[JsonKey::MeshData];

	Json::GetValue(meshDataJson, JsonKey::Index, result->meshData->index);
	Json::GetValue(meshDataJson, JsonKey::MeshFilePath, result->meshData->meshFilePath, 256);
	Json::GetValue(meshDataJson, JsonKey::DiffuseTexturePath, result->meshData->diffuseTexturePath, 256);

	/* For MapData */
	Json::Value mapDataJson = root[JsonKey::MapData];

	Json::GetValue(mapDataJson, JsonKey::Index, result->mapData->index);
	Json::GetValue(mapDataJson, JsonKey::Group, result->mapData->group);

	/* For NavMeshData */
	Json::Value navMeshJson = root[JsonKey::NavMeshData];

	Json::GetValue(navMeshJson, JsonKey::Index, result->navMeshData->index);
	Json::GetValue(navMeshJson, JsonKey::CellCount, result->navMeshData->cellCount);

	/* For Cells */
	for (int i = 0; i < result->navMeshData->cellCount; i++)
	{
		string key = CString::string_format("Cell_%d", i);
		Json::Value cellJson = root[key];
		
		CellData * cellData = new CellData();
		Json::GetValue(cellJson, JsonKey::CellIndex, cellData->cellIndex);
		Json::GetValue(cellJson, JsonKey::PositionX, cellData->position.x);
		Json::GetValue(cellJson, JsonKey::PositionY, cellData->position.y);
		Json::GetValue(cellJson, JsonKey::PositionZ, cellData->position.z);
		Json::GetValue(cellJson, JsonKey::Option, cellData->option);
		Json::GetValue(cellJson, JsonKey::Group, cellData->group);
		result->cells.push_back(cellData);
	}
	return result;
}

shared_ptr<ChunkMapData> HyEngine::Deserializer::MapDeserialize(std::wstring jsonPath)
{
	Json::Value root;
	Json::ReadData(jsonPath, &root);

	shared_ptr<ChunkMapData> result = std::make_shared<ChunkMapData>();
	
	/* For.ChunkData */
	result->group = root[JsonKey::Group].asInt();
	result->mapCount = root[JsonKey::MapCount].asInt();


	/* For.Hierarchy */
	for (int i = 0; i < result->mapCount; i++)
	{
		shared_ptr<HierarchyData> hierarchyData = std::make_shared<HierarchyData>();
		string key = CString::string_format("Hierarchy_%d", i);
		Json::Value hierarchyJson = root[key];

		/* For.GameObjectData */
		Json::Value gameObjectDataJson = hierarchyJson[JsonKey::GameObjectData];
		Json::Value transformDataJson = gameObjectDataJson[JsonKey::Transform];
		Json::Value positionDataJson = transformDataJson[JsonKey::Position];
		Json::Value rotationDataJson = transformDataJson[JsonKey::Rotation];
		Json::Value scaleDataJson = transformDataJson[JsonKey::Scale];

		Json::GetValue(gameObjectDataJson, JsonKey::Index, hierarchyData->gameObjectData->index);
		Json::GetValue(gameObjectDataJson, JsonKey::Name, hierarchyData->gameObjectData->name, 256);
		Json::GetValue(gameObjectDataJson, JsonKey::Tag, hierarchyData->gameObjectData->tag, 256);
		Json::GetValue(gameObjectDataJson, JsonKey::Layer, hierarchyData->gameObjectData->layer);
		Json::GetValue(gameObjectDataJson, JsonKey::StaticType, hierarchyData->gameObjectData->staticType);
		Json::GetValue(transformDataJson, JsonKey::Position, hierarchyData->gameObjectData->transform.position); // TEST
		Json::GetValue(transformDataJson, JsonKey::Rotation, hierarchyData->gameObjectData->transform.rotation);
		Json::GetValue(transformDataJson, JsonKey::Scale, hierarchyData->gameObjectData->transform.scale);


		/* For MeshData */
		Json::Value meshDataJson = hierarchyJson[JsonKey::MeshData];

		Json::GetValue(meshDataJson, JsonKey::Index, hierarchyData->meshData->index);
		Json::GetValue(meshDataJson, JsonKey::MeshFilePath, hierarchyData->meshData->meshFilePath, 256);
		Json::GetValue(meshDataJson, JsonKey::DiffuseTexturePath, hierarchyData->meshData->diffuseTexturePath, 256);

		/* For MapData */
		Json::Value mapDataJson = hierarchyJson[JsonKey::MapData];

		Json::GetValue(mapDataJson, JsonKey::Index, hierarchyData->mapData->index);
		Json::GetValue(mapDataJson, JsonKey::Group, hierarchyData->mapData->group);

		/* For NavMeshData */
		Json::Value navMeshJson = hierarchyJson[JsonKey::NavMeshData];

		Json::GetValue(navMeshJson, JsonKey::Index, hierarchyData->navMeshData->index);
		Json::GetValue(navMeshJson, JsonKey::CellCount, hierarchyData->navMeshData->cellCount);

		result->hierarchies.push_back(hierarchyData);
	}
	return result;
}
