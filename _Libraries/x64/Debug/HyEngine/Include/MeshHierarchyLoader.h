#pragma once

namespace HyEngine
{
	class AnimationController;
	class MeshHierarchy;

	struct HierarchyedMesh
	{
		ID3DXAllocateHierarchy* pLoader;
		AnimationController * pAniCtrl;
		D3DXFRAME * pRootFrame;
	};


	class ENGINE_DLL MeshHierarchyLoader
	{
	public :
		static bool TryGetMeshHierarchy(std::wstring filePath, _Out_ AnimationController** ppAniCtrl, _Out_ D3DXFRAME** ppRootFrame);
		static bool TryGetMeshHierarchySW(std::wstring filePath, _Out_ AnimationController** ppAniCtrl, _Out_ D3DXFRAME** ppRootFrame);

		static void Clear();

	private :
		static std::unordered_map<std::wstring, HierarchyedMesh*> meshHierarchyMap;
	};
}

