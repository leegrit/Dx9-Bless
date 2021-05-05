#include "StandardEngineFramework.h"
#include "MeshHierarchySW.h"

HyEngine::MeshHierarchySW::MeshHierarchySW(std::wstring path)
	: m_path(path)
{

}

HyEngine::MeshHierarchySW::~MeshHierarchySW()
{
}

STDMETHODIMP HyEngine::MeshHierarchySW::CreateFrame(LPCSTR name, _Out_ LPD3DXFRAME * ppNewFrame)
{
	D3DXFRAME_DERIVED* pNewFrame = new D3DXFRAME_DERIVED();
	ZeroMemory(pNewFrame, sizeof(D3DXFRAME_DERIVED));

	Allocate_Name(&pNewFrame->Name, name);

	pNewFrame->CombinedTransformMatrix = *D3DXMatrixIdentity(&pNewFrame->TransformationMatrix);
	*ppNewFrame = pNewFrame;

	return S_OK;
}

STDMETHODIMP HyEngine::MeshHierarchySW::CreateMeshContainer(LPCSTR name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstance, DWORD numMaterials, CONST DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = new D3DXMESHCONTAINER_DERIVED();
	ZeroMemory(pMeshContainer, sizeof(D3DXMESHCONTAINER_DERIVED));

	Allocate_Name(&pMeshContainer->Name, name);

	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	LPD3DXMESH pMesh = pMeshData->pMesh;

	/* Get adjacency */
	pMeshContainer->pAdjacency = new DWORD[pMesh->GetNumFaces() * 3];
	pMesh->GenerateAdjacency(0.0001f, pMeshContainer->pAdjacency);

	/* Get Face */
	DWORD paletteEntry = pSkinInfo->GetNumBones();
	DWORD maxVtxInfl;
	pSkinInfo->GetMaxVertexInfluences(&maxVtxInfl);
	DWORD numBoneComboEntries = 0;
	//ID3DXBuffer* pBoneComboTable = nullptr;
	ID3DXMesh * pSkinnedMesh = nullptr;


	/* Convert To IndexedBlendedMesh */
	//////////////////////////////////////////////////////////////////////////
#pragma region Convert To IndexedBlendedMesh

	//HRESULT hr = pSkinInfo->ConvertToIndexedBlendedMesh
	//(
	//	pMesh,
	//	pMesh->GetOptions(),//D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,
	//	paletteEntry,
	//	pMeshContainer->pAdjacency,
	//	NULL,
	//	NULL,
	//	NULL,
	//	&maxVtxInfl,
	//	&numBoneComboEntries,
	//	&pMeshContainer->pBoneCombinationBuf,
	//	&pSkinnedMesh
	//);
	//assert(SUCCEEDED(hr));


	//pMesh = pSkinnedMesh;


#pragma endregion
	//////////////////////////////////////////////////////////////////////////

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

	/* Compute tangent vector */
	D3DXComputeTangent(pMesh, 0, 0, 0, 1, pMeshContainer->pAdjacency);



	//unsigned long numFaces = pMesh->GetNumFaces();

	/* Get Face */
	unsigned long numFaces = pMesh->GetNumFaces();

	unsigned long fvf = pMesh->GetFVF();

	pMesh->CloneMesh(pMesh->GetOptions(), meshDeclaration, DEVICE, &pMeshContainer->MeshData.pMesh);


	pMeshContainer->MeshData.pMesh->GetAttributeTable(NULL, &pMeshContainer->numAttributeGroups);
	pMeshContainer->pAttributeTable = new D3DXATTRIBUTERANGE[pMeshContainer->numAttributeGroups];
	pMeshContainer->MeshData.pMesh->GetAttributeTable(pMeshContainer->pAttributeTable, NULL);


	// ������ ������ ä���ִµ� ���� ��쵵 �ֱ� ������ ���ǹ��� �޾��ش�.
	pMeshContainer->NumMaterials = (numMaterials == 0 ? 1 : numMaterials);

	// ���� �����Ҵ� (���� ������ŭ)
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * pMeshContainer->NumMaterials);

	// �ؽ�ó �����Ҵ� (���� ������ŭ)
	pMeshContainer->ppTexture = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	pMeshContainer->ppNormal = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->ppNormal, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	pMeshContainer->ppSpecularMask = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->ppSpecularMask, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	pMeshContainer->pTextureNames.reserve(pMeshContainer->NumMaterials);// = new std::wstring[pMeshContainer->NumMaterials];
	pMeshContainer->pTextureNames.resize(pMeshContainer->NumMaterials);
	// ������ �ִ� ���
	if (0 != numMaterials)
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

			pMeshContainer->ppTexture[i] = (IDirect3DTexture9*)TextureLoader::GetTexture(fullPath);
			/*if (FAILED(D3DXCreateTextureFromFile(DEVICE, fullPath, &pMeshContainer->ppTexture[i])))
			{
			return E_FAIL;
			}*/
			/* For Others map */
			std::wstring name = fileName;
			std::wstring dirPath = fullPath;
			dirPath = Path::GetDirectoryName(dirPath);

			/* Find Normal Map */
			std::wstring normalMapName = name;
			CString::Replace(&normalMapName, L"_D_", L"_N_");
			IDirect3DTexture9* normalMap = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + normalMapName);
			pMeshContainer->ppNormal[i] = normalMap;

			/* Find Specular Mask */
			std::wstring specularMaskName = name;
			CString::Replace(&specularMaskName, L"_D_", L"_C_");
			IDirect3DTexture9* specularMask = (IDirect3DTexture9*)TextureLoader::GetTexture(dirPath + specularMaskName);
			pMeshContainer->ppSpecularMask[i] = specularMask;

			pMeshContainer->pTextureNames[i] = CString::CharToWstring(pMeshContainer->pMaterials[i].pTextureFilename);
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
		pMeshContainer->ppNormal[0] = NULL;
	}

	if (nullptr == pSkinInfo) // Skinned Mesh�� �ƴ� ��� �׳� ��ȯ�Ѵ�.
		return S_OK;

	pSkinInfo->SetDeclaration(meshDeclaration);
	//pSkinInfo->Remap(pMesh->GetNumVertices(), (DWORD*)pRemapVtx->GetBufferPointer());

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

STDMETHODIMP HyEngine::MeshHierarchySW::DestroyFrame(LPD3DXFRAME pFrameToFree)
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

STDMETHODIMP HyEngine::MeshHierarchySW::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
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

void HyEngine::MeshHierarchySW::Allocate_Name(_Out_ char ** ppName, const char * pFrameName)
{
	if (nullptr == pFrameName)
		return;

	ULONG iLength = strlen(pFrameName);
	*ppName = new char[iLength + 1];

	strcpy_s(*ppName, iLength + 1, pFrameName);
}
