#include "StandardEngineFramework.h"
#include "MeshLoader.h"
using namespace HyEngine;



//std::unordered_map<std::string, std::shared_ptr< Mesh>> MeshLoader::meshMap;

bool HyEngine::MeshLoader::TryGetMesh(std::wstring filePath, _Out_ ID3DXBuffer ** ppAdjBuffer, _Out_  ID3DXBuffer ** ppMtrlBuffer, _Out_ DWORD * pNumMtrls, _Out_ ID3DXMesh ** ppMesh)
{
	auto& iter = meshMap.find(filePath);
	if (meshMap.end() == iter)
	{
		ID3DXBuffer* pAdjBuffer = nullptr;
		ID3DXBuffer* pMtrlBuffer = nullptr;
		DWORD numMtrls = 0;
		ID3DXMesh* pMesh = nullptr;
		/* 없을 경우 */
		HRESULT hr;
		hr = D3DXLoadMeshFromX
		(
			filePath.c_str(),
			D3DXMESH_MANAGED,
			DEVICE,
			&pAdjBuffer,
			&pMtrlBuffer,
			0,
			&numMtrls,
			&pMesh
		);
		assert(SUCCEEDED(hr));

		SMesh* data = new SMesh();
		data->pAdjBuffer = pAdjBuffer;
		data->pMtrlBuffer = pMtrlBuffer;
		data->numMtrls = numMtrls;
		data->pMesh = pMesh;

		meshMap.insert(std::make_pair(filePath, data));

		*ppAdjBuffer = pAdjBuffer;
		*ppMtrlBuffer = pMtrlBuffer;
		*pNumMtrls = numMtrls;
		*ppMesh = pMesh;

	}
	else
	{
		SMesh* data = meshMap[filePath];

		*ppAdjBuffer = data->pAdjBuffer;
		*ppMtrlBuffer = data->pMtrlBuffer;
		*pNumMtrls = data->numMtrls;
		*ppMesh = data->pMesh;
	}
	return true;
}

std::unordered_map<std::wstring, SMesh*> MeshLoader::meshMap;