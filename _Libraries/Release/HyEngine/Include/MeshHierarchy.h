#pragma once

namespace HyEngine
{

	class MeshHierarchy : public ID3DXAllocateHierarchy
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	public :
		explicit MeshHierarchy(std::wstring path);
		virtual ~MeshHierarchy();

		//////////////////////////////////////////////////////////////////////////
		// CREATE & DESTROY
		//////////////////////////////////////////////////////////////////////////
	public :
		STDMETHOD(CreateFrame)(THIS_ LPCSTR name, _Out_ LPD3DXFRAME * ppNewFrame);
		STDMETHOD(CreateMeshContainer)(THIS_
			LPCSTR name,
			CONST D3DXMESHDATA * pMeshData,
			CONST D3DXMATERIAL * pMaterials,
			CONST D3DXEFFECTINSTANCE* pEffectInstance,
			DWORD numMaterials,
			CONST DWORD* pAdjacency,
			LPD3DXSKININFO pSkinInfo,
			LPD3DXMESHCONTAINER* ppNewMeshContainer);
		
		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

		//////////////////////////////////////////////////////////////////////////
		// PRIVATE METHODS
		//////////////////////////////////////////////////////////////////////////
	private :
		void Allocate_Name(_Out_ char** ppName, const char* pFrameName);


		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		const std::wstring m_path;



	};

}