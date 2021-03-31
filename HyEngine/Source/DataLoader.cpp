#include "StandardEngineFramework.h"
#include "DataLoader.h"

using namespace HyEngine;

std::unordered_map<std::wstring, std::shared_ptr<HierarchyData> > DataLoader::dataMap;