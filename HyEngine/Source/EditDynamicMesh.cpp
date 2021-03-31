#include "StandardEngineFramework.h"
#include "EditDynamicMesh.h"
#include "MeshHierarchy.h"
#include "AnimationController.h"
#include "GameObject.h"
#include "MeshData.h"
#include "AnimNameData.h"

HyEngine::EditDynamicMesh::EditDynamicMesh(Scene * scene, GameObject * parent, int editID)
	: EditObject(ERenderType::RenderMesh, scene, parent, editID),
	m_pLoader(nullptr),
	m_pAniCtrl(nullptr)
{

}

HyEngine::EditDynamicMesh::EditDynamicMesh(const EditDynamicMesh & rhs)
	: EditObject(ERenderType::RenderMesh, rhs.GetScene(), rhs.GetParent(), rhs.GetEditID()),
	m_pLoader(rhs.m_pLoader),
	m_pRootFrame(rhs.m_pRootFrame),
	m_MeshContainerList(rhs.m_MeshContainerList)
{
	m_pAniCtrl = new AnimationController(*rhs.m_pAniCtrl);
}

HyEngine::EditDynamicMesh::~EditDynamicMesh()
{
	SAFE_DELETE(m_pAniCtrl);

	m_pLoader->DestroyFrame(m_pRootFrame);
	SAFE_DELETE(m_pLoader);

	m_MeshContainerList.clear();
}

void HyEngine::EditDynamicMesh::Initialize()
{
	
}

void HyEngine::EditDynamicMesh::Update()
{
	EditObject::Update();
	//TEST
	if (m_pAniCtrl == nullptr)
		return;
	PlayAnimationSet(EDIT_TIMER->getDeltaTime());
}

void HyEngine::EditDynamicMesh::Render()
{
	EditObject::Render();

	auto iter = m_MeshContainerList.begin();
	auto iter_end = m_MeshContainerList.end();

	for (; iter != iter_end; iter++)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (*iter);

		for (ULONG i = 0; i < pMeshContainer->numBones; i++)
			pMeshContainer->pRenderingMatrix[i] = pMeshContainer->pFrameOffsetMatrix[i] * (*pMeshContainer->ppFrameCombinedMatrix[i]);

		void* pSrcVtx = nullptr;
		void* pDestVtx = nullptr;

		pMeshContainer->pOriMesh->LockVertexBuffer(0, &pSrcVtx);
		pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVtx);

		// ����Ʈ���� ��Ű���� �����ϴ� �Լ�.
		// ��Ű�� �� �ƴ϶� �ִϸ��̼� ���� ��,
		// ������ ���� �������� ������ ���ÿ� �������ֱ⵵ �Ѵ�.
		pMeshContainer->pSkinInfo->UpdateSkinnedMesh(
			pMeshContainer->pRenderingMatrix, // ���� ���� ��ȯ ����
			NULL, // �����·� �������� ���� ���� ����� �ּҰ�(������ ���븶�� �� �� ������� �����༭ �־�������� �ȳ־��൵ ������� 
			pSrcVtx, // ������ �ʴ� ���� �޽��� ���� ����
			pDestVtx // ��ȯ�� ������ ������� ���� ����
		);

		// ���� ��ºκ�
		for (ULONG i = 0; i < pMeshContainer->NumMaterials; i++)
		{
			DEVICE->SetTexture(0, pMeshContainer->ppTexture[i]);
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}

		pMeshContainer->pOriMesh->UnlockVertexBuffer();
		pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
	}
}

void HyEngine::EditDynamicMesh::UpdatedData(EDataType dataType)
{
	if (dataType != EDataType::MeshData)return;
	// mesh ������ ����Ǿ��� �� 
	// ���⼭ �ʱ�ȭ���ش�.
	assert(m_pMeshData);
	std::wstring meshPath = CString::CharToWstring(m_pMeshData->meshFilePath);
	std::wstring meshPathExt = HyEngine::Path::GetExtension(meshPath);
	if (meshPath == m_lastMeshPath) return;
	m_lastMeshPath = meshPath;
	std::wstring dirPath = Path::GetDirectoryName(ResourcePath::ResourcesPath + meshPath);
	std::wstring fileName = Path::GetFileName(ResourcePath::ResourcesPath + meshPath);

	if (std::wcscmp(meshPathExt.c_str(), L"x") != 0 && std::wcscmp(meshPathExt.c_str(), L"X") != 0)
		return;

	InitializeMeshes(dirPath, fileName);
	SetAnimationSet(0);
}

