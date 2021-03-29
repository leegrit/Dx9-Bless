#include "StandardEngineFramework.h"
#include "MeshHierarchy.h"

HyEngine::MeshHierarchy::MeshHierarchy(std::wstring path)
	: m_path(path)
{

}

HyEngine::MeshHierarchy::~MeshHierarchy()
{
}

STDMETHODIMP HyEngine::MeshHierarchy::CreateFrame(LPCSTR name, _Out_ LPD3DXFRAME * ppNewFrame)
{
	D3DXFRAME_DERIVED* pNewFrame = new D3DXFRAME_DERIVED();
	ZeroMemory(pNewFrame, sizeof(D3DXFRAME_DERIVED));

	Allocate_Name(&pNewFrame->Name, name);

	pNewFrame->CombinedTransformMatrix = *D3DXMatrixIdentity(&pNewFrame->TransformationMatrix);
	*ppNewFrame = pNewFrame;

	return S_OK;
}

STDMETHODIMP HyEngine::MeshHierarchy::CreateMeshContainer(LPCSTR name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstance, DWORD numMaterials, CONST DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = new D3DXMESHCONTAINER_DERIVED();
	ZeroMemory(pMeshContainer, sizeof(D3DXMESHCONTAINER_DERIVED));

	Allocate_Name(&pMeshContainer->Name, name);

	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	LPD3DXMESH pMesh = pMeshData->pMesh;

	unsigned long numFaces = pMesh->GetNumFaces();

	pMeshContainer->pAdjacency = new unsigned long[numFaces * 3];
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(unsigned long) * numFaces * 3);

	unsigned long fvf = pMesh->GetFVF();

	if (!(fvf & D3DFVF_NORMAL))
	{
		pMesh->CloneMeshFVF(pMesh->GetOptions(),
			fvf | D3DFVF_NORMAL,
			DEVICE,
			&pMeshContainer->MeshData.pMesh);
		D3DXComputeNormals(pMeshContainer->MeshData.pMesh, pMeshContainer->pAdjacency);
	}
	else
	{
		
	}

	return S_OK;
}

STDMETHODIMP HyEngine::MeshHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	return E_NOTIMPL;
}

STDMETHODIMP HyEngine::MeshHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	return E_NOTIMPL;
}

void HyEngine::MeshHierarchy::Allocate_Name(char ** ppName, const char * pFrameName)
{
}
