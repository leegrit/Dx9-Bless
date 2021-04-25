#pragma once
#include "Mesh.h"
namespace HyEngine
{
	struct SMesh
	{
		ID3DXBuffer* pAdjBuffer = nullptr;
		ID3DXBuffer* pMtrlBuffer = nullptr;
		DWORD numMtrls = 0;
		ID3DXMesh* pMesh = nullptr;
	};
	class ENGINE_DLL MeshLoader
	{
		
	public :
		static bool TryGetMesh(std::wstring filePath, _Out_ ID3DXBuffer** ppAdjBuffer, _Out_ ID3DXBuffer** ppMtrlBuffer, _Out_ DWORD * pNumMtrls, _Out_ ID3DXMesh** ppMesh);


		static void Clear();

	private :
		static std::unordered_map<std::wstring, SMesh*> meshMap;
	};
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