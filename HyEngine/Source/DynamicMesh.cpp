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
	: GameObject(ERenderType::RenderOpaque, scene, parent, name),
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

		// 소프트웨어 스키닝을 수행하는 함수.
		// 스키닝 뿐 아니라 애니메이션 변경 시,
		// 뼈대들과 정점 정보들의 변경을 동시에 수행해주기도 한다.
		pMeshContainer->pSkinInfo->UpdateSkinnedMesh(
			pMeshContainer->pRenderingMatrix, // 뼈의 최종 변환 상태
			NULL, // 원상태로 돌려놓기 위한 상태 행렬의 주소값(본래는 뼈대마다 싹 다 역행렬을 구해줘서 넣어야하지만 안넣어줘도 상관없음 
			pSrcVtx, // 변하지 않는 원본 메쉬의 정점 정보
			pDestVtx // 변환된 정보를 담기위한 정점 정보
		);

		/* Get Shader */
		ID3DXEffect* pShader = nullptr;
		ENGINE->TryGetShader(L"GBuffer", &pShader);
		assert(pShader);

		/* Get Selected Cam */
		Camera* pSelectedCamera = nullptr;
		pSelectedCamera = GetScene()->GetSelectedCamera();
		assert(pSelectedCamera);

		// 실제 출력부분
		for (ULONG i = 0; i < pMeshContainer->NumMaterials; i++)
		{
			pShader->SetValue("WorldMatrix", &m_pTransform->GetWorldMatrix(), sizeof(m_pTransform->GetWorldMatrix()));
			pShader->SetValue("ViewMatrix", &pSelectedCamera->GetViewMatrix(), sizeof(pSelectedCamera->GetViewMatrix()));
			pShader->SetValue("ProjMatrix", &pSelectedCamera->GetProjectionMatrix(), sizeof(pSelectedCamera->GetProjectionMatrix()));

			pShader->SetValue("WorldPosition", &m_pTransform->m_position, sizeof(m_pTransform->m_position));

			D3DXHANDLE albedoHandle = pShader->GetParameterByName(0, "AlbedoTex");
			pShader->SetTexture(albedoHandle, pMeshContainer->ppTexture[i]);

			pShader->SetTechnique("GBuffer");
			pShader->Begin(0, 0);
			{
				pShader->BeginPass(0);
				pMeshContainer->MeshData.pMesh->DrawSubset(i);
				pShader->EndPass();
			}
			pShader->End();


		}

		pMeshContainer->pOriMesh->UnlockVertexBuffer();
		pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
	}
}

void HyEngine::DynamicMesh::UpdatedData(EDataType dataType)
{
	if (dataType != EDataType::MeshData)return;
	// mesh 정보가 변경되었을 때 
	// 여기서 초기화해준다.
	assert(m_pMeshData);
	std::wstring meshPath = CString::CharToWstring(m_pMeshData->meshFilePath);
	std::wstring meshPathExt = HyEngine::Path::GetExtension(meshPath);
	if (m_lastMeshPath == meshPath) return;
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
	// 해당 뼈의 이름을 통해 뼈의 정보 구조체를 반환한다.
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
	// 부모가 없는 경우 종료한다.
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
			// 뼈의 이름을 가져온다.
			const char* boneName = pMeshContainer->pSkinInfo->GetBoneName(i);

			// D3DXFrameFind를 통해 뼈대 이름으로 뼈대를 가져올 수 있다.
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
