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