void HyEngine::EditDynamicMesh::InitializeMeshes(std::wstring filePath, std::wstring fileName)
{
	TCHAR fullPath[MAX_PATH] = L"";

	lstrcpy(fullPath, filePath.c_str());
	lstrcat(fullPath, fileName.c_str());

	m_pLoader = new MeshHierarchy(filePath);
	assert(m_pLoader);

	LPD3DXANIMATIONCONTROLLER pAniCtrl = nullptr;

	HRESULT hr;
	hr = D3DXLoadMeshHierarchyFromX(fullPath,
		D3DXMESH_MANAGED,
		DEVICE,
		m_pLoader,
		NULL,
		&m_pRootFrame,
		&pAniCtrl
	);
	assert(SUCCEEDED(hr));

	m_pAniCtrl = new AnimationController(pAniCtrl);
	assert(m_pAniCtrl);

	SAFE_RELEASE(pAniCtrl);

	D3DXMATRIX matTemp;
	UpdateFrameMatrix((D3DXFRAME_DERIVED*)m_pRootFrame, D3DXMatrixIdentity(&matTemp));

	SetupFrameMatrixPointer((D3DXFRAME_DERIVED*)m_pRootFrame);

}

const D3DXFRAME_DERIVED * HyEngine::EditDynamicMesh::GetFrameByName(const char * frameName)
{
	// �ش� ���� �̸��� ���� ���� ���� ����ü�� ��ȯ�Ѵ�.
	return (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, frameName);
}

bool HyEngine::EditDynamicMesh::IsAnimationSetEnd(double endTime)
{
	return m_pAniCtrl->IsAnimationSetEnd(endTime);
}

bool HyEngine::EditDynamicMesh::IsAnimationAfterTrack(double afterTime)
{
	return m_pAniCtrl->IsAnimationAfterTrack(afterTime);
}

const unsigned int & HyEngine::EditDynamicMesh::GetAnimationNum()
{
	return m_pAniCtrl->GetAnimationNum();
}

double HyEngine::EditDynamicMesh::GetCurAnimationPosition()
{
	return m_pAniCtrl->GetCurAnimationPosition();
}

const list<D3DXMESHCONTAINER_DERIVED*>& HyEngine::EditDynamicMesh::GetMeshContainerList()
{
	return m_MeshContainerList;
}

void HyEngine::EditDynamicMesh::SetAnimationSet(const unsigned int & index)
{
	m_pAniCtrl->SetAnimationSet(index);
}

void HyEngine::EditDynamicMesh::PlayAnimationSet(const float & timeDelta)
{
	if (m_pAniCtrl == nullptr)
		return;

	m_pAniCtrl->PlayAnimationSet(timeDelta);

	D3DXMATRIX matTemp;

	UpdateFrameMatrix((D3DXFRAME_DERIVED*)m_pRootFrame, D3DXMatrixIdentity(&matTemp));
}

int HyEngine::EditDynamicMesh::GetAnimationCount()
{
	if (m_pAniCtrl == nullptr)
		return 0;
	return m_pAniCtrl->GetAnimationNum();
}

void HyEngine::EditDynamicMesh::GetAnimationName(_Out_ AnimNameData* outString, int index)
{
	if (index >= GetAnimationCount())return;
	LPD3DXANIMATIONSET pAs = NULL;
	m_pAniCtrl->GetAnimationSet()->GetAnimationSet(index, &pAs);
	
	LPCSTR a = pAs->GetName();
	std::wstring name = CString::CharToWstring(pAs->GetName());
	std::string convertedName = CString::ToString(name);
	strcpy_s(outString->name, 256, pAs->GetName());


}



void HyEngine::EditDynamicMesh::UpdateFrameMatrix(D3DXFRAME_DERIVED * frame, const D3DXMATRIX * parentMatrix)
{
	// �θ� ���� ��� �����Ѵ�.
	if (frame == nullptr) return;

	frame->CombinedTransformMatrix = frame->TransformationMatrix * (*parentMatrix);

	if (frame->pFrameSibling != nullptr)
		UpdateFrameMatrix((D3DXFRAME_DERIVED*)frame->pFrameSibling, parentMatrix);

	if (frame->pFrameFirstChild != nullptr)
		UpdateFrameMatrix((D3DXFRAME_DERIVED*)frame->pFrameFirstChild, &frame->CombinedTransformMatrix);
}

void HyEngine::EditDynamicMesh::SetupFrameMatrixPointer(D3DXFRAME_DERIVED * frame)
{
	if (frame->pMeshContainer != nullptr)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)frame->pMeshContainer;

		for (ULONG i = 0; i < pMeshContainer->numBones; i++)
		{
			// ���� �̸��� �����´�.
			const char* boneName = pMeshContainer->pSkinInfo->GetBoneName(i);
				
			// D3DXFrameFind�� ���� ���� �̸����� ���븦 ������ �� �ִ�.
			D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, boneName);

			pMeshContainer->ppFrameCombinedMatrix[i] = &pFrame->CombinedTransformMatrix;
		}

		m_MeshContainerList.emplace_back(pMeshContainer);
	}

	if (frame->pFrameSibling != nullptr)
		SetupFrameMatrixPointer((D3DXFRAME_DERIVED*)frame->pFrameSibling);

	if (frame->pFrameFirstChild != nullptr)
		SetupFrameMatrixPointer((D3DXFRAME_DERIVED*)frame->pFrameFirstChild);

}
