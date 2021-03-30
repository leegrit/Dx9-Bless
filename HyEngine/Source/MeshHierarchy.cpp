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
		pMesh->CloneMeshFVF(pMesh->GetOptions(), fvf, DEVICE, &pMeshContainer->MeshData.pMesh);
	}

	// ������ ������ ä���ִµ� ���� ��쵵 �ֱ� ������ ���ǹ��� �޾��ش�.
	pMeshContainer->NumMaterials = (numMaterials == 0 ? 1 : numMaterials);

	// ���� �����Ҵ� (���� ������ŭ)
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * pMeshContainer->NumMaterials);

	// �ؽ�ó �����Ҵ� (���� ������ŭ)
	pMeshContainer->ppTexture = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	// ������ �ִ� ���
	if(0 != numMaterials) 
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * pMeshContainer->NumMaterials);

		for (unsigned long i = 0; i < pMeshContainer->NumMaterials; i++)
		{

			// �ش� ������ �̸��� X���Ͽ� �ִµ�
			// �̴� �ƽ�Ű�ڵ�� �ۼ��Ǿ� �ֱ� ������ �����ڵ�� ��ȯ�ϰ�
			// �ؽ�ó�� �־��ִ� �۾��� �Ѵ�.
			TCHAR fullPath[128] = L"";
			TCHAR fileName[128] = L"";

			MultiByteToWideChar(CP_ACP, 0,
				pMeshContainer->pMaterials[i].pTextureFilename,
				strlen(pMeshContainer->pMaterials[i].pTextureFilename),
				fileName,
				128);

			lstrcpy(fullPath, m_path.c_str());
			lstrcat(fullPath, fileName);

			if (FAILED(D3DXCreateTextureFromFile(DEVICE, fullPath, &pMeshContainer->ppTexture[i])))
			{
				return E_FAIL;
			}
		}
	}
	else // ������ ���� ���
	{
		// ������ ���� ���� ���� ä���־��ش�. (0���� ���� : ������ ����)
		pMeshContainer->pMaterials[0].MatD3D.Diffuse = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Specular = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Ambient = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Power = 0.f;

		pMeshContainer->ppTexture[0] = NULL;
	}

	if (nullptr == pSkinInfo) // Skinned Mesh�� �ƴ� ��� �׳� ��ȯ�Ѵ�.
		return S_OK;

	pMeshContainer->pSkinInfo = pSkinInfo;
	pMeshContainer->pSkinInfo->AddRef();

	pMeshContainer->MeshData.pMesh->CloneMeshFVF(pMeshContainer->MeshData.pMesh->GetOptions(),
		pMeshContainer->MeshData.pMesh->GetFVF(),
		DEVICE,
		&pMeshContainer->pOriMesh);

	// �� �޽� �����̳ʿ� ������ ��ġ�� ���� ������ ���´�.
	pMeshContainer->numBones = pMeshContainer->pSkinInfo->GetNumBones();

	// ������ �� ��� ���� ���� �����ϱ� ���� ���� �迭
	pMeshContainer->pFrameOffsetMatrix = new D3DXMATRIX[pMeshContainer->numBones];
	ZeroMemory(pMeshContainer->pFrameOffsetMatrix, sizeof(D3DXMATRIX) * pMeshContainer->numBones);

	// �޽ø� �׸��� ���� ����鿡�� �ε��� ���� �Ű��� �ִ�. �̷� ������� ��ȸ�ϸ鼭 ��� ������ ���ʴ�� �������ش�.
	for (ULONG i = 0; i < pMeshContainer->numBones; i++)
		pMeshContainer->pFrameOffsetMatrix[i] = *pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i);

	// ������� ���� �ִ� CombinedMatrix�� �Ź� �����ͼ� �����ִ� ���� �۾���
	// �����ϰ� �����ϱ� ���� �����صδ� ���� �迭
	pMeshContainer->ppFrameCombinedMatrix = new D3DXMATRIX*[pMeshContainer->numBones];
	ZeroMemory(pMeshContainer->ppFrameCombinedMatrix, sizeof(D3DXMATRIX*) * pMeshContainer->numBones);

	// ������ �Ҵ��س��� pMeshContainer->pFrameOffsetmatrix�� pMeshContainer->ppFrameCombinedMatrix�� ������ ��� ���
	pMeshContainer->pRenderingMatrix = new D3DXMATRIX[pMeshContainer->numBones];
	ZeroMemory(pMeshContainer->pRenderingMatrix, sizeof(D3DXMATRIX) * pMeshContainer->numBones);

	*ppNewMeshContainer = pMeshContainer;

	return S_OK;
}

STDMETHODIMP HyEngine::MeshHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	SAFE_DELETE_ARRAY(pFrameToFree->Name);

	if (pFrameToFree->pMeshContainer != nullptr)
		DestroyMeshContainer(pFrameToFree->pMeshContainer);
	if (pFrameToFree->pFrameSibling != nullptr)
		DestroyFrame(pFrameToFree->pFrameSibling);
	if (pFrameToFree->pFrameFirstChild != nullptr)
		DestroyFrame(pFrameToFree->pFrameFirstChild);

	SAFE_DELETE(pFrameToFree);

	return S_OK;
}

STDMETHODIMP HyEngine::MeshHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerToFree;

	for (ULONG i = 0; i < pMeshContainerToFree->NumMaterials; i++)
		SAFE_RELEASE(pMeshContainer->ppTexture[i]);

	SAFE_DELETE_ARRAY(pMeshContainer->ppTexture);
	
	SAFE_RELEASE(pMeshContainer->pOriMesh);
	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
	SAFE_RELEASE(pMeshContainer->pSkinInfo);

	SAFE_DELETE_ARRAY(pMeshContainer->pFrameOffsetMatrix);
	SAFE_DELETE_ARRAY(pMeshContainer->ppFrameCombinedMatrix);
	SAFE_DELETE_ARRAY(pMeshContainer->pRenderingMatrix);
	SAFE_DELETE_ARRAY(pMeshContainer->Name);
	SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
	SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);

	SAFE_DELETE(pMeshContainer);

	return S_OK;
}

void HyEngine::MeshHierarchy::Allocate_Name(_Out_ char ** ppName, const char * pFrameName)
{
	if (nullptr == pFrameName)
		return;

	ULONG iLength = strlen(pFrameName);
	*ppName = new char[iLength + 1];

	strcpy_s(*ppName, iLength + 1, pFrameName);
}
