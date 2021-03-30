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

	// 재질의 개수를 채워주는데 없는 경우도 있기 때문에 조건문을 달아준다.
	pMeshContainer->NumMaterials = (numMaterials == 0 ? 1 : numMaterials);

	// 재질 동적할당 (재질 개수만큼)
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * pMeshContainer->NumMaterials);

	// 텍스처 동적할당 (재질 개수만큼)
	pMeshContainer->ppTexture = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	// 재질이 있는 경우
	if(0 != numMaterials) 
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * pMeshContainer->NumMaterials);

		for (unsigned long i = 0; i < pMeshContainer->NumMaterials; i++)
		{

			// 해당 재질의 이름은 X파일에 있는데
			// 이는 아스키코드로 작성되어 있기 때문에 유니코드로 변환하고
			// 텍스처를 넣어주는 작업을 한다.
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
	else // 재질이 없는 경우
	{
		// 재질이 없을 때는 직접 채워넣어준다. (0으로 통일 : 검은색 재질)
		pMeshContainer->pMaterials[0].MatD3D.Diffuse = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Specular = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Ambient = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
		pMeshContainer->pMaterials[0].MatD3D.Power = 0.f;

		pMeshContainer->ppTexture[0] = NULL;
	}

	if (nullptr == pSkinInfo) // Skinned Mesh가 아닌 경우 그냥 반환한다.
		return S_OK;

	pMeshContainer->pSkinInfo = pSkinInfo;
	pMeshContainer->pSkinInfo->AddRef();

	pMeshContainer->MeshData.pMesh->CloneMeshFVF(pMeshContainer->MeshData.pMesh->GetOptions(),
		pMeshContainer->MeshData.pMesh->GetFVF(),
		DEVICE,
		&pMeshContainer->pOriMesh);

	// 이 메시 컨테이너에 영향을 미치는 뼈의 개수를 얻어온다.
	pMeshContainer->numBones = pMeshContainer->pSkinInfo->GetNumBones();

	// 최초의 뼈 행렬 상태 값을 저장하기 위한 동적 배열
	pMeshContainer->pFrameOffsetMatrix = new D3DXMATRIX[pMeshContainer->numBones];
	ZeroMemory(pMeshContainer->pFrameOffsetMatrix, sizeof(D3DXMATRIX) * pMeshContainer->numBones);

	// 메시를 그리기 위한 뼈대들에는 인덱스 값이 매겨져 있다. 이런 뼈대들을 순회하면서 행렬 정보를 차례대로 대입해준다.
	for (ULONG i = 0; i < pMeshContainer->numBones; i++)
		pMeshContainer->pFrameOffsetMatrix[i] = *pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i);

	// 뼈대들이 갖고 있는 CombinedMatrix를 매번 가져와서 곱해주는 연산 작업을
	// 원할하게 수행하기 위해 저장해두는 동적 배열
	pMeshContainer->ppFrameCombinedMatrix = new D3DXMATRIX*[pMeshContainer->numBones];
	ZeroMemory(pMeshContainer->ppFrameCombinedMatrix, sizeof(D3DXMATRIX*) * pMeshContainer->numBones);

	// 위에서 할당해놓은 pMeshContainer->pFrameOffsetmatrix와 pMeshContainer->ppFrameCombinedMatrix의 곱셈의 결과 행렬
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
