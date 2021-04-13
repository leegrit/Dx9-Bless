#include "StandardEngineFramework.h"
#include "GroupMapObject.h"
#include "ChunkMapData.h"
#include "Deserializer.h"
#include "MapObject.h"
#include "StaticMesh.h"

HyEngine::GroupMapObject::GroupMapObject(Scene * scene, GameObject * parent, std::wstring name)
	: GameObject(ERenderType::None, scene, parent, name)
{

}

HyEngine::GroupMapObject::~GroupMapObject()
{
}

void HyEngine::GroupMapObject::Initialize(std::wstring dataPath)
{
	std::shared_ptr<ChunkMapData> data = Deserializer::MapDeserialize(dataPath);
	
	for (int i = 0; i < data->mapCount; i++)
	{
		StaticMesh::Create(GetScene(), this, L"MapObject_" + i, data->hierarchies[i]);
	}
}

void HyEngine::GroupMapObject::Render()
{
	assert(false);
}

void HyEngine::GroupMapObject::UpdatedData(EDataType dataType)
{
}
