#include "StandardEngineFramework.h"
#include "Layer.h"

using namespace HyEngine;
std::unordered_map<std::wstring, UINT> Layer::layersMap =
{
	{ L"Default", Layer::Default },
	{ L"UI", Layer::UI },
	{ L"Player", Layer::Player },
	{L"Enemy", Layer::Enemy}
};
std::vector< unsigned long long> Layer::layersVec =
{
	Layer::Default,
	Layer::UI,
	Layer::Player,
	Layer::Enemy,
	Layer::Slot1,
	Layer::Slot2,
	Layer::Slot3,
	Layer::Slot4,
	Layer::Slot5,
	Layer::Slot6,
	Layer::Slot7,
	Layer::Slot8,
	Layer::Slot9,
	Layer::Slot10,
	Layer::Slot11,
	Layer::Slot12,
	Layer::Slot13,
	Layer::Slot14,
	Layer::Slot15,
	Layer::Slot16
};

void HyEngine::Layer::AddLayer(std::wstring layerName, UINT layer)
{
	layersMap.insert(std::make_pair(layerName, layer));

}

UINT HyEngine::Layer::GetLayer(std::wstring name)
{
	for (auto layerMap : layersMap)
	{
		if (layerMap.first == name)
			return layerMap.second;
	}
	return NULL;
}

std::wstring HyEngine::Layer::LayerToName(UINT layer)
{
	for (auto layerMap : layersMap)
	{
		if (layerMap.second == layer)
			return layerMap.first;
	}
	return NULL;
}

UINT HyEngine::Layer::NameToLayer(std::wstring name)
{
	for (auto layerMap : layersMap)
	{
		if (layerMap.first == name)
			return layerMap.second;
	}
	return NULL;
}

UINT HyEngine::Layer::IndexToLayer(int index)
{
	if (index >= layersVec.size())
		assert(false);
	if (index < 0)
		assert(false);
	return layersVec[index];
}
