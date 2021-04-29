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
		//assert(SUCCEEDED(hr));

		hr = pMesh->OptimizeInplace
		(
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_COMPACT |
			D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)pAdjBuffer->GetBufferPointer(),
			0, 0, 0
		);
		//assert(SUCCEEDED(hr));

		D3DVERTEXELEMENT9 meshDeclaration[MAX_FVF_DECL_SIZE];
		DWORD vertexStride = pMesh->GetNumBytesPerVertex();
		if (SUCCEEDED(pMesh->GetDeclaration(meshDeclaration)))
		{
			DWORD numDeclarations = 0;
			for (int i = 0; (i < MAX_FVF_DECL_SIZE) && (meshDeclaration[i].Stream != 0xFF); i++)
			{
				numDeclarations++;
			}
			/* Tangent */
			meshDeclaration[numDeclarations].Stream = 0;
			meshDeclaration[numDeclarations].Offset = (WORD)vertexStride;
			meshDeclaration[numDeclarations].Type = D3DDECLTYPE_FLOAT3;
			meshDeclaration[numDeclarations].Method = D3DDECLMETHOD_DEFAULT;
			meshDeclaration[numDeclarations].Usage = D3DDECLUSAGE_TANGENT;
			meshDeclaration[numDeclarations].UsageIndex = 0;

			/* Binormal */
			meshDeclaration[numDeclarations + 1].Stream = 0;
			meshDeclaration[numDeclarations + 1].Offset = (WORD)(vertexStride + 3 * sizeof(float));
			meshDeclaration[numDeclarations + 1].Type = D3DDECLTYPE_FLOAT3;
			meshDeclaration[numDeclarations + 1].Method = D3DDECLMETHOD_DEFAULT;
			meshDeclaration[numDeclarations + 1].Usage = D3DDECLUSAGE_BINORMAL;
			meshDeclaration[numDeclarations + 1].UsageIndex = 0;

			/* Ending element */
			memset(&meshDeclaration[numDeclarations + 2], 0, sizeof(D3DVERTEXELEMENT9));
			meshDeclaration[numDeclarations + 2].Stream = 0xFF;
			meshDeclaration[numDeclarations + 2].Type = D3DDECLTYPE_UNUSED;

			ID3DXMesh* clonedMesh = nullptr;
			if (SUCCEEDED(pMesh->CloneMesh(pMesh->GetOptions(), meshDeclaration, DEVICE, &clonedMesh)))
			{
				pMesh->Release();
				pMesh = clonedMesh;
			}

		}
		pMesh->UpdateSemantics(meshDeclaration);


		/* Get adjacency */
		LPDWORD pAdjacency = new DWORD[pMesh->GetNumFaces() * 3];
		pMesh->GenerateAdjacency(0.0001f, pAdjacency);

		/* Compute tangent vector */
		D3DXComputeTangent(pMesh, 0, 0, 0, 1, pAdjacency);




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