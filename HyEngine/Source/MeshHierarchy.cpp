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

	/* Calculate Tangent */
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

		ID3DXMesh* clonedMesh;
		if (SUCCEEDED(pMesh->CloneMesh(pMesh->GetOptions(), meshDeclaration, DEVICE, &clonedMesh)))
		{
			//pMesh->Release();
			pMesh = clonedMesh;
		}

	}
	pMesh->UpdateSemantics(meshDeclaration);


	/* Get adjacency */
	pMeshContainer->pAdjacency = new DWORD[pMesh->GetNumFaces() * 3];
	pMesh->GenerateAdjacency(0.0001f, pMeshContainer->pAdjacency);

	/* Compute tangent vector */
	D3DXComputeTangent(pMesh, 0, 0, 0, 1, pMeshContainer->pAdjacency);




	unsigned long numFaces = pMesh->GetNumFaces();


	unsigned long fvf = pMesh->GetFVF();

	pMesh->CloneMesh(pMesh->GetOptions(), meshDeclaration, DEVICE, &pMeshContainer->MeshData.pMesh);

	// 재질의 개수를 채워주는데 없는 경우도 있기 때문에 조건문을 달아준다.
	pMeshContainer->NumMaterials = (numMaterials == 0 ? 1 : numMaterials);

	// 재질 동적할당 (재질 개수만큼)
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * pMeshContainer->NumMaterials);

	// 텍스처 동적할당 (재질 개수만큼)
	pMeshContainer->ppTexture = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	pMeshContainer->ppNormal = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->ppNormal, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	pMeshContainer->pTextureNames.reserve(pMeshContainer->NumMaterials);// = new std::wstring[pMeshContainer->NumMaterials];
	pMeshContainer->pTextureNames.resize(pMeshContainer->NumMaterials);
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
			/* For Others map */
			std::wstring name = fileName;
			std::wstring dirPath = fullPath;
			dirPath = Path::GetDirectoryName(dirPath);

			/* Find Normal Map */
			std::wstring normalMapName = name;
			CString::Replace(&normalMapName, L"_D_", L"_N_");
			IDirect3DTexture9* normalMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + normalMapName);

			pMeshContainer->ppNormal[i] = normalMap;

			pMeshContainer->pTextureNames[i] = CString::CharToWstring( pMeshContainer->pMaterials[i].pTextureFilename);
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
		pMeshContainer->ppNormal[0] = NULL;
	}

	if (nullptr == pSkinInfo) // Skinned Mesh가 아닌 경우 그냥 반환한다.
		return S_OK;

	pSkinInfo->SetDeclaration(meshDeclaration);


	pMeshContainer->pSkinInfo = pSkinInfo;
	pMeshContainer->pSkinInfo->AddRef();

	/*pMeshContainer->MeshData.pMesh->CloneMeshFVF(pMeshContainer->MeshData.pMesh->GetOptions(),
		pMeshContainer->MeshData.pMesh->GetFVF(),
		DEVICE,
		&pMeshContainer->pOriMesh);*/
	pMesh->CloneMesh(pMesh->GetOptions(),
		meshDeclaration,
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
	SAFE_DELETE_ARRAY(pMeshContainer->ppNormal);
	
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
