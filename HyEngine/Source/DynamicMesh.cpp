#include "StandardEngineFramework.h"
#include "DynamicMesh.h"
#include "MeshHierarchy.h"
#include "AnimationController.h"
#include "GameObject.h"
#include "MeshData.h"
#include "AnimNameData.h"
#include "Deserializer.h"
#include "PathManager.h"
#include "HierarchyData.h"
HyEngine::DynamicMesh::DynamicMesh(Scene * scene, GameObject * parent,std::wstring name)
	: GameObject(ERenderType::RenderMesh, scene, parent, name),
	m_pLoader(nullptr),
	m_pAniCtrl(nullptr)
{

}

HyEngine::DynamicMesh::~DynamicMesh()
{
	SAFE_DELETE(m_pAniCtrl);

	m_pLoader->DestroyFrame(m_pRootFrame);
	SAFE_DELETE(m_pLoader);

	m_MeshContainerList.clear();
}

void HyEngine::DynamicMesh::Initialize(std::wstring dataPath)
{
	std::shared_ptr<HierarchyData> data = Deserializer::Deserialize(dataPath);
	InsertGameData(data->gameObjectData);
	InsertMeshData(data->meshData);
}

void HyEngine::DynamicMesh::Update()
{
	GameObject::Update();
	//TEST
	if (m_pAniCtrl == nullptr)
		return;
	PlayAnimationSet(TIMER->getDeltaTime());
}

void HyEngine::DynamicMesh::Render()
{
	GameObject::Render();

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

void HyEngine::DynamicMesh::UpdatedData(EDataType dataType)
{
	if (dataType != EDataType::MeshData)return;
	// mesh ������ ����Ǿ��� �� 
	// ���⼭ �ʱ�ȭ���ش�.
	assert(m_pMeshData);
	std::wstring meshPath = CString::CharToWstring(m_pMeshData->meshFilePath);
	std::wstring meshPathExt = HyEngine::Path::GetExtension(meshPath);
	m_lastMeshPath = meshPath;
	std::wstring dirPath = Path::GetDirectoryName(PATH->ResourcesPathW() + meshPath);
	std::wstring fileName = Path::GetFileName(PATH->ResourcesPathW() + meshPath);

	if (std::wcscmp(meshPathExt.c_str(), L"x") != 0 && std::wcscmp(meshPathExt.c_str(), L"X") != 0)
		return;

	InitializeMeshes(dirPath, fileName);
	SetAnimationSet(0);
}

void HyEngine::DynamicMesh::InitializeMeshes(std::wstring filePath, std::wstring fileName)
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

const D3DXFRAME_DERIVED * HyEngine::DynamicMesh::GetFrameByName(const char * frameName)
{
	// �ش� ���� �̸��� ���� ���� ���� ����ü�� ��ȯ�Ѵ�.
	return (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, frameName);
}

bool HyEngine::DynamicMesh::IsAnimationSetEnd(double endTime)
{
	return m_pAniCtrl->IsAnimationSetEnd(endTime);
}

bool HyEngine::DynamicMesh::IsAnimationAfterTrack(double afterTime)
{
	return m_pAniCtrl->IsAnimationAfterTrack(afterTime);
}

const unsigned int & HyEngine::DynamicMesh::GetAnimationNum()
{
	return m_pAniCtrl->GetAnimationNum();
}

double HyEngine::DynamicMesh::GetCurAnimationPosition()
{
	return m_pAniCtrl->GetCurAnimationPosition();
}

const list<D3DXMESHCONTAINER_DERIVED*>& HyEngine::DynamicMesh::GetMeshContainerList()
{
	return m_MeshContainerList;
}

void HyEngine::DynamicMesh::SetAnimationSet(const unsigned int & index)
{
	m_pAniCtrl->SetAnimationSet(index);
}

void HyEngine::DynamicMesh::PlayAnimationSet(const float & timeDelta)
{
	if (m_pAniCtrl == nullptr)
		return;

	m_pAniCtrl->PlayAnimationSet(timeDelta);

	D3DXMATRIX matTemp;

	UpdateFrameMatrix((D3DXFRAME_DERIVED*)m_pRootFrame, D3DXMatrixIdentity(&matTemp));
}

void HyEngine::DynamicMesh::UpdateFrameMatrix(D3DXFRAME_DERIVED * frame, const D3DXMATRIX * parentMatrix)
{
	// �θ� ���� ��� �����Ѵ�.
	if (frame == nullptr) return;

	frame->CombinedTransformMatrix = frame->TransformationMatrix * (*parentMatrix);

	if (frame->pFrameSibling != nullptr)
		UpdateFrameMatrix((D3DXFRAME_DERIVED*)frame->pFrameSibling, parentMatrix);

	if (frame->pFrameFirstChild != nullptr)
		UpdateFrameMatrix((D3DXFRAME_DERIVED*)frame->pFrameFirstChild, &frame->CombinedTransformMatrix);
}

void HyEngine::DynamicMesh::SetupFrameMatrixPointer(D3DXFRAME_DERIVED * frame)
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
