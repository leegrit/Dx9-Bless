#include "StandardEngineFramework.h"
#include "MeshHierarchyLoader.h"
#include "AnimationController.h"
#include "MeshHierarchy.h"



bool HyEngine::MeshHierarchyLoader::TryGetMeshHierarchy(std::wstring filePath,_Out_ AnimationController ** ppAniCtrl,_Out_ D3DXFRAME ** ppRootFrame)
{
	auto& iter = meshHierarchyMap.find(filePath);
	if (meshHierarchyMap.end() == iter)
	{
		std::wstring dirPath = Path::GetDirectoryName(filePath);
		/* Create Hierarchy Allocator */
		MeshHierarchy * pLoader = new MeshHierarchy(dirPath);
		if (pLoader == nullptr)
			return false;

		LPD3DXANIMATIONCONTROLLER pAniCtrl = nullptr;

		D3DXFRAME * pRootFrame = nullptr;

		HRESULT hr;
		hr = D3DXLoadMeshHierarchyFromX
		(
			filePath.c_str(),
			D3DXMESH_MANAGED,
			DEVICE,
			pLoader,
			NULL,
			&pRootFrame,
			&pAniCtrl
		);
		if (FAILED(hr))
		{
			SEND_LOG_WARNING("MeshHierarchyLoad Failed");
			return false;
		}

		AnimationController* pAnimationController = new AnimationController(pAniCtrl);
		if (pAnimationController == nullptr)
			return false;


		HierarchyedMesh * pHierarchyedMesh = new HierarchyedMesh();
		pHierarchyedMesh->pLoader = pLoader;
		pHierarchyedMesh->pRootFrame = pRootFrame;
		pHierarchyedMesh->pAniCtrl = pAnimationController;


		meshHierarchyMap.insert(std::make_pair(filePath, pHierarchyedMesh));

		*ppAniCtrl = pAnimationController;
		*ppRootFrame = (D3DXFRAME_DERIVED*)pRootFrame;
	}
	else
	{
		HierarchyedMesh * result = meshHierarchyMap[filePath];

		*ppAniCtrl = new AnimationController(*result->pAniCtrl);
		*ppRootFrame = result->pRootFrame;
	}
// 	else
// 	{
// 		HierarchyedMesh * result = meshHierarchyMap[filePath];
// 
// 		/* Test */
// 		//*ppAniCtrl = pAnimationController;
// 		//*ppRootFrame = pRootFrame;
// 
// 		//*ppAniCtrl = result->pAniCtrl;
// 		*ppAniCtrl = new AnimationController(*result->pAniCtrl);
// 		//*ppRootFrame = result->pRootFrame;
// 		*ppRootFrame = new D3DXFRAME_DERIVED(*(D3DXFRAME_DERIVED*)result->pRootFrame);
// 	}
	//**ppRootFrame = *result->pRootFrame;
	return true;
}

void HyEngine::MeshHierarchyLoader::Clear()
{
	for (auto& meshHierarchy : meshHierarchyMap)
	{
		SAFE_DELETE(meshHierarchy.second->pAniCtrl);
		meshHierarchy.second->pLoader->DestroyFrame(meshHierarchy.second->pRootFrame);
		SAFE_DELETE(meshHierarchy.second->pLoader);
		SAFE_DELETE(meshHierarchy.second);
	}
	meshHierarchyMap.clear();
}



std::unordered_map<std::wstring, HierarchyedMesh*> MeshHierarchyLoader::meshHierarchyMap;

