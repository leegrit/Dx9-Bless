#pragma once
#include "Mesh.h"
namespace HyEngine
{
// 		class ENGINE_DLL MeshLoader
// 		{
// 		public:
// 			static std::shared_ptr<Mesh> GetMesh(std::string filePath)
// 			{
// 				auto& iter = meshMap.find(filePath);
// 				if (meshMap.end() == iter)
// 				{
// 					std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
// 					mesh->Load(filePath);
// 					meshMap.insert(std::make_pair(filePath, mesh));
// 				}
// 				return meshMap[filePath];
// 
// 			}
// 
// 		private :
// 			static std::unordered_map<std::string, std::shared_ptr<Mesh>>  meshMap;
// 		};
